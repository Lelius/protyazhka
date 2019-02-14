#include "stockoutforma.h"
#include "ui_stockoutforma.h"
#include "myqsqlquerymodel.h"

StockOutForma::StockOutForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockOutForma)
{
    ui->setupUi(this);

    //создаём временную таблицу Temp
    QSqlQuery query;
    if (!query.exec("SELECT * FROM TempOut;")){
        qDebug() << "DBTempOut? No!";
        query.exec("CREATE TABLE TempOut(Номер INTEGER PRIMARY KEY NOT NULL, Тип, Размер, Количество, Метраж, Наличие);");
    }
    if (query.exec("SELECT * FROM TempOut")){
        qDebug() << "DB TempOut? Yes!";
    }

    //обнуляем поля заполнения данных
    emit on_pushButtonDelTempOut_clicked();
}

StockOutForma::~StockOutForma()
{
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS TempOut;");

    delete ui;
}

void StockOutForma::on_pushButtonAddTempOut_clicked()
{
    if (ui->lineEditOutSize->displayText() != "" && ui->lineEditOutType->displayText() != "" && ui->lineEditOutNumber->displayText() != ""){

        //В исходных числах меняем запятую на точку
        QString strSize = commaToPointOutString(ui->lineEditOutSize->displayText());
        QString strNumber = commaToPointOutString(ui->lineEditOutNumber->displayText());
        QString strAv = "Нет";

        //Проверяем: а числа ли? Буквы преобразовываются в ноль
        //Числовой ноль тоже отбрасываем
        if (strSize.toDouble() == 0.0){
            ui->labelOutTextCostOfWork->clear();
            ui->labelOutTextCostOfWork->setText("В графах Размер и Количество разрешаются только числа.");
            return;
        }
        if (strNumber.toDouble() == 0.0){
            ui->labelOutTextCostOfWork->clear();
            ui->labelOutTextCostOfWork->setText("В графах Размер и Количество разрешаются только числа.");
            return;
        }

        //Проверяем наличие в таблице профиля заданого типа и размера
        //и его достаточного количества
        QSqlQuery query;
        query.exec("SELECT Тип, Размер "
                   "FROM Stock "
                   "WHERE Тип = '" + ui->lineEditOutType->displayText() + "'"
                   "AND Размер = '" + strSize + "';");
        if (query.next()){
            strAv = "Есть";
            if (!query.exec("SELECT SUM(Количество) AS Количество "
                            "FROM Stock "
                            "WHERE Тип = '" + ui->lineEditOutType->displayText() + "' "
                            "AND Размер = '" + strSize + "';"))
                qDebug() << "Ошибка запроса " + query.lastError().text();

            //читаем результат выборки
            QSqlRecord rec = query.record();
            int numStock, numTemp;
            query.next();
            numStock = query.value(rec.indexOf("Количество")).toInt();
            qDebug()<< "Количество в Stock = " + QString::number(numStock);
            //и во временной посмотрим
            if (!query.exec("SELECT SUM(Количество) AS Количество "
                            "FROM TempOut "
                            "WHERE Тип = '" + ui->lineEditOutType->displayText() + "' "
                            "AND Размер = '" + strSize + "';"))
                qDebug() << "Ошибка запроса " + query.lastError().text();
            rec = query.record();
            query.next();
            numTemp = query.value(rec.indexOf("Количество")).toInt();
            qDebug() << "Количество в TempOut = " + QString::number(numTemp);
            if (strNumber.toInt() > (numStock - numTemp))
                strAv = "Меньше";
        }
// ?????

        QString stringQueryTemp = "INSERT INTO TempOut (Тип, Размер, Количество, Метраж , Наличие ) VALUES ('%1', '%2', '%3', '%4', '%5');";
        QString stringQueryTempAll = stringQueryTemp.arg(ui->lineEditOutType->displayText())
                .arg(strSize)
                .arg(strNumber)
                .arg(strSize.toDouble() * strNumber.toDouble())
                .arg(strAv);

        if (!query.exec(stringQueryTempAll))
            qDebug() << "Строка не вставилась";
        query.exec("SELECT * FROM TempOut;");
        MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
        model->setQuery(query);
        ui->tableViewOutStock->setModel(model);

        clearLinesEdit();
    }
}

void StockOutForma::on_pushButtonDelTempOut_clicked()
{
    QSqlQuery query;
    if (!query.exec("DELETE FROM TempOut WHERE Номер = (SELECT MAX(Номер) FROM TempOut LIMIT 1);")){
        qDebug() << "Строка не удалена";
        qDebug() << query.lastError().text();
    }
    else {
        qDebug() << "Строка удалена.";
        qDebug() << query.lastError().text();
    }
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    query.exec("SELECT * FROM TempOut;");
    model->setQuery(query);
    ui->tableViewOutStock->setModel(model);
    clearLinesEdit();
}

void StockOutForma::on_pushButtonStockOut_clicked()
{
    emit signalPushButtonStockOut(1);
}

void StockOutForma::clearLinesEdit()
{
    ui->lineEditOutType->setText("");
    ui->lineEditOutSize->setText("");
    ui->lineEditOutNumber->setText("");
    //и 100% установка фокуса ( фокус! (: )
    QTimer::singleShot(0, ui->lineEditOutType, SLOT(setFocus()));
}

QString StockOutForma::commaToPointOutString(QString s)
{
    QString str = "";

    for (int i = 0; i < s.length(); i++){
        if (s.at(i) == ',')
            str += '.';
        else
            str += s.at(i);
    }

    return str;
}

void StockOutForma::on_lineEditOutType_returnPressed()
{
    ui->lineEditOutSize->setFocus();
}

void StockOutForma::on_lineEditOutSize_returnPressed()
{
    ui->lineEditOutNumber->setFocus();
}

void StockOutForma::on_lineEditOutNumber_returnPressed()
{
    ui->lineEditOutType->setFocus();
}




