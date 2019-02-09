#include "stockforma.h"
#include "ui_stockforma.h"
#include "mainwindow.h"
#include "myqsqlquerymodel.h"

StockForma::StockForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockForma)
{
    ui->setupUi(this);

    //comboBoxSort для сортировки таблицы Stock в tableViewStock
    QStringList stringListComboBoxSort;
    stringListComboBoxSort << "Номер по возрастанию" << "Номер по убыванию" << "Тип по возрастанию" << "Тип по убыванию" << "Размер по возрастанию" << "Размер по убыванию" << "Количество по возрастанию" << "Количество по убыванию" << "Метраж по возрастанию" << "Метраж по убыванию" << "Изменение по возрастанию" << "Изменение по убыванию";
    ui->comboBoxSort->addItems(stringListComboBoxSort);

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
        query.exec("CREATE TABLE Stock (Номер INTEGER PRIMARY KEY NOT NULL, Тип , Размер , Количество , Метраж , Изменение );");
    }
    if (query.exec("SELECT * FROM Stock;")) {
        qDebug() << "DB Stock? Yes!";
    }
    if (!query.exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? No!";
        query.exec("CREATE TABLE RateStock (Номер INTEGER PRIMARY KEY NOT NULL, Тип , Расценка , Изменение );");
    }
    if (query.exec("SELECT * FROM RateStock;")) {
        qDebug() << "DB RateStock? Yes!";
    }

//    query.exec("INSERT INTO Stock (Номер, Тип, Размер, Количество, Метраж, Изменение) VALUES ('5', 'Б22-2', '4.32', '10', '43.2', '27.11.18');");
//    if (query.lastError().isValid()) {
//        qDebug() << query.lastError();
//        qDebug() << "Insert not worked!";
//    } else {
//        qDebug() << "Insert worked!";
//    }

    //Выводим нередактируемую таблицу Stock в tableViewStock
    //сортируя при этом по значению comboBoxSort
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);

    model->setQuery(comboBoxSortCurrentIndexChanged(ui->comboBoxSort->currentIndex()));
    if (model->lastError().isValid()){
        qDebug() << model->lastError();
    }

    ui->tableViewStock->setModel(model);
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

void StockForma::on_comboBoxSort_currentIndexChanged(int index)
{
    emit signalComboBoxSort_currentIndexChanged(index);
}

QString StockForma::comboBoxSortCurrentIndexChanged(int index)
{
    QString *stringQuery = new QString("");
    QString *s1 = new QString("");
    QString *s2 = new QString("");
    switch(index)
    {
    case 0:{
        *s1 = "Номер";
        *s2 = "ASC";
        break;
    }
    case 1:{
        *s1 = "Номер";
        *s2 = "DESC";
        break;
    }
    case 2:{
        *s1 = "Тип";
        *s2 = "ASC";
        break;
    }
    case 3:{
        *s1 = "Тип";
        *s2 = "DESC";
        break;
    }
    case 4:{
        *s1 = "Размер";
        *s2 = "ASC";
        break;
    }
    case 5:{
        *s1 = "Размер";
        *s2 = "DESC";
        break;
    }
    case 6:{
        *s1 = "Количество";
        *s2 = "ASC";
        break;
    }
    case 7:{
        *s1 = "Количество";
        *s2 = "DESC";
        break;
    }
    case 8:{
        *s1 = "Метраж";
        *s2 = "ASC";
        break;
    }
    case 9:{
        *s1 = "Метраж";
        *s2 = "DESC";
        break;
    }
    case 10:{
        *s1 = "Изменение";
        *s2 = "ASC";
        break;
    }
    case 11:{
        *s1 = "Изменение";
        *s2 = "DESC";
        break;
    }
    }

    *stringQuery = "SELECT * FROM Stock ORDER BY " + *s1 + " " + *s2 + ";";

    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    model->setQuery(*stringQuery);
    StockForma::ui->tableViewStock->setModel(model);

    qDebug() << *stringQuery;

    return *stringQuery;
}

void StockForma::on_pushButtonStockIn_clicked()
{
    emit signalChangeStackWidget(3);
}

void StockForma::on_pushButtonStockOut_clicked()
{
    emit signalChangeStackWidget(4);
}
