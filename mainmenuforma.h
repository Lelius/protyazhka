#ifndef MAINMENUFORMA_H
#define MAINMENUFORMA_H

#include <QWidget>

namespace Ui {
class MainMenuForma;
}

class MainMenuForma : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuForma(QWidget *parent = nullptr);
    ~MainMenuForma();

signals:
    void signalChangeStackWidget(int index);

private slots:
    void on_pushButtonStock_clicked();

private:
    Ui::MainMenuForma *ui;
};

#endif // MAINMENUFORMA_H