#include "subgraphtab.h"
#include "editordata.h"
#include <QSpinBox>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>

enum
{
	idxName,
	idxTexture
};

SubGraphTab::SubGraphTab(QWidget *parent)
	: QWidget(parent)
	, m_pEditorData(nullptr)
	, m_bSelectUpdating(false)
	, m_zoom(1.0)
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

	m_pGraphScene = new QGraphicsScene(this);
	ui.graphicsView->setScene(m_pGraphScene);
	m_pGraphScene->installEventFilter(this);

	updateTextureName();
	SubGraphInfos& infos = m_pEditorData->subgraphies();
	for (size_t i = 0; i < infos.size(); ++i)
	{
		int row = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(row);
		ui.tableWidget->setItem(row, idxName, new QTableWidgetItem(infos[i].name));
		ui.tableWidget->setItem(row, idxTexture, new QTableWidgetItem(infos[i].texture));
		ui.tableWidget->selectRow(row);
	}

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

void SubGraphTab::onAdd()
{
	m_pEditorData->subgraphies().push_back(SubGraphData());
	SubGraphData& data = m_pEditorData->subgraphies().back();
	data.name = "new";

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
	m_pEditorData->subgraphies().erase(m_pEditorData->subgraphies().begin() + row);
}

void SubGraphTab::onNameChanged(const QString& name)
{
	if (m_bSelectUpdating) return;

	SubGraphData* pData = getSelectedData();
	if (!pData) return;

	QTableWidgetItem* pItem = getSelectedItem(idxName);
	if (!pItem) return;

	pData->name = name;
	pItem->setText(name);
	updatePreview();
}

void SubGraphTab::onTextureChanged(const QString& texture)
{
	if (m_bSelectUpdating) return;

	SubGraphData* pData = getSelectedData();
	if (!pData) return;

	QTableWidgetItem* pItem = getSelectedItem(idxTexture);
	if (!pItem) return;

	pData->texture = texture;
	pItem->setText(texture);
	updatePreview();
}

void SubGraphTab::onInfoChanged()
{
	if (m_bSelectUpdating) return;

	SubGraphData* pData = getSelectedData();
	if (!pData) return;

	for (size_t i = 0; i < m_spinBoxs.size(); ++i)
	{
		pData->param.raw[i] = m_spinBoxs[i]->value();
	}
	updatePreview();
}

void SubGraphTab::onSelectionChanged()
{
	SubGraphData* pData = getSelectedData();
	if (!pData) return;

	m_bSelectUpdating = true;

	ui.edName->setText(pData->name);
	ui.cbTexture->setCurrentIndex(ui.cbTexture->findText(pData->texture));
	ui.cbTexture->setEditText(pData->texture);
	for (size_t i = 0; i < m_spinBoxs.size(); ++i)
	{
		m_spinBoxs[i]->setValue(pData->param.raw[i]);
	}

	m_bSelectUpdating = false;
	ui.graphicsView->resetTransform();
	updatePreview();
	ui.lbSize->setText(QString("%1x%2").arg(m_cacheImg.width()).arg(m_cacheImg.height()));
}

void SubGraphTab::updatePreview()
{
	SubGraphData* pData = getSelectedData();
	if (!pData) return;

	m_pGraphScene->clear();
	if (pData->texture.isEmpty())
		return;

	QString texture = ui.cbTexture->itemData(ui.cbTexture->findText(pData->texture)).toString();
	QPixmap img = m_pEditorData->getTexture(texture);
	if (img.isNull())
		return;

	QPainterPath path;
	QRectF rect(pData->param.srcX, pData->param.srcY, pData->param.sizeX, pData->param.sizeY);
	int all = 0;
	for (int i = 0; i < pData->param.numY; ++i)
	{
		rect.moveLeft(pData->param.srcX);
		for (int j = 0; j < pData->param.numX; ++j)
		{
			path.addRect(rect);
			rect.moveLeft(rect.left() + pData->param.sizeX);
			if (++all >= pData->param.allNum)
				break;
		}
		rect.moveTop(rect.top() + pData->param.sizeY);
		if (all >= pData->param.allNum)
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
	m_pGraphScene->addPixmap(m_cacheImg);
}

void SubGraphTab::updateTextureName()
{
	m_bSelectUpdating = true;

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
	m_bSelectUpdating = false;
}

bool SubGraphTab::eventFilter(QObject* obj, QEvent* e)
{
	if (e->type() == QEvent::GraphicsSceneWheel)
	{
		QGraphicsSceneWheelEvent* pEvent = static_cast<QGraphicsSceneWheelEvent*>(e);
		if (pEvent->modifiers() & Qt::ControlModifier)
		{
			qreal delta = pEvent->delta() / 120.0;
			if (m_zoom < 1)
				m_zoom += 0.01 * delta;
			else
				m_zoom += 0.1 * delta;

			if (m_zoom < 0)
				m_zoom = 0;
			ui.graphicsView->resetTransform();
			ui.graphicsView->scale(m_zoom, m_zoom);
			ui.sbZoom->setValue(m_zoom);
		}
	}
	return QWidget::eventFilter(obj, e);
}

SubGraphData* SubGraphTab::getSelectedData()
{
	int row = ui.tableWidget->currentRow();
	if (row < 0)
		return nullptr;
	else
		return &m_pEditorData->subgraphies()[row];
}

QTableWidgetItem* SubGraphTab::getSelectedItem(int col)
{
	int row = ui.tableWidget->currentRow();
	if (row < 0)
		return nullptr;

	return ui.tableWidget->item(row, col);
}
