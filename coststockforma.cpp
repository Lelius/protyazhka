#include "coststockforma.h"
#include "ui_coststockforma.h"

CostStockForma::CostStockForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostStockForma)
{
    ui->setupUi(this);
}

CostStockForma::~CostStockForma()
{
    delete ui;
}
