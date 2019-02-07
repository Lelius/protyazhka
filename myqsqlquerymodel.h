#ifndef MYQSQLQUERYMODEL_H
#define MYQSQLQUERYMODEL_H

//Класс преопределяющий функцию data в классе QSqlQueryModel
//для изменения отрисовки модели (текст по центру ячейки таблицы)

#include <QSqlQueryModel>

class MyQSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit MyQSqlQueryModel(QWidget *parent = nullptr);

    QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;

signals:

public slots:
};

#endif // MYQSQLQUERYMODEL_H
