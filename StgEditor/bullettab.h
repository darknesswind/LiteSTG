#ifndef BULLETTAB_H
#define BULLETTAB_H

#include <QWidget>
#include "ui_bullettab.h"

class BulletTab : public QWidget
{
	Q_OBJECT

public:
	BulletTab(QWidget *parent = 0);
	~BulletTab();

private:
	Ui::BulletTab ui;
};

#endif // BULLETTAB_H
