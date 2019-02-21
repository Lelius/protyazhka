#ifndef COSTMENUFORMA_H
#define COSTMENUFORMA_H

#include <QWidget>
#include <QFile>
#include <QtSql>

namespace Ui {
class CostMenuForma;
}

class CostMenuForma : public QWidget
{
    Q_OBJECT

public:
    explicit CostMenuForma(QWidget *parent = nullptr);
    ~CostMenuForma();

signals:
    void signalChangeStackWidget(int index);

private slots:
    void on_pushButtonCostMenuExit_clicked();

    void on_pushButtonCostStock_clicked();

    void on_pushButtonCostWork_clicked();

private:
    Ui::CostMenuForma *ui;
};

#endif // COSTMENUFORMA_H
