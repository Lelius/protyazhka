#ifndef COSTSTOCKFORMA_H
#define COSTSTOCKFORMA_H

#include <QWidget>
#include <QtSql>
#include "myqsqlquerymodel.h"

namespace Ui {
class CostStockForma;
}

class CostStockForma : public QWidget
{
    Q_OBJECT

public:
    explicit CostStockForma(QWidget *parent = nullptr);
    ~CostStockForma();

signals:
    void signalChangeStackWidget(int index);

private slots:
    void on_pushButtonExitCostStockForma_clicked();

    void resetTableViewCostStockModel();

private:
    Ui::CostStockForma *ui;
};

#endif // COSTSTOCKFORMA_H
