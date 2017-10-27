/************************************************************************
*   文件名称：SelfSqlQueryModel.h
*   编写人员：LHH
*   创建日期：2017/10/10
*   功能描述：自定义QSqlQueryModel，数据可读写：重写setData() 和 flags() 两个函数，改变数据的显示：重写data() 函数
*   备    注：
*   修改描述：
************************************************************************/

#ifndef SELFSQLQUERYMODEL_H
#define SELFSQLQUERYMODEL_H

#include <QSqlQueryModel>

class SelfSqlQueryModel: public QSqlQueryModel
{
     Q_OBJECT

public:
    explicit SelfSqlQueryModel(QObject *parent = 0);

    /*
    * @author by lhh
    * @brief Item属性设置
    * @param QModelIndex 序号
    * @return void
    */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /*
    * @author by lhh
    * @brief 添加数据
    * @param QModelIndex 序号
    * @param QVariant 数据
    * @param role 角色
    * @return void
    */
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    /*
    * @author by lhh
    * @brief 数据显示属性设置
    * @param QModelIndex 序号
    * @param role 角色
    * @return void
    */
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

private:
    bool setName(int studentId, const QString &name);

    /*
    * @author by lhh
    * @brief 刷新
    * @param 无
    * @return void
    */
    void refresh();

};

#endif // SELFSQLQUERYMODEL_H
