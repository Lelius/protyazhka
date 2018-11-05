#include "stockinforma.h"
#include "ui_stockinforma.h"

StockInForma::StockInForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockInForma)
{
    ui->setupUi(this);
}

StockInForma::~StockInForma()
{
    delete ui;
}

void StockInForma::on_pushButtonBackStock_clicked()
{
    emit signalPushButtonBackStock(1);
}
