#include "MainWin.h"
#include "ui_MainWin.h"

#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

MainWin::MainWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);

    InitUI();
}

MainWin::~MainWin()
{
    delete ui;
}


/*
* @author by lhh
* @brief 初始化界面
* @param 无
* @return void
*/
void MainWin::InitUI()
{
    // 界面属性
    setWindowTitle(QString::fromUtf8("QSqlRelationalTableModel读写数据库的：两个表外键关联"));
    resize(WIN_WIDTH, WIN_HEIGHT);

    // 表初始化
    InitTbl();

    // 信号连接
//    QObject::connect(ui->m_pSqlQueryBtn, SIGNAL(clicked()), this, SLOT(OnSqlQueryByCondition()));
//    QObject::connect(ui->m_pSqlQueryAllBtn, SIGNAL(clicked()), this, SLOT(OnSqlQueryAll()));
//    QObject::connect(ui->m_pSqlQueryLineEdt, SIGNAL(textEdited(const QString&)), this, SLOT(OnTextEdit(const QString&)));
//    QObject::connect(ui->m_pComfirmModifyBtn, SIGNAL(clicked()), this, SLOT(OnComfirmModify()));
//    QObject::connect(ui->m_pUndoModifyBtn, SIGNAL(clicked()), this, SLOT(OnUndoModify()));
//    QObject::connect(ui->m_pAddRecordBtn, SIGNAL(clicked()), this, SLOT(OnAddRecord()));
//    QObject::connect(ui->m_pDeleteSelectRowBtn, SIGNAL(clicked()), this, SLOT(OnDeleteSelectRow()));
//    QObject::connect(ui->m_pAscendSortBtn, SIGNAL(clicked()), this, SLOT(OnAscendSort()));
//    QObject::connect(ui->m_pDeascendSortBtn, SIGNAL(clicked()), this, SLOT(OnDescendSort()));

}


/*
* @author by lhh
* @brief 表的初始化以及属性设置
* @param 无
* @return void
*/
void MainWin::InitTbl()
{
    // 设置垂直头不可见
    ui->tableView->verticalHeader()->setVisible(false);
    // 设置序列状态表不可编辑
    //ui->m_pSqlQueryTblView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置表格宽度为等宽格式(表头可拖动)
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    // 设置表格宽度为等宽格式(表头不可拖动)
    //ui->m_pSqlQueryTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 显示水平和垂直滚动条
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // 初始化表
    InitDataTbl();
}


/*
* @author by lhh
* @brief 初始化表头
* @param QSqlTableModel对象
* @return void
*/
void MainWin::InitHeaderTbl(QSqlRelationalTableModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("学号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("姓名"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("课程"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromUtf8("分数"));
}

/*
* @author by lhh
* @brief 初始化表数据
* @param 无
* @return void
*/
void MainWin::InitDataTbl()
{
    m_pSqlRelationalTableModel = new QSqlRelationalTableModel(this);
    //字段变化时写入数据库
    m_pSqlRelationalTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_pSqlRelationalTableModel->setTable("tbl_stu");

    //将student表的第三个字段设为course表的id字段的外键，
    //并将其显示为course表的name字段的值
    m_pSqlRelationalTableModel->setRelation(2,QSqlRelation("course","id","name"));

    m_pSqlRelationalTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_pSqlRelationalTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    m_pSqlRelationalTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Course"));

    // 表头
    //InitHeaderTbl(m_pSqlRelationalTableModel);
    m_pSqlRelationalTableModel->select();
    // 显示
    ui->tableView->setModel(m_pSqlRelationalTableModel);
    ui->tableView->setItemDelegate(
                new QSqlRelationalDelegate(ui->tableView));

}



/*
* @author by lhh
* @brief 删除表内容
* @param 表对象
* @return void
*/
void MainWin::DelContentTbl(QSqlRelationalTableModel *model)
{
    int iRowCount = model->rowCount();
    for (int iRow = 0; iRow < iRowCount; ++iRow)
    {
        model->removeRow(iRow);
    }
}
