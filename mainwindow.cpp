#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Делаем окно в два раза меньше разрешения рабочего стола
    QScreen *scr = QGuiApplication::primaryScreen();
    QRect rect = scr->geometry();
    MainWindow::resize(rect.width()/2, rect.height()/2);

    //Инициализируем виджеты-формы для QStackedWidget
    StockForma *stockForma = new StockForma(this);
    MainMenuForma *mainMenuForma = new MainMenuForma(this);
    ExitForma *exitForma = new ExitForma(this);
    StockInForma *stockInForma = new StockInForma(this);
    StockOutForma *stockOutForma = new StockOutForma(this);
    CostMenuForma *costMenuForma = new CostMenuForma(this);
    CostStockForma *costStockForma = new CostStockForma(this);
    CostWorkForma *costWorkForma = new CostWorkForma(this);

    //Назначаем индексы страниц для QStackedWidget
    ui->stackedWidget->insertWidget(0, mainMenuForma);
    ui->stackedWidget->insertWidget(1, stockForma);
    ui->stackedWidget->insertWidget(2, exitForma);
    ui->stackedWidget->insertWidget(3, stockInForma);
    ui->stackedWidget->insertWidget(4, stockOutForma);
    ui->stackedWidget->insertWidget(5, costMenuForma);
    ui->stackedWidget->insertWidget(6, costStockForma);
    ui->stackedWidget->insertWidget(7, costWorkForma);
    ui->stackedWidget->setCurrentIndex(0);

    connect(stockForma, &StockForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(mainMenuForma, &MainMenuForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(exitForma, &ExitForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(stockInForma, &StockInForma::signalPushButtonBackStock, this, &MainWindow::slotChangeStackWidget);
    connect(stockOutForma, &StockOutForma::signalPushButtonStockOutExit, this, &MainWindow::slotChangeStackWidget);
    connect(stockInForma, &StockInForma::signalResetModelOnTableView, stockForma, &StockForma::slotResetModelOnTableView);
    connect(stockOutForma, &StockOutForma::signalResetModelOnTableView, stockForma, &StockForma::slotResetModelOnTableView);
    connect(costMenuForma, &CostMenuForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(costStockForma, &CostStockForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(costWorkForma, &CostWorkForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
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
