#include "subgraphtab.h"
#include <QSpinBox>
#include <QGraphicsItem>
#include <QToolTip>
enum
{
	idxName,
	idxTexture
};

SubGraphTab::SubGraphTab(QWidget *parent)
	: TabBase(parent)
	, m_pEditorData(nullptr)
	, m_bSelectUpdating(false)
{
	ui.setupUi(this);
	init();
}

SubGraphTab::~SubGraphTab()
{

}

void SubGraphTab::init()
{
	m_pEditorData = EditorData::instance();
	m_spinBoxs[0] = ui.sbSrcX;
	m_spinBoxs[1] = ui.sbSrcY;
	m_spinBoxs[2] = ui.sbAllNum;
	m_spinBoxs[3] = ui.sbNumX;
	m_spinBoxs[4] = ui.sbNumY;
	m_spinBoxs[5] = ui.sbSizeX;
	m_spinBoxs[6] = ui.sbSizeY;

	updateTextureName();
	initContext();

	connect(ui.edName, &QLineEdit::textChanged, this, &SubGraphTab::onNameChanged);
	connect(ui.cbTexture, &QComboBox::currentTextChanged, this, &SubGraphTab::onTextureChanged);
	for (size_t i = 0; i < m_spinBoxs.size(); ++i)
	{
		connect(m_spinBoxs[i], (void (QSpinBox::*)(int))&QSpinBox::valueChanged, this, &SubGraphTab::onInfoChanged);
	}
	connect(ui.btnAdd, &QPushButton::clicked, this, &SubGraphTab::onAdd);
	connect(ui.btnCopy, &QPushButton::clicked, this, &SubGraphTab::onCopy);
	connect(ui.btnRemove, &QPushButton::clicked, this, &SubGraphTab::onRemove);
	connect(ui.tableWidget, &QTableWidget::currentItemChanged, this, &SubGraphTab::onSelectionChanged);
}

void SubGraphTab::initContext()
{
	SubGraphInfos& infos = m_pEditorData->subgraphies();
	for (size_t i = 0; i < infos.size(); ++i)
	{
		int row = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(row);
		ui.tableWidget->setItem(row, idxName, new QTableWidgetItem(infos[i].name));
		ui.tableWidget->setItem(row, idxTexture, new QTableWidgetItem(infos[i].texture));
		ui.tableWidget->selectRow(row);
	}
	refreshCache();
	refreshCtrlData();
}

void SubGraphTab::onAdd()
{
	m_pEditorData->subgraphies().emplace_back(SubGraphData());
	SubGraphData& data = m_pEditorData->subgraphies().back();
	data.name = QString::number(rand(), 16);

	int row = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setItem(row, idxName, new QTableWidgetItem(data.name));
	ui.tableWidget->setItem(row, idxTexture, new QTableWidgetItem(data.texture));
	ui.tableWidget->selectRow(row);
}

void SubGraphTab::onCopy()
{
	SubGraphData* pSel = getSelectedData();
	if (!pSel) return;

	m_pEditorData->subgraphies().push_back(*pSel);
	SubGraphData& data = m_pEditorData->subgraphies().back();
	data.name += QString::number(rand(), 16);

	int row = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setItem(row, idxName, new QTableWidgetItem(data.name));
	ui.tableWidget->setItem(row, idxTexture, new QTableWidgetItem(data.texture));
	ui.tableWidget->selectRow(row);
}

void SubGraphTab::onRemove()
{
	int row = ui.tableWidget->currentRow();
	if (row < 0)
		return;

	ui.tableWidget->removeRow(row);
	m_pEditorData->removeSubGraph(row);
}

void SubGraphTab::onNameChanged(const QString& name)
{
	QTableWidgetItem* pItem = getSelectedItem(idxName);
	if (!pItem)
		return;

	if (!m_pEditorData->canChangeSubGraphName(currentIdx(), name))
	{
		QToolTip::showText(ui.edName->mapToGlobal(QPoint(0, 0)), QString("\"%1\" already exist").arg(name), ui.edName);
	}
	else
	{
		m_cache.name = name;
		pItem->setText(name);
	}
}

void SubGraphTab::onTextureChanged(const QString& texture)
{
	m_cache.texture = texture;
	updatePreview();
}

void SubGraphTab::onInfoChanged()
{
	for (size_t i = 0; i < m_spinBoxs.size(); ++i)
	{
		m_cache.param.raw[i] = m_spinBoxs[i]->value();
	}
	updatePreview();
}

void SubGraphTab::onSelectionChanged(QTableWidgetItem* cur, QTableWidgetItem* prev)
{
	if (cur == prev)
		return;

	if (prev)
	{
		if (!commitCacheTo(prev->row()))
			return;
	}

	if (cur)
	{
		refreshCache();
		refreshCtrlData();
	}
}

void SubGraphTab::updatePreview()
{
	ui.preview->clear();
	if (m_cache.texture.isEmpty())
		return;

	QString texture = ui.cbTexture->itemData(ui.cbTexture->findText(m_cache.texture)).toString();
	QPixmap img = m_pEditorData->getTexture(texture);
	if (img.isNull())
		return;

	QPainterPath path;
	QRectF rect(m_cache.param.srcX, m_cache.param.srcY, m_cache.param.sizeX, m_cache.param.sizeY);
	int all = 0;
	for (int i = 0; i < m_cache.param.numY; ++i)
	{
		rect.moveLeft(m_cache.param.srcX);
		for (int j = 0; j < m_cache.param.numX; ++j)
		{
			path.addRect(rect);
			rect.moveLeft(rect.left() + m_cache.param.sizeX);
			if (++all >= m_cache.param.allNum)
				break;
		}
		rect.moveTop(rect.top() + m_cache.param.sizeY);
		if (all >= m_cache.param.allNum)
			break;
	}
	{
		m_cacheImg = QPixmap(img.width(), img.height());
		QPainter painter(&m_cacheImg);
		QBrush brush(QColor(0x4a, 0x4a, 0x4a), Qt::Dense4Pattern);
		painter.setBrush(brush);
		painter.drawRect(0, 0, img.width(), img.height());
		painter.setBrush(Qt::NoBrush);
		painter.drawPixmap(0, 0, img);
		painter.drawPath(path);
	}
	ui.preview->addPixmap(m_cacheImg);
}

bool SubGraphTab::commitCacheTo(int row)
{
	bool bSucceed = m_pEditorData->commitSubGraph(row, m_cache);
	if (!bSucceed)
	{
		m_cache = m_pEditorData->subgraphies()[row];
		refreshCtrlData();
	}
	return bSucceed;
}

int SubGraphTab::currentIdx()
{
	return ui.tableWidget->currentRow();
}

void SubGraphTab::refreshCtrlData()
{
	QObject* objs[] = {
		ui.edName, ui.cbTexture, m_spinBoxs[0], m_spinBoxs[1],
		m_spinBoxs[2], m_spinBoxs[3], m_spinBoxs[4], m_spinBoxs[5],
		m_spinBoxs[6]
	};
	for each(auto pObj in objs)
		pObj->blockSignals(true);

	ui.edName->setText(m_cache.name);
	ui.cbTexture->setCurrentIndex(ui.cbTexture->findText(m_cache.texture));
	ui.cbTexture->setEditText(m_cache.texture);
	for (size_t i = 0; i < m_spinBoxs.size(); ++i)
	{
		m_spinBoxs[i]->setValue(m_cache.param.raw[i]);
	}

	for each(auto pObj in objs)
		pObj->blockSignals(false);

	ui.preview->resetZoom();
	updatePreview();
}

void SubGraphTab::refreshCache()
{
	SubGraphData* pData = getSelectedData();
	if (!pData) return;

	m_cache = *pData;
}

void SubGraphTab::updateTextureName()
{
	ui.cbTexture->clear();
	TextureMap& map = m_pEditorData->textureMap();
	for (auto iter = map.begin(); iter != map.end(); ++iter)
	{
		ui.cbTexture->addItem(iter.value(), iter.key());
	}

	SubGraphInfos& infos = m_pEditorData->subgraphies();
	for (size_t i = 0; i < infos.size(); ++i)
	{
		auto pItem = ui.tableWidget->item(i, idxTexture);
		if (pItem)
			pItem->setText(infos[i].texture);
	}

	auto pSel = getSelectedData();
	if (pSel)
	{
		ui.cbTexture->setCurrentIndex(ui.cbTexture->findText(pSel->texture));
	}
}

bool SubGraphTab::commitCache()
{
	int row = currentIdx();
	if (row < 0)
		return true;

	return commitCacheTo(row);
}

void SubGraphTab::enterTab()
{
	updateTextureName();
}

SubGraphData* SubGraphTab::getSelectedData()
{
	int row = currentIdx();
	if (row < 0)
		return nullptr;
	else
		return &m_pEditorData->subgraphies()[row];
}

QTableWidgetItem* SubGraphTab::getSelectedItem(int col)
{
	int row = currentIdx();
	if (row < 0)
		return nullptr;

	return ui.tableWidget->item(row, col);
}
