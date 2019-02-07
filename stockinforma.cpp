#include "stockinforma.h"
#include "ui_stockinforma.h"
#include "myqsqlquerymodel.h"

StockInForma::StockInForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockInForma)
{
    ui->setupUi(this);

    //создаём временную таблицу Temp
    QSqlQuery query;
    if (!query.exec("SELECT * FROM Temp;")){
        qDebug() << "DBTemp? No!";
        query.exec("CREATE TABLE Temp(Номер INTEGER PRIMARY KEY NOT NULL, Тип, Размер, Количество, Метраж, Изменение);");
    }
    if (query.exec("SELECT * FROM Temp")){
        qDebug() << "DB Temp? Yes!";
    }

    //обнуляем поля заполнения данных
    clearLinesEdit();
}

StockInForma::~StockInForma()
{
    //уничтожаем временную таблицу Temp
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS Temp;");

    delete ui;
}

void StockInForma::on_pushButtonBackStock_clicked()
{
    emit signalPushButtonBackStock(1);
}

void StockInForma::on_pushButtonInNext_clicked()
{
    if (ui->lineEditInSize->displayText() != "" && ui->lineEditInType->displayText() != "" && ui->lineEditInNumber->displayText() != ""){
        QDate currentDate = QDate::currentDate();
        QString stringCurrentDate = QString::number(currentDate.day()) + "." + QString::number(currentDate.month()) + "." + QString::number(currentDate.year() % 100);

        QString stringQueryTemp = "INSERT INTO Temp (Тип, Размер, Количество, Метраж, Изменение) VALUES ('%1', '%2', '%3', '%4', '%5');";
        QString stringQueryTempAll = stringQueryTemp.arg(ui->lineEditInType->displayText())
                .arg(ui->lineEditInSize->displayText())
                .arg(ui->lineEditInNumber->displayText())
                .arg(ui->lineEditInSize->displayText().toDouble() * ui->lineEditInNumber->displayText().toDouble())
                .arg(stringCurrentDate);

        QSqlQuery query;
        if (!query.exec(stringQueryTempAll))
            qDebug() << "Строка не вставилась";
        query.exec("SELECT * FROM Temp;");
        MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
        model->setQuery(query);
        ui->tableViewInStock->setModel(model);

        clearLinesEdit();
    }
}

void StockInForma::on_pushButtonInReset_clicked()
{
    QSqlQuery query;
    if (!query.exec("DELETE FROM Temp WHERE Номер = (SELECT MAX(Номер) FROM Temp LIMIT 1);")){
        qDebug() << "Строка не удалена";
        qDebug() << query.lastError().text();
    }
    else {
        qDebug() << "Строка удалена.";
        qDebug() << query.lastError().text();
    }
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    query.exec("SELECT * FROM Temp;");
    model->setQuery(query);
    ui->tableViewInStock->setModel(model);
    clearLinesEdit();
}

void StockInForma::on_pushButtonInAddStock_clicked()
{

}

void StockInForma::on_lineEditInType_returnPressed()
{
    ui->lineEditInSize->setFocus();
}

void StockInForma::on_lineEditInSize_returnPressed()
{
    ui->lineEditInNumber->setFocus();
}

void StockInForma::on_lineEditInNumber_returnPressed()
{
    ui->lineEditInType->setFocus();
}

void StockInForma::clearLinesEdit()
{
    ui->lineEditInType->setText("");
    ui->lineEditInSize->setText("");
    ui->lineEditInNumber->setText("");
    ui->lineEditInType->setFocus();
}
