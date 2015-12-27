#include "previewwidget.h"
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>

class PreviewScene : public QGraphicsScene
{
	PreviewWidget* m_parent;
public:
	PreviewScene(PreviewWidget* parent)
		: QGraphicsScene(parent)
		, m_parent(parent)
	{
	}

	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override
	{
		m_parent->setMousePos(mouseEvent->scenePos().toPoint());
	}

	void wheelEvent(QGraphicsSceneWheelEvent* wheelEvent) override
	{
		if (wheelEvent->modifiers() & Qt::ControlModifier)
		{
			qreal zoom = m_parent->getZoom();
			qreal delta = wheelEvent->delta() / 120.0;
			if (zoom < 1)
				zoom += 0.01 * delta;
			else
				zoom += 0.1 * delta;

			if (zoom < 0)
				zoom = 0;

			m_parent->setZoom(zoom);
		}
	}
};

PreviewWidget::PreviewWidget(QWidget *parent)
	: QWidget(parent)
	, m_pGraphScene(nullptr)
	, m_zoom(1.0)
{
	ui.setupUi(this);

	m_pGraphScene = new PreviewScene(this);
	ui.graphicsView->setScene(m_pGraphScene);

	m_pGraphScene->installEventFilter(this);

	connect(ui.sbZoom, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, &PreviewWidget::setZoom);
}

PreviewWidget::~PreviewWidget()
{

}

void PreviewWidget::clear()
{
	m_pGraphScene->clear();
}

void PreviewWidget::addPixmap(const QPixmap& pixmap)
{
	m_pGraphScene->addPixmap(pixmap);
	ui.lbSize->setText(QString("%1x%2").arg(pixmap.width()).arg(pixmap.height()));
}

void PreviewWidget::resetZoom()
{
	ui.graphicsView->resetTransform();
}

void PreviewWidget::setZoom(qreal zoom)
{
	m_zoom = zoom;
	ui.graphicsView->resetTransform();
	ui.graphicsView->scale(zoom, zoom);
	ui.sbZoom->setValue(zoom);
}

void PreviewWidget::setMousePos(const QPoint& pos)
{
	ui.lbPos->setText(QString("(%1,%2)").arg(pos.x()).arg(pos.y()));
}

bool PreviewWidget::eventFilter(QObject* obj, QEvent* e)
{
	return QWidget::eventFilter(obj, e);
}
