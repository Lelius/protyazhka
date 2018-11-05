#ifndef STOCKOUTFORMA_H
#define STOCKOUTFORMA_H

#include <QWidget>

namespace Ui {
class StockOutForma;
}

class StockOutForma : public QWidget
{
    Q_OBJECT

public:
    explicit StockOutForma(QWidget *parent = nullptr);
    ~StockOutForma();

signals:
    void signalPushButtonStockOut(int index);

private slots:
    void on_pushButtonStockOut_clicked();

private:
    Ui::StockOutForma *ui;
};

#endif // STOCKOUTFORMA_H
