#ifndef COSTWORKFORMA_H
#define COSTWORKFORMA_H

#include <QWidget>

namespace Ui {
class CostWorkForma;
}

class CostWorkForma : public QWidget
{
    Q_OBJECT

public:
    explicit CostWorkForma(QWidget *parent = nullptr);
    ~CostWorkForma();

private:
    Ui::CostWorkForma *ui;
};

#endif // COSTWORKFORMA_H
