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
    fileDataBase.setFileName(fileNameDataBase);
    if (!fileDataBase.exists()) {
        fileDataBase.open(QIODevice::WriteOnly);
        fileDataBase.close();
    }

    //Проверяем наличие таблиц в файле БД. Нет? Создаём.
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileNameDataBase);
    if (!db.open()) {
        qDebug() << db.lastError().text();
        qDebug() << "Open? No!";
    }
    QSqlQuery query;
    if (!query.exec("SELECT * FROM Stock;")) {
        qDebug() << "DB Stock? No!";
        query.exec("CREATE TABLE Stock (№ INTEGER PRIMARY KEY NOT NULL, Тип VARCHAR(4), Размер VARCHAR(5), Количество VARCHAR(5), Метраж VARCHAR(8), Изменили VARCHAR(8));");
    }
    if (query.exec("SELECT * FROM Stock;")) {
        qDebug() << "DB Stock? Yes!";
    }
    if (!query.exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? No!";
        query.exec("CREATE TABLE RateStock (№ INTEGER PRIMARY KEY NOT NULL, Тип VARCHAR(4), Расценка VARCHAR(10), Изменили VARCHAR(8));");
    }
    if (query.exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? Yes!";
    }
}

StockForma::~StockForma()
{
    delete ui;
}

void StockForma::on_pushButtonReturn_clicked()
{
    emit signalChangeStackWidget(0);
}
