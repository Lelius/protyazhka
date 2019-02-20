#include "costmenuforma.h"
#include "ui_costmenuforma.h"

CostMenuForma::CostMenuForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostMenuForma)
{
    ui->setupUi(this);
}

CostMenuForma::~CostMenuForma()
{
    delete ui;
}

void CostMenuForma::on_pushButtonCostMenuExit_clicked()
{
    emit signalChangeStackWidget(0);
}

void CostMenuForma::on_pushButtonCostStock_clicked()
{
    emit signalChangeStackWidget(6);
}

void CostMenuForma::on_pushButtonCostWork_clicked()
{
    emit signalChangeStackWidget(7);
}
