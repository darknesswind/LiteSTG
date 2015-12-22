#include "smarttip.h"
#include <QPainter>
#include "editordata.h"

SmartTip::SmartTip(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
}

SmartTip::~SmartTip()
{

}

SmartTip* SmartTip::inst()
{
	static SmartTip* pInstance = new SmartTip(nullptr);
	return pInstance;
}

void SmartTip::showTexture(QPoint pos, QString source)
{
	m_curPixmap = EditorData::instance()->getTexture(source);
	move(pos);
	QRect rect = geometry();
	rect.setSize(m_curPixmap.size());
	rect.adjust(0, 0, 6, 6);
	setGeometry(rect);
	if (isVisible())
		repaint();
	else
		QWidget::show();
}

void SmartTip::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);

	QBrush brush(Qt::Dense4Pattern);
	painter.setBrush(brush);
	painter.drawRect(QRect(3, 3, width() - 6, height() - 6));

	painter.drawPixmap(3, 3, m_curPixmap);
}
