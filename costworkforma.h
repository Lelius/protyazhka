#ifndef COSTWORKFORMA_H
#define COSTWORKFORMA_H

#include <QWidget>
#include <QtSql>
#include "myqsqlquerymodel.h"

namespace Ui {
class CostWorkForma;
}

class CostWorkForma : public QWidget
{
    Q_OBJECT

public:
    explicit CostWorkForma(QWidget *parent = nullptr);
    ~CostWorkForma();

signals:
    void signalChangeStackWidget(int index);

private slots:
    void on_pushButtonExitCostWorkForma_clicked();

    void resetTableViewCostWorkModel();

private:
    Ui::CostWorkForma *ui;
};

#endif // COSTWORKFORMA_H
