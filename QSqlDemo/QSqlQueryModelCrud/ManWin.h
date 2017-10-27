/************************************************************************
*   文件名称：ManWin.h
*   编写人员：LHH
*   创建日期：2017/10/01
*   功能描述：数据库操作主界面类，QSqlQueryModel操作数据库，并在界面显示
*   备    注：
*   修改描述：
************************************************************************/

#ifndef MANWIN_H
#define MANWIN_H

#include <QWidget>

class QSqlQueryModel;
class QSqlQuery;
class QSqlRecord;

namespace Ui {
class ManWin;
}

class ManWin : public QWidget
{
    Q_OBJECT

public:
    explicit ManWin(QWidget *parent = 0);
    ~ManWin();

    /*
    * @author by lhh
    * @brief 界面初始化
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
    * @brief 初始化表数据
    * @param 无
    * @return void
    */
    void InitDataTbl();

private:
    Ui::ManWin *ui;

    QSqlQueryModel *m_pSqlQueryModel;
};

#endif // MANWIN_H
