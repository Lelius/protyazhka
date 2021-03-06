#include "stockinforma.h"
#include "ui_stockinforma.h"
#include "myqsqlquerymodel.h"

StockInForma::StockInForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockInForma)
{
    ui->setupUi(this);

    //создаём временную таблицу Temp
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);
    if (!query.exec("SELECT * FROM TempIn;")){
        qDebug() << "DBTempIn? No!";
        query.exec("CREATE TABLE TempIn(Номер INTEGER PRIMARY KEY NOT NULL, Тип, Размер, Количество, Метраж, Дата);");
    }
    if (query.exec("SELECT * FROM TempIn")){
        qDebug() << "DB TempIn? Yes!";
    }

    //обнуляем поля заполнения данных
    emit on_pushButtonInReset_clicked();
}

StockInForma::~StockInForma()
{
    //уничтожаем временную таблицу Temp
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);
    query.exec("DROP TABLE IF EXISTS TempIn;");

    delete ui;
}

void StockInForma::on_pushButtonBackStock_clicked()
{
    emit signalPushButtonBackStock(1);
}

void StockInForma::on_pushButtonInNext_clicked()
{
    if (ui->lineEditInSize->displayText() != "" && ui->lineEditInType->displayText() != "" && ui->lineEditInNumber->displayText() != ""){

        //В исходных числах меняем запятую на точку
        QString strSize = commaToPointInString(ui->lineEditInSize->displayText());
        QString strNumber = commaToPointInString(ui->lineEditInNumber->displayText());

        //Проверяем: а числа ли? Буквы преобразовываются в ноль
        //Числовой ноль тоже отбрасываем
        if (strSize.toDouble() == 0.0){
            ui->labelTextCostOfWork->clear();
            ui->labelTextCostOfWork->setText("В графах Размер и Количество разрешаются только числа больше нуля.");
            return;
        }
        if (strNumber.toDouble() == 0.0){
            ui->labelTextCostOfWork->clear();
            ui->labelTextCostOfWork->setText("В графах Размер и Количество разрешаются только числа больше нуля.");
            return;
        }

        QString stringQueryTemp = "INSERT INTO TempIn (Тип, Размер, Количество, Метраж, Дата) VALUES ('%1', '%2', '%3', '%4', strftime('%d-%m-%Y'));";
        QString stringQueryTempAll = stringQueryTemp.arg(ui->lineEditInType->displayText())
                .arg(strSize)
                .arg(strNumber)
                .arg(strSize.toDouble() * strNumber.toDouble());

        QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
        QSqlQuery query(dbStock);
        if (!query.exec(stringQueryTempAll))
            qDebug() << "Строка не вставилась";
        query.exec("SELECT * FROM TempIn;");
        MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
        model->setQuery(query);
        ui->tableViewInStock->setModel(model);
        QHeaderView *headerView = ui->tableViewInStock->horizontalHeader();
        headerView->setSectionResizeMode(QHeaderView::Stretch);

        clearLinesEdit();
    }
}

void StockInForma::on_pushButtonInReset_clicked()
{
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);
    if (!query.exec("DELETE FROM TempIn WHERE Номер = (SELECT MAX(Номер) FROM TempIn LIMIT 1);")){
        qDebug() << "Строка не удалена";
        qDebug() << query.lastError().text();
    }
    else {
        qDebug() << "Строка удалена.";
        qDebug() << query.lastError().text();
    }
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    query.exec("SELECT * FROM TempIn;");
    model->setQuery(query);
    ui->tableViewInStock->setModel(model);
    QHeaderView *headerView = ui->tableViewInStock->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    clearLinesEdit();
}

void StockInForma::on_pushButtonInAddStock_clicked()
{
    QSqlDatabase dbStock = QSqlDatabase::database("StockDB");
    QSqlQuery query(dbStock);

    if(!query.exec("INSERT INTO Stock ("
               "Тип, Размер, Количество, Метраж, Дата) "
               "SELECT "
               "Тип, Размер, Количество, Метраж, Дата "
               "FROM TempIn;")){
        qDebug() << "Ошибка переноса в основную таблицу!";
    }

    query.exec("DELETE FROM TempIn;");
    query.exec("SELECT * FROM TempIn;");
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    model->setQuery(query);
    ui->tableViewInStock->setModel(model);
    QHeaderView *headerView = ui->tableViewInStock->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    emit signalResetModelOnTableView();
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
    //и 100% установка фокуса ( фокус! (: )
    QTimer::singleShot(0, ui->lineEditInType, SLOT(setFocus()));
}

QString StockInForma::commaToPointInString(QString s)
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
