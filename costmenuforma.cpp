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
