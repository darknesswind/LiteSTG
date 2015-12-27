#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include "ui_previewwidget.h"

class PreviewWidget : public QWidget
{
	Q_OBJECT

public:
	PreviewWidget(QWidget *parent = 0);
	~PreviewWidget();

	void clear();
	void addPixmap(const QPixmap& pixmap);
	void resetZoom();
	void setZoom(qreal zoom);
	qreal getZoom() const { return m_zoom; }
	void setMousePos(const QPoint& pos);

protected:
	bool eventFilter(QObject* obj, QEvent* e) override;

private:
	Ui::PreviewWidget ui;
	qreal m_zoom;
	QGraphicsScene* m_pGraphScene;
};

#endif // PREVIEWWIDGET_H
