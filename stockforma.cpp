#include "stockforma.h"
#include "ui_stockforma.h"
#include "mainwindow.h"

StockForma::StockForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockForma)
{
    ui->setupUi(this);

    //Нет файла базы? Создаём.
    fileNameDataBase = "stock.db";
    QFile *fileDataBase = new QFile(this);
    fileDataBase->setFileName(fileNameDataBase);
    if (!fileDataBase->exists()) {
        fileDataBase->open(QIODevice::WriteOnly);
        fileDataBase->close();
    }

    //Проверяем наличие таблиц в файле БД. Нет? Создаём.
    QSqlDatabase *db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName(fileNameDataBase);
    if (!db->open()) {
        qDebug() << db->lastError().text();
        qDebug() << "Open? No!";
    }
    QSqlQuery *query = new QSqlQuery();
    if (!query->exec("SELECT * FROM Stock;")) {
        qDebug() << "DB Stock? No!";
        query->exec("CREATE TABLE Stock (Номер , Тип , Размер , Количество , Метраж , Изменили );");
    }
    if (query->exec("SELECT * FROM Stock;")) {
        qDebug() << "DB Stock? Yes!";
    }
    if (!query->exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? No!";
        query->exec("CREATE TABLE RateStock (Номер , Тип , Расценка , Изменили );");
    }
    if (query->exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? Yes!";
    }

    query->exec("INSERT INTO Stock (Номер, Тип, Размер, Количество, Метраж, Изменили) VALUES ('1', 'А38', '6.02', '4', '24.08', '02.11.18');");
    if (query->lastError().isValid()) {
        qDebug() << query->lastError();
        qDebug() << "Insert not worked!";
    } else {
        qDebug() << "Insert worked!";
    }

    //Выводим нередактируемую таблицу Stock в tableViewStock
    QSqlQueryModel *querymodel = new QSqlQueryModel(this);
    querymodel->setQuery("SELECT * From Stock;");
    if (querymodel->lastError().isValid()){
        qDebug() << querymodel->lastError();
    }

    ui->tableViewStock->setModel(querymodel);
    ui->tableViewStock->verticalHeader()->setVisible(false); //убираем автоматическую нумерацию строк
    ui->tableViewStock->show();
}

StockForma::~StockForma()
{
    delete ui;
}

void StockForma::on_pushButtonReturn_clicked()
{
    emit signalChangeStackWidget(0);
}
