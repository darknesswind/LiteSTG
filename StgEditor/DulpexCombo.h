#pragma once
#include <QComboBox>
#include <editordata.h>

class DulpexCombo : public QComboBox
	, INameChangedNotify
{
public:
	using QComboBox::QComboBox;
	~DulpexCombo() override
	{
		if (m_pNotifyHelper)
			m_pNotifyHelper->unregisterNotify(this);
	}

	void registerNameChanged(NameChangedNotifyHelper& helper)
	{
		m_pNotifyHelper = &helper;
		m_pNotifyHelper->registerNotify(this);
	}

private:
	void onNameChanged(uint id, IContainer* pContainer) override
	{
		int row = findData(id);
		this->setItemText(row, pContainer->getName(id));
	}

private:
	NameChangedNotifyHelper* m_pNotifyHelper{ nullptr };
};
