#include "bullettab.h"
#include <QToolTip>

enum ColIndex
{
	idxName,
	idxType,
	idxCollide,
};

class BulletItem : public QTableWidgetItem
	, INameChangedNotify
{
public:
	BulletItem(EditorData* pData, uint id, ColIndex idx)
		: m_pData(pData), m_id(id), m_col(idx)
	{
		QTableWidgetItem::setData(Qt::DisplayRole, data(Qt::DisplayRole).toString());
		m_pData->bulletStyles().nameChangedNotify().registerNotify(this);
	}
	virtual ~BulletItem() override
	{
		m_pData->bulletStyles().nameChangedNotify().unregisterNotify(this);
	}
	virtual QVariant data(int role) const override
	{
		if (role != Qt::DisplayRole)
			return QTableWidgetItem::data(role);

		return m_pData->bulletStyles().nameOfId(m_id);
	}
	virtual void setData(int role, const QVariant &value) override
	{
		if (role != Qt::DisplayRole && m_col == idxName)
		{
			m_pData->bulletStyles().rename(m_id, value.toString());
			return;
		}
		return QTableWidgetItem::setData(role, value);
	}
	virtual void onNameChanged(uint id, IContainer*) override
	{
		if (id == m_id)
		{
			QString texture = m_pData->bulletStyles().nameOfId(id);
			QTableWidgetItem::setData(Qt::DisplayRole, texture);
		}
	}

	uint id() const { return m_id; }

private:
	EditorData* m_pData;
	uint m_id;
	ColIndex m_col;
};

BulletTab::BulletTab(QWidget *parent)
	: TabBase(parent)
	, m_cache("")
	, m_pEditorData(nullptr)
{
	ui.setupUi(this);
	init();
}

BulletTab::~BulletTab()
{

}

bool BulletTab::commitCache()
{
	int row = currentIdx();
	if (row < 0)
		return true;

	return commitCacheTo(row);
}

void BulletTab::enterTab()
{
	updateSubGraphName();
	refreshCtrlData();
}

bool BulletTab::commitCacheTo(int row)
{
	bool bSucceed = m_pEditorData->bulletStyles().updateData(idByRow(row), m_cache);
	if (!bSucceed)
	{
		m_cache = m_pEditorData->bulletStyles()[idByRow(row)];
		refreshCtrlData();
	}
	return bSucceed;
}

int BulletTab::currentIdx()
{
	return ui.tableWidget->currentRow();
}

uint BulletTab::idByRow(int row)
{
	BulletItem* pItem = static_cast<BulletItem*>(ui.tableWidget->item(row, idxName));
	return pItem->id();
}

void BulletTab::init()
{
	m_pEditorData = EditorData::instance();
	updateSubGraphName();
	initContext();

	connect(ui.tableWidget, &QTableWidget::currentItemChanged, this, &BulletTab::onSelectionChanged);
	connect(ui.tableWidget, &QTableWidget::doubleClicked, this, &BulletTab::queryEdit);

	connect(ui.btnAdd, &QPushButton::clicked, this, &BulletTab::onAdd);
	connect(ui.btnCopy, &QPushButton::clicked, this, &BulletTab::onCopy);
	connect(ui.btnRemove, &QPushButton::clicked, this, &BulletTab::onRemove);

	connect(ui.cbType, (void (QComboBox::*)(int))&QComboBox::currentIndexChanged, this, &BulletTab::onTypeChanged);

	connect(ui.cbCollide, (void (QComboBox::*)(int))&QComboBox::currentIndexChanged, this, &BulletTab::onCollideChanged);
	connect(ui.sbCenterX, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, &BulletTab::onCollideXChanged);
	connect(ui.sbCenterY, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, &BulletTab::onCollideYChanged);
	connect(ui.sbRadianX, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, &BulletTab::onCollideRXChanged);
	connect(ui.sbRadianY, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, &BulletTab::onCollideRYChanged);

	connect(ui.cbSubGraph, &QComboBox::currentTextChanged, this, &BulletTab::onSubGraphChanged);
}

void BulletTab::initContext()
{
	BulletStyles& infos = m_pEditorData->bulletStyles();
	for (const BulletStyle& info : infos)
	{
		addRow(info);
	}
	refreshCache();
	refreshCtrlData();

	ui.cbSubGraph->registerNotify(&m_pEditorData->bulletStyles());
}

void BulletTab::updateSubGraphName()
{
	ui.cbSubGraph->blockSignals(true);

	ui.cbSubGraph->clear();
	ui.cbSubGraph->addItem("");
	SubGraphInfos& subGraphs = m_pEditorData->subgraphies();
	for (auto iter = subGraphs.begin(); iter != subGraphs.end(); ++iter)
	{
		ui.cbSubGraph->addItem(iter->name());
	}

	ui.cbSubGraph->blockSignals(false);
}

void BulletTab::updatePreview()
{
	ui.preview->clear();
	const SubGraphData* pDat = m_pEditorData->subgraphies().tryGet(m_cache.iSubGraph);
	if (!pDat)
		return;

	QPixmap texture = m_pEditorData->getTexture(pDat);
	texture = texture.copy(pDat->srcX, pDat->srcY, pDat->sizeX, pDat->sizeY);
	{
		QRectF coillide(0, 0, 2 * m_cache.radianX, 2 * m_cache.radianY);
		if (m_cache.collide == BulletStyle::cCircle)
			coillide.setHeight(coillide.width());

		int width = std::max(texture.width(), (int)std::ceil(coillide.width())) + 2;
		int height = std::max(texture.height(), (int)std::ceil(coillide.height())) + 2;
		if (width & 1) ++width;
		if (height & 1) ++height;

		m_cacheImg = QPixmap(width, height);
		QPainter painter(&m_cacheImg);
		QBrush brush(QColor(0x4a, 0x4a, 0x4a), Qt::Dense4Pattern);
		painter.setPen(Qt::NoPen);
		painter.setBrush(brush);
		painter.drawRect(0, 0, width, height);
		painter.setBrush(Qt::NoBrush);
		painter.drawPixmap((width - texture.width()) / 2, (height - texture.height()) / 2, texture);

		painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
		painter.setBrush(QColor(0xFF, 0, 0, 0x80));
		coillide.moveLeft((width - coillide.width()) / 2 + m_cache.centerX);
		coillide.moveTop((height - coillide.height()) / 2 + m_cache.centerY);

		switch (m_cache.collide)
		{
		case BulletStyle::cCircle:
			painter.drawEllipse(coillide);
			break;
		case BulletStyle::cRectangle:
			painter.drawRect(coillide);
			break;
		}
		painter.setRenderHint(QPainter::HighQualityAntialiasing, false);
	}

	ui.preview->addPixmap(m_cacheImg);
}

void BulletTab::refreshCtrlData()
{
	QObject* objs[] = {
		ui.cbType, ui.cbCollide, ui.sbCenterX,
		ui.sbCenterY, ui.sbRadianX, ui.sbRadianY, ui.cbSubGraph
	};
	for (QObject* pObj : objs)
		pObj->blockSignals(true);

	ui.cbType->setCurrentIndex(m_cache.type);
	ui.cbCollide->setCurrentIndex(m_cache.collide);
	ui.sbCenterX->setValue(m_cache.centerX);
	ui.sbCenterY->setValue(m_cache.centerY);
	ui.sbRadianX->setValue(m_cache.radianX);
	ui.sbRadianY->setValue(m_cache.radianY);

	QString subGraph = m_pEditorData->subgraphies().nameOfId(m_cache.iSubGraph);
	ui.cbSubGraph->setCurrentIndex(ui.cbSubGraph->findText(subGraph));
	ui.cbSubGraph->setEditText(subGraph);

	for (QObject* pObj : objs)
		pObj->blockSignals(false);

	ui.preview->resetZoom();
	ui.sbRadianY->setEnabled(m_cache.collide != BulletStyle::cCircle);
	updatePreview();
}

void BulletTab::refreshCache()
{
	const BulletStyle* pData = getSelectedData();
	if (!pData) return;

	m_cache = *pData;
}

const BulletStyle* BulletTab::getSelectedData()
{
	BulletItem* pItem = static_cast<BulletItem*>(getSelectedItem(idxName));
	if (!pItem)
		return nullptr;
	else
		return m_pEditorData->bulletStyles().tryGet(pItem->id());
}

QTableWidgetItem* BulletTab::getSelectedItem(int col)
{
	int row = currentIdx();
	if (row < 0)
		return nullptr;

	return ui.tableWidget->item(row, col);
}

void BulletTab::addRow(const BulletStyle& data)
{
	int row = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setItem(row, idxName, new BulletItem(m_pEditorData, data.id(), idxName));
	ui.tableWidget->setItem(row, idxType, new QTableWidgetItem(EditorData::enum2String(data.type)));
	ui.tableWidget->setItem(row, idxCollide, new QTableWidgetItem(EditorData::enum2String(data.collide)));
	ui.tableWidget->selectRow(row);
}

void BulletTab::onSelectionChanged(QTableWidgetItem* cur, QTableWidgetItem* prev)
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

void BulletTab::onAdd()
{
	if (!commitCache())
		return;

	m_pEditorData->bulletStyles().append(BulletStyle(QString::number(rand(), 16)));
	addRow(m_pEditorData->bulletStyles().back());
}

void BulletTab::onCopy()
{
	if (!commitCache())
		return;

	const BulletStyle* pSel = getSelectedData();
	if (!pSel) return;

	m_pEditorData->bulletStyles().append(*pSel);
	const BulletStyle& dat = m_pEditorData->bulletStyles().back();
	addRow(dat);
}

void BulletTab::onRemove()
{
	int row = currentIdx();
	if (row < 0)
		return;

	m_pEditorData->bulletStyles().erase(idByRow(row));
	ui.tableWidget->removeRow(row);
}

void BulletTab::onTypeChanged(int type)
{
	QTableWidgetItem* pItem = getSelectedItem(idxType);
	if (!pItem)
		return;

	QString typeTxt = EditorData::enum2String((BulletStyle::BulletType)type);
	if (typeTxt.isEmpty())
		return;

	m_cache.type = (BulletStyle::BulletType)type;
	pItem->setText(typeTxt);
}

void BulletTab::onCollideChanged(int type)
{
	QTableWidgetItem* pItem = getSelectedItem(idxCollide);
	if (!pItem)
		return;

	QString typeTxt = EditorData::enum2String((BulletStyle::CollideType)type);
	if (typeTxt.isEmpty())
		return;

	m_cache.collide = (BulletStyle::CollideType)type;
	pItem->setText(typeTxt);

	ui.sbRadianY->setEnabled(m_cache.collide != BulletStyle::cCircle);
	updatePreview();
}

void BulletTab::onCollideXChanged(double val)
{
	m_cache.centerX = val;
	updatePreview();
}

void BulletTab::onCollideYChanged(double val)
{
	m_cache.centerY = val;
	updatePreview();
}

void BulletTab::onCollideRXChanged(double val)
{
	m_cache.radianX = val;
	updatePreview();
}

void BulletTab::onCollideRYChanged(double val)
{
	m_cache.radianY = val;
	updatePreview();
}

void BulletTab::onSubGraphChanged(const QString& txt)
{
	int row = ui.cbSubGraph->findText(txt);
	m_cache.iSubGraph = ui.cbSubGraph->itemData(row).toUInt();
	updatePreview();
}

void BulletTab::queryEdit(const QModelIndex& idx)
{
	if (idx.column() == idxName)
		ui.tableWidget->edit(idx);
}
