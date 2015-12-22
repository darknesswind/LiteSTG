#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

class PreviewWidget : public QWidget
{
	Q_OBJECT

public:
	PreviewWidget(QWidget *parent);
	~PreviewWidget();

	void paintEvent(QPaintEvent *e);
private:
	
};

#endif // PREVIEWWIDGET_H
