#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>

#include "stockforma.h"
#include "mainmenuforma.h"
#include "exitforma.h"
#include "stockinforma.h"
#include "stockoutforma.h"
#include "costmenuforma.h"
#include "coststockforma.h"
#include "costworkforma.h"

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
};

#endif // MAINWINDOW_H
