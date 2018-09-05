#include "widget.h"
#include <QApplication>
#include <QtSql>
#include"database.h"
#include <QSqlDatabase>
#include<qdebug.h>
int main(int argc, char *argv[])
{
    DataBase db;
    db.connectDB();

    QApplication a(argc, argv);
    Widget w;

    w.show();
    qDebug()<<"hello tq";

   // 加载QSS样式
   // CommonHelper::setStyle("cssStyle.qss");
    QFile qss(":/cssStyle.qss");
    qss.open(QFile::ReadOnly);
    w.setStyleSheet(qss.readAll());
    qss.close();


    return a.exec();
}
