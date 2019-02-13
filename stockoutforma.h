#ifndef STOCKOUTFORMA_H
#define STOCKOUTFORMA_H

#include <QWidget>
#include <QtSql>
#include "myqsqlquerymodel.h"

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

    void clearLinesEdit();

    void on_lineEditOutType_returnPressed();

    void on_lineEditOutSize_returnPressed();

    void on_lineEditOutNumber_returnPressed();

    QString commaToPointOutString(QString);

    void on_pushButtonAddTempOut_clicked();

    void on_pushButtonDelTempOut_clicked();

private:
    Ui::StockOutForma *ui;
};

#endif // STOCKOUTFORMA_H
