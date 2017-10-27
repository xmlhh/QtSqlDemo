#include "ManWin.h"
#include "ui_ManWin.h"

#include "SelfSqlQueryModel.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 600

ManWin::ManWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManWin)
{
    ui->setupUi(this);

    // 初始化界面
    InitUI();
}

ManWin::~ManWin()
{
    delete ui;
}


/*
* @author by lhh
* @brief 界面初始化
* @param 无
* @return void
*/
void ManWin::InitUI()
{
    // 界面属性
    setWindowTitle(QString::fromUtf8("QSqlQueryModel操作数据库"));
    resize(WIN_WIDTH, WIN_HEIGHT);

    // 表初始化
    InitTbl();

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
    ui->m_pSqlTblView->verticalHeader()->setVisible(false);
    ui->m_pSqlSelfTblView->verticalHeader()->setVisible(false);
    // 设置序列状态表不可编辑
    //ui->m_pSqlTblView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置表格宽度为等宽格式(表头可拖动)
    ui->m_pSqlTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->m_pSqlSelfTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    // 设置表格宽度为等宽格式(表头不可拖动)
    //ui->m_pSqlTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置整行选中
    ui->m_pSqlTblView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_pSqlSelfTblView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 显示水平和垂直滚动条
    ui->m_pSqlTblView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->m_pSqlTblView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->m_pSqlSelfTblView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->m_pSqlSelfTblView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    // 初始化表数据
    InitDataTbl();
}


/*
* @author by lhh
* @brief 初始化表数据
* @param 无
* @return void
*/
void ManWin::InitDataTbl()
{
#if 1
    QSqlQueryModel *sqlQueryModel = new QSqlQueryModel(this);
    // 查找表中所有员工信息
    sqlQueryModel->setQuery("SELECT * FROM tbl_staff");
    sqlQueryModel->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("工号"));
    sqlQueryModel->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("员工"));
    sqlQueryModel->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("工龄"));
    sqlQueryModel->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("部门"));
    sqlQueryModel->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("职位"));

    // QSqlQueryModel常用的操作
    int column = sqlQueryModel->columnCount();          // 获得列数
    int row = sqlQueryModel->rowCount();                // 获得行数
    QSqlRecord record = sqlQueryModel->record(1);       // 获得一条记录
    QModelIndex index = sqlQueryModel->index(1, 1);     // 获得一条记录的一个字段的索引
    qDebug() << "iCol is: " << column << endl
             << "iRow is: " << row << endl
             <<"the second record is: " << record << endl
            << "the data of index(1,1) is: "<< index.data();

    // 插入一条新记录
    QSqlQuery query = sqlQueryModel->query();
    query.exec("INSERT INTO tbl_staff VALUES(1006, 'LaoZhu', 24, 'R&D', 'Andorid')");

    // （注意）再次重新查询表
    sqlQueryModel->setQuery("SELECT * FROM tbl_staff");

    // 展示数据
    ui->m_pSqlTblView->setModel(sqlQueryModel);
#endif


#if 1
    // 创建自己模型的对象
    SelfSqlQueryModel *selfSqlQueryModel = new SelfSqlQueryModel(this);
    // 查找表中所有员工信息
    selfSqlQueryModel->setQuery("SELECT * FROM tbl_staff");
    selfSqlQueryModel->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("工号"));
    selfSqlQueryModel->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("员工"));
    selfSqlQueryModel->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("工龄"));
    selfSqlQueryModel->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("部门"));
    selfSqlQueryModel->setHeaderData(4, Qt::Horizontal, QString::fromUtf8("职位"));

    //selfSqlQueryModel->setData(8, QVariant("GaoJun"));
    ui->m_pSqlSelfTblView->setModel(selfSqlQueryModel);
#endif
}

