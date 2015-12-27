#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	bool eventFilter(QObject* o, QEvent* e) override;

private slots:
	void showOptionDlg();
	void onTabChanged(int idx);
	void saveData();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
