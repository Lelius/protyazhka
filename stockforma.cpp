#include "stockforma.h"
#include "ui_stockforma.h"
#include "mainwindow.h"

StockForma::StockForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockForma)
{
    ui->setupUi(this);

    //Нет файла базы? Создаём.
    fileNameDataBase = QApplication::applicationDirPath() + "stock.db";
    fileDataBase.setFileName(fileNameDataBase);
    if (!fileDataBase.exists()) {
        fileDataBase.open(QIODevice::WriteOnly);
        fileDataBase.close();
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
