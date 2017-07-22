#ifndef EDITORDATA_H
#define EDITORDATA_H
#include <QMap>
#include <QString>
#include <unordered_map>
#include <vector>
#include <QPixmap>
#include "dulpexmap.h"

struct Texture : public DulpexMapItem<Texture>
{
	typedef DulpexMapItem<Texture> Base;
public:
	Texture(const QString& name, const QString& _path)
		: Base(name), path(_path)
	{	}
	Texture(const std::string& name, const std::string& _path)
		: Base(QString::fromUtf8(name.c_str()))
		, path(QString::fromUtf8(_path.c_str()))
	{	}
public:
	QString path;
};
typedef DulpexMap<Texture> TextureMap;

struct SubGraphData : public DulpexMapItem<SubGraphData>
{
	typedef DulpexMapItem<SubGraphData> Base;
public:
	enum { ParamCount = 7 };
	SubGraphData(const QString& name)
		: Base(name)
	{	}
	bool updateData(const SubGraphData& other)
	{
		iTexture = other.iTexture;
		memcpy(raw, other.raw, sizeof(raw));
		return true;
	}
public:
	uint iTexture;
	union
	{
		struct
		{
			uint srcX, srcY;
			uint allNum;
			uint numX, numY;
			uint sizeX, sizeY;
		};
		int raw[ParamCount];
	};
	static_assert(sizeof(decltype(raw)) == sizeof(uint) * ParamCount, "ParamCount may be error");
};
template <>
void DulpexMap<SubGraphData>::onErase(uint id, IContainer*)
{
	for (auto& pair : m_entryMap)
	{
		if (pair.second.iTexture == id)
			pair.second.iTexture = 0;
	}
};
typedef DulpexMap<SubGraphData> SubGraphInfos;

struct BulletStyle
{
	enum BulletType
	{
		tGeneral,
		tRay,
		tSegment,
		tCurve,
	};
	enum CollideType
	{
		cCircle,
		cRectangle,
	};

	QString name;
	BulletType type;
	
	CollideType collide;
	qreal centerX;
	qreal centerY;
	qreal radianX;
	qreal radianY;

	QString subGraph;
};
typedef std::vector<BulletStyle> BulletStyles;

class EditorData
{
public:
	EditorData();
	static EditorData* instance();
	static QString enum2String(BulletStyle::BulletType type);
	static QString enum2String(BulletStyle::CollideType type);

	void load();
	void save();

	QString basePath();
	bool setBasePath(QString path);

	TextureMap& textureMap() { return m_textures; }
	SubGraphInfos& subgraphies() { return m_subGraphes; }
	BulletStyles& bulletStyles() { return m_bulletStyles; }

	QString getTextureFullPath(QString source);
	QPixmap getTextureByPath(QString source);
	QPixmap getTextureByName(QString name);
	QPixmap getTexture(const SubGraphData* pDat);

public:
	void removeTexture(const QString& name);
	void removeSubGraph(uint id);
	void removeBulletStyle(int idx);
	bool commitBulletStyle(int idx, const BulletStyle& style);
	bool canChangeBulletStyleName(int idx, const QString& newName);

protected:

protected:
	void loadSettings();
	void saveSettings();
	void loadTextures();
	void saveTextures();
	void loadSubGraphies();
	void saveSubGraphies();
	void loadBulletStyles();
	void saveBulletStyles();

	void savePathSet();
private:
	QString m_basePath;
	TextureMap m_textures;
	SubGraphInfos m_subGraphes;
	BulletStyles m_bulletStyles;
	QMap<QString, QPixmap> m_textureCache;

	std::unordered_map<uint, uint> m_textureConv;
};

#endif // EDITORDATA_H
