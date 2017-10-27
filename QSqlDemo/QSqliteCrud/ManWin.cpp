#include "ManWin.h"
#include "ui_ManWin.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QDateTime>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 700

//#define Q_DEBUG   // 屏蔽debug输出

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
* @brief 界面初始化
* @param 无
* @return void
*/
void ManWin::InitUI()
{
    // 界面属性
    setWindowTitle(QString::fromUtf8("QSqlQuery类执行SQL语句示例"));
    resize(WIN_WIDTH, WIN_HEIGHT);

    // 表初始化
    InitTbl();

    // 信号连接
    QObject::connect(ui->m_pQueryBtn, SIGNAL(clicked()), this, SLOT(OnQueryBtn()));
    QObject::connect(ui->m_pSqlQueryEdt, SIGNAL(textEdited(const QString&)), this, SLOT(OnReturnEnter(const QString&)));
    QObject::connect(ui->m_pHandleResultSetBtn, SIGNAL(clicked()), this, SLOT(OnHandleResultSetBtn()));
    QObject::connect(ui->m_pSqlUseVariableBtn, SIGNAL(clicked()), this, SLOT(OnSqlUseVariableBtn()));
    QObject::connect(ui->m_pBatchHandleBtn, SIGNAL(clicked()), this, SLOT(OnBatchHandleBtn()));
    QObject::connect(ui->m_pAffairsHandleBtn, SIGNAL(clicked()), this, SLOT(OnAffairsHandleBtn()));

}


/*
* @author by lhh
* @brief 表的初始化以及属性设置
* @param 无
* @return void
*/
void ManWin::InitTbl()
{
    m_pStuModel = new QStandardItemModel;
    m_pStuModel->setColumnCount(4);

    // 表头
    QStringList strLst;
    strLst << QString::fromUtf8("学号") << QString::fromUtf8("姓名")
           << QString::fromUtf8("性别") << QString::fromUtf8("年龄")
           << QString::fromUtf8("语文") << QString::fromUtf8("数学")
           << QString::fromUtf8("英语") << QString::fromUtf8("物理")
           << QString::fromUtf8("化学") << QString::fromUtf8("生物")
           << QString::fromUtf8("历史") << QString::fromUtf8("地理");
    m_pStuModel->setHorizontalHeaderLabels(strLst);

    // 设置垂直头不可见
    ui->m_pSqlTblView->verticalHeader()->setVisible(false);
    // 设置序列状态表不可编辑
    //ui->m_pSqlTblView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置表格宽度为等宽格式(表头可拖动)
    ui->m_pSqlTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    // 设置表格宽度为等宽格式(表头不可拖动)
    //ui->m_pSqlTblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置整行选中
    ui->m_pSqlTblView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 显示水平和垂直滚动条
    ui->m_pSqlTblView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->m_pSqlTblView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


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
    QSqlQuery query;
    // 查找表中所有学生信息
    query.exec("SELECT * FROM tbl_student");

    // 展示数据
    ShowDataTbl(query);
}


/*
* @author by lhh
* @brief 显示数据到表
* @param 无
* @return void
*/
void ManWin::ShowDataTbl(QSqlQuery query)
{
    int iCount = 0;

    while(query.next())
    {
        //query.value(0)是id的值，将其转换为int型
        //int v_id = query.value(0).toInt();
        int v_id        = query.value("stu_id").toInt();
        QString v_name  = query.value("stu_name").toString();
        QString v_sex   = query.value("stu_sex").toString();
        int v_age       = query.value("stu_age").toInt();
        int v_chinese   = query.value("stu_chinese").toInt();
        int v_math      = query.value("stu_math").toInt();
        int v_english   = query.value("stu_english").toInt();
        int v_physics   = query.value("stu_physics").toInt();
        int v_chemistry = query.value("stu_chemistry").toInt();
        int v_biology   = query.value("stu_biology").toInt();
        int v_history   = query.value("stu_history").toInt();
        int v_geography = query.value("stu_geography").toInt();

        //输出
        #ifdef  Q_DEBUG
        qDebug() << v_id << "\t"  << v_name << "\t"
                 << v_sex << "\t" << v_age << "\t"
                 << v_chinese << "\t" << v_math << "\t"
                 << v_english << "\t" << v_physics << "\t"
                 << v_chemistry << "\t" << v_biology << "\t"
                 << v_history << "\t" << v_geography << "\t"
                 ;
        #endif

        m_pStuModel->setRowCount(iCount);
        // 将数据插入界面的表
        QStandardItem *ItemId = new QStandardItem(QString::number(v_id));
        QStandardItem *ItemName = new QStandardItem(v_name);
        QStandardItem *ItemSex = new QStandardItem(v_sex);
        QStandardItem *ItemAge = new QStandardItem(QString::number(v_age));

        QStandardItem *ItemChinese = new QStandardItem(QString::number(v_chinese));
        QStandardItem *ItemMath = new QStandardItem(QString::number(v_math));
        QStandardItem *ItemEnglish = new QStandardItem(QString::number(v_english));
        QStandardItem *ItemPhysics = new QStandardItem(QString::number(v_physics));
        QStandardItem *ItemChemistry = new QStandardItem(QString::number(v_chemistry));
        QStandardItem *ItemBiology = new QStandardItem(QString::number(v_biology));
        QStandardItem *ItemHistory = new QStandardItem(QString::number(v_history));
        QStandardItem *ItemGeography = new QStandardItem(QString::number(v_geography));

        m_pStuModel->setItem(iCount, 0, ItemId);
        m_pStuModel->setItem(iCount, 1, ItemName);
        m_pStuModel->setItem(iCount, 2, ItemSex);
        m_pStuModel->setItem(iCount, 3, ItemAge);
        m_pStuModel->setItem(iCount, 4, ItemChinese);
        m_pStuModel->setItem(iCount, 5, ItemMath);
        m_pStuModel->setItem(iCount, 6, ItemEnglish);
        m_pStuModel->setItem(iCount, 7, ItemPhysics);
        m_pStuModel->setItem(iCount, 8, ItemChemistry);
        m_pStuModel->setItem(iCount, 9, ItemBiology);
        m_pStuModel->setItem(iCount, 10, ItemHistory);
        m_pStuModel->setItem(iCount, 11, ItemGeography);

        ItemId->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemName->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemSex->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemAge->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemChinese->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemMath->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemEnglish->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemPhysics->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemChemistry->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemBiology->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemHistory->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ItemGeography->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        ++iCount;
    }

    ui->m_pSqlTblView->setModel(m_pStuModel);
}


/*
* @author by lhh
* @brief 删除表内容
* @param 表对象
* @return void
*/
void ManWin::DelContentTbl(QStandardItemModel *model)
{
    int iRowCount = model->rowCount();
    for (int iRow = 0; iRow < iRowCount; ++iRow)
    {
        model->takeRow(iRow);
    }
    model->setRowCount(0);
}


/*
* @author by lhh
* @brief 数据库查询的槽
* @param 无
* @return void
*/
void ManWin::OnQueryBtn()
{
    QSqlQuery query;
    #ifdef Q_DEBUG
    qDebug() << QString::fromUtf8("学号:") << "\t" << QString::fromUtf8("姓名:") << "\t\t"
             << QString::fromUtf8("性别:") << "\t" << QString::fromUtf8("年龄:") << "\t"
             << QString::fromUtf8("语文:") << "\t" << QString::fromUtf8("数学:") << "\t"
             << QString::fromUtf8("英语:") << "\t" << QString::fromUtf8("物理:") << "\t"
             << QString::fromUtf8("化学:") << "\t" << QString::fromUtf8("生物:") << "\t"
             << QString::fromUtf8("历史:") << "\t" << QString::fromUtf8("地理:") << "\t"
             ;
    #endif
    // 查找表中stu_id >=1003 的记录stu_id, stu_name, stu_sex, stu_age的值
    //query.exec("select stu_id, stu_name, stu_sex, stu_age from tbl_student where stu_id >= 1003");

    QString strText = ui->m_pSqlQueryEdt->text();
    //strText = QString("\"%1\"").arg(strText);
    QRegExp regx("[a-zA-Z]+$");

    if (strText.isEmpty())
    {
        // 查找表中所有学生信息
        query.exec("SELECT *FROM tbl_student");
    }
    else if (strText.toInt() > 0 && strText.toInt() < 99)
    {
        // 查找表中某个学生信息，根据年龄查询
        QString strSearch_stu_age =
                "SELECT stu_id, stu_name, stu_sex, stu_age,"
                "stu_chinese, stu_math, stu_english, stu_physics, stu_chemistry, stu_biology, stu_history, stu_geography "
                "FROM tbl_student WHERE stu_age == "
                + strText;
        query.exec(strSearch_stu_age);
    }
    else if (strText.toInt() >= 1000 && strText.toInt() <= 10000)
    {
        // 查找表中某个学生信息，根据学号查询
        QString strSearch_stu_id =
                "SELECT stu_id, stu_name, stu_sex, stu_age,"
                "stu_chinese, stu_math, stu_english, stu_physics, stu_chemistry, stu_biology, stu_history, stu_geography "
                "FROM tbl_student WHERE stu_id == "
                + strText;
        query.exec(strSearch_stu_id);
    }
    else if((strText.at(0) >= 'a' && strText.at(0) <= 'z') ||
            (strText.at(0) >= 'A' && strText.at(0) <= 'Z'))
    {
        // stu_name添加双引号
        //strText = QString("\"%1\"").arg(strText);
        // 查找表中某个学生信息，根据姓名查询
        QString strSearch_stu_name =
                QString("SELECT stu_id, stu_name, stu_sex, stu_age,"
                        "stu_chinese, stu_math, stu_english, stu_physics, stu_chemistry, stu_biology, stu_history, stu_geography "
                        "FROM tbl_student WHERE stu_name like '%1%' ").arg(strText);
        query.exec(strSearch_stu_name);
    }
    else
    {
        // 删除表中原有内容
        DelContentTbl(m_pStuModel);
    }

    // 删除表中原有内容
    DelContentTbl(m_pStuModel);

    // 在界面的表中展示数据库的数据
    ShowDataTbl(query);

}


/*
* @author by lhh
* @brief 接收QLineEdit的回车信号
* @param 无
* @return void
*/
void ManWin::OnReturnEnter(const QString& /*strText*/)
{
    // 查询
    OnQueryBtn();

    //ui->m_pSqlQueryEdt->selectAll();
}


/*
* @author by lhh
* @brief 操作结果集的槽
* @param 无
* @return void
*/
void ManWin::OnHandleResultSetBtn()
{
    ui->m_pSqlHandleTextEdt->clear();

    // 输出当前操作时间
    ShowHandleTime("操作结果集_开始 ");

    QString strContent = QString::fromUtf8("-> seek(int n) ：query指向结果集的第n+1条记录；\n\n"
            "-> first() ：query指向结果集的第一条记录；\n\n"
            "-> last() ：query指向结果集的最后一条记录；\n\n"
            "-> next() ：query指向下一条记录，每执行一次该函数，便指向相邻的下一条记录；\n\n"
            "-> previous() ：query指向上一条记录，每执行一次该函数，便指向相邻的上一条记录；\n\n"
            "-> record() ：获得现在指向的记录；\n\n"
            "-> value(int n) ：获得字段的值。其中n表示你查询的第n个字段，\n\n"
            "-> 比如前面我们使用“select * from student”就相当于“select id, name from student”，\n\n"
            "-> 那么value(0)返回id字段的值，value(1)返回name字段的值。该函数返回QVariant类型的数据，关于该类型与其他类型的对应关系，可以在帮助中查看QVariant；\n\n"
            "-> at() ：获得现在query指向的记录在结果集中的编号。\n\n"
            "-> 需要特别注意，刚执行完query.exec(\"select * from student\");这行代码时，query是指向结果集以外的，我们可以利用query.next()使得query指向结果集的第一条记录。\n\n"
            "-> 当然我们也可以利用seek(0)函数或者first()函数使query指向结果集的第一条记录。但是为了节省内存开销，推荐的方法是，在query.exec(\"select * from student\");\n\n"
            "-> 这行代码前加上query.setForwardOnly(true);这条代码，此后只能使用next()和seek()函数。\n");

    ui->m_pSqlHandleTextEdt->append(strContent);

    QSqlQuery query;
    query.exec("SELECT * FROM tbl_student");

    #ifdef Q_DEBUG
    qDebug() << QString::fromUtf8("-> ************ 第一条记录 ************");
    #endif
    // 开始就先执行一次next()函数，那么query指向结果集的第一条记录
    if(query.next())
    {
        // 获取query所指向的记录在结果集中的编号
        int rowNum = query.at();
        // 获取每条记录中字段（即列）的个数
        int columnNum = query.record().count();

        // 获取stu_id字段的值，并转换为int型
        int stu_id = query.value(0).toInt();

        // 获取"stu_name"字段所在列的编号，列从左向右编号，最左边的编号为0
        int stu_name_no = query.record().indexOf("stu_name");
        // 获取name字段的值
        QString stu_name = query.value(stu_name_no).toString();

        // 输出
        #ifdef Q_DEBUG
        qDebug() << QString::fromUtf8("-> 当前记录编号: ")          << "\t\t"   << rowNum      << "\n"
                 << QString::fromUtf8("-> 该记录的字段个数（列）: ") << "\t"     << columnNum   << "\n"
                 << QString::fromUtf8("-> stu_id字段的值: ")        << "\t\t"   << stu_id      << "\n"
                 << QString::fromUtf8("-> stu_name字段的编号: ")    << "\t"     << stu_name_no << "\n"
                 << QString::fromUtf8("-> stu_name字段的值: ")      << "\t"     << stu_name    << "\n"
                 ;
        #endif

        ui->m_pSqlHandleTextEdt->append(QString::fromUtf8("-> ****************** 第%1条记录 ******************").arg(rowNum + 1) + "\n" +
            QString::fromUtf8("-> 当前记录编号: ") + "\t" + QString::number(rowNum) + "\n" +
            QString::fromUtf8("-> 该记录的字段个数（列）: ")  + QString::number(columnNum) + "\n" +
            QString::fromUtf8("-> stu_id字段的值: ") + "\t" + QString::number(stu_id) + "\n" +
            QString::fromUtf8("-> stu_name字段的编号: ") + "\t" + QString::number(stu_name_no) + "\n" +
            QString::fromUtf8("-> stu_name字段的值: ") + "\t" + stu_name + "\n"
            );
    }

    //定位到结果集中编号为2的记录，即第三条记录，因为第一条记录的编号为0
    #ifdef Q_DEBUG
    qDebug() << QString::fromUtf8("-> ****************** 记录编号为2的记录: 第三条记录 ******************");
    #endif
    int iIndex = 2;
    if(query.seek(iIndex))
    {
        PrintCurrentvRecord(query, iIndex + 1);
    }

    //定位到结果集中最后一条记录
    #ifdef Q_DEBUG
    qDebug() << QString::fromUtf8("-> ****************** 最后一条记录 ******************");
    #endif
    if(query.last())
    {
        int rowNum = query.at();
        PrintCurrentvRecord(query, rowNum + 1);
    }

    // 输出当前操作时间
    ShowHandleTime("操作结果集_结束 ");
}


/*
* @author by lhh
* @brief SQL语句使用变量的槽
* @param 无
* @return void
*/
void ManWin::OnSqlUseVariableBtn()
{
    ui->m_pSqlHandleTextEdt->clear();

    ShowHandleTime("SQL语句使用变量_开始 ");

    // 增加一条新记录(如果记录存在，只执行一次)
    QSqlQuery query;
    query.exec("DELETE FROM tbl_student WHERE stu_id >= 1010");
    query.prepare("INSERT INTO tbl_student (stu_id, stu_name, stu_sex, stu_age) "
                        "VALUES (:stu_id, :stu_name, :stu_sex, :stu_age)");
    query.bindValue(":stu_id", 1010);
    query.bindValue(":stu_name", "Houyi");
    query.bindValue(":stu_sex", "mela");
    query.bindValue(":stu_age", 20);
#if 0
    query.bindValue(0, 1010);
    query.bindValue(1, "Houyi");
    query.bindValue(2, "mela");
    query.bindValue(3, 20);
#endif
#if 0
    QSqlQuery query;
    query.prepare("INSERT INTO tbl_student (stu_id, stu_name, stu_sex, stu_age) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(1010);
    query.addBindValue("Houyi");
    query.addBindValue("mela");
    query.addBindValue(20);
    query.exec();
#endif
    query.exec();
    // 这里在tbl_student表的最后又添加了一条记录
    // 特别注意，在最后一定要执行exec()函数，所做的操作才能被真正执行。

    // 查询该记录（最后一条记录）
    query.exec("SELECT * FROM tbl_student");
    query.last();

    // 输出显示
    int rowNum = query.at();
    PrintCurrentvRecord(query, rowNum + 1);


    // 在SQL语句中使用变量
    query.prepare("SELECT stu_id, stu_name, stu_sex, stu_age,"
                  "stu_chinese, stu_math, stu_english, stu_physics, "
                  "stu_chemistry, stu_biology, stu_history, stu_geography "
                  "FROM tbl_student WHERE stu_id = ?");
    int id = ui->m_pSqlQueryEdt->text().toInt();
    if(id > 1000 && id < 10000)
    {
        query.addBindValue(id);
        query.exec();

        query.next();
        //int rNum = query.at();
        #ifdef Q_DEBUG
        qDebug() << query.value(0).toString();
        #endif

        QString strText = "";
        int iq = ui->m_pSqlQueryEdt->text().toInt();
        if (iq > 1000 && iq <= 1009)
        {
            strText = ui->m_pSqlQueryEdt->text().right(1);
        }
        else if (iq > 1009 && iq <= 1099)
        {
            strText = ui->m_pSqlQueryEdt->text().right(2);
        }
        else if (iq > 1099 && iq <= 1199)
        {
            strText = ui->m_pSqlQueryEdt->text().right(3);
        }
        // 输出显示
        int iNum = strText.toInt();
        PrintCurrentvRecord(query, iNum);
    }

    ShowHandleTime("SQL语句使用变量_结束 ");
}


/*
* @author by lhh
* @brief 批量操作集的槽
* @param 无
* @return void
*/
void ManWin::OnBatchHandleBtn()
{
    ui->m_pSqlHandleTextEdt->clear();

    ShowHandleTime("批量操作集_开始 ");
    QSqlQuery query;
    query.exec("DELETE FROM tbl_student WHERE stu_id >= 1011");
    query.prepare("INSERT INTO tbl_student (stu_id, stu_name, stu_sex, stu_age) "
                  "VALUES (?, ?, ?, ?)");

    QVariantList ids;
    ids << 1011 << 1012 << 1013 << 1014;
    query.addBindValue(ids);

    QVariantList names;
    // 最后一个是空字符串，应与前面的格式相同
    names << "Xiaoming" << "Laoliang"
        << "Zhaogang" << QVariant(QVariant::String);
    query.addBindValue(names);

    QVariantList sexs;
    sexs << "fema" << "mela"
        << "mela" << QVariant(QVariant::String);
    query.addBindValue(sexs);

    QVariantList ages;
    ages << 20 << 19 << 23 << QVariant(QVariant::Int);
    query.addBindValue(ages);

    //execBatch()进行批处理
    if (!query.execBatch())
        qDebug() << query.lastError();


    // 输出整张表
    query.exec("SELECT * FROM tbl_student");
    int iIndex = 0;
    while(query.next())
    {
        int v_id        = query.value("stu_id").toInt();
        QString v_name  = query.value("stu_name").toString();
        QString v_sex   = query.value("stu_sex").toString();
        int v_age       = query.value("stu_age").toInt();
        int v_chinese   = query.value("stu_chinese").toInt();
        int v_math      = query.value("stu_math").toInt();
        int v_english   = query.value("stu_english").toInt();
        int v_physics   = query.value("stu_physics").toInt();
        int v_chemistry = query.value("stu_chemistry").toInt();
        int v_biology   = query.value("stu_biology").toInt();
        int v_history   = query.value("stu_history").toInt();
        int v_geography = query.value("stu_geography").toInt();

        ui->m_pSqlHandleTextEdt->append(QString::fromUtf8("-> ****************** 第%1条记录 ******************").arg(iIndex + 1) + "\n" +
            QString::fromUtf8("-> 当前记录编号: ")            + "\t" + QString::number(iIndex)      + "\n" +
            QString::fromUtf8("-> stu_id字段的值: ")          + "\t" + QString::number(v_id)        + "\n" +
            QString::fromUtf8("-> stu_name字段的值: ")        + "\t" + v_name                       + "\n" +
            QString::fromUtf8("-> stu_sex字段的值: ")         + "\t" + v_sex                        + "\n" +
            QString::fromUtf8("-> stu_age字段的值: ")         + "\t" + QString::number(v_age)       + "\n" +
            QString::fromUtf8("-> stu_chinese字段的值: ")     + "\t" + QString::number(v_chinese)   + "\n" +
            QString::fromUtf8("-> stu_math字段的值: ")        + "\t" + QString::number(v_math)      + "\n" +
            QString::fromUtf8("-> stu_english字段的值: ")     + "\t" + QString::number(v_english)   + "\n" +
            QString::fromUtf8("-> stu_physics字段的值: ")     + "\t" + QString::number(v_physics)   + "\n" +
            QString::fromUtf8("-> stu_chemistry字段的值: ")   + "\t" + QString::number(v_chemistry) + "\n" +
            QString::fromUtf8("-> stu_biology字段的值: ")     + "\t" + QString::number(v_biology)   + "\n" +
            QString::fromUtf8("-> stu_history字段的值: ")     + "\t" + QString::number(v_history)   + "\n" +
            QString::fromUtf8("-> stu_geography字段的值: ")   + "\t" + QString::number(v_geography) + "\n"
            );
        ++iIndex;

    }

    ShowHandleTime("批量操作集_结束 ");
}


/*
* @author by lhh
* @brief 事务处理的槽
* @param 无
* @return void
*/
void ManWin::OnAffairsHandleBtn()
{
    ui->m_pSqlHandleTextEdt->clear();

    ShowHandleTime("事务处理_开始 ");

    // 启动事务
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    query.exec("SELECT stu_id FROM tbl_student WHERE stu_name = 'XiaoWang'");

    if (query.next())
    {
        int employeeId = query.value(0).toInt();
        query.exec("INSERT INTO tbl_student (stu_id, stu_name, stu_sex, stu_age) "
                   "VALUES (1015, 'MMP', " + QString::number(employeeId) + ')');
        ui->m_pSqlHandleTextEdt->append(
            QString::fromUtf8("-> 事务可以保证一个复杂的操作的原子性，就是对于一个数据库操作序列，这些操作要么全部做完，要么一条也不做，它是一个不可分割的工作单位；\n\n"
                            "-> 在Qt中，如果底层的数据库引擎支持事务，那么QSqlDriver::hasFeature(QSqlDriver::Transactions)会返回true；\n\n"
                            "-> 可以使用QSqlDatabase::transaction()来启动一个事务，然后编写一些希望在事务中执行的SQL语句，\n\n"
                            "-> 最后调用QSqlDatabase::commit()或者QSqlDatabase::rollback()；\n\n"
                            "-> 当使用事务时必须在创建查询以前就开始事务。\n"));
    }
    // 事务结束
    QSqlDatabase::database().commit();

    ShowHandleTime("事务处理_结束 ");
}


/*
* @author by lhh
* @brief 日志输出操作时间
* @param 操作名称
* @return void
*/
QString ManWin::ShowHandleTime(const char* strName)
{
    // 获取系统现在的时间
    QDateTime cTime = QDateTime::currentDateTime();
    cTime.setTimeSpec(Qt::UTC);
    // 设置系统时间显示格式
    QString strCTime = cTime.toString("yyyy/MM/dd hh:mm:ss.zzz");

    // 打印输出
    ui->m_pSqlHandleTextEdt->append(QString("-> ================================================ "
        + QString::fromUtf8(strName) + "%1 ================================================\n").arg(strCTime));
    //m_pLogTextEdit->setPlainText(m_strLog);

    // 光标移动到最后, 并设置拥有焦点
    QTextCursor textCursor = ui->m_pSqlHandleTextEdt->textCursor();
    textCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    ui->m_pSqlHandleTextEdt->setTextCursor(textCursor);
    ui->m_pSqlHandleTextEdt->setFocus(Qt::MouseFocusReason);

    return strCTime;
}


/*
* @author by lhh
* @brief 调试输出
* @param 无
* @return void
*/
void ManWin::PrintCurrentvRecord(QSqlQuery query, int iIndex)
{
    #ifdef Q_DEBUG
    qDebug() << QString::fromUtf8("-> 当前记录编号: ")       << "\t\t"   << query.at()                 << "\n"
             << QString::fromUtf8("-> stu_id字段的值: ")     << "\t"   << query.value(0).toInt()    << "\n"
             << QString::fromUtf8("-> stu_name字段的值: ")   << "\t"     << query.value(1).toString()  << "\n"
             << QString::fromUtf8("-> stu_sex字段的值: ")    << "\t"     << query.value(2).toString()  << "\n"
             << QString::fromUtf8("-> stu_age字段的值: ")    << "\t"     << query.value(3).toInt()     << "\n"
             << QString::fromUtf8("-> stu_chinese字段的值: ")    << "\t"     << query.value(4).toInt()     << "\n"
             << QString::fromUtf8("-> stu_math字段的值: ")    << "\t"     << query.value(5).toInt()     << "\n"
             << QString::fromUtf8("-> stu_english字段的值: ")    << "\t"     << query.value(6).toInt()     << "\n"
             << QString::fromUtf8("-> stu_physics字段的值: ")    << "\t"     << query.value(7).toInt()     << "\n"
             << QString::fromUtf8("-> stu_chemistry字段的值: ")    << "\t"     << query.value(8).toInt()     << "\n"
             << QString::fromUtf8("-> stu_biology字段的值: ")    << "\t"     << query.value(9).toInt()     << "\n"
             << QString::fromUtf8("-> stu_history字段的值: ")    << "\t"     << query.value(10).toInt()     << "\n"
             << QString::fromUtf8("-> stu_geography字段的值: ")    << "\t"     << query.value(11).toInt()     << "\n"
             ;
    #endif

    ui->m_pSqlHandleTextEdt->append(QString::fromUtf8("-> ****************** 第%1条记录 ******************").arg(iIndex) + "\n" +
        QString::fromUtf8("-> 当前记录编号: ") + "\t" + QString::number(iIndex - 1) + "\n" +
        QString::fromUtf8("-> stu_id字段的值: ") + "\t" + QString::number(query.value(0).toInt()) + "\n" +
        QString::fromUtf8("-> stu_name字段的值: ") + "\t" + query.value(1).toString() + "\n" +
        QString::fromUtf8("-> stu_sex字段的值: ") + "\t" + query.value(2).toString() + "\n" +
        QString::fromUtf8("-> stu_age字段的值: ") + "\t" + QString::number(query.value(3).toInt()) + "\n" +
        QString::fromUtf8("-> stu_chinese字段的值: ") + "\t" + QString::number(query.value(4).toInt()) + "\n" +
        QString::fromUtf8("-> stu_math字段的值: ") + "\t" + QString::number(query.value(5).toInt()) + "\n" +
        QString::fromUtf8("-> stu_english字段的值: ") + "\t" + QString::number(query.value(6).toInt()) + "\n" +
        QString::fromUtf8("-> stu_physics字段的值: ") + "\t" + QString::number(query.value(7).toInt()) + "\n" +
        QString::fromUtf8("-> stu_chemistry字段的值: ") + "\t" + QString::number(query.value(8).toInt()) + "\n" +
        QString::fromUtf8("-> stu_biology字段的值: ") + "\t" + QString::number(query.value(9).toInt()) + "\n" +
        QString::fromUtf8("-> stu_history字段的值: ") + "\t" + QString::number(query.value(10).toInt()) + "\n" +
        QString::fromUtf8("-> stu_geography字段的值: ") + "\t" + QString::number(query.value(11).toInt()) + "\n"
        );
}
