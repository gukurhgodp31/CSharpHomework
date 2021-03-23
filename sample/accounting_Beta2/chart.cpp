#include "chart.h"
#include "ui_chart.h"
#include "barChart.h"
#include "donutChart.h"
#include "accounting.h"
#include "accountstatement.h"
#include "homepage_1.h"
#include <QtCharts>
#include <QString>
#include "setting.h"
#include "setting_2.h"
using namespace QtCharts;
static QChartView *currentChartView;
static bool isDonut=false;
static QChartView *currentDonutChart;

chart::chart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chart)
{

    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinMaxButtonsHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    ui->setupUi(this);



//Layout Starts
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
    ui->incomeInfo->setVisible(false);
    ui->incomeLabel->setVisible(false);
    ui->outcomeInfo->setVisible(false);
    ui->outcomeLabel->setVisible(false);


    //信号与槽的链接
    connect(ui->chooseChart,SIGNAL(currentIndexChanged(int)),this,SLOT(selectChart()));
    connect(ui->chooseMonth,SIGNAL(currentIndexChanged(int)),this,SLOT(selectChart()));
    connect(ui->chooseYear,SIGNAL(currentIndexChanged(int)),this,SLOT(selectChart()));
    connect(ui->AccountingBtn,SIGNAL(clicked(bool)),this,SLOT(change2Accounting()));
    connect(ui->AccountStatementBtn,SIGNAL(clicked(bool)),this,SLOT(change2AcountStatement()));
    connect(ui->HomepageBtn,SIGNAL(clicked(bool)),this,SLOT(change2HomePage()));

    defaultChart();
}

chart::~chart()
{
    delete ui;
}
void chart::defaultChart(){
    barChart defaultChart;
    QChartView *monthView=new QChartView(defaultChart.showInOutCmp(2016));
    monthView->setRenderHint(QPainter::Antialiasing);
    monthView->setBackgroundBrush(QBrush(QColor("#fafafa")));
    ui->chartLayout->addWidget(monthView);
    currentChartView=monthView;
}
void chart::showInOutCmpBar(){
    ui->incomeInfo->setVisible(false);
    ui->incomeLabel->setVisible(false);
    ui->outcomeInfo->setVisible(false);
    ui->outcomeLabel->setVisible(false);

    int year=getYear();
    barChart inOutChart;
    QChartView *inOutCmpBarView=new QChartView(inOutChart.showInOutCmp(year));
    inOutCmpBarView->setRenderHint(QPainter::Antialiasing);
    inOutCmpBarView->setBackgroundBrush(QBrush(QColor("#fafafa")));
    if(isDonut){
        ui->chartLayout->removeWidget(currentDonutChart);
        isDonut=false;
    }
    ui->chartLayout->replaceWidget(currentChartView,inOutCmpBarView);
    currentChartView=inOutCmpBarView;
}
void chart::showInCmpBar(){
    ui->incomeInfo->setVisible(false);
    ui->incomeLabel->setVisible(false);
    ui->outcomeInfo->setVisible(false);
    ui->outcomeLabel->setVisible(false);

    int year=getYear();
    int month=getMonth();
    barChart inCmpChart;
    QChartView *inCmpBarView=new QChartView(inCmpChart.showInCmp(year,month));
    inCmpBarView->setRenderHint(QPainter::Antialiasing);
    inCmpBarView->setBackgroundBrush(QBrush(QColor("#fafafa")));
    if(isDonut){
        ui->chartLayout->removeWidget(currentDonutChart);
        isDonut=false;
    }
    ui->chartLayout->replaceWidget(currentChartView,inCmpBarView);
    currentChartView=inCmpBarView;
}
void chart::showOutCmpBar(){
    ui->incomeInfo->setVisible(false);
    ui->incomeLabel->setVisible(false);
    ui->outcomeInfo->setVisible(false);
    ui->outcomeLabel->setVisible(false);

    int year=getYear();
    int month=getMonth();
    barChart outCmpChart;
    QChartView *outCmpBarView=new QChartView(outCmpChart.showOutCmp(year,month));
    outCmpBarView->setRenderHint(QPainter::Antialiasing);
    outCmpBarView->setBackgroundBrush(QBrush(QColor("#fafafa")));
    if(isDonut){
        ui->chartLayout->removeWidget(currentDonutChart);
        isDonut=false;
    }
    ui->chartLayout->replaceWidget(currentChartView,outCmpBarView);
    currentChartView=outCmpBarView;
}
void chart::showInOutCmpDonut(){
    int year=getYear();
    int month=getMonth();
    donutChart inCmpChart;
    QChartView *inCmpChartView=new QChartView(inCmpChart.showInCmp(year,month));
    inCmpChartView->setRenderHint(QPainter::Antialiasing);
    inCmpChartView->setBackgroundBrush(QBrush(QColor("#fafafa")));

    donutChart outCmpChart;
    QChartView *outCmpChartView=new QChartView(outCmpChart.showOutCmp(year,month));
    outCmpChartView->setRenderHint(QPainter::Antialiasing);
    outCmpChartView->setBackgroundBrush(QBrush(QColor("#fafafa")));
    //ui->chartLayout->removeWidget(currentChartView);
    if(isDonut){
        ui->chartLayout->removeWidget(currentDonutChart);
        isDonut=false;
    }
    ui->incomeInfo->setVisible(true);
    ui->incomeLabel->setVisible(true);
    ui->outcomeInfo->setVisible(true);
    ui->outcomeLabel->setVisible(true);

    ui->chartLayout->replaceWidget(currentChartView,outCmpChartView);
    ui->chartLayout->addWidget(inCmpChartView);
    ui->chartLayout->setStretchFactor(outCmpChartView,1);
    ui->chartLayout->setStretchFactor(inCmpChartView,1);
    currentChartView=inCmpChartView;
    currentDonutChart=outCmpChartView;
    isDonut=true;
}

int chart::getYear(){
    int year;
    int index=ui->chooseYear->currentIndex();
    year=index+2015;
    return year;
}
int chart::getMonth(){
    int month;
    int data=ui->chooseMonth->currentIndex();
    if(data==0){
        month=0;
    }
    else{
        month=data;
    }
    return month;
}
void chart::selectChart(){
    int chart=ui->chooseChart->currentIndex();
    switch(chart){
    case 0:
        showInOutCmpBar();
        break;
    case 1:
        showInCmpBar();
        break;
    case 2:
        showOutCmpBar();
        break;
    case 3:
        showInOutCmpDonut();
        break;
    }
}
void chart::change2Accounting(){

    accounting *newAccountingPage=new accounting;
    newAccountingPage->show();
    this->close();
    newAccountingPage->exec();
}
void chart::change2AcountStatement(){

    accountStatement *newAccountStatement=new accountStatement();
    newAccountStatement->show();
    newAccountStatement->DayChoose();
    this->close();
    newAccountStatement->exec();
}
void chart::change2HomePage(){
    Homepage_1 *newHomePage=new Homepage_1();
    newHomePage->show();
    this->close();
    newHomePage->exec();
}
void chart::on_setBtn_clicked()//页面跳转
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
