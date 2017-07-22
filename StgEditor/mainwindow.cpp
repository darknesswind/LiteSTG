#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texturetab.h"
#include "subgraphtab.h"
#include "optiondialog.h"
#include "editordata.h"
#include "bullettab.h"
#include <QMouseEvent>


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
	ui->tabWidget->addTab(new BulletTab(), "Bullet");

	connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
	ui->tabWidget->tabBar()->installEventFilter(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::eventFilter(QObject* o, QEvent* e)
{
	if (o == ui->tabWidget->tabBar() && e->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* pEvent = static_cast<QMouseEvent*>(e);
		if (pEvent->button() == Qt::LeftButton)
		{
			TabBase* tab = dynamic_cast<TabBase*>(ui->tabWidget->currentWidget());
			if (tab)
			{
				if (!tab->commitCache())
				{
					e->accept();
					return true;
				}
			}
		}
	}
	return QMainWindow::eventFilter(o, e);
}

void MainWindow::showOptionDlg()
{
	OptionDialog dlg;
	dlg.exec();
}

void MainWindow::onTabChanged(int)
{
	TabBase* tab = dynamic_cast<TabBase*>(ui->tabWidget->currentWidget());
	if (tab)
		tab->enterTab();
}

void MainWindow::saveData()
{
	bool bDoSave = true;
	TabBase* tab = dynamic_cast<TabBase*>(ui->tabWidget->currentWidget());
	if (tab)
		bDoSave = tab->commitCache();

	if (bDoSave)
		EditorData::instance()->save();
}
