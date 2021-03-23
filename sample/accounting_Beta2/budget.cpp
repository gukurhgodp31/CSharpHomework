#include "budget.h"
#include "ui_budget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "homepage_1.h"

Budget::Budget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Budget)
{
    ui->setupUi(this);
     //增加放大缩小控件
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
}

Budget::~Budget()
{
    delete ui;
}
void Budget::on_setBtn_clicked()
{
    //重新设置预算
    QSqlQuery query_2;
    QString lineEditText = ui->lineEdit->text();
    QString update_sql = "update Budget set budget = :budget where id = :id";
    query_2.prepare(update_sql);
    query_2.bindValue(":budget", lineEditText);
    query_2.bindValue(":id", 1);
    if(query_2.exec())
    {
        qDebug()<<"updated!";
        this->close();//关闭此页面
        Homepage_1  *myhomepage_1 = new Homepage_1();//新建了一个类的页面
        myhomepage_1->show(); //展示新的页面
        myhomepage_1->exec();

    }
}

void Budget::on_pushButton_clicked()
{
   this->close();
    Homepage_1  *myhomepage_1 = new Homepage_1();//新建了一个类的页面
    myhomepage_1->show(); //展示新的页面
    myhomepage_1->exec();
}
