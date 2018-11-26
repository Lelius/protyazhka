#ifndef STOCKINFORMA_H
#define STOCKINFORMA_H

#include <QWidget>

namespace Ui {
class StockInForma;
}

class StockInForma : public QWidget
{
    Q_OBJECT

public:
    explicit StockInForma(QWidget *parent = nullptr);
    ~StockInForma();

signals:
    void signalPushButtonBackStock(int index);

private slots:
    void on_pushButtonBackStock_clicked();

    void on_pushButtonInNext_clicked();

    void on_pushButtonInReset_clicked();

    void on_pushButtonInAddStock_clicked();

private:
    Ui::StockInForma *ui;
};

#endif // STOCKINFORMA_H
