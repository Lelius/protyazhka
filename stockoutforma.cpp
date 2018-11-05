#include "stockoutforma.h"
#include "ui_stockoutforma.h"

StockOutForma::StockOutForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockOutForma)
{
    ui->setupUi(this);
}

StockOutForma::~StockOutForma()
{
    delete ui;
}

void StockOutForma::on_pushButtonStockOut_clicked()
{
    emit signalPushButtonStockOut(1);
}
