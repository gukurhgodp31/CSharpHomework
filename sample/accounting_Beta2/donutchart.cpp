#include "donutChart.h"
#include <QtCharts>
#include <QApplication>
#include <QtSql>

donutChart::donutChart()
{
    series_income = new QPieSeries();
    series_outcome=new QPieSeries();
}

QChart *donutChart::showInCmp(int year, int month){
    if(month!=0){
        QSqlQuery query;
        query.prepare("select * from account where year=:currentYear and month=:currentMonth");
        query.bindValue(":currentYear",year);
        query.bindValue(":currentMonth",month);
        query.exec();

        double incomeTypeStatistics[6]={0};
        int type;
        while(query.next()){
            type=query.value(2).toInt();
            if(query.value(3)=="收入"){
                 incomeTypeStatistics[type]+=query.value(7).toDouble();
            }
        }
        series_income->append("一般",incomeTypeStatistics[0]);
        series_income->append("生活费",incomeTypeStatistics[1]);
        series_income->append("奖学金",incomeTypeStatistics[2]);
        series_income->append("工资",incomeTypeStatistics[3]);
        series_income->append("红包",incomeTypeStatistics[4]);
        series_income->append("其他",incomeTypeStatistics[5]);

        slice_1=series_income->slices().at(0);
        slice_2=series_income->slices().at(1);
        slice_3=series_income->slices().at(2);
        slice_4=series_income->slices().at(3);
        slice_5=series_income->slices().at(4);
        slice_6=series_income->slices().at(5);


        slice_1->setColor(QColor("#ff7052"));
        slice_2->setColor(QColor("#fff510"));
        slice_3->setColor(QColor("#6cdb44"));
        slice_4->setColor(QColor("#62acff"));
        slice_5->setColor(QColor("#8f52d9"));
        slice_6->setColor(QColor("#c0c0c0"));


        QChart *incomeCmp =new QChart();
        incomeCmp->addSeries(series_income);
        //incomeCmp->setTitle("月收入份额");
        incomeCmp->legend()->setVisible(false);
        incomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));

        return incomeCmp;
    }
    if(month==0){
            QSqlQuery query;
            query.prepare("select * from account where year=:currentYear");
            query.bindValue(":currentYear",year);
            query.exec();

            double incomeTypeStatistics[6]={0};
            int type;
            while(query.next()){
                type=query.value(2).toInt();
                if(query.value(3)=="收入"){
                     incomeTypeStatistics[type]+=query.value(7).toDouble();
                }
            }
            series_income->append("一般",incomeTypeStatistics[0]);
            series_income->append("生活费",incomeTypeStatistics[1]);
            series_income->append("奖学金",incomeTypeStatistics[2]);
            series_income->append("工资",incomeTypeStatistics[3]);
            series_income->append("红包",incomeTypeStatistics[4]);
            series_income->append("其他",incomeTypeStatistics[5]);

            slice_1=series_income->slices().at(0);
            slice_2=series_income->slices().at(1);
            slice_3=series_income->slices().at(2);
            slice_4=series_income->slices().at(3);
            slice_5=series_income->slices().at(4);
            slice_6=series_income->slices().at(5);

            slice_1->setColor(QColor("#ff7052"));
            slice_2->setColor(QColor("#fff510"));
            slice_3->setColor(QColor("#6cdb44"));
            slice_4->setColor(QColor("#62acff"));
            slice_5->setColor(QColor("#8f52d9"));
            slice_6->setColor(QColor("#c0c0c0"));


            QChart *incomeCmp =new QChart();
            incomeCmp->addSeries(series_income);
            //incomeCmp->setTitle("年收入份额");
            incomeCmp->legend()->setVisible(false);
            incomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));


            return incomeCmp;

    }
}

QChart *donutChart::showOutCmp(int year,int month){
    if(month!=0){
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
        series_outcome->append("一般",outcomeTypeStatistics[0]);
        series_outcome->append("饮食",outcomeTypeStatistics[1]);
        series_outcome->append("交通",outcomeTypeStatistics[2]);
        series_outcome->append("衣饰",outcomeTypeStatistics[3]);
        series_outcome->append("医疗",outcomeTypeStatistics[4]);
        series_outcome->append("通讯",outcomeTypeStatistics[5]);
        series_outcome->append("化妆",outcomeTypeStatistics[6]);
        series_outcome->append("学习",outcomeTypeStatistics[7]);
        series_outcome->append("日用",outcomeTypeStatistics[8]);
        series_outcome->append("娱乐",outcomeTypeStatistics[9]);
        series_outcome->append("社交",outcomeTypeStatistics[10]);
        series_outcome->append("其他",outcomeTypeStatistics[11]);


        slice_1=series_outcome->slices().at(0);
        slice_2=series_outcome->slices().at(1);
        slice_3=series_outcome->slices().at(2);
        slice_4=series_outcome->slices().at(3);
        slice_5=series_outcome->slices().at(4);
        slice_6=series_outcome->slices().at(5);
        slice_7=series_outcome->slices().at(6);
        slice_8=series_outcome->slices().at(7);
        slice_9=series_outcome->slices().at(8);
        slice_10=series_outcome->slices().at(9);
        slice_11=series_outcome->slices().at(10);
        slice_12=series_outcome->slices().at(11);

        slice_1->setColor(QColor("#ff7052"));
        slice_2->setColor(QColor("#ffa530"));
        slice_3->setColor(QColor("#fff510"));
        slice_4->setColor(QColor("#bff700"));
        slice_5->setColor(QColor("#6cdb44"));
        slice_6->setColor(QColor("#4adfaa"));
        slice_7->setColor(QColor("#62acff"));
        slice_8->setColor(QColor("#6170e7"));
        slice_9->setColor(QColor("#8f52d9"));
        slice_10->setColor(QColor("#cd58cf"));
        slice_11->setColor(QColor("#f35e91"));
        slice_12->setColor(QColor("#c0c0c0"));




        QChart *outcomeCmp =new QChart();
        outcomeCmp->addSeries(series_outcome);
        //outcomeCmp->setTitle("月支出份额");
        outcomeCmp->legend()->setVisible(false);
        outcomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));


        return outcomeCmp;
    }
    if(month==0){
            QSqlQuery query;
            query.prepare("select * from account where year=:currentYear");
            query.bindValue(":currentYear",year);
            query.exec();

            double outcomeTypeStatistics[12]={0};
            int type;
            while(query.next()){
                type=query.value(2).toInt()-6;
                if(query.value(3)=="支出"){
                     outcomeTypeStatistics[type]+=query.value(7).toDouble();
                }
            }
            series_outcome->append("一般",outcomeTypeStatistics[0]);
            series_outcome->append("饮食",outcomeTypeStatistics[1]);
            series_outcome->append("交通",outcomeTypeStatistics[2]);
            series_outcome->append("衣饰",outcomeTypeStatistics[3]);
            series_outcome->append("医疗",outcomeTypeStatistics[4]);
            series_outcome->append("通讯",outcomeTypeStatistics[5]);
            series_outcome->append("化妆",outcomeTypeStatistics[6]);
            series_outcome->append("学习",outcomeTypeStatistics[7]);
            series_outcome->append("日用",outcomeTypeStatistics[8]);
            series_outcome->append("娱乐",outcomeTypeStatistics[9]);
            series_outcome->append("社交",outcomeTypeStatistics[10]);
            series_outcome->append("其他",outcomeTypeStatistics[11]);



            slice_1=series_outcome->slices().at(0);
            slice_2=series_outcome->slices().at(1);
            slice_3=series_outcome->slices().at(2);
            slice_4=series_outcome->slices().at(3);
            slice_5=series_outcome->slices().at(4);
            slice_6=series_outcome->slices().at(5);
            slice_7=series_outcome->slices().at(6);
            slice_8=series_outcome->slices().at(7);
            slice_9=series_outcome->slices().at(8);
            slice_10=series_outcome->slices().at(9);
            slice_11=series_outcome->slices().at(10);
            slice_12=series_outcome->slices().at(11);

            slice_1->setColor(QColor("#ff7052"));
            slice_2->setColor(QColor("#ffa530"));
            slice_3->setColor(QColor("#fff510"));
            slice_4->setColor(QColor("#bff700"));
            slice_5->setColor(QColor("#6cdb44"));
            slice_6->setColor(QColor("#4adfaa"));
            slice_7->setColor(QColor("#62acff"));
            slice_8->setColor(QColor("#6170e7"));
            slice_9->setColor(QColor("#8f52d9"));
            slice_10->setColor(QColor("#cd58cf"));
            slice_11->setColor(QColor("#f35e91"));
            slice_12->setColor(QColor("#c0c0c0"));





            QChart *outcomeCmp =new QChart();
            outcomeCmp->addSeries(series_outcome);
            //outcomeCmp->setTitle("年支出份额");
            outcomeCmp->legend()->setVisible(false);
            outcomeCmp->setBackgroundBrush(QBrush(QColor("#fafafa")));

            return outcomeCmp;

    }
}
