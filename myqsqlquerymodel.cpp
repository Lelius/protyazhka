#include "myqsqlquerymodel.h"

//Класс переопределяющий функцию data в классе QSqlQueryModel
//для изменения отрисовки модели (текст по центру ячейки таблицы)

MyQSqlQueryModel::MyQSqlQueryModel()
{

}

QVariant MyQSqlQueryModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole){
        return Qt::AlignCenter;
    }
    return QSqlQueryModel::data(index, role);
}
