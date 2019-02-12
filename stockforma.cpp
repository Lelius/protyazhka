#include "stockforma.h"
#include "ui_stockforma.h"
#include "mainwindow.h"
#include "myqsqlquerymodel.h"

StockForma::StockForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockForma)
{
    ui->setupUi(this);

    //Нет файла базы? Создаём.
    QFile *fileDataBase = new QFile(this);
    fileDataBase->setFileName("stock.db");
    if (!fileDataBase->exists()) {
        fileDataBase->open(QIODevice::WriteOnly);
        fileDataBase->close();
    }

    //Проверяем наличие таблиц в файле БД. Нет? Создаём.
    QSqlDatabase *db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("stock.db");
    if (!db->open()) {
        qDebug() << db->lastError().text();
        qDebug() << "Open? No!";
    }
    QSqlQuery query;
    if (!query.exec("SELECT * FROM Stock;")) {
        qDebug() << "DB Stock? No!";
        query.exec("CREATE TABLE Stock (Номер INTEGER PRIMARY KEY NOT NULL, Тип , Размер , Количество , Метраж , Дата );");
    }
    if (query.exec("SELECT * FROM Stock;")) {
        qDebug() << "DB Stock? Yes!";
    }
    if (!query.exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? No!";
        query.exec("CREATE TABLE RateStock (Номер INTEGER PRIMARY KEY NOT NULL, Тип , Расценка , Дата );");
    }
    if (query.exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? Yes!";
    }

    checkBoxGroupState = true;
    ui->checkBoxGroup->setChecked(true);

    //Выводим нередактируемую таблицу Stock в tableViewStock
    //сортируя при этом по значению comboBoxSort
    resetModelOnTableView();
    ui->tableViewStock->verticalHeader()->setVisible(false); //убираем автоматическую нумерацию строк
}

StockForma::~StockForma()
{
    delete ui;
}

void StockForma::on_pushButtonReturn_clicked()
{
    emit signalChangeStackWidget(0);
}

void StockForma::resetModelOnTableView()
{
    QSqlQuery query;
    //обновление модели без группировки
    if (!checkBoxGroupState){
        query.exec("SELECT Тип, Размер, Количество, Метраж, Дата "
                   "FROM Stock "
                   "ORDER BY Тип, Размер;");
        MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
        model->setQuery(query);
        ui->tableViewStock->setModel(model);
        return;
    }
    //или с группировкой
    if (!query.exec("SELECT Тип , Размер , SUM(Количество) AS Количество, SUM(Метраж) AS Метраж, Дата "
                   "FROM Stock "
                   "GROUP BY Тип, Размер "
                   "ORDER BY Тип, Размер;"))
        qDebug() << query.lastError().text();
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    model->setQuery(query);
    ui->tableViewStock->setModel(model);
}

void StockForma::on_pushButtonStockIn_clicked()
{
    emit signalChangeStackWidget(3);
}

void StockForma::on_pushButtonStockOut_clicked()
{
    emit signalChangeStackWidget(4);
}

void StockForma::slotResetModelOnTableView()
{
    resetModelOnTableView();
}


void StockForma::on_checkBoxGroup_stateChanged(int arg1)
{
    if (arg1 == 0)
        checkBoxGroupState = false;
    else if (arg1 == 2)
        checkBoxGroupState = true;
    else
        return;
    resetModelOnTableView();
}
