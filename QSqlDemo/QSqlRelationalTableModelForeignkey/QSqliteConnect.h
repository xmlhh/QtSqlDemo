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
    //query.exec("CREATE table tbl_staff(id int primary key, name varchar, age int, department varchar, position varchar)");
    // 往表中插入数据
    //query.exec("delete from tbl_staff where id >= 1001");
//    // 学生信息表
//    query.exec("create table tbl_stu (id int primarykey, name varchar, course int)");
//    query.exec("insert into tbl_stu values(1001, 'LaoLiu',   1)");
//    query.exec("insert into tbl_stu values(1002, 'XiaoWang', 2)");
//    query.exec("insert into tbl_stu values(1003, 'ZhaoQuan', 2)");
//    query.exec("insert into tbl_stu values(1004, 'WangYuan', 3)");
//    query.exec("insert into tbl_stu values(1005, 'YueYue',   4)");
//    query.exec("insert into tbl_stu values(1006, 'XiaXia',   5)");

//    // 学生科目分数表
//    query.exec("create table tbl_course (id int primary key, name varchar, score int)");
//    query.exec("insert into tbl_course values(1, 'Chianese', 135)");
//    query.exec("insert into tbl_course values(2, 'Math', 138)");
//    query.exec("insert into tbl_course values(3, 'English', 126)");
//    query.exec("insert into tbl_course values(4, 'Computer', 98)");
//    query.exec("insert into tbl_course values(5, 'History', 96)");

    query.exec("delete from tbl_stu where id >= 1");
    query.exec("create table tbl_stu (id int primary key, name varchar,course int)");
    query.exec("insert into tbl_stu values (1,'yafei0',1)");
    query.exec("insert into tbl_stu values (2,'yafei1',1)");
    query.exec("insert into tbl_stu values (3,'yafei2',2)");

    query.exec("delete from course where id >= 1");
    query.exec("create table course (id int primary key, name varchar, teacher varchar)");
    query.exec("insert into course values (1,'Math','yafeilinux1')");
    query.exec("insert into course values (2,'English','yafeilinux2')");
    query.exec("insert into course values (3,'Computer','yafeilinux3')");



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
