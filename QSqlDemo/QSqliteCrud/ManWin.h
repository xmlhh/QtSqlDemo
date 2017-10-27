/************************************************************************
*   文件名称：ManWin.h
*   编写人员：LHH
*   创建日期：2017/10/01
*   功能描述：数据库操作主界面类，执行SQL语句操作数据库，并在界面显示
*   备    注：
*   修改描述：
************************************************************************/

#ifndef MANWIN_H
#define MANWIN_H

#include <QWidget>

class QSqlQuery;
class QSqlRecord;
class QSqlError;
class QDebug;

class QStandardItemModel;
class QStandardItem;
class QDateTime;

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


    /*
    * @author by lhh
    * @brief 显示数据到表
    * @param SQL语句执行对象
    * @return void
    */
    void ShowDataTbl(QSqlQuery query);


    /*
    * @author by lhh
    * @brief 清除表内容
    * @param 表对象
    * @return void
    */
    void DelContentTbl(QStandardItemModel* model);


private slots:
    /*
    * @author by lhh
    * @brief 数据库查询的槽
    * @param 无
    * @return void
    */
    void OnQueryBtn();

    /*
    * @author by lhh
    * @brief 接收QLineEdit的回车信号
    * @param 无
    * @return void
    */
    void OnReturnEnter(const QString& strText);

    /*
    * @author by lhh
    * @brief 操作结果集的槽
    * @param 无
    * @return void
    */
    void OnHandleResultSetBtn();


    /*
    * @author by lhh
    * @brief SQL语句使用变量的槽
    * @param 无
    * @return void
    */
    void OnSqlUseVariableBtn();


    /*
    * @author by lhh
    * @brief 批量操作集的槽
    * @param 无
    * @return void
    */
    void OnBatchHandleBtn();


    /*
    * @author by lhh
    * @brief 事务处理的槽
    * @param 无
    * @return void
    */
    void OnAffairsHandleBtn();


private:
    /*
    * @author by lhh
    * @brief 日志输出操作时间
    * @param 操作名称
    * @return void
    */
    QString ShowHandleTime(const char* strName);


    /*
    * @author by lhh
    * @brief 调试输出
    * @param SQL语句执行对象
    * @return void
    */
    void PrintCurrentvRecord(QSqlQuery query, int iIndex);


private:
    Ui::ManWin *ui;

    QStandardItemModel *m_pStuModel;

};

#endif // MANWIN_H
