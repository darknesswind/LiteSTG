#pragma once
#include <QComboBox>
#include <editordata.h>

class DulpexCombo : public QComboBox
	, IEraseNotify
	, INameChangedNotify
	, IItemAddedNotify
{
public:
	using QComboBox::QComboBox;
	~DulpexCombo() override
	{
		if (m_pContainer)
		{
			m_pContainer->eraseNotify().unregisterNotify(this);
			m_pContainer->nameChangedNotify().unregisterNotify(this);
			m_pContainer->itemAddedNotify().unregisterNotify(this);
		}
	}

	void registerNotify(IContainer* pContainer)
	{
		m_pContainer = pContainer;
		m_pContainer->eraseNotify().registerNotify(this);
		m_pContainer->nameChangedNotify().registerNotify(this);
		m_pContainer->itemAddedNotify().registerNotify(this);
	}

private:
	void onErase(uint id, IContainer*) override
	{
		int row = findData(id);
		removeItem(row);
	}
	void onNameChanged(uint id, IContainer* pContainer) override
	{
		int row = findData(id);
		setItemText(row, pContainer->getName(id));
	}
	void onItemAdded(uint id, IContainer* pContainer) override
	{
		addItem(pContainer->getName(id), id);
	}

private:
	IContainer* m_pContainer{ nullptr };
};
