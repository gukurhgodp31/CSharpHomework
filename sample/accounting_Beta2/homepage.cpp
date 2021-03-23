#include "homepage.h"
#include "ui_homepage.h"
#include <QtGui>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include<QSqlTableModel>
#include <QSqlRecord>
#include<QKeyEvent>
#include<QShortcut>
#include "homepage_1.h"
#include <QValidator>

homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
//    ui->loginBtn->setEnabled(true);
    //增加放大缩小控件
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    ui->pwdLineEdit->setValidator(new  QIntValidator(0,9999,this));
}

homepage::~homepage()
{
    delete ui;
}
void homepage::on_loginBtn_clicked()
{
    spassword = ui->pwdLineEdit->text().toInt();
    //通过遍历查询到的结果找到自己想要的，然后可以将此值传递给指定的控件，并将其显示。
    QSqlQuery query;
    query.exec("select * from Password where id = 1");
    query.next();
    password  = query.value(1).toInt();
    //将密码框的密码与数据库存储的密码比对
    if(password==spassword){
        //页面跳转
        this->close();
        Homepage_1  *myhomepage_1 = new Homepage_1();//新建了一个类的页面
        myhomepage_1->show(); //展示新的页面
        myhomepage_1->exec();

    }
    else{
        //QMessageBox::warning(this,tr("Warning"),tr("password error!"),QMessageBox::Yes); //如果不正确，弹出警告对话框
        ui->warning->setText("密码错误");
        ui->pwdLineEdit->clear();//清空密码输入框
        ui->pwdLineEdit->setFocus();//将光标转到密码输入框
    }
   query.finish();
}
