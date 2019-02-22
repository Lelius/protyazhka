#include "costworkforma.h"
#include "ui_costworkforma.h"

CostWorkForma::CostWorkForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostWorkForma)
{
    ui->setupUi(this);

    resetTableViewCostWorkModel();
}

CostWorkForma::~CostWorkForma()
{
    delete ui;
}

void CostWorkForma::resetTableViewCostWorkModel()
{
    QSqlDatabase dbCostWork = QSqlDatabase::database("CostDB");
    QSqlQuery query(dbCostWork);
    if (!query.exec("SELECT * FROM CostWork;"))
        qDebug() << query.lastError().text();
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    model->setQuery(query);
    ui->tableViewCostWork->setModel(model);
    QHeaderView *header = ui->tableViewCostWork->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void CostWorkForma::on_pushButtonExitCostWorkForma_clicked()
{
    emit signalChangeStackWidget(5);
}


