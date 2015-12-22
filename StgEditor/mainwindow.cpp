#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texturetab.h"
#include "subgraphtab.h"
#include "optiondialog.h"
#include "editordata.h"

enum
{
	idxTexture,
	idxSubGraph,
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QAction* pSettingAct = ui->menuBar->addAction("Option");
	QAction* pSaveAct = ui->menuBar->addAction("Save");
	connect(pSettingAct, &QAction::triggered, this, &MainWindow::showOptionDlg);
	connect(pSaveAct, &QAction::triggered, this, &MainWindow::saveData);

	ui->tabWidget->addTab(new TextureTab(), "Texture");
	ui->tabWidget->addTab(new SubGraphTab(), "GraphGroup");

	connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::showOptionDlg()
{
	OptionDialog dlg;
	dlg.exec();
}

void MainWindow::onTabChanged(int idx)
{
	if (idx == idxSubGraph)
	{
		SubGraphTab* tab = qobject_cast<SubGraphTab*>(ui->tabWidget->currentWidget());
		tab->updateTextureName();
	}
}

void MainWindow::saveData()
{
	EditorData::instance()->save();
}
