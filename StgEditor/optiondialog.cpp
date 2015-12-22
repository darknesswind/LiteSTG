#include "optiondialog.h"
#include "ui_optiondialog.h"
#include "editordata.h"
#include <QFileDialog>
#include <QMessageBox>

OptionDialog::OptionDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OptionDialog)
{
	ui->setupUi(this);
	m_pEditorData = EditorData::instance();


}

OptionDialog::~OptionDialog()
{
	delete ui;
}

void OptionDialog::accept()
{
	if (!m_pEditorData->setBasePath(ui->edBasePath->text()))
	{
		QMessageBox::warning(this, "error",
							 QString(R"("%1" is not exist!")").arg(ui->edBasePath->text()),
							 QMessageBox::Ok);
		return;
	}
	QDialog::accept();
}

void OptionDialog::browseBasePath()
{
	QString path = QFileDialog::getExistingDirectory(this, "Set Base Path", m_pEditorData->basePath());
	if (!path.isEmpty())
		ui->edBasePath->setText(path);
}
