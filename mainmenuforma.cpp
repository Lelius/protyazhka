#include "mainmenuforma.h"
#include "ui_mainmenuforma.h"

MainMenuForma::MainMenuForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuForma)
{
    ui->setupUi(this);
}

MainMenuForma::~MainMenuForma()
{
    delete ui;
}

void MainMenuForma::on_pushButtonStock_clicked()
{
    emit signalChangeStackWidget(1);
}

void MainMenuForma::on_pushButtonExit_clicked()
{
    emit signalChangeStackWidget(2);
}

void MainMenuForma::on_pushButtonCost_clicked()
{
    emit signalChangeStackWidget(5);
}
