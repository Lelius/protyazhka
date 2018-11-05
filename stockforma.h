#ifndef STOCKFORMA_H
#define STOCKFORMA_H

#include <QWidget>
#include <QFile>
#include <QDir>
#include <QtSql>
#include <QDebug>
#include "myqsqlquerymodel.h"

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
    void signalChangeStackWidget(int indexStackWidget);
    void signalComboBoxSort_currentIndexChanged(int indexComboBox);

private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonStockIn_clicked();

    void on_pushButtonStockOut_clicked();

public slots:
    void on_comboBoxSort_currentIndexChanged(int index);
    QString comboBoxSortCurrentIndexChanged(int index);

private:
    Ui::StockForma *ui;
    QString fileNameDataBase;
};

#endif // STOCKFORMA_H
