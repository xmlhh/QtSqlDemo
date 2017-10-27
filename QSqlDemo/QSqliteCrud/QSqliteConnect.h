/************************************************************************
*   文件名称：QSqliteConnect.h
*   编写人员：LHH
*   创建日期：2017/10/01
*   功能描述：建立数据库连接以及数据库的操作：增、删、改、查
*   备    注：
*   修改描述：
************************************************************************/

#ifndef QSQLITECONNECT_H
#define QSQLITECONNECT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>


static bool SqlConnect()
{

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
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection."),
            QMessageBox::Cancel);
        return false;
    }


    // 执行sql语句
    QSqlQuery query;
    // 新建表
    query.exec("create table tbl_student(stu_id int primary key, stu_name varchar, stu_sex varchar, stu_age int, "
               "stu_chinese int, stu_math, stu_english, stu_physics, stu_chemistry int, stu_biology int, "
               "stu_history int, stu_geography int)");
    // 往表中插入数据
    //query.exec("insert into tbl_staff values(1001, 'Zhangsan', 'male', 19, 132)");
    query.exec("insert into tbl_student values(1001, 'Zhangsan', 'male', 19, 132, 146, 125, 98, 93, 91, 92, 95)");
    query.exec("insert into tbl_student values(1002, 'Zhaosi', 'fema',   19, 113, 124, 138, 92, 95, 98, 90, 92)");
    query.exec("insert into tbl_student values(1003, 'Wangwu', 'male',   21, 90,  98,  126, 95, 92, 96, 98, 90)");
    query.exec("insert into tbl_student values(1004, 'Laoliu', 'fema',   20, 109, 137, 97,  97, 91, 92, 95, 93)");
    query.exec("insert into tbl_student values(1005, 'Hongqi', 'male',   23, 96,  128, 109, 98, 93, 90, 93, 98)");
    query.exec("insert into tbl_student values(1006, 'ZhuHao', 'male',   22, 121, 119, 132, 90, 98, 94, 96, 92)");
    query.exec("insert into tbl_student values(1007, 'XiaoWang', 'fema', 20, 98,  150, 110, 99, 90, 95, 91, 98)");
    query.exec("insert into tbl_student values(1008, 'LaoYang', 'fema',  19, 115, 123, 99,  93, 95, 97, 90, 96)");
    query.exec("insert into tbl_student values(1009, 'LaoSun', 'male',   21, 103, 135, 145, 95, 93, 96, 99, 91)");

    // 重命名表
    //query.exec("rename table tbl_student to tbl_staff");
    // 删除表
    //query.exec("drop table tbl_student");
    //query.exec("drop table tbl_staff");
    //query.exec("drop table tbl_lhh");

    // 删除表中stu_id >=1007 的记录
    //query.exec("delete from tbl_staff where stu_id >= 1007");
    //query.exec("delete from tbl_staff where stu_id >= 1001");


    /* 字段操作 */
    //alter table tbl_name [add][drop][modify][change] + 字段名 + [数据类型]
    // 删除一个字段（列）Drop + 字段名
    query.exec("alter table tbl_staff drop stu_geography");
    // 增加一个字段（列）Add + 字段名 + 数据类型
    // 修改一个字段（列）Modify + 指定的字段名 + 数据类型（修改的是该字段的数据类型）
    // 重命名一个字段：Change + 旧字段名 + 新字段名 + 数据类型（修改的是字段名）



#endif

    return true;
}

#endif // QSQLITECONNECT_H
