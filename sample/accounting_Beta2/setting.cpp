#include "setting.h"
#include "ui_setting.h"
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

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    ui->lineEdit->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_2->setValidator(new QIntValidator(0,9999,this));
}

Setting::~Setting()
{
    delete ui;
}
void Setting::on_pushButton_4_clicked()
{
    //修改密码
    spassword = ui->lineEdit->text().toInt();
    xinmima=ui->lineEdit_2->text().toInt();


    QSqlQuery query1;
//通过遍历查询到的结果找到自己想要的，然后可以将此值传递给指定的控件，并将其显示。
    query1.exec("select * from Password where id = 1");
    query1.next();
    password  = query1.value(1).toInt();
    query1.finish();


    if(password==spassword){

            int lineEdit_2Text = ui->lineEdit_2->text().toInt();
            //int lineEdit_3Text = ui->lineEdit_3->text().toInt();
            //页面跳转
            ui->lineEdit_2->setFocus();//将光标转到密码输入框

            QString update_sql = "update Password set password = :password where id = :id";
            query1.prepare(update_sql);
            query1.bindValue(":password", lineEdit_2Text);
            query1.bindValue(":id", 1);
            if(!query1.exec())
            {

                qDebug()<<query1.lastError();
            }
            else
            {

                qDebug()<<"updated!";
                //QMessageBox::information(NULL, "congratuulations", "success", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                ui->warning->setText("密码修改成功");

                Homepage_1  *myhomepage_1 = new Homepage_1();//新建了一个类的页面
                myhomepage_1->show(); //展示新的页面
                this->close();
                myhomepage_1->exec();

            }

        }

    else{
       // QMessageBox::warning(this,tr("Warning"),tr("password error!"),QMessageBox::Yes);//如果不正确，弹出警告对话框
        ui->warning->setText("密码错误");
        ui->lineEdit->clear();//清空密码输入框
        ui->lineEdit->setFocus();//将光标转到密码输入框
    }
}
void Setting::on_cancelBtn_clicked()
{
    Homepage_1  *myhomepage_1 = new Homepage_1();//新建了一个类的页面
    myhomepage_1->show(); //展示新的页面
    this->close();
    myhomepage_1->exec();}
