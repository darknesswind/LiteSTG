#ifndef SUBGRAPHTAB_H
#define SUBGRAPHTAB_H

#include <QWidget>
#include "ui_subgraphtab.h"
#include <array>

class EditorData;
struct SubGraphData;
class SubGraphTab : public QWidget
{
	Q_OBJECT

public:
	SubGraphTab(QWidget *parent = 0);
	~SubGraphTab();
	void init();
	void updateTextureName();

protected:
	void onAdd();
	void onCopy();
	void onRemove();
	void onNameChanged(const QString& name);
	void onTextureChanged(const QString& texture);
	void onInfoChanged();
	void onSelectionChanged();

	void updatePreview();

	bool eventFilter(QObject* obj, QEvent* e) override;

	SubGraphData* getSelectedData();
	QTableWidgetItem* getSelectedItem(int col);

private:
	Ui::SubGraphTab ui;
	EditorData* m_pEditorData;
	std::array<QSpinBox*, 7> m_spinBoxs;
	bool m_bSelectUpdating;

	QGraphicsScene* m_pGraphScene;
	QPixmap m_cacheImg;
	qreal m_zoom;
};

#endif // SUBGRAPHTAB_H
