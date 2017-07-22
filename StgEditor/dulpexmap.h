#pragma once
#include <QString>
#include <QMap>
#include <vector>
#include <unordered_set>
#include <cassert>

struct IContainer;
struct IEraseNotify
{
	virtual void onErase(uint id, IContainer* pContainer) = 0;
};
struct INameChangedNotify
{
	virtual void onNameChanged(uint id, IContainer* pContainer) = 0;
};
struct IItemAddedNotify
{
	virtual void onItemAdded(uint id, IContainer* pContainer) = 0;
};

template <typename INotify>
class NotifyHelper
{
public:
	NotifyHelper(IContainer* pContainer)
		: m_pContainer(pContainer)
	{
	}
	void registerNotify(INotify* pNotify) { if (pNotify) m_notify.insert(pNotify); }
	void unregisterNotify(INotify* pNotify) { m_notify.erase(pNotify); }
	void notify(uint id)
	{
		for (INotify* pNotify : m_notify)
			notify(pNotify, id);
	}
private:
	void notify(INotify* notify, uint id) { assert(false); }

private:
	IContainer* m_pContainer;
	std::unordered_set<INotify*> m_notify;
};
typedef NotifyHelper<IEraseNotify> EraseNotifyHelper;
typedef NotifyHelper<INameChangedNotify> NameChangedNotifyHelper;
typedef NotifyHelper<IItemAddedNotify> ItemAddedNotifyHelper;
struct IContainer
{
	virtual QString getName(uint id) = 0;

	virtual EraseNotifyHelper& eraseNotify() = 0;
	virtual NameChangedNotifyHelper& nameChangedNotify() = 0;
	virtual ItemAddedNotifyHelper& itemAddedNotify() = 0;
};

template <typename Entry>
class DulpexMap : public IContainer, public IEraseNotify
{
	typedef std::map<uint, Entry> EntryMap;
	typedef QMap<QString, uint> NameMap;

public:
	static const uint InvaildIndex = 0;

	DulpexMap() {}
	bool append(const Entry& entry);
	bool erase(const QString& name);
	bool erase(uint id);

	bool contains(uint id) const { return m_entryMap.find(id) != m_entryMap.end(); }
	bool contains(const QString& name) const { return m_nameMap.contains(name); }
	bool rename(const QString& oldName, const QString& newName);
	bool rename(uint id, const QString& name);
	bool updateData(uint id, const Entry& other);

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
	EraseNotifyHelper& eraseNotify() override final { return m_eraseNotify; }
	NameChangedNotifyHelper& nameChangedNotify() override final { return m_nameChangedNotify; }
	ItemAddedNotifyHelper& itemAddedNotify() override final { return m_itemAddedNotify; }

private:
	uint allocID() { return ++m_maxId; } // ´Ó 1 ¿ªÊ¼
	bool resolveName(QString& name);

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
//	bool updateData(const Entry& other) { assert(false); return false; }

private:
	friend class ContainerMap;

	uint m_id{ 0 };
	QString m_name;
};

template <>
void EraseNotifyHelper::notify(IEraseNotify* notify, uint id)
{
	notify->onErase(id, m_pContainer);
}
template <>
void NameChangedNotifyHelper::notify(INameChangedNotify* notify, uint id)
{
	notify->onNameChanged(id, m_pContainer);
}
template <>
void ItemAddedNotifyHelper::notify(IItemAddedNotify* notify, uint id)
{
	notify->onItemAdded(id, m_pContainer);
}

template <typename Entry>
bool DulpexMap<Entry>::append(const Entry& entry)
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

template <typename Entry>
bool DulpexMap<Entry>::erase(const QString& name)
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

template <typename Entry>
bool DulpexMap<Entry>::erase(uint id)
{
	auto iter = m_entryMap.find(id);
	if (iter == m_entryMap.end())
		return false;

	m_nameMap.erase(m_nameMap.find(iter->second.name()));
	m_entryMap.erase(iter);

	m_eraseNotify.notify(id);
	return true;
}

template <typename Entry>
bool DulpexMap<Entry>::rename(const QString& oldName, const QString& newName)
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

template <typename Entry>
bool DulpexMap<Entry>::rename(uint id, const QString& name)
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

template <typename Entry>
bool DulpexMap<Entry>::resolveName(QString& name)
{
	if (!m_nameMap.contains(name) || name.isEmpty())
		return true;

	auto iter = name.rbegin();
	for (; iter != name.rend(); ++iter)
	{
		QChar ch = *iter;
		if (ch < '0' || ch > '9')
			break;
	}
	uint i = 0;
	if (iter != name.rend() && name.rend() - iter > 1)
	{
		QChar ch = *iter;
		if (ch == '_')
		{
			i = name.rightRef(iter - name.rbegin()).toUInt() + 1;
			name = name.left(name.rend() - iter - 1);
		}
	}
	name.push_back('_');
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

template <typename Entry>
bool DulpexMap<Entry>::updateData(uint id, const Entry& other)
{
	auto iter = m_entryMap.find(id);
	if (iter != m_entryMap.end())
		return iter->second.updateData(other);
	else
		return false;
}
