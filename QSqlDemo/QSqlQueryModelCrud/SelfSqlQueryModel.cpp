#include "SelfSqlQueryModel.h"

#include <QSqlQuery>
#include <QColor>

SelfSqlQueryModel::SelfSqlQueryModel(QObject *parent)
    :QSqlQueryModel(parent)
{

}


/*
* @author by lhh
* @brief Item属性设置
* @param QModelIndex 序号
* @return void
*/
Qt::ItemFlags SelfSqlQueryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);

    if (index.column() == 1
            || index.column() == 2
            || index.column() == 3
            || index.column() == 4
            || index.column() == 5)
    {
        //第二个字段可编辑
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}


/*
* @author by lhh
* @brief 添加数据
* @param QModelIndex 序号
* @param QVariant 数据
* @param role 角色
* @return void
*/
bool SelfSqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int/* role*/)
{
    //if (index.column() < 1 || index.column() > 2)
    //    return false;
    if (index.column() < 1)
        return false;
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    // 获取id号
    int id = data(primaryKeyIndex).toInt();
    clear();
    bool ok;
    if (index.column() == 1)
    {
        // 第二个字段可编辑
        ok = setName(id, value.toString());
    }

    else if (index.column() == 2
            || index.column() == 3
            || index.column() == 4
            || index.column() == 5)
    {
        // 可编辑
        ok = setName(id, value.toString());
    }

    refresh();

    return ok;
}


/*
* @author by lhh
* @brief 数据显示属性设置
* @param QModelIndex 序号
* @param role 角色
* @return void
*/
QVariant  SelfSqlQueryModel::data(const QModelIndex & index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    if (role == Qt::TextAlignmentRole)
    {
        // 字体居中显示
        value = (Qt::AlignCenter);
        return value;
    }
    else if (role == Qt::TextColorRole && index.column() == 0)
    {
        // 第一个字段的字体颜色
        return qVariantFromValue(QColor(Qt::darkCyan));
    }

    return value;
}


/*
* @author by lhh
* @brief 添加字段的值
* @param 字段
* @return void
*/
bool SelfSqlQueryModel::setName(int id, const QString &name)
{
    QSqlQuery query;
    query.prepare("update tbl_staff set name = ? where id = ?");
    query.addBindValue(name);
    query.addBindValue(id);

    return query.exec();
}


/*
* @author by lhh
* @brief 刷新
* @param 无
* @return void
*/
void SelfSqlQueryModel::refresh()
{
    setQuery("SELECT * FROM tbl_staff");
    setHeaderData(0, Qt::Horizontal, QString::fromUtf8("工号"));
    setHeaderData(1, Qt::Horizontal, QString::fromUtf8("员工"));
    setHeaderData(2, Qt::Horizontal, QString::fromUtf8("工龄"));
    setHeaderData(3, Qt::Horizontal, QString::fromUtf8("部门"));
    setHeaderData(4, Qt::Horizontal, QString::fromUtf8("职位"));
}
