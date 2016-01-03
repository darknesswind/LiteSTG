#ifndef EDITORDATA_H
#define EDITORDATA_H
#include <QMap>
#include <QString>
#include <vector>
#include <QPixmap>

typedef QMap<QString, QString> TextureMap;	// path, name
struct SubGraphData
{
	enum { ParamCount = 7 };

	QString name;
	QString texture;
	union
	{
		struct
		{
			int srcX, srcY;
			int allNum;
			int numX, numY;
			int sizeX, sizeY;
		};
		int raw[ParamCount];
	} param;
	static_assert(sizeof(decltype(param)) == ParamCount * sizeof(int), "ParamCount may be error");
};
typedef std::vector<SubGraphData> SubGraphInfos;

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
	QPixmap getTexture(QString source);
	QPixmap getTextureByName(QString name);
	SubGraphData* getSubGraphByName(QString name);

public:
	void removeTexture(const QString& source);
	void removeSubGraph(int idx);
	void removeBulletStyle(int idx);
	QString changeTextureName(const QString& source, const QString& newName);
	bool commitSubGraph(int idx, const SubGraphData& newName);
	bool commitBulletStyle(int idx, const BulletStyle& style);
	bool canChangeSubGraphName(int idx, const QString& newName);
	bool canChangeBulletStyleName(int idx, const QString& newName);

protected:
	void updateTextureRef(QString srcName, QString dstName);

protected:
	void loadSettings();
	void saveSettings();
	void loadTextures();
	void saveTextures();
	void loadSubGraphies();
	void saveSubGraphies();
	void loadBulletStyles();
	void saveBulletStyles();

private:
	QString m_basePath;
	TextureMap m_textures;
	SubGraphInfos m_subGraphes;
	BulletStyles m_bulletStyles;
	QMap<QString, QPixmap> m_textureCache;
};

#endif // EDITORDATA_H
