#include "bullettab.h"
#include <QToolTip>

enum
{
	idxName,
	idxType,
	idxCollide,
};

BulletTab::BulletTab(QWidget *parent)
	: TabBase(parent)
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
	bool bSucceed = m_pEditorData->commitBulletStyle(row, m_cache);
	if (!bSucceed)
	{
		m_cache = m_pEditorData->bulletStyles()[row];
		refreshCtrlData();
	}
	return bSucceed;
}

int BulletTab::currentIdx()
{
	return ui.tableWidget->currentRow();
}

void BulletTab::init()
{
	m_pEditorData = EditorData::instance();
	updateSubGraphName();
	initContext();

	connect(ui.tableWidget, &QTableWidget::currentItemChanged, this, &BulletTab::onSelectionChanged);
	connect(ui.btnAdd, &QPushButton::clicked, this, &BulletTab::onAdd);
	connect(ui.btnCopy, &QPushButton::clicked, this, &BulletTab::onCopy);
	connect(ui.btnRemove, &QPushButton::clicked, this, &BulletTab::onRemove);

	connect(ui.edName, &QLineEdit::textChanged, this, &BulletTab::onNameChanged);
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
	for (size_t i = 0; i < infos.size(); ++i)
	{
		addRow(infos[i]);
	}
	refreshCache();
	refreshCtrlData();
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
	if (m_cache.subGraph.isEmpty())
		return;

	const SubGraphData* pDat = m_pEditorData->subgraphies().tryGet(m_cache.subGraph);
	if (!pDat)
		return;

	QPixmap texture = m_pEditorData->getTexture(pDat);
	texture = texture.copy(pDat->param.srcX, pDat->param.srcY, pDat->param.sizeX, pDat->param.sizeY);
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
		ui.edName, ui.cbType, ui.cbCollide, ui.sbCenterX,
		ui.sbCenterY, ui.sbRadianX, ui.sbRadianY, ui.cbSubGraph
	};
	for each(auto pObj in objs)
		pObj->blockSignals(true);

	ui.edName->setText(m_cache.name);
	ui.cbType->setCurrentIndex(m_cache.type);
	ui.cbCollide->setCurrentIndex(m_cache.collide);
	ui.sbCenterX->setValue(m_cache.centerX);
	ui.sbCenterY->setValue(m_cache.centerY);
	ui.sbRadianX->setValue(m_cache.radianX);
	ui.sbRadianY->setValue(m_cache.radianY);
	ui.cbSubGraph->setCurrentText(m_cache.subGraph);

	for each(auto pObj in objs)
		pObj->blockSignals(false);

	ui.preview->resetZoom();
	ui.sbRadianY->setEnabled(m_cache.collide != BulletStyle::cCircle);
	updatePreview();
}

void BulletTab::refreshCache()
{
	BulletStyle* pData = getSelectedData();
	if (!pData) return;

	m_cache = *pData;
}

BulletStyle* BulletTab::getSelectedData()
{
	int row = currentIdx();
	if (row < 0)
		return nullptr;
	else
		return &m_pEditorData->bulletStyles()[row];
}

QTableWidgetItem* BulletTab::getSelectedItem(int col)
{
	int row = currentIdx();
	if (row < 0)
		return nullptr;

	return ui.tableWidget->item(row, col);
}

void BulletTab::addRow(BulletStyle& data)
{
	int row = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setItem(row, idxName, new QTableWidgetItem(data.name));
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

	m_pEditorData->bulletStyles().emplace_back(BulletStyle());
	BulletStyle& dat = m_pEditorData->bulletStyles().back();
	dat.name = QString::number(rand(), 16);
	addRow(dat);
}

void BulletTab::onCopy()
{
	if (!commitCache())
		return;

	BulletStyle* pSel = getSelectedData();
	if (!pSel) return;

	m_pEditorData->bulletStyles().push_back(*pSel);
	BulletStyle& dat = m_pEditorData->bulletStyles().back();
	dat.name += QString::number(rand(), 16);
	addRow(dat);
}

void BulletTab::onRemove()
{
	int row = currentIdx();
	if (row < 0)
		return;

	ui.tableWidget->removeRow(row);
	m_pEditorData->removeBulletStyle(row);
}

void BulletTab::onNameChanged(const QString& newName)
{
	QTableWidgetItem* pItem = getSelectedItem(idxName);
	if (!pItem)
		return;

	if (!m_pEditorData->canChangeBulletStyleName(currentIdx(), newName))
	{
		QToolTip::showText(ui.edName->mapToGlobal(QPoint(0, 0)), QString("\"%1\" already exist").arg(newName), ui.edName);
	}
	else
	{
		m_cache.name = newName;
		pItem->setText(newName);
	}
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
	m_cache.subGraph = txt;
	updatePreview();
}
