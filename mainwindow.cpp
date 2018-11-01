#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stockForma = new StockForma();
    mainMenuForma = new MainMenuForma();

    ui->stackedWidget->insertWidget(0, mainMenuForma);
    ui->stackedWidget->insertWidget(1, stockForma);
    ui->stackedWidget->setCurrentIndex(0);

    connect(stockForma, &StockForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(mainMenuForma, &MainMenuForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotChangeStackWidget(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
