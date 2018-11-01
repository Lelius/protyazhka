#ifndef EXITFORMA_H
#define EXITFORMA_H

#include <QWidget>

namespace Ui {
class ExitForma;
}

class ExitForma : public QWidget
{
    Q_OBJECT

public:
    explicit ExitForma(QWidget *parent = nullptr);
    ~ExitForma();

signals:
    void signalChangeStackWidget(int index);

private slots:
    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::ExitForma *ui;
};

#endif // EXITFORMA_H
