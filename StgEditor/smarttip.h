#ifndef SMARTTIP_H
#define SMARTTIP_H

#include <QWidget>
#include <QMap>

class SmartTip : public QWidget
{
	Q_OBJECT

public:
	SmartTip(QWidget *parent);
	~SmartTip();

	static SmartTip* inst();
	void showTexture(QPoint pos, QString source);

protected:
	void paintEvent(QPaintEvent *e) override;

private:
	QPixmap m_curPixmap;
};

#endif // SMARTTIP_H
