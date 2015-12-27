#pragma once

class TabBase : public QWidget
{
public:
	using QWidget::QWidget;
	virtual bool commitCache() = 0;
	virtual void enterTab() {};
};
