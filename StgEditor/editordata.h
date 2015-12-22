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

class EditorData
{
public:
	EditorData();
	static EditorData* instance();

	void load();
	void save();

	QString basePath();
	bool setBasePath(QString path);

	TextureMap& textureMap() { return m_textures; }
	SubGraphInfos& subgraphies() { return m_subGraphes; }

	QPixmap getTexture(QString source);
	void updateTextureRef(QString srcName, QString dstName);

protected:
	void loadSettings();
	void saveSettings();
	void loadTextures();
	void saveTextures();
	void loadSubGraphies();
	void saveSubGraphies();

private:
	QString m_basePath;
	TextureMap m_textures;
	SubGraphInfos m_subGraphes;

	QMap<QString, QPixmap> m_textureCache;
};

#endif // EDITORDATA_H
