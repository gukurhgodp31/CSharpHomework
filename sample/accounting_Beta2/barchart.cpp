#include "barChart.h"

#include <QApplication>
#include<QtCharts>
#include<QtSql>
#include<QDebug>
#include<QStringList>


barChart::barChart()
{
    //创建柱
    barIncome_total=new QBarSet("总收入");
    barOutcome_total=new QBarSet("总支出");
    barIncome_sep=new QBarSet("分类收入");
    barOutcome_sep=new QBarSet("分类支出");


    barIncome_total->setColor(QColor("#3893ff"));
    barOutcome_total->setColor(QColor("#ff6c50"));
    barIncome_sep->setColor(QColor("#ffbc2e"));
    barOutcome_sep->setColor(QColor("#ffbc2e"));



    series_totalCmp=new QBarSeries();
    series_incomeCmp=new QBarSeries();
    series_outcomeCmp=new QBarSeries();

    series_totalCmp->append(barIncome_total);
    series_totalCmp->append(barOutcome_total);
    series_incomeCmp->append(barIncome_sep);
    series_outcomeCmp->append(barOutcome_sep);


}
barChart::~barChart(){

}


QChart *barChart::showInOutCmp(int year){
        //输入输出年表
        //开启数据库
        QSqlQuery query;
        query.prepare("select * from account where year=:Year");
        query.bindValue(":Year",year);
        query.exec();

        double incomeStatistics[12]={0};
        double outcomeStatistics[12]={0};
        int date;
        while(query.next()){
            date=query.value(5).toInt();
            if(query.value(3)=="收入"){
                incomeStatistics[date-1]+=query.value(7).toDouble();
            }
            else{
                outcomeStatistics[date-1]+=query.value(7).toDouble();
            }
        }
        //添加数据
        for(int i=0;i<12;i++){
            barIncome_total->append(incomeStatistics[i]);
            barOutcome_total->append(outcomeStatistics[i]);
        }

        QChart *monthC=new QChart();
        monthC->addSeries(series_totalCmp);
        //monthC->setTitle("收支对比年报");
        monthC->setAnimationOptions(QChart::SeriesAnimations);
        monthC->setBackgroundBrush(QBrush(QColor("#fafafa")));
        //创建下标
        QStringList monthList;
        monthList<<"1月"<<"2月"<<"3月"<<"4月"<<"5月"<<"6月"<<"7月"<<"8月"<<"9月"<<"10月"<<"11月"<<"12月";
        QBarCategoryAxis *monthAxis=new QBarCategoryAxis();
        monthAxis->append(monthList);
        monthC->createDefaultAxes();
        monthC->setAxisX(monthAxis,series_totalCmp);
        monthC->legend()->setVisible(true);
        monthC->legend()->setAlignment(Qt::AlignBottom);

        return monthC;
}



QChart *barChart::showInCmp(int year,int month){
    //判断年表或月表
    if(0!=month){
        //开启数据库
        QSqlQuery query;
        query.prepare("select * from account where year=:currentYear and month=:currentMonth");
        query.bindValue(":currentYear",year);
        query.bindValue(":currentMonth",month);
        query.exec();

        double incomeTypeStatistics[6]={0};
        int type;
        while(query.next()){//数据录入
            type=query.value(2).toInt();
            if(query.value(3)=="收入"){
                incomeTypeStatistics[type]+=query.value(7).toDouble();
            }
        }
        for(int i=0;i<6;i++){
            barIncome_sep->append(incomeTypeStatistics[i]);
        }

        QChart *incomeCmp=new QChart();
        incomeCmp->addSeries(series_incomeCmp);
        //incomeCmp->setTitle("收入对比月报");
        incomeCmp->setAnimationOptions(QChart::SeriesAnimations);
        incomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));
        //创建下标
        QStringList incomeType;
        incomeType<<"一般"<<"生活费"<<"奖学金"<<"工资"<<"红包"<<"其他";
        QBarCategoryAxis *incomeAxis=new QBarCategoryAxis();
        incomeAxis->append(incomeType);
        incomeCmp->createDefaultAxes();
        incomeCmp->setAxisX(incomeAxis,series_incomeCmp);

        return incomeCmp;
    }
    if(0==month){
        QSqlQuery query;
        query.prepare("select * from account where year=:Year");
        query.bindValue(":Year",year);
        query.exec();

        double incomeTypeStatistics[6]={0};
        int type;
        while(query.next()){
            type=query.value(2).toInt();
            if(query.value(3)=="收入"){
                incomeTypeStatistics[type]+=query.value(7).toDouble();
            }
        }
        for(int i=0;i<6;i++){//导入数据
            barIncome_sep->append(incomeTypeStatistics[i]);
        }

        QChart *incomeCmp=new QChart();
        incomeCmp->addSeries(series_incomeCmp);
        //incomeCmp->setTitle("收入对比年报");
        incomeCmp->setAnimationOptions(QChart::SeriesAnimations);
        incomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));

        QStringList incomeType;
        incomeType<<"一般"<<"生活费"<<"奖学金"<<"工资"<<"红包"<<"其他";;
        QBarCategoryAxis *incomeAxis=new QBarCategoryAxis();
        incomeAxis->append(incomeType);
        incomeCmp->createDefaultAxes();
        incomeCmp->setAxisX(incomeAxis,series_incomeCmp);


        return incomeCmp;
    }
}
//支出类型对比
QChart *barChart::showOutCmp(int year,int month){
    if(0!=month){
        QSqlQuery query;
        query.prepare("select * from account where year=:currentYear and month=:currentMonth");
        query.bindValue(":currentYear",year);
        query.bindValue(":currentMonth",month);
        query.exec();

        double outcomeTypeStatistics[12]={0};
        int type;
        while(query.next()){
            type=query.value(2).toInt()-6;
            if(query.value(3)=="支出"){
                outcomeTypeStatistics[type]+=query.value(7).toDouble();
            }
        }
        for(int i=0;i<12;i++){
            barOutcome_sep->append(outcomeTypeStatistics[i]);
        }

        QChart *outcomeCmp=new QChart();
        outcomeCmp->addSeries(series_outcomeCmp);
        //outcomeCmp->setTitle("支出对比月报");
        outcomeCmp->setAnimationOptions(QChart::SeriesAnimations);
        outcomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));

        QStringList outcomeType;
        outcomeType<<"一般"<<"饮食"<<"交通"<<"衣饰"<<"医疗"<<"通讯"<<"化妆"<<"学习"<<"日用"<<"娱乐"<<"社交"<<"其他";
        QBarCategoryAxis *outcomeAxis=new QBarCategoryAxis();
        outcomeAxis->append(outcomeType);
        outcomeCmp->createDefaultAxes();
        outcomeCmp->setAxisX(outcomeAxis,series_outcomeCmp);
        outcomeCmp->legend()->setVisible(true);
        outcomeCmp->legend()->setAlignment(Qt::AlignBottom);

        return outcomeCmp;
    }
    if(0==month){
        QSqlQuery query;
        query.prepare("select * from account where year=:Year");
        query.bindValue(":Year",year);
        query.exec();

        double outcomeTypeStatistics[12]={0};
        int type;
        while(query.next()){
            type=query.value(2).toInt()-6;
            if(query.value(3)=="支出"){
                outcomeTypeStatistics[type]+=query.value(7).toDouble();
            }
        }
        for(int i=0;i<12;i++){
            barOutcome_sep->append(outcomeTypeStatistics[i]);
        }

        QChart *outcomeCmp=new QChart();
        outcomeCmp->addSeries(series_outcomeCmp);
        //outcomeCmp->setTitle("支出对比年报");
        outcomeCmp->setAnimationOptions(QChart::SeriesAnimations);
        outcomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));

        QStringList outcomeType;
        outcomeType<<"一般"<<"饮食"<<"交通"<<"衣饰"<<"医疗"<<"通讯"<<"化妆"<<"学习"<<"日用"<<"娱乐"<<"社交"<<"其他";
        QBarCategoryAxis *outcomeAxis=new QBarCategoryAxis();
        outcomeAxis->append(outcomeType);
        outcomeCmp->createDefaultAxes();
        outcomeCmp->setAxisX(outcomeAxis,series_outcomeCmp);
        outcomeCmp->legend()->setVisible(true);
        outcomeCmp->legend()->setAlignment(Qt::AlignBottom);

        return outcomeCmp;
    }
}
