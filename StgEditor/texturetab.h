#ifndef TEXTURETAB_H
#define TEXTURETAB_H

#include <QWidget>
#include <QTimer>

namespace Ui {
	class TextureTab;
}

class EditorData;
class QTableWidgetItem;
class TextureTab : public QWidget
{
	Q_OBJECT

public:
	explicit TextureTab(QWidget *parent = 0);
	~TextureTab();

protected:
	void init();
	void hideTip();
	bool eventFilter(QObject* o, QEvent* e) override;

protected slots:
	void onAdd();
	void onRemove();
	void onPreMulti();
	void queryEdit(const QModelIndex& idx);
	void checkTip();

private:
	Ui::TextureTab *ui;
	EditorData* m_pEditorData;
	QString m_prevPath;
	QTimer m_timer;
	int m_lastTipRow = -1;
};

#endif // TEXTURETAB_H
