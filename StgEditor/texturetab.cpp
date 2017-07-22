#include "texturetab.h"
#include "ui_texturetab.h"
#include "editordata.h"
#include "smarttip.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QCursor>
#include <QDesktopServices>
#include <QMessageBox>
#include <QImage>

#include <set>
#include <cassert>

enum TableItemIdx
{
	idxName,
	idxSource,
};

class TextureItem : public QTableWidgetItem
	, INameChangedNotify
{
public:
	TextureItem(EditorData* pData, uint id, TableItemIdx idx)
		: m_pData(pData), m_id(id), m_col(idx)
	{
		QTableWidgetItem::setData(Qt::DisplayRole, data(Qt::DisplayRole).toString());
		m_pData->textureMap().nameChangedNotify().registerNotify(this);
	}
	virtual ~TextureItem() override
	{
		m_pData->textureMap().nameChangedNotify().unregisterNotify(this);
	}
	virtual QVariant data(int role) const override
	{
		if (role != Qt::DisplayRole)
			return QTableWidgetItem::data(role);

		return m_pData->textureMap().nameOfId(m_id);
	}
	virtual void setData(int role, const QVariant &value) override
	{
		if (role != Qt::DisplayRole)
		{
			if (m_col == idxName)
			{
				m_pData->textureMap().rename(m_id, value.toString());
				return;
			}
		}
		return QTableWidgetItem::setData(role, value);
	}
	virtual void onNameChanged(uint id, IContainer*) override
	{
		if (id == m_id)
		{
			QString texture = m_pData->textureMap().nameOfId(id);
			QTableWidgetItem::setData(Qt::DisplayRole, texture);
		}
	}

	uint id() const { return m_id; }

private:
	EditorData* m_pData;
	uint m_id;
	TableItemIdx m_col;
};

TextureTab::TextureTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TextureTab)
{
	ui->setupUi(this);
	init();
	m_timer.setInterval(200);

	connect(ui->btnAdd, &QPushButton::clicked, this, &TextureTab::onAdd);
	connect(ui->btnRemove, &QPushButton::clicked, this, &TextureTab::onRemove);
	connect(ui->btnPreMulti, &QPushButton::clicked, this, &TextureTab::onPreMulti);

	connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &TextureTab::queryEdit);
	connect(&m_timer, &QTimer::timeout, this, &TextureTab::checkTip);
	ui->tableWidget->setMouseTracking(true);
	ui->tableWidget->installEventFilter(this);

	ui->tableWidget->horizontalHeader()->setSectionResizeMode(idxSource, QHeaderView::ResizeToContents);
	ui->tableWidget->horizontalHeaderItem(idxSource)->setText(tr("Source"));
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(idxName, QHeaderView::ResizeToContents);
	ui->tableWidget->horizontalHeaderItem(idxName)->setText(tr("Name"));
}

TextureTab::~TextureTab()
{
	delete ui;
}

void TextureTab::init()
{
	m_pEditorData = EditorData::instance();
	TextureMap& textureMap = m_pEditorData->textureMap();
	for (const Texture& texture : textureMap)
	{
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, idxName, new TextureItem(m_pEditorData, texture.id(), idxName));
		ui->tableWidget->setItem(row, idxSource, new QTableWidgetItem(texture.path));
	}
}

void TextureTab::onAdd()
{
	QString startPath = m_prevPath;
	if (startPath.isEmpty())
		startPath = m_pEditorData->basePath();

	QStringList fileList =
		QFileDialog::getOpenFileNames(
			this, "Add Texture",
			startPath, "Images (*.png *.bmp *.jpg)");

	QDir baseDir(m_pEditorData->basePath());
	TextureMap& textureMap = m_pEditorData->textureMap();
	for (int i = 0; i < fileList.size(); ++i)
	{
		if (0 == i)
			m_prevPath = QFileInfo(fileList[0]).absolutePath();

		QString relPath = baseDir.relativeFilePath(fileList[i]);
		if (textureMap.contains(relPath))
			continue;

		QFileInfo info(fileList[i]);
		textureMap.append(Texture(info.baseName(), relPath));

		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, idxName, new TextureItem(m_pEditorData, textureMap.back().id(), idxName));
		ui->tableWidget->setItem(row, idxSource, new QTableWidgetItem(relPath));
	}
	ui->tableWidget->adjustSize();
}

void TextureTab::onRemove()
{
	QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

	std::set<int> removeRows;
	for (QTableWidgetItem* item : items)
	{
		if (!item || item->column() != idxName)
			continue;

		if (removeRows.find(item->row()) == removeRows.end())
		{
			removeRows.insert(item->row());
			m_pEditorData->removeTexture(item->text());
		}
	}

	for (auto iter = removeRows.rbegin(); iter != removeRows.rend(); ++iter)
		ui->tableWidget->removeRow(*iter);
}

void TextureTab::onPreMulti()
{
	QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

	std::set<int> removeRows;
	for (auto iter = items.begin(); iter != items.end(); ++iter)
	{
		QTableWidgetItem* item = *iter;
		if (!item || item->column() != idxSource)
			continue;

		QPixmap texture = EditorData::instance()->getTextureByPath(item->text());
		QImage target = texture.toImage();
		if (target.format() != QImage::Format_ARGB32)
		{
			QImage newImg = target.convertToFormat(QImage::Format_ARGB32);
			if (!newImg.isNull())
			{
				bool bSucc = newImg.save(EditorData::instance()->getTextureFullPath(item->text()), "PNG");
				assert(bSucc);
			}
		}
	}
}

void TextureTab::queryEdit(const QModelIndex& idx)
{
	if (idx.column() == idxName)
		ui->tableWidget->edit(idx);
	else
	{
		QString path = EditorData::instance()->basePath() + "\\" + idx.data().toString();
		QDesktopServices::openUrl(QUrl::fromLocalFile(path));
	}
}

void TextureTab::hideTip()
{
	m_lastTipRow = -1;
	SmartTip::inst()->hide();
}

bool TextureTab::eventFilter(QObject* o, QEvent* e)
{
	switch (e->type())
	{
	case QEvent::Enter:
		m_timer.start();
		break;
	case QEvent::Leave:
		m_timer.stop();
		checkTip();
	default:
		break;
	}
	return QWidget::eventFilter(o, e);
}

void TextureTab::checkTip()
{
	if (!ui->tableWidget->isActiveWindow())
	{
		hideTip();
		return;
	}

	QPoint pos = ui->tableWidget->mapFromGlobal(QCursor::pos());
	pos.ry() -= ui->tableWidget->horizontalHeader()->height();
	QTableWidgetItem* item = ui->tableWidget->itemAt(pos);

	if (!item || item->column() != idxSource)
	{
		hideTip();
		return;
	}

	if (m_lastTipRow >= 0 && m_lastTipRow == item->row())
		return;

	QPoint dispPos = QCursor::pos() + QPoint(10, 10);
	SmartTip::inst()->showTexture(dispPos, item->text());
	m_lastTipRow = item->row();
}
