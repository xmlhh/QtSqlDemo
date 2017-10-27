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
    db.setDatabaseName("db_lhh");
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
    query.exec("CREATE table tbl_staff(id int primary key, name varchar, age int, department varchar, position varchar)");
    // 往表中插入数据
    query.exec("delete from tbl_staff where id >= 1001");
    //query.exec("insert into tbl_staff values(10001, 'LaoWang', 22, 'R&D', C++)");
    query.exec("INSERT INTO tbl_staff VALUES(1001, 'LaoWang', 22, 'R&D', 'C/C++')");
    query.exec("INSERT INTO tbl_staff VALUES(1002, 'LaoLiao', 23, 'R&D', 'Qt')");
    query.exec("INSERT INTO tbl_staff VALUES(1003, 'XiaoYang', 21, 'R&D', 'JAVA')");
    query.exec("INSERT INTO tbl_staff VALUES(1004, 'ZhangJun', 22, 'R&D', 'Python')");
    query.exec("INSERT INTO tbl_staff VALUES(1005, 'ZhangJun', 20, 'R&D', 'Web')");


    // 重命名表
    //query.exec("rename table tbl_student to tbl_staff");
    // 删除表
    //query.exec("drop table tbl_student");
    //query.exec("drop table tbl_staff");
    //query.exec("drop table tbl_lhh");

    // 删除表中stu_id >=1007 的记录
    //query.exec("delete from tbl_staff where stu_id >= 1007");
    //query.exec("delete from tbl_staff where id >= 1001");


    /* 字段操作 */
    //alter table tbl_name [add][drop][modify][change] + 字段名 + [数据类型]
    // 删除一个字段（列）Drop + 字段名
    //query.exec("alter table tbl_staff drop stu_geography");
    // 增加一个字段（列）Add + 字段名 + 数据类型
    // 修改一个字段（列）Modify + 指定的字段名 + 数据类型（修改的是该字段的数据类型）
    // 重命名一个字段：Change + 旧字段名 + 新字段名 + 数据类型（修改的是字段名）



#endif

    return true;
}

#endif // QSQLITECONNECT_H
