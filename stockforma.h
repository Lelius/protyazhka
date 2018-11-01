#ifndef STOCKFORMA_H
#define STOCKFORMA_H

#include <QWidget>

namespace Ui {
class StockForma;
}

class StockForma : public QWidget
{
    Q_OBJECT

public:
    explicit StockForma(QWidget *parent = nullptr);
    ~StockForma();

signals:
    void signalChangeStackWidget(int index);

private slots:
    void on_pushButtonReturn_clicked();

private:
    Ui::StockForma *ui;
};

#endif // STOCKFORMA_H
