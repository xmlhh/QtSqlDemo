/************************************************************************
*   文件名称：ManWin.h
*   编写人员：LHH
*   创建日期：2017/10/15
*   功能描述：数据库操作主界面类，QSqlRelationalTableModel读写数据库的两张表数据，并在界面显示。
*            QSqlRelationalTableModel继承自QSqlTableModel，并且对其进行了扩展，提供了对外键的支持。
*            一个外键就是一个表中的一个字段和其他表中的主键字段之间的一对一的映射。
*   备    注：
*   修改描述：
************************************************************************/

#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>

class QSqlRelationalTableModel;
class QSqlRelation;
class QSqlRelationalDelegate;

namespace Ui {
class MainWin;
}

class MainWin : public QWidget
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

    /*
    * @author by lhh
    * @brief 初始化界面
    * @param 无
    * @return void
    */
    void InitUI();

private:
    /*
    * @author by lhh
    * @brief 表的初始化以及属性设置
    * @param 无
    * @return void
    */
    void InitTbl();

    /*
    * @author by lhh
    * @brief 初始化表头
    * @param QSqlTableModel对象
    * @return void
    */
    void InitHeaderTbl(QSqlRelationalTableModel *model);

    /*
    * @author by lhh
    * @brief 初始化表数据
    * @param 无
    * @return void
    */
    void InitDataTbl();

    /*
    * @author by lhh
    * @brief 删除表内容
    * @param 表对象
    * @return void
    */
    void DelContentTbl(QSqlRelationalTableModel *model);


private:
    Ui::MainWin *ui;

    QSqlRelationalTableModel* m_pSqlRelationalTableModel;
};

#endif // MAINWIN_H
