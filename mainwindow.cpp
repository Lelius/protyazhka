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
    stockForma = new StockForma(this);
    mainMenuForma = new MainMenuForma(this);
    exitForma = new ExitForma(this);

    //Назначаем индексы страниц для QStackedWidget
    ui->stackedWidget->insertWidget(0, mainMenuForma);
    ui->stackedWidget->insertWidget(1, stockForma);
    ui->stackedWidget->insertWidget(2, exitForma);
    ui->stackedWidget->setCurrentIndex(0);

    connect(stockForma, &StockForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(mainMenuForma, &MainMenuForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(exitForma, &ExitForma::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
    connect(stockForma, &StockForma::signalComboBoxSort_currentIndexChanged, stockForma, &StockForma::comboBoxSortCurrentIndexChanged);
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
