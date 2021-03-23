#include "homepage_1.h"
#include "ui_homepage_1.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QSqlRecord>
#include<QSqlTableModel>
#include "setting.h"
#include "setting_2.h"
#include "budget.h"
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSlider>
#include <QtCharts>
#include <QDate>
#include <QtCharts/QAbstractBarSeries>
#include <QApplication>
#include "accounting.h"
#include "accountstatement.h"
#include "chart.h"

using namespace QtCharts;



Homepage_1::Homepage_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Homepage_1)
{
    ui->setupUi(this);





//Layout starts
    ui->leftLayout->addWidget(ui->HomepageBtn);
    ui->leftLayout->addWidget(ui->AccountingBtn);
    ui->leftLayout->addWidget(ui->AccountStatementBtn);
    ui->leftLayout->addWidget(ui->ChartBtn);



    ui->leftLayout->setSpacing(0);
    ui->leftLayout->setContentsMargins(QMargins(0,30,0,0));
    ui->leftLayout->addStretch();

    ui->leftContainer->setLayout(ui->leftLayout);
    ui->leftContainer->setMinimumWidth(165);
    ui->leftContainer->setMaximumWidth(165);




    connect(ui->AccountingBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_3_clicked()));
    connect(ui->AccountStatementBtn,SIGNAL(clicked(bool)),this,SLOT(change2AcountStatement()));
    connect(ui->ChartBtn,SIGNAL(clicked(bool)),this,SLOT(change2Chart()));
    showProgressDonut();
    list();

    //Budgetshow();
}

Homepage_1::~Homepage_1()
{
    delete ui;
}

void Homepage_1::list()
{
    //增加放大缩小控件
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    QDate currentDate;
    int ChosenYear=currentDate.currentDate().year();
    int ChosenMonth=currentDate.currentDate().month();
    int ChosenDay=currentDate.currentDate().day();
    double income=0;
    double outcome=0;

    QSqlQuery query;
    //查询获取本月收入支出
    query.prepare("select * from account where  year = :year and month = :month");
    query.bindValue(":year",ChosenYear);
    query.bindValue(":month",ChosenMonth);
    query.exec();
    while(query.next()){
        qDebug()<<QObject::tr("aaa");
        if(query.value(3)=="收入"){
            income += query.value(7).toDouble();
        }


        if(query.value(3)=="支出"){
            outcome +=query.value(7).toDouble();

        }
    }


    QString Income = QString::number(income);
    QString Outcome = QString::number(outcome);
    QString day=QString("%1年%2月%3日").arg(ChosenYear).arg(ChosenMonth).arg(ChosenDay);
    ui->IncomeLabel->setText(Income);
    ui->OutcomeLabel->setText(Outcome);
    ui->labelout->setText(Outcome);
    ui->day->setText(day);

    double budget=0;
    QSqlQuery query_2;
    //获取预算
    query_2.exec("select * from Budget where id = 1");
    query_2.exec();
    query_2.next();
   budget = query_2.value(1).toDouble();
    QString Budget = QString::number(budget);
    ui->label_5->setText(Budget);
    ui->labelbudget->setText(Budget);

   //计算余额
    double Remain = budget-outcome;
    QString remain = QString::number(Remain);
    ui->RemainLabel->setText(remain);
    ui->RemainLabel_2->setText(remain);
 //计算日均
    double Day=double(ChosenDay);
    double dayout_1=(outcome)/(Day);
    QString Dayout_1 = QString::number(dayout_1);
    ui->dayout_1label->setText(Dayout_1 );
    //计算百分比
    double output =(outcome)/(budget);
    double output_1;
    output_1= (floor(output * 100.000f + 0.5) / 100.000f)*100;/*保留小数点后两位*/
    //double output_1=(output)*100;
    QString Output_2 = QString::number(output_1);

    ui->percent->setText(Output_2+"%");

}

void Homepage_1::on_setBtn_clicked()//页面跳转
{

    QSqlQuery query_1;

    query_1.exec("select * from Password where id = 1");



    if(query_1.next())
    {
        Setting  *mysetting = new Setting();//新建了一个类的页面
        mysetting->show(); //展示新的页面
          this->close();
        mysetting->exec();

    }
    else
    {
        Setting_2  *mysetting_2 = new Setting_2();//新建了一个类的页面
        mysetting_2->show(); //展示新的页面
        this->close();
        mysetting_2->exec();

    }
}
void Homepage_1::on_pushButton_clicked()
{

    Budget  *mybudget = new Budget();//新建了一个类的页面
    mybudget->show(); //展示新的页面
    this->close();
    mybudget->exec();
}

QChart *Homepage_1::progressDonut(double budget){
    QDate current;
    int year=current.currentDate().year();
    int month=current.currentDate().month();
    QPieSeries *series=new QPieSeries();
    QSqlQuery query;
    query.prepare("select * from account where year=:currentYear and month =:currentMonth");
    query.bindValue(":currentYear",year);
    query.bindValue(":currentMonth",month);
    query.exec();

    double income=0;
    double outcome=0;
    while(query.next()){
        if(query.value(3)=="收入"){
            income+=query.value(7).toDouble();
        }
        if(query.value(3)=="支出"){
            outcome+=query.value(7).toDouble();
        }
    }
    if(budget>=outcome){
    double Remain = budget-outcome;
    series->append("支出",outcome);
    series->append("剩余",Remain);
    series->setHoleSize(0.6);

    QPieSlice *slice_in;
    QPieSlice *slice_out;
    slice_in=series->slices().at(0);
    slice_out=series->slices().at(1);

    slice_in->setColor(QColor("#ffbc2e"));
    slice_out->setColor(QColor("#fff"));
    }
    else{
        double Remain = outcome-budget;
        series->append("支出",outcome);
        series->append("超额",Remain);
        series->setHoleSize(0.5);

        QPieSlice *slice_in;
        QPieSlice *slice_out;
        slice_in=series->slices().at(0);
        slice_out=series->slices().at(1);


        //支出对应颜色调整

        //slice_in->setColor(QColor(""));
        slice_out->setColor(QColor("#ff0000"));
        ui->warning->setText("已超额");
        QString remain = QString::number(Remain);
        ui->remainmoney->setText(remain);
    }
    QChart *progressDonut=new QChart();
    progressDonut->addSeries(series);
    progressDonut->legend()->setVisible(false);
    progressDonut->setBackgroundBrush(QColor("#fafafa"));

    return progressDonut;
}
void Homepage_1::showProgressDonut(){

    double budget;
    QSqlQuery query_2;
    query_2.exec("select * from Budget where id = 1");
    query_2.exec();
    query_2.next();
budget = query_2.value(1).toDouble();

//画出图形
    QChartView *chartView=new QChartView(this->progressDonut(budget));
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setBackgroundBrush(QColor("#fafafa"));
    ui->progressDonut->addWidget(chartView);


}
void Homepage_1::on_pushButton_3_clicked()
{
    this->close();
    accounting  *myaccounting = new accounting();//新建了一个类的页面
    myaccounting->show(); //展示新的页面
    myaccounting->exec();
}
void Homepage_1::change2AcountStatement(){

    accountStatement *newAccountStatement=new accountStatement();
    newAccountStatement->show();
    newAccountStatement->DayChoose();
    this->close();
    newAccountStatement->exec();
}void Homepage_1::change2Chart(){

    chart *newChartPage=new chart();
    newChartPage->show();
    this->close();
    newChartPage->exec();
}
