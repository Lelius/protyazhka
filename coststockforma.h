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

private:
    Ui::CostStockForma *ui;
};

#endif // COSTSTOCKFORMA_H
