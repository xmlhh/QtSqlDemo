#include "ManWin.h"
#include "ui_ManWin.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

ManWin::ManWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManWin)
{
    ui->setupUi(this);

    InitUI();
}

ManWin::~ManWin()
{
    delete ui;
}


/*
* @author by lhh
* @brief 初始化界面
* @param 无
* @return void
*/
void ManWin::InitUI()
{
    // 界面属性
    setWindowTitle(QString::fromUtf8("QSqlTableModel读写数据库"));
    resize(WIN_WIDTH, WIN_HEIGHT);

    // 表初始化
    InitTbl();

    // 信号连接
    QObject::connect(ui->m_pSqlQueryBtn, SIGNAL(clicked()), this, SLOT(OnSqlQueryByCondition()));
    QObject::connect(ui->m_pSqlQueryAllBtn, SIGNAL(clicked()), this, SLOT(OnSqlQueryAll()));
    QObject::connect(ui->m_pSqlQueryLineEdt, SIGNAL(textEdited(const QString&)), this, SLOT(OnTextEdit(const QString&)));
    QObject::connect(ui->m_pComfirmModifyBtn, SIGNAL(clicked()), this, SLOT(OnComfirmModify()));
    QObject::connect(ui->m_pUndoModifyBtn, SIGNAL(clicked()), this, SLOT(OnUndoModify()));
    QObject::connect(ui->m_pAddRecordBtn, SIGNAL(clicked()), this, SLOT(OnAddRecord()));
    QObject::connect(ui->m_pDeleteSelectRowBtn, SIGNAL(clicked()), this, SLOT(OnDeleteSelectRow()));
    QObject::connect(ui->m_pAscendSortBtn, SIGNAL(clicked()), this, SLOT(OnAscendSort()));
    QObject::connect(ui->m_pDeascendSortBtn, SIGNAL(clicked()), this, SLOT(OnDescendSort()));

}


/*
* @author by lhh
* @brief 表的初始化以及属性设置
* @param 无
* @return void
*/
void ManWin::InitTbl()
{
    // 设置垂直头不可见
    ui->m_pSqlQueryTblView->verticalHeader()->setVisible(false);
    // 设置序列状态表不可编辑
    //ui->m_pSqlQueryTblView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置表格宽度为等宽格式(表头可拖动)
    ui->m_pSqlQueryTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    // 设置表格宽度为等宽格式(表头不可拖动)
    //ui->m_pSqlQueryTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置整行选中
    ui->m_pSqlQueryTblView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 显示水平和垂直滚动条
    ui->m_pSqlQueryTblView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->m_pSqlQueryTblView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // 初始化表
    InitDataTbl();
}


/*
* @author by lhh
* @brief 初始化表头
* @param QSqlTableModel对象
* @return void
*/
void ManWin::InitHeaderTbl(QSqlTableModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("工号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("员工"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("工龄"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("部门"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("职位"));
}


/*
* @author by lhh
* @brief 初始化表数据
* @param 无
* @return void
*/
void ManWin::InitDataTbl()
{
    m_pSqlTableModel = new QSqlTableModel(this);
    // 指定表名
    m_pSqlTableModel->setTable("tbl_staff");
    // 编辑保存策略
    m_pSqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
#if 1
    // 查询条件
    //m_pSqlTableModel->setFilter(QString("name = '%1'").arg("LaoLiao"));
    //m_pSqlTableModel->setFilter(QString("id = %1").arg(1005));
    // 查询整张表
    m_pSqlTableModel->select();
#endif
    // 表头
    InitHeaderTbl(m_pSqlTableModel);
    // 显示
    ui->m_pSqlQueryTblView->setModel(m_pSqlTableModel);
}



/*
* @author by lhh
* @brief 删除表内容
* @param 表对象
* @return void
*/
void ManWin::DelContentTbl(QSqlTableModel *model)
{
    int iRowCount = model->rowCount();
    for (int iRow = 0; iRow < iRowCount; ++iRow)
    {
        model->removeRow(iRow);
    }
}


/*
* @author by lhh
* @brief 接收QLineEdit的编辑信号
* @param 文本内容
* @return void
*/
void ManWin::OnTextEdit(const QString &/*strText*/)
{
    // 按编辑框的条件查询
    OnSqlQueryByCondition();
}


/*
* @author by lhh
* @brief 按条件查询
* @param 无
* @return void
*/
void ManWin::OnSqlQueryByCondition()
{
    QString strText = ui->m_pSqlQueryLineEdt->text();

    if (strText.isEmpty())
    {
        // 查找表中所有信息
        m_pSqlTableModel->setTable("tbl_staff");
        m_pSqlTableModel->select();
        // 表头
        InitHeaderTbl(m_pSqlTableModel);
    }
    else if (strText.toInt() > 1000 && strText.toInt() < 1099)
    {
        // 按数字查询
        m_pSqlTableModel->setFilter(QString("id = %1").arg(strText.toInt()));
        m_pSqlTableModel->select();
        // 表头
        InitHeaderTbl(m_pSqlTableModel);
    }
    else if((strText.at(0) >= 'a' && strText.at(0) <= 'z') ||
            (strText.at(0) >= 'A' && strText.at(0) <= 'Z'))
    {
        // 按字母查询
        m_pSqlTableModel->setFilter(QString("name like '%1%' ").arg(strText));
        m_pSqlTableModel->select();
        // 表头
        InitHeaderTbl(m_pSqlTableModel);
    }
    else
    {
        // 删除表中原有内容
        DelContentTbl(m_pSqlTableModel);
    }

}


/*
* @author by lhh
* @brief 查询整张表
* @param 无
* @return void
*/
void ManWin::OnSqlQueryAll()
{
    m_pSqlTableModel->setTable("tbl_staff");
    m_pSqlTableModel->select();
    // 表头
    InitHeaderTbl(m_pSqlTableModel);
}


/*
* @author by lhh
* @brief 确认修改
* @param 无
* @return void
*/
void ManWin::OnComfirmModify()
{
    // 开始事务处理
    m_pSqlTableModel->database().transaction();
    if (m_pSqlTableModel->submitAll())
    {
        // 提交
        m_pSqlTableModel->database().commit();
    }
    else
    {
        // 回滚
        m_pSqlTableModel->database().rollback();
    }
}


/*
* @author by lhh
* @brief 撤销修改
* @param 无
* @return void
*/
void ManWin::OnUndoModify()
{
    // 恢复所有
    m_pSqlTableModel->revertAll();
}


/*
* @author by lhh
* @brief 添加记录
* @param 无
* @return void
*/
void ManWin::OnAddRecord()
{
    int iRowCount = m_pSqlTableModel->rowCount();

    m_pSqlTableModel->insertRow(iRowCount);
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 0), 1010);
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 1), QString::fromUtf8("XiaoGu"));
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 2), 20);
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 3), QString::fromUtf8("R&D"));
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 4), QString::fromUtf8("安全渗透&漏洞"));

    // 获取选中的行
    int iCurRow = ui->m_pSqlQueryTblView->currentIndex().row();
    QSqlRecord record = m_pSqlTableModel->record(iCurRow);

    // 获取当前记录的值
    QVariant id = record.value(0);
    QVariant name = record.value(1);
    QVariant age = record.value(2);
    QVariant department = record.value(3);
    QVariant position = record.value(4);

    if (id.isNull())
    {
        return;
    }
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 0), id);
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 1), name);
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 2), age);
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 3), department);
    m_pSqlTableModel->setData(m_pSqlTableModel->index(iRowCount, 4), position);

    // 提交到数据库的表中
    //m_pSqlTableModel->submitAll();
#if 0
    QString strCRow = QString("确定保存第%1行到数据库中吗？").arg(iCurRow + 1);
    // 是否删除
    QMessageBox msgBox(QMessageBox::Warning, QString::fromUtf8("保存到数据库"), strCRow);
    msgBox.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setButtonText (QMessageBox::Ok, QString("确 定"));
    msgBox.setButtonText (QMessageBox::Cancel, QString("取 消"));
    int iRet = msgBox.exec ();

    if (iRet == QMessageBox::Ok)
    {
        // 提交，保存到数据库中
        m_pSqlTableModel->submitAll();
    }
    else
    {
        // 撤销
        m_pSqlTableModel->revertAll();
    }
#endif
}


/*
* @author by lhh
* @brief 删除选中行
* @param 无
* @return void
*/
void ManWin::OnDeleteSelectRow()
{
    // 获取选中的行
    int iCurRow = ui->m_pSqlQueryTblView->currentIndex().row();
    if (-1 == iCurRow)
    {
        return;
    }
    // 删除当前行
    m_pSqlTableModel->removeRow(iCurRow);

    QString strCRow = QString("确定删除第%1行吗？").arg(iCurRow + 1);
    // 是否删除
    QMessageBox msgBox(QMessageBox::Warning, QString::fromUtf8("删除行"), strCRow);
    msgBox.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setButtonText (QMessageBox::Ok, QString("确 定"));
    msgBox.setButtonText (QMessageBox::Cancel, QString("取 消"));
    int iRet = msgBox.exec ();

    if (iRet == QMessageBox::Ok)
    {
        // 提交，在数据库中删除该行
        m_pSqlTableModel->submitAll();
    }
    else
    {
        // 撤销
        m_pSqlTableModel->revertAll();
    }
}


/*
* @author by lhh
* @brief 按id升序排列
* @param 无
* @return void
*/
void ManWin::OnAscendSort()
{
    m_pSqlTableModel->setSort(0, Qt::AscendingOrder); //id属性即第0列，升序排列
    m_pSqlTableModel->select();
}


/*
* @author by lhh
* @brief 按id降序排列
* @param 无
* @return void
*/
void ManWin::OnDescendSort()
{
    m_pSqlTableModel->setSort(0, Qt::DescendingOrder); //id属性即第0列，降序排列
    m_pSqlTableModel->select();
}
