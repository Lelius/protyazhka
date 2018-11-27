#include "stockinforma.h"
#include "ui_stockinforma.h"
#include "myqsqlquerymodel.h"

StockInForma::StockInForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockInForma)
{
    ui->setupUi(this);

    //переподключаемся к базе данных
    fileNameDataBase = "stock.db";
    dbTemp = new QSqlDatabase();
    *dbTemp = QSqlDatabase::addDatabase("QSQLITE");
    dbTemp->setDatabaseName(fileNameDataBase);
    if (!dbTemp->open()){
        qDebug() << dbTemp->lastError();
    }

    //создаём временную таблицу Temp
    queryTemp = new QSqlQuery(*dbTemp);
    if (!queryTemp->exec("SELECT * FROM Temp;")){
        qDebug() << "DBTemp? No!";
        queryTemp->exec("CREATE TABLE Temp(Номер, Тип, Размер, Количество, Метраж, Изменение);");
    }
    if (queryTemp->exec("SELECT * FROM Temp")){
        qDebug() << "DB Temp? Yes!";
    }

    //создаём модель представления
    queryModelTemp = new MyQSqlQueryModel;
    queryModelTemp->setQuery(*queryTemp);
    if (queryModelTemp->lastError().isValid()){
        qDebug() << queryModelTemp->lastError();
    }

    //визуализация модели
    ui->tableViewInStock->setModel(queryModelTemp);
    ui->tableViewInStock->verticalHeader()->setVisible(false);
    ui->tableViewInStock->show();

    //обнуляем поля заполнения данных
    ui->lineEditInType->setText("0");
    ui->lineEditInSize->setText("0");
    ui->lineEditInNumber->setText("0");
}

StockInForma::~StockInForma()
{
    //уничтожаем временную таблицу Temp
    queryTemp->exec("DROP TABLE IF EXISTS Temp;");

    delete ui;
}

void StockInForma::on_pushButtonBackStock_clicked()
{
    emit signalPushButtonBackStock(1);
}

void StockInForma::on_pushButtonInNext_clicked()
{
    if (ui->lineEditInSize->displayText() != "0" && ui->lineEditInType->displayText() != "0" && ui->lineEditInNumber->displayText() != "0"){
        QDate currentDate = QDate::currentDate();
        QString stringCurrentDate = QString::number(currentDate.day()) + "." + QString::number(currentDate.month()) + "." + QString::number(currentDate.year() % 100);

        QString stringQueryTemp = "INSERT INTO Temp (Номер, Тип, Размер, Количество, Метраж, Изменение) VALUES ('%1', '%2', '%3', '%4', '%5', '%6');";
        QString stringQueryTempAll = stringQueryTemp.arg("1")
                .arg(ui->lineEditInType->displayText())
                .arg(ui->lineEditInSize->displayText())
                .arg(ui->lineEditInNumber->displayText())
                .arg(ui->lineEditInSize->displayText().toDouble() * ui->lineEditInNumber->displayText().toDouble())
                .arg(stringCurrentDate);
        queryTemp->exec(stringQueryTempAll);

        queryTemp->exec("SELECT * FROM Temp;");
        queryModelTemp->setQuery(*queryTemp);
        ui->tableViewInStock->setModel(queryModelTemp);
    }
}

void StockInForma::on_pushButtonInReset_clicked()
{

}

void StockInForma::on_pushButtonInAddStock_clicked()
{

}
