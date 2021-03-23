#include "setting_2.h"
#include "ui_setting_2.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtCore/QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QSqlRecord>
#include<QSqlTableModel>
#include<QSqlError>
#include "homepage_1.h"
#include <QValidator>



Setting_2::Setting_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting_2)
{
    ui->setupUi(this);
     //增加放大缩小控件
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    ui->lineEdit_4->setValidator(new QIntValidator(0,9999,this));
}

Setting_2::~Setting_2()
{
    delete ui;
}


void Setting_2::on_pushButton_2_clicked()
{
    //设置密码
    QSqlQuery query_1;
    int lineEdit_4Text = ui->lineEdit_4->text().toInt();
    //写入密码
    query_1.prepare("insert into Password values(NULL,:password)");
     query_1.bindValue(":password",lineEdit_4Text);
     bool success = query_1.exec();
     if(success){
     qDebug()<<lineEdit_4Text<<QObject::tr("写入成功");
     }else{
     qDebug()<<QObject::tr("写入失败");
     }
    query_1.finish();

    Homepage_1  *myhomepage_1 = new Homepage_1();//新建了一个类的页面
    myhomepage_1->show(); //展示新的页面
    this->close();
    myhomepage_1->exec();


}


void Setting_2::on_pushButton_clicked() //提交修改
{
    Homepage_1  *myhomepage_1 = new Homepage_1();//新建了一个类的页面
    myhomepage_1->show(); //展示新的页面
    this->close();
    myhomepage_1->exec();

}
