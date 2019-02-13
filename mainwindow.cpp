#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Делаем окно в два раза меньше разрешения рабочего стола
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry(desktop->primaryScreen());
    MainWindow::resize(rect.width()/2, rect.height()/2);

    //Инициализируем виджеты-формы для QStackedWidget
    StockForma *stockForma = new StockForma(this);
    MainMenuForma *mainMenuForma = new MainMenuForma(this);
    ExitForma *exitForma = new ExitForma(this);
    StockInForma *stockInForma = new StockInForma(this);
    StockOutForma *stockOutForma = new StockOutForma(this);

    //Назначаем индексы страниц для QStackedWidget
    ui->stackedWidget->insertWidget(0, mainMenuForma);
    ui->stackedWidget->insertWidget(1, stockForma);
    ui->stackedWidget->insertWidget(2, exitForma);
    ui->stackedWidget->insertWidget(3, stockInForma);
    ui->stackedWidget->insertWidget(4, stockOutForma);
    ui->stackedWidget->setCurrentIndex(0);

    connect(stockForma, &StockForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(mainMenuForma, &MainMenuForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(exitForma, &ExitForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(stockInForma, &StockInForma::signalPushButtonBackStock, this, &MainWindow::slotChangeStackWidget);
    connect(stockOutForma, &StockOutForma::signalPushButtonStockOut, this, &MainWindow::slotChangeStackWidget);
    connect(stockInForma, &StockInForma::signalResetModelOnTableView, stockForma, &StockForma::slotResetModelOnTableView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotChangeStackWidget(int index)
{
    if (index == -2)
        this->close();
    ui->stackedWidget->setCurrentIndex(index);
}
