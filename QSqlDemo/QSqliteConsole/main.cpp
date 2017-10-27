/************************************************************************
*   文件名称：main.h
*   编写人员：LHH
*   创建日期：2017/08/25
*   功能描述：在sqlite数据库中插入数据并显示在控制台
*   备    注：
*   修改描述：
************************************************************************/
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if 1
    qDebug() << "Qt 可利用的数据库的驱动:";
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers)
    {
        //qDebug() << driver;
        qDebug("%s", qPrintable(driver));

    }
    qDebug() << endl;

#endif

#if 1
    // 创建数据库的连接(数据库的驱动)
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("lhh");
    db.setDatabaseName("db_student");
    //db.setUserName("root");
    //db.setPassword("root");
    if(!db.open())
        return false;

    // 执行sql语句
    QSqlQuery query;
    // 新建表
    query.exec("create table tbl_student(stu_id int primary key, stu_name varchar, stu_sex varchar, stu_age int)");
    // 往表中插入数据
    query.exec("insert into tbl_student values(1001, 'Zhangsan', 'male', 23)");
    query.exec("insert into tbl_student values(1002, 'Lisi', 'female', 19)");
    query.exec("insert into tbl_student values(1003, 'Wangwu', 'male', 21)");
    query.exec("insert into tbl_student values(1004, 'Laoliu', 'female', 20)");
    query.exec("insert into tbl_student values(1005, 'Hongqi', 'male', 23)");
    query.exec("insert into tbl_student values(1006, 'Zhuba', 'male', 22)");
    query.exec("insert into tbl_student values(1007, 'XiaoWang', 'female', 20)");
    query.exec("insert into tbl_student values(1008, 'LaoYang', 'female', 21)");
    query.exec("insert into tbl_student values(1009, 'LaoSun', 'male', 19)");

    // 删除表中stu_id >=1007 的记录
    query.exec("delete from tbl_student where stu_id >= 1007");
    qDebug() << "学号:" << "姓名:" << "性别:" << "年龄:";
    // 查找表中stu_id >=1003 的记录stu_id, stu_name, stu_sex, stu_age的值
    //query.exec("select stu_id, stu_name, stu_sex, stu_age from tbl_student where stu_id >= 1003");

    // 查找表中所有学生信息
    query.exec("select *from tbl_student");
    while(query.next())
    {
        //query.value(0)是id的值，将其转换为int型
        //int v_id = query.value(0).toInt();
        int v_id = query.value("stu_id").toInt();
        QString v_name = query.value("stu_name").toString();
        QString v_sex = query.value("stu_sex").toString();
        int v_age = query.value("stu_age").toInt();
        //输出
        qDebug() << v_id << v_name << v_sex << v_age;
    }
#endif

    return a.exec();
}
