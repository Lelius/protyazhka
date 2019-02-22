#include "stockoutforma.h"
#include "ui_stockoutforma.h"
#include "myqsqlquerymodel.h"

StockOutForma::StockOutForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockOutForma)
{
    ui->setupUi(this);

    //создаём временную таблицу Temp
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);
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
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);
    query.exec("DROP TABLE IF EXISTS TempOut;");

    delete ui;
}

//заполнение TempOut
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
            ui->labelOutTextCostOfWork->setText("В графах Размер и Количество разрешаются только числа больше нуля.");
            return;
        }
        if (strNumber.toDouble() == 0.0){
            ui->labelOutTextCostOfWork->clear();
            ui->labelOutTextCostOfWork->setText("В графах Размер и Количество разрешаются только числа больше нуля.");
            return;
        }

        //Проверяем наличие в таблице профиля заданого типа и размера
        //и его достаточного количества
        QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
        QSqlQuery query(dbStock);
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
            if ((numStock - numTemp) == 0)
                strAv = "Нет";
        }

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
        QHeaderView *headerView = ui->tableViewOutStock->horizontalHeader();
        headerView->setSectionResizeMode(QHeaderView::Stretch);
        clearLinesEdit();
    }
}

//удаление нижней строки в TempOut
void StockOutForma::on_pushButtonDelTempOut_clicked()
{
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);
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
    QHeaderView *headerView = ui->tableViewOutStock->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    clearLinesEdit();
}

//удаление из Stock на основе данных в TempOut
void StockOutForma::on_pushButtonOutStock_clicked()
{
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);
    //выбираем строки в TempOut того что в наличии
    if (!query.exec("SELECT Номер, Тип, Размер, Количество "
                    "FROM TempOut "
                    "WHERE Наличие = 'Есть';"))
        qDebug() << "Ошибка запроса 1" + query.lastError().text();
    QString strType, strSize, strNumber;
    int numb;
    //перебираем эти строки
    while (query.next()){
        QSqlRecord rec = query.record();
        strNumber = query.value(rec.indexOf("Номер")).toString();
        strType = query.value(rec.indexOf("Тип")).toString();
        strSize = query.value(rec.indexOf("Размер")).toString();
        numb = query.value(rec.indexOf("Количество")).toInt();

        QSqlQuery q(dbStock);
        QSqlRecord r;
        QString nn;
        int n;
        //пока есть что сдавать
        while (numb > 0){
            //ищем строку в Stock с самой древней датой
            if (!q.exec("SELECT Номер, Количество FROM Stock WHERE Тип = '" + strType + "' AND Размер = '" + strSize + "' AND Дата = (SELECT MIN(Дата) AS Дата FROM Stock WHERE Тип = '" + strType + "' AND Размер = '" + strSize + "');"))
                qDebug() << "Ошибка запроса 2" + q.lastError().text();
            q.next();
            r = q.record();
            nn = q.value(r.indexOf("Номер")).toString();
            n = q.value(r.indexOf("Количество")).toInt();
            //если в наличии меньше удаляем строку
            //и получаем разницу для следующей строки
            if (numb >= n){
                if (!q.exec("DELETE FROM Stock "
                       "WHERE Номер = '" + nn + "';"))
                    qDebug() << "Ошибка запроса 3" + q.lastError().text();
                numb -= n;
            }
            //если в наличии больше (равно) списываем разницу
            else {
                int i;
                if ((i = n - numb) < 0)
                    qDebug() << "Попытка введения в таблицу отрицательного числа";
                if (!q.exec("UPDATE Stock SET Количество = '" + QString::number(i) + "' WHERE Номер = '" + nn + "';"))
                    qDebug() << "Ошибка запроса 4" + q.lastError().text();
                numb = 0;
            }
        }
        //удаляем обработанную выдачу из TempOut
        if (!query.exec("DELETE FROM TempOut WHERE Номер = '" + strNumber + "';"))
            qDebug() << "Ошибка запроса 5" + query.lastError().text();
    }
    //перерисовываем TempOut с тем что осталось
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    query.exec("SELECT * FROM TempOut;");
    model->setQuery(query);
    ui->tableViewOutStock->setModel(model);
    QHeaderView *headerView = ui->tableViewOutStock->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    //и перезагружаем новую модель Stock
    emit signalResetModelOnTableView();
}

void StockOutForma::on_pushButtonStockOutExit_clicked()
{
    emit signalPushButtonStockOutExit(1);
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
