#pragma once
#include <unordered_set>
#include <cassert>

struct IContainer;
struct IContainer
{
	virtual QString getName(uint id) = 0;
};
/*
struct INotifyHelper
{
	virtual void registerNotify(void* pNotify) = 0;
	virtual void unregisterNotify(void* pNotify) = 0;
};
*/

template <typename INotify>
class NotifyHelper //: INotifyHelper
{
public:
	NotifyHelper(IContainer* pContainer)
		: m_pContainer(pContainer)
	{
	}
	void registerNotify(INotify* pNotify)
	{
		if (pNotify != nullptr)
			m_notify.insert(pNotify);
	}
	void unregisterNotify(INotify* pNotify)
	{
		m_notify.erase(pNotify);
	}
	void notify(uint id)
	{
		for (INotify* pNotify : m_notify)
			notify(pNotify, id);
	}
private:
	void notify(INotify* notify, uint id) { assert(false); }
	void registerNotify(void* pNotify)// override final
	{
		registerNotify((INotify*)pNotify);
	}
	void unregisterNotify(void* pNotify)// override final
	{
		unregisterNotify((INotify*)pNotify);
	}

private:
	IContainer* m_pContainer;
	std::unordered_set<INotify*> m_notify;
};

struct IEraseNotify
{
	virtual void onErase(uint id, IContainer* pContainer) = 0;
};
typedef NotifyHelper<IEraseNotify> EraseNotifyHelper;
template <> void EraseNotifyHelper::notify(IEraseNotify* notify, uint id)
{ notify->onErase(id, m_pContainer); }

struct INameChangedNotify
{
	virtual void onNameChanged(uint id, IContainer* pContainer) = 0;
};
typedef NotifyHelper<INameChangedNotify> NameChangedNotifyHelper;
void NameChangedNotifyHelper::notify(INameChangedNotify* notify, uint id)
{ notify->onNameChanged(id, m_pContainer); }

struct IItemAddedNotify
{
	virtual void onItemAdded(uint id, IContainer* pContainer) = 0;
};
typedef NotifyHelper<IItemAddedNotify> ItemAddedNotifyHelper;
void ItemAddedNotifyHelper::notify(IItemAddedNotify* notify, uint id)
{ notify->onItemAdded(id, m_pContainer); }

template <typename Entry>
class DulpexMap : public IContainer, public IEraseNotify
{
	typedef std::map<uint, Entry> EntryMap;
	typedef QMap<QString, uint> NameMap;

public:
	static const uint InvaildIndex = 0;

	DulpexMap() {}
	bool append(const Entry& entry)
	{
		QString name = entry.name();
		if (!resolveName(name))
			return false;

		uint id = allocID();
		m_entryMap.insert(std::make_pair(id, entry));

		m_entryMap.at(id).m_id = id;
		m_entryMap.at(id).m_name = name;
		m_nameMap[name] = id;

		m_itemAddedNotify.notify(id);
		return true;
	}
	bool erase(const QString& name)
	{
		auto iter = m_nameMap.find(name);
		if (iter == m_nameMap.end())
			return false;

		uint id = iter.value();
		m_entryMap.erase(m_entryMap.find(id));
		m_nameMap.erase(iter);

		m_eraseNotify.notify(id);
		return true;
	}
	bool erase(uint id)
	{
		auto iter = m_entryMap.find(id);
		if (iter == m_entryMap.end())
			return false;

		m_nameMap.erase(m_nameMap.find(iter.value().name()));
		m_entryMap.erase(iter);

		m_eraseNotify.notify(id);
		return true;
	}

	bool contains(uint id) const { return m_entryMap.find(id) != m_entryMap.end(); }
	bool contains(const QString& name) const { return m_nameMap.contains(name); }
	uint idOfName(const QString& name) const
	{
		auto iter = m_nameMap.find(name);
		return (iter != m_nameMap.end()) ? iter.value() : InvaildIndex;
	}
	QString nameOfId(uint id) const
	{
		auto iter = m_entryMap.find(id);
		return (iter != m_entryMap.end()) ? iter->second.name() : QString();
	}
	bool rename(const QString& oldName, const QString& newName)
	{
		if (newName.isEmpty() || oldName == newName)
			return false;

		auto iter = m_nameMap.find(oldName);
		if (iter == m_nameMap.end())
			return false;

		QString name = newName;
		if (!resolveName(name))
			return false;

		uint id = iter.value();
		m_entryMap.at(id).m_name = name;
		m_nameMap.erase(iter);
		m_nameMap[name] = id;

		m_nameChangedNotify.notify(id);
		return true;
	}
	bool rename(uint id, const QString& name)
	{
		if (!contains(id) || name.isEmpty())
			return false;

		QString oldName = m_entryMap.at(id).name();
		if (name == oldName)
			return false;

		QString newName = name;
		if (!resolveName(newName))
			return false;

		m_entryMap.at(id).m_name = newName;
		m_nameMap.erase(m_nameMap.find(oldName));
		m_nameMap[name] = id;

		m_nameChangedNotify.notify(id);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	const Entry& at(uint id) const { return m_entryMap.at(id); }
	const Entry& operator[](uint id) const { return m_entryMap.at(id); }
	const Entry& operator[](const QString& name) const { return m_entryMap.at(m_nameMap.find(name).value()); }
	const Entry* tryGet(uint id) const
	{
		auto iter = m_entryMap.find(id);
		return (iter != m_entryMap.end()) ? &iter->second : nullptr;
	}
	const Entry* tryGet(const QString& name) const
	{
		return tryGet(idOfName(name));
	}

	//////////////////////////////////////////////////////////////////////////
	class iterator : protected EntryMap::const_iterator
	{
		typedef typename EntryMap::const_iterator Base;
	public:
		using Base::Base;
		bool operator!=(const iterator& other) { return Base::operator!=(other); }
		iterator& operator++() { Base::operator++(); return *this; }

		iterator(const Base& iter) : Base(iter) {}
		uint id() const { return key(); }
		const Entry& value() const { return Base::operator*().second; }
		const Entry& operator*() const { return value(); };
		const Entry* operator->() const { return &value(); };
	};
	iterator begin() { return iterator(m_entryMap.cbegin()); }
	iterator end() { return iterator(m_entryMap.cend()); }
	const Entry& back() const { return m_entryMap.rbegin()->second; }

	//////////////////////////////////////////////////////////////////////////
	auto& eraseNotify() { return m_eraseNotify; }
	auto& nameChangedNotify() { return m_nameChangedNotify; }
	auto& itemAddedNotify() { return m_itemAddedNotify; }

private:
	uint allocID() { return ++m_maxId; } // �� 1 ��ʼ
	bool resolveName(QString& name)
	{
		if (!m_nameMap.contains(name))
			return true;

		uint i = 0;
		const uint max = 100000;
		while (i < max && m_nameMap.contains(name + QString::number(i)))
			++i;

		if (i < max)
		{
			name += QString::number(i);
			return true;
		}
		return false;
	}
private: // IContainer
	QString getName(uint id) override final { return nameOfId(id); }

private: // IEraseNotify
	void onErase(uint, IContainer*) override { assert(false); }

private:
	uint m_maxId{ 0 };
	EntryMap m_entryMap;
	NameMap m_nameMap;
	EraseNotifyHelper m_eraseNotify{ this };
	NameChangedNotifyHelper m_nameChangedNotify{ this };
	ItemAddedNotifyHelper m_itemAddedNotify{ this };
};

template <typename DiveType>
class DulpexMapItem
{
	typedef DulpexMap<DiveType> ContainerMap;
public:
	DulpexMapItem(const QString& name) : m_name(name) {}

	uint id() const { return m_id; }
	const QString& name() const { return m_name; }

private:
	friend class ContainerMap;

	uint m_id{ 0 };
	QString m_name;
};
