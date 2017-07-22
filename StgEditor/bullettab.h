#ifndef BULLETTAB_H
#define BULLETTAB_H

#include <QWidget>
#include "ui_bullettab.h"
#include "editordata.h"
#include "tabbase.h"
#include <QPixmap>

class QTableWidgetItem;
class BulletTab : public TabBase
{
	Q_OBJECT

public:
	BulletTab(QWidget *parent = 0);
	~BulletTab();

	bool commitCache() override;
	void enterTab() override;

protected:
	void init();
	void initContext();
	void updateSubGraphName();
	void updatePreview();
	void refreshCtrlData();
	void refreshCache();
	bool commitCacheTo(int row);
	int currentIdx();
	uint idByRow(int row);

	const BulletStyle* getSelectedData();
	QTableWidgetItem* getSelectedItem(int col);
	void addRow(const BulletStyle& data);

protected slots:
	void onSelectionChanged(QTableWidgetItem* cur, QTableWidgetItem* prev);
	void onAdd();
	void onCopy();
	void onRemove();
	void onTypeChanged(int type);
	void onCollideChanged(int type);
	void onCollideXChanged(double val);
	void onCollideYChanged(double val);
	void onCollideRXChanged(double val);
	void onCollideRYChanged(double val);
	void onSubGraphChanged(const QString& subGraph);
	void queryEdit(const QModelIndex& idx);

private:
	Ui::BulletTab ui;
	EditorData* m_pEditorData;
	BulletStyle m_cache;
	QPixmap m_cacheImg;
};

#endif // BULLETTAB_H
