#ifndef COSTMENUFORMA_H
#define COSTMENUFORMA_H

#include <QWidget>

namespace Ui {
class CostMenuForma;
}

class CostMenuForma : public QWidget
{
    Q_OBJECT

public:
    explicit CostMenuForma(QWidget *parent = nullptr);
    ~CostMenuForma();

private:
    Ui::CostMenuForma *ui;
};

#endif // COSTMENUFORMA_H
