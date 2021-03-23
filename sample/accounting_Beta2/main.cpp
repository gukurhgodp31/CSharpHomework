#include "accounting.h"
#include "chart.h"
#include "homepage.h"
#include <QApplication>
#include <QtSql>
#include <QtCharts>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    if(!db.open()){
        return false;
    }
    QSqlQuery query;
    query.exec("create table account (id INTEGER primary key autoincrement,category varchar(8),categoryNum int,inoutcome varchar(8),year int,month int,day int,amount varchar(13),RemarkText varchar(255))");
    homepage w;
    //新建存储密码表
    QSqlQuery query_1;
    query_1.exec("create table Password (id INTEGER primary key autoincrement, password int)");
    //新建存储预算表
    QSqlQuery query_2;
    query_2.exec("create table Budget (id INTEGER primary key autoincrement, budget int)");
    query_2.prepare("insert into Budget values(1,:budget)");
    query_2.bindValue(":budget",800);
    query_2.exec();

    w.show();

    return a.exec();
}
