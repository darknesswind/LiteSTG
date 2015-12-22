#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
	class OptionDialog;
}

class EditorData;
class OptionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit OptionDialog(QWidget *parent = 0);
	~OptionDialog();

public slots:
	void accept() override;
	void browseBasePath();

private:
	Ui::OptionDialog *ui;
	EditorData* m_pEditorData;
};

#endif // OPTIONDIALOG_H
