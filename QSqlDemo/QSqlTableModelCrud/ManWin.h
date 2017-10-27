/************************************************************************
*   文件名称：ManWin.h
*   编写人员：LHH
*   创建日期：2017/10/15
*   功能描述：数据库操作主界面类，QSqlTableModel读写数据库，并在界面显示。
*           只读的QSqlQueryModel模型其实也可以实现编辑功能的，但是实现起来很麻烦。
*           而QSqlTableModel提供了一个一次只能操作单个SQL表的读写模型，
*           它是QSqlQuery的更高层次的替代品，可以浏览和修改独立的SQL表，
*           并且只需编写很少的代码，而且不需要了解SQL语法。
*   备    注：
*   修改描述：
************************************************************************/

#ifndef MANWIN_H
#define MANWIN_H

#include <QWidget>

class QSqlTableModel;
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
    void InitHeaderTbl(QSqlTableModel *model);

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
    void DelContentTbl(QSqlTableModel *model);

private slots:
    /*
    * @author by lhh
    * @brief 接收QLineEdit的编辑信号
    * @param 文本内容
    * @return void
    */
    void OnTextEdit(const QString& strText);

    /*
    * @author by lhh
    * @brief 按条件查询
    * @param 无
    * @return void
    */
    void OnSqlQueryByCondition();

    /*
    * @author by lhh
    * @brief 查询整张表
    * @param 无
    * @return void
    */
    void OnSqlQueryAll();

    /*
    * @author by lhh
    * @brief 确认修改
    * @param 无
    * @return void
    */
    void OnComfirmModify();

    /*
    * @author by lhh
    * @brief 撤销修改
    * @param 无
    * @return void
    */
    void OnUndoModify();

    /*
    * @author by lhh
    * @brief 添加记录
    * @param 无
    * @return void
    */
    void OnAddRecord();

    /*
    * @author by lhh
    * @brief 删除选中行
    * @param 无
    * @return void
    */
    void OnDeleteSelectRow();

    /*
    * @author by lhh
    * @brief 按id升序排列
    * @param 无
    * @return void
    */
    void OnAscendSort();

    /*
    * @author by lhh
    * @brief 按id降序排列
    * @param 无
    * @return void
    */
    void OnDescendSort();


private:
    Ui::ManWin *ui;

    QSqlTableModel *m_pSqlTableModel;
};

#endif // MANWIN_H
