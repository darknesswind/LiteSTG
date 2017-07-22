#ifndef EDITORDATA_H
#define EDITORDATA_H
#include <unordered_map>
#include <QPixmap>
#include "dataobj.h"

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
