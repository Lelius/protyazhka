#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stockforma.h"
#include "mainmenuforma.h"
#include "exitforma.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotChangeStackWidget(int index);

private:
    Ui::MainWindow *ui;
    StockForma *stockForma;
    MainMenuForma *mainMenuForma;
    ExitForma *exitForma;
};

#endif // MAINWINDOW_H
