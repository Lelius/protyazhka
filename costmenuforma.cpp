#include "costmenuforma.h"
#include "ui_costmenuforma.h"

CostMenuForma::CostMenuForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostMenuForma)
{
    ui->setupUi(this);

    //проверяем наличие файла базы расценок
    //нет? создаём!
    QFile *fileDataBase = new QFile(this);
    fileDataBase->setFileName("cost.db");
    if (!fileDataBase->exists()) {
        fileDataBase->open(QIODevice::WriteOnly);
        fileDataBase->close();
    }

    //проверяем наличие таблиц в базе
    //нет? создаём!
    QSqlDatabase *dbCost = new QSqlDatabase();
    *dbCost = QSqlDatabase::addDatabase("QSQLITE", "CostDB");
    dbCost->setDatabaseName("cost.db");
    if (!dbCost->open()){
        qDebug() << dbCost->lastError().text();
        qDebug() << "cost.db не открыт!";
    }
    QSqlQuery query (*dbCost);
    if (!query.exec("SELECT * FROM CostStock;")){
        qDebug() << "Нет таблицы CostStock.";
        query.exec("CREATE TABLE CostStock (Номер INTEGER PRIMARY KEY NOT NULL, Профиль, Расценка, Дата);");
    }
    if (query.exec("SELECT * FROM CostStock")){
        qDebug() << "Таблица CostStock есть!";
    }
    if (!query.exec("SELECT * FROM CostWork;")){
        qDebug() << "Нет таблицы CostWork.";
        query.exec("CREATE TABLE CostWork (Номер INTEGER PRIMARY KEY NOT NULL, Профиль, Должность, Расценка, Дата);");
    }
    if (query.exec("SELECT * FROM CostWork")){
        qDebug() << "Таблица CostWork есть!";
    }
}

CostMenuForma::~CostMenuForma()
{
    delete ui;
}

void CostMenuForma::on_pushButtonCostMenuExit_clicked()
{
    emit signalChangeStackWidget(0);
}

void CostMenuForma::on_pushButtonCostStock_clicked()
{
    emit signalChangeStackWidget(6);
}

void CostMenuForma::on_pushButtonCostWork_clicked()
{
    emit signalChangeStackWidget(7);
}
