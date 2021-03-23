#ifndef DONUTCHART_H
#define DONUTCHART_H
#include<QtCharts>
#include<QMainWindow>
using namespace QtCharts;
class donutChart
{
private:
    QPieSeries *series_income;
    QPieSeries *series_outcome;
    QPieSlice *slice_1;
    QPieSlice *slice_2;
    QPieSlice *slice_3;
    QPieSlice *slice_4;
    QPieSlice *slice_5;
    QPieSlice *slice_6;
    QPieSlice *slice_7;
    QPieSlice *slice_8;
    QPieSlice *slice_9;
    QPieSlice *slice_10;
    QPieSlice *slice_11;
    QPieSlice *slice_12;
public:
    donutChart();
    QChart *showInCmp(int year,int month);
    QChart *showOutCmp(int year,int month);
};

#endif // DONUTCHART_H
