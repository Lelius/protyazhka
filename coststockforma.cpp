#include "coststockforma.h"
#include "ui_coststockforma.h"

CostStockForma::CostStockForma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostStockForma)
{
    ui->setupUi(this);

    resetTableViewCostStockModel();
}

CostStockForma::~CostStockForma()
{
    delete ui;
}

void CostStockForma::resetTableViewCostStockModel()
{
    QSqlDatabase dbCostStock = QSqlDatabase::database("CostDB");
    QSqlQuery query(dbCostStock);
    if (!query.exec("SELECT * FROM CostStock;"))
        qDebug() << query.lastError().text();
    MyQSqlQueryModel *model = new MyQSqlQueryModel(this);
    model->setQuery(query);
    ui->tableViewCostStock->setModel(model);
    QHeaderView *header = ui->tableViewCostStock->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void CostStockForma::on_pushButtonExitCostStockForma_clicked()
{
    emit signalChangeStackWidget(5);
}
