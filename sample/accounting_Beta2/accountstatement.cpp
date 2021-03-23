#include "accountstatement.h"
#include "ui_accountstatement.h"
#include "accounting.h"
#include "editpage.h"
#include "chart.h"
#include "homepage_1.h"
#include <QDate>
#include <QString>
#include <QTableView>
#include <QtSql/QSqlTableModel>
#include "setting.h"
#include "setting_2.h"
static QString StrYear = "2016";
static QString StrMonth = "1";
static QString StrDay = "1";
static QString InOutCome = "收入与支出";


accountStatement::accountStatement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountStatement)
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




        connect(ui->DayBox,SIGNAL(currentTextChanged(QString)),this,SLOT(DayChoose()));
        connect(ui->InOutcomeBox,SIGNAL(currentTextChanged(QString)),this,SLOT(InOutcomeBoxChanged()));
        connect(ui->EditBtn,SIGNAL(clicked(bool)),this,SLOT(EditBtnClicked()));
        connect(ui->MonthBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(MonthChoose()));
        connect(ui->AccountingBtn,SIGNAL(clicked(bool)),this,SLOT(change2Accounting()));
        connect(ui->ChartBtn,SIGNAL(clicked(bool)),this,SLOT(change2Chart()));
        connect(ui->HomepageBtn,SIGNAL(clicked(bool)),this,SLOT(change2HomePage()));

}

void accountStatement::DayChoose(){//选择日期下拉框时显示表格
            int IncomeAccount = 0;
            int OutcomeAccount = 0;
            int ChosenYear = ui->YearBox->currentText().toInt();
            int ChosenMonth = ui->MonthBox->currentText().toInt();
            int ChosenDay = ui->DayBox->currentText().toInt();
            StrYear = QString::number(ChosenYear,10);
            StrMonth = QString::number(ChosenMonth,10);
            StrDay = QString::number(ChosenDay,10);


            //ui->Calendar->setHidden(true);




            QSqlQuery query;//从数据库中筛选账目并统计收入、支出显示在用户界面上
            query.prepare("select * from account where inoutcome = :inoutcome and year = :year and month = :month and day = :day");
            query.bindValue(":inoutcome","收入");
            query.bindValue(":year",ChosenYear);
            query.bindValue(":month",ChosenMonth);
            query.bindValue(":day",ChosenDay);
            query.exec();
            while(query.next()){
                IncomeAccount += query.value(7).toInt();
                qDebug()<<QObject::tr("咕咕咕");
            }
            query.prepare("select * from account where inoutcome = :inoutcome and year = :year and month = :month and day = :day");
            query.bindValue(":inoutcome","支出");
            query.bindValue(":year",ChosenYear);
            query.bindValue(":month",ChosenMonth);
            query.bindValue(":day",ChosenDay);
            query.exec();
            while(query.next()){
                OutcomeAccount += query.value(7).toInt();
                qDebug()<<QObject::tr("咕咕咕");
            }
            QString Income = QString::number(IncomeAccount);
            QString Outcome = QString::number(OutcomeAccount);
            ui->IncomeLabel->setText(Income);
            ui->OutcomeLabel->setText(Outcome);



            QSqlTableModel *TestModel;//建立表格

            TestModel = new QSqlTableModel(this);
            TestModel->setTable("account");
            TestModel->setHeaderData(0, Qt::Horizontal, tr("类别"));
            TestModel->setHeaderData(1, Qt::Horizontal, tr("收入/支出"));
            TestModel->setHeaderData(2, Qt::Horizontal, tr("金额"));
            TestModel->setHeaderData(3, Qt::Horizontal, tr("备注"));
            TestModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            //TestModel->setFilter(QObject::tr("year = %1 ").arg(StrYear));
            //TestModel->setFilter(QObject::tr("month = %1 ").arg(StrMonth));
            if(InOutCome == "收入"){
                TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 and inoutcome = '收入'").arg(StrYear,StrMonth,StrDay));
            }
            if(InOutCome == "支出"){
                TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 and inoutcome = '支出'").arg(StrYear,StrMonth,StrDay));
            }
            if(InOutCome == "收入与支出"){
                TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 ").arg(StrYear,StrMonth,StrDay));
            }
            TestModel->select();
            TestModel->removeColumn(0);
            TestModel->removeColumn(1);
            TestModel->removeColumn(2);
            TestModel->removeColumn(2);
            TestModel->removeColumn(2);
            qDebug()<<QObject::tr("哔哔哔");

            ui->tableView->setModel(TestModel);
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);




        }
accountStatement::~accountStatement()
{
    delete ui;
}
        void accountStatement::MonthChoose(){//选择月份下拉框时显示表格

            int IncomeAccount = 0;
            int OutcomeAccount = 0;
            int ChosenYear = ui->YearBox->currentText().toInt();
            int ChosenMonth = ui->MonthBox->currentText().toInt();
            int ChosenDay = ui->DayBox->currentText().toInt();
            StrYear = QString::number(ChosenYear,10);
            StrMonth = QString::number(ChosenMonth,10);
            StrDay = QString::number(ChosenDay,10);


            QSqlQuery query;
            query.prepare("select * from account where inoutcome = :inoutcome and year = :year and month = :month and day = :day");
            query.bindValue(":inoutcome","收入");
            query.bindValue(":year",ChosenYear);
            query.bindValue(":month",ChosenMonth);
            query.bindValue(":day",ChosenDay);
            query.exec();
            while(query.next()){
                IncomeAccount += query.value(7).toInt();
                qDebug()<<QObject::tr("咕咕咕");
            }
            query.prepare("select * from account where inoutcome = :inoutcome and year = :year and month = :month and day = :day");
            query.bindValue(":inoutcome","支出");
            query.bindValue(":year",ChosenYear);
            query.bindValue(":month",ChosenMonth);
            query.bindValue(":day",ChosenDay);
            query.exec();
            while(query.next()){
                OutcomeAccount += query.value(7).toInt();
                qDebug()<<QObject::tr("咕咕咕");
            }
            QString Income = QString::number(IncomeAccount);
            QString Outcome = QString::number(OutcomeAccount);
            ui->IncomeLabel->setText(Income);
            ui->OutcomeLabel->setText(Outcome);




            QSqlTableModel *TestModel;

            TestModel = new QSqlTableModel(this);
            TestModel->setTable("account");
            TestModel->setHeaderData(0, Qt::Horizontal, tr("类别"));
            TestModel->setHeaderData(1, Qt::Horizontal, tr("收入/支出"));
            TestModel->setHeaderData(2, Qt::Horizontal, tr("金额"));
            TestModel->setHeaderData(3, Qt::Horizontal, tr("备注"));
            TestModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            //TestModel->setFilter(QObject::tr("year = %1 ").arg(StrYear));
            //TestModel->setFilter(QObject::tr("month = %1 ").arg(StrMonth));
            if(InOutCome == "收入"){
                TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 and inoutcome = '收入'").arg(StrYear,StrMonth,StrDay));
            }
            if(InOutCome == "支出"){
                TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 and inoutcome = '支出'").arg(StrYear,StrMonth,StrDay));
            }
            if(InOutCome == "收入与支出"){
                TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 ").arg(StrYear,StrMonth,StrDay));
            }
            TestModel->select();
            TestModel->removeColumn(0);
            TestModel->removeColumn(1);
            TestModel->removeColumn(2);
            TestModel->removeColumn(2);
            TestModel->removeColumn(2);
            qDebug()<<QObject::tr("哔哔哔");


            ui->tableView->setModel(TestModel);
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);




        }

void accountStatement::InOutcomeBoxChanged(){//选择收入支出框时显示表格
    InOutCome = ui->InOutcomeBox->currentText();


    QSqlQuery query;

    QSqlTableModel *TestModel;

    TestModel = new QSqlTableModel(this);
    TestModel->setTable("account");
    TestModel->setHeaderData(0, Qt::Horizontal, tr("类别"));
    TestModel->setHeaderData(1, Qt::Horizontal, tr("收入/支出"));
    TestModel->setHeaderData(2, Qt::Horizontal, tr("金额"));
    TestModel->setHeaderData(3, Qt::Horizontal, tr("备注"));
    TestModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //TestModel->setFilter(QObject::tr("year = %1 ").arg(StrYear));
    //TestModel->setFilter(QObject::tr("month = %1 ").arg(StrMonth));
    if(InOutCome == "收入"){
        TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 and inoutcome = '收入'").arg(StrYear,StrMonth,StrDay));
    }
    if(InOutCome == "支出"){
        TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 and inoutcome = '支出'").arg(StrYear,StrMonth,StrDay));
    }
    if(InOutCome == "收入与支出"){
        TestModel->setFilter(QObject::tr("year = %1 and month = %2 and day = %3 ").arg(StrYear,StrMonth,StrDay));
    }
    TestModel->select();
    TestModel->removeColumn(0);
    TestModel->removeColumn(1);
    TestModel->removeColumn(2);
    TestModel->removeColumn(2);
    TestModel->removeColumn(2);

    ui->tableView->setModel(TestModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void accountStatement::change2Accounting(){//跳转到记账界面

    accounting *newAccountingPage=new accounting;
    newAccountingPage->show();
    this->close();
    newAccountingPage->exec();
}
void accountStatement::change2Chart(){//跳转到图表界面

    chart *newChartPage=new chart();
    newChartPage->show();
    this->close();
    newChartPage->exec();
}
void accountStatement::change2HomePage(){//跳转到首页
    Homepage_1 *newHomePage=new Homepage_1();
    newHomePage->show();
    this->close();
    newHomePage->exec();
}
void accountStatement::EditBtnClicked(){//跳转到编辑界面

    editPage New;
    New.show();
    New.exec();

}
void accountStatement::on_setBtn_clicked()//页面跳转
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
