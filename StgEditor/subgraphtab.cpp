#include "subgraphtab.h"
#include <QSpinBox>
#include <QGraphicsItem>
#include <QToolTip>

enum ColIndex
{
	idxName,
	idxTexture
};

class SubGraphItem : public QTableWidgetItem
	, INameChangedNotify
{
public:
	SubGraphItem(EditorData* pData, const SubGraphData* pInfo, ColIndex idx)
		: m_pData(pData), m_pInfo(pInfo), m_idx(idx)
	{
		QTableWidgetItem::setData(Qt::DisplayRole, data(Qt::DisplayRole).toString());
		switch (m_idx)
		{
		case idxName:
			m_pData->subgraphies().nameChangedNotify().registerNotify(this);
			break;
		case idxTexture:
			m_pData->textureMap().nameChangedNotify().registerNotify(this);
			break;
		}
	}
	virtual ~SubGraphItem() override
	{
		switch (m_idx)
		{
		case idxName:
			m_pData->subgraphies().nameChangedNotify().unregisterNotify(this);
			break;
		case idxTexture:
			m_pData->textureMap().nameChangedNotify().unregisterNotify(this);
			break;
		}
	}
	virtual QVariant data(int role) const override
	{
		if (role != Qt::DisplayRole)
			return QTableWidgetItem::data(role);

		switch (m_idx)
		{
		case idxName:
			return m_pInfo->name();
		case idxTexture:
			return m_pData->textureMap().nameOfId(m_pInfo->iTexture);
		default:
			return QTableWidgetItem::data(role);
		}
	}
	virtual void setData(int role, const QVariant &value) override
	{
		return QTableWidgetItem::setData(role, value);
	}
	virtual void onNameChanged(uint id, IContainer*) override
	{
		switch (m_idx)
		{
		case idxName:
			if (id == m_pInfo->id())
			{
				QString name = m_pData->subgraphies().nameOfId(id);
				QTableWidgetItem::setData(Qt::DisplayRole, name);
			}
			break;
		case idxTexture:
			if (id == m_pInfo->iTexture)
			{
				QString texture = m_pData->textureMap().nameOfId(id);
				QTableWidgetItem::setData(Qt::DisplayRole, texture);
			}
			break;
		}
	}

	uint id() const { return m_pInfo->id(); }
	const SubGraphData* graphInfo() const { return m_pInfo; }

private:
	EditorData* m_pData;
	const SubGraphData* m_pInfo;
	ColIndex m_idx;
};

SubGraphTab::SubGraphTab(QWidget *parent)
	: TabBase(parent)
	, m_cache("")
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
	for (const SubGraphData& dat : infos)
	{
		int row = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(row);
		ui.tableWidget->setItem(row, idxName, new SubGraphItem(m_pEditorData, &dat, idxName));
		ui.tableWidget->setItem(row, idxTexture, new SubGraphItem(m_pEditorData, &dat, idxTexture));
		ui.tableWidget->selectRow(row);
	}
	refreshCache();
	refreshCtrlData();
}

void SubGraphTab::onAdd()
{
	m_pEditorData->subgraphies().append(SubGraphData(QString::number(rand(), 16)));
	const SubGraphData& data = m_pEditorData->subgraphies().back();

	int row = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setItem(row, idxName, new SubGraphItem(m_pEditorData, &data, idxName));
	ui.tableWidget->setItem(row, idxTexture, new SubGraphItem(m_pEditorData, &data, idxTexture));
	ui.tableWidget->selectRow(row);
}

void SubGraphTab::onCopy()
{
	const SubGraphData* pSel = getSelectedData();
	if (!pSel) return;

	m_pEditorData->subgraphies().append(*pSel);
	const SubGraphData& data = m_pEditorData->subgraphies().back();

	int row = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setItem(row, idxName, new SubGraphItem(m_pEditorData, &data, idxName));
	ui.tableWidget->setItem(row, idxTexture, new SubGraphItem(m_pEditorData, &data, idxTexture));
	ui.tableWidget->selectRow(row);
}

void SubGraphTab::onRemove()
{
	int row = ui.tableWidget->currentRow();
	if (row < 0)
		return;

	ui.tableWidget->removeRow(row);
	m_pEditorData->removeSubGraph(idByRow(row));
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
// 		m_cache.m_name = name;
		pItem->setText(name);
	}
}

void SubGraphTab::onTextureChanged(const QString& texture)
{
// 	QTableWidgetItem* pItem = getSelectedItem(idxTexture);
// 	if (!pItem)
// 		return;
// 
// 	m_cache.texture = texture;
// 	pItem->setText(texture);

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
// 	if (m_cache.texture.isEmpty())
// 		return;

	QString texture = m_pEditorData->textureMap().nameOfId(m_cache.iTexture);
	QPixmap img = m_pEditorData->getTextureByName(texture);
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
	uint id = idByRow(row);
	bool bSucceed = m_pEditorData->commitSubGraph(id, m_cache);
	if (!bSucceed)
	{
		m_cache = m_pEditorData->subgraphies()[id];
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

	ui.edName->setText(m_cache.name());
	QString texture = m_pEditorData->textureMap().nameOfId(m_cache.iTexture);

	ui.cbTexture->setCurrentIndex(ui.cbTexture->findText(texture));
	ui.cbTexture->setEditText(texture);
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
	const SubGraphData* pData = getSelectedData();
	if (!pData) return;

	m_cache = *pData;
}

uint SubGraphTab::idByRow(int row)
{
	SubGraphItem* pItem = static_cast<SubGraphItem*>(ui.tableWidget->item(row, idxName));
	return pItem->id();
}

void SubGraphTab::updateTextureName()
{
	ui.cbTexture->clear();
	TextureMap& map = m_pEditorData->textureMap();
	for (const Texture& texture : map)
	{
		ui.cbTexture->addItem(texture.name(), texture.id());
	}
	ui.cbTexture->registerNameChanged(map.nameChangedNotify());
// 	SubGraphInfos& infos = m_pEditorData->subgraphies();
// 	for (size_t i = 0; i < infos.size(); ++i)
// 	{
// 		auto pItem = ui.tableWidget->item(i, idxTexture);
// 		if (pItem)
// 			pItem->setText(infos[i].texture);
// 	}

	auto pSel = getSelectedData();
	if (pSel)
	{
		int row = ui.cbTexture->findData(pSel->iTexture);
		ui.cbTexture->setCurrentIndex(row);
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
// 	updateTextureName();
}

const SubGraphData* SubGraphTab::getSelectedData()
{
	SubGraphItem* pItem = static_cast<SubGraphItem*>(getSelectedItem(idxName));
	if (!pItem)
		return nullptr;
	else
		return pItem->graphInfo();
}

QTableWidgetItem* SubGraphTab::getSelectedItem(int col)
{
	int row = currentIdx();
	if (row < 0)
		return nullptr;

	return ui.tableWidget->item(row, col);
}
