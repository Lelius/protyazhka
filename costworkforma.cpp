#include "costworkforma.h"
#include "ui_costworkforma.h"

CostWorkForma::CostWorkForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostWorkForma)
{
    ui->setupUi(this);
}

CostWorkForma::~CostWorkForma()
{
    delete ui;
}
