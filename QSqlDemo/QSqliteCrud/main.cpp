#include "ManWin.h"
#include <QApplication>
#include "QSqliteConnect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建数据库数据和连接数据库
    if (!SqlConnect())
    {
        return true;
    }

    ManWin w;
    w.show();

    return a.exec();
}
