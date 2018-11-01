#include "exitforma.h"
#include "ui_exitforma.h"

ExitForma::ExitForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExitForma)
{
    ui->setupUi(this);
}

ExitForma::~ExitForma()
{
    delete ui;
}

void ExitForma::on_pushButtonYes_clicked()
{
    emit signalChangeStackWidget(-2);
}

void ExitForma::on_pushButtonNo_clicked()
{
    emit signalChangeStackWidget(0);
}
