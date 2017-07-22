#ifndef SUBGRAPHTAB_H
#define SUBGRAPHTAB_H

#include <QWidget>
#include "ui_subgraphtab.h"
#include <array>
#include "tabbase.h"
#include "editordata.h"

class EditorData;
struct SubGraphData;
class SubGraphTab : public TabBase
{
	Q_OBJECT

public:
	SubGraphTab(QWidget *parent = 0);
	~SubGraphTab();

	bool commitCache();
	void enterTab();

protected slots:
	void onAdd();
	void onCopy();
	void onRemove();
	void onTextureChanged(const QString& texture);
	void onInfoChanged();
	void onSelectionChanged(QTableWidgetItem* cur, QTableWidgetItem* prev);
	void queryEdit(const QModelIndex& idx);

protected:
	void init();
	void initContext();
	void updateTextureName();
	void updatePreview();
	bool commitCacheTo(int row);
	int currentIdx();
	void refreshCtrlData();
	void refreshCache();

	uint idByRow(int row);
	const SubGraphData* getSelectedData();
	QTableWidgetItem* getSelectedItem(int col);

private:
	Ui::SubGraphTab ui;
	EditorData* m_pEditorData;
	std::array<QSpinBox*, 7> m_spinBoxs;
	bool m_bSelectUpdating;

	SubGraphData m_cache;
	QPixmap m_cacheImg;
};

#endif // SUBGRAPHTAB_H
