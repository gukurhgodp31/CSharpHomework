#ifndef BARCHART_H
#define BARCHART_H

#include<QtCharts>
#include<QtCharts/QBarSet>
#include <QMainWindow>


using namespace QtCharts;
class barChart
{

public:
    //构造函数用于创建数据
    barChart();
    ~barChart();
    /*int checkMonth(int year,int month);
    bool checkFeb(int year);*/

    QChart *showInOutCmp(int year);
    QChart *showInCmp(int year,int month);
    QChart *showOutCmp(int year,int month);
private:
    QBarSet *barIncome_total;
    QBarSet *barOutcome_total;
    QBarSet *barIncome_sep;
    QBarSet *barOutcome_sep;
    /*QBarSet *barIncome_1;
    QBarSet *barIncome_2;
    QBarSet *barIncome_3;
    QBarSet *barIncome_4;
    QBarSet *barIncome_5;
    QBarSet *barIncome_6;
    QBarSet *barOutcome_1;
    QBarSet *barOutcome_2;
    QBarSet *barOutcome_3;
    QBarSet *barOutcome_4;
    QBarSet *barOutcome_5;
    QBarSet *barOutcome_6;
    QBarSet *barOutcome_7;
    QBarSet *barOutcome_8;
    QBarSet *barOutcome_9;
    QBarSet *barOutcome_10;
    QBarSet *barOutcome_11;
    QBarSet *barOutcome_12;*/

    QBarSeries *series_totalCmp;
    QBarSeries *series_incomeCmp;
    QBarSeries *series_outcomeCmp;
    //barIncome_1,barIncome_2,barIncome_3,barIncome_4,barIncome_5,barIncome_6,barIncome_total=new QBarSet;
    //barOutcome_1,barOutcome_2,barOutcome_3,barOutcome_4,barOutcome_5,barOutcome_6,barOutcome_7,barOutcome_8,barOutcome_9,barOutcome_10,barOutcome_11,barOutcome_12,barOutcome_13,barOutcome_total=new QBarSet;
};

#endif // BARCHART_H
