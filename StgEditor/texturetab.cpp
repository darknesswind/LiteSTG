#include "texturetab.h"
#include "ui_texturetab.h"
#include <QFileDialog>
#include <QFileInfo>
#include "editordata.h"
#include "smarttip.h"
#include <QCursor>
#include <QDesktopServices>
#include <QMessageBox>

enum TableItemIdx
{
	idxSource = 0,
	idxName,
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
	connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &TextureTab::queryEdit);
	connect(ui->tableWidget, &QTableWidget::itemChanged, this, &TextureTab::onItemChanged);
	connect(&m_timer, &QTimer::timeout, this, &TextureTab::checkTip);
	ui->tableWidget->setMouseTracking(true);
	ui->tableWidget->installEventFilter(this);

	ui->tableWidget->horizontalHeader()->setSectionResizeMode(idxSource, QHeaderView::ResizeToContents);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(idxName, QHeaderView::Stretch);
}

TextureTab::~TextureTab()
{
	delete ui;
}

void TextureTab::init()
{
	m_pEditorData = EditorData::instance();
	TextureMap& textureMap = m_pEditorData->textureMap();
	for (auto iter = textureMap.begin(); iter != textureMap.end(); ++iter)
	{
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, idxSource, new QTableWidgetItem(iter.key()));
		ui->tableWidget->setItem(row, idxName, new QTableWidgetItem(iter.value()));
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
		textureMap[relPath] = info.baseName();

		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, idxSource, new QTableWidgetItem(relPath));
		ui->tableWidget->setItem(row, idxName, new QTableWidgetItem(info.baseName()));
	}
	ui->tableWidget->adjustSize();
}

void TextureTab::onRemove()
{
	QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

	for (auto iter = items.begin(); iter != items.end(); ++iter)
	{
		QTableWidgetItem* item = *iter;
		if (!item || item->column() != idxSource)
			continue;

		m_pEditorData->removeTexture(item->text());
		ui->tableWidget->removeRow(item->row());
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

void TextureTab::onItemChanged(QTableWidgetItem* pNameItem)
{
	if (!pNameItem  || pNameItem->column() != idxName)
		return;

	QTableWidgetItem* srcItem = ui->tableWidget->item(pNameItem->row(), idxSource);
	if (!srcItem)
		return;

	QString res = m_pEditorData->changeTextureName(srcItem->text(), pNameItem->text());
	pNameItem->setText(res);
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
