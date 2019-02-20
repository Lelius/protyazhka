#ifndef COSTSTOCKFORMA_H
#define COSTSTOCKFORMA_H

#include <QWidget>

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

private:
    Ui::CostStockForma *ui;
};

#endif // COSTSTOCKFORMA_H
