#ifndef __LPATHSET_H__
#define __LPATHSET_H__

#include "LPathNodes.h"
class QXmlStreamReader;
class QXmlStreamAttributes;
class LPathSet
{
	enum PathNodeID
	{
		xPath,
		xEmptyNode,
		xLineNode,
		xSineNode,
	};
public:
	LPathSet();
	~LPathSet();

	bool load(LPCWSTR lpFile);
	const LPathNodes* getPath(uint id);
	void clear();

private:
	bool parse(QXmlStreamReader& reader);
	void parsePath(QXmlStreamReader& reader);
	void parseEmptyNode(QXmlStreamReader& reader);
	void parseLineNode(QXmlStreamReader& reader);
	void parseSineNode(QXmlStreamReader& reader);

	inline int getIntAttr(QXmlStreamAttributes& attr, const QString& key, int defVal = 0);
	inline float getFloatAttr(QXmlStreamAttributes& attr, const QString& key, float defVal = 0);

private:
	static void setupParseMap();
	static std::map<QString, PathNodeID> s_parser;

private:
	std::unordered_map<uint, LPathNodes> m_paths;

	LPathNodes* m_pReadingPath = nullptr;
};

#endif // __LPATHSET_H__
