#include "accounting.h"
#include "ui_accounting.h"
#include "chart.h"
#include "accountstatement.h"
#include "homepage_1.h"
#include <QStringList>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtCore/QTextStream>
#include <QDebug>
#include <string>
#include <QDate>
#include <QTimer>
#include "setting.h"
#include "setting_2.h"

static int ItemChosen=0;
static QString StrItemChosen="一般";
static QString InOutcome="支出";
static int Year  = 2016;
static int Month = 1;
static int Day   = 1;

accounting::accounting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accounting)
{
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinMaxButtonsHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    ui->setupUi(this);
    QDoubleValidator*validator=new QDoubleValidator(0.00,999999999.99,2,this);
        validator->setNotation(QDoubleValidator::StandardNotation);
        ui->Amount->setValidator(validator);



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







        connect(ui->SaveBtn,           SIGNAL(clicked(bool)),this,SLOT(SaveClicked()));
        connect(ui->IncomeBtn,         SIGNAL(clicked(bool)),this,SLOT(ItemChange()));
        connect(ui->OutcomeBtn,        SIGNAL(clicked(bool)),this,SLOT(ItemChange()));
        connect(ui->NormalBtn,         SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->LivingExpenseBtn,  SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->RedPacketBtn,      SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->BounsBtn,          SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->SalaryBtn,         SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->OtherBtn,          SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->NormalBtn_2,       SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->DietBtn,           SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->ClothesBtn,        SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->MakeupBtn,         SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->ChemicalBtn,       SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->StudyBtn,          SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->TrafficBtn,        SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->EntertainmentBtn,  SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        //connect(ui->SocialBtn,         SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->DigitalBtn,        SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->CommunicationBtn,  SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->MedicalBtn,        SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        connect(ui->OtherBtn_2,        SIGNAL(clicked(bool)),this,SLOT(ItemChoose()));
        //connect(ui->Date,              SIGNAL(dateChanged(QDate)),this,SLOT(DateChoose()));
        connect(ui->chooseDay,SIGNAL(currentTextChanged(QString)),this,SLOT(DateChoose()));
        connect(ui->chooseMonth,SIGNAL(currentTextChanged(QString)),this,SLOT(DateChoose()));
        connect(ui->chooseYear,SIGNAL(currentTextChanged(QString)),this,SLOT(DateChoose()));
        connect(ui->ChartBtn,             SIGNAL(clicked(bool)),this,SLOT(change2Chart()));
        connect(ui->AccountStatementBtn,SIGNAL(clicked(bool)),this,SLOT(change2AcountStatement()));
        connect(ui->HomepageBtn,SIGNAL(clicked(bool)),this,SLOT(change2HomePage()));

        HiddenIncome();//设置支出为默认页面
}

accounting::~accounting()
{
    delete ui;
}
void accounting::SaveClicked(){



    QSqlQuery query;
    QString AmountText = ui->Amount->text();//读取用户界面中输入的金额
    QString RemarkText = ui->RemarkText->toPlainText();//读取用户界面中输入的备注
    query.prepare("insert into account values(NULL,:category,:categoryNum,:inoutcome,:year,:month,:day,:amount,:remarktext)");
    query.bindValue(":categoryNum",ItemChosen);
    query.bindValue(":category",StrItemChosen);
    query.bindValue(":inoutcome",InOutcome);
    query.bindValue(":year",Year);
    query.bindValue(":month",Month);
    query.bindValue(":day",Day);
    query.bindValue(":amount",AmountText);
    query.bindValue(":remarktext",RemarkText);
    bool success = query.exec();//将数据写入数据库
    if(success){
    qDebug()<<ItemChosen<<InOutcome<<Year<<Month<<Day<<AmountText<<RemarkText<<QObject::tr("写入成功");
    }else{
    qDebug()<<QObject::tr("写入失败");
    }
    ui->SaveLabel->setText("保存成功");
    QTimer::singleShot(1000,this,SLOT(ClearSavedText()));
    ui->RemarkText->clear();
    ui->Amount->clear();
}
void accounting::ClearSavedText(){
    ui->SaveLabel->setText("");
}
void accounting::HiddenIncome(){//设置支出为默认页面
    ui->NormalLabel->setHidden(true);
    ui->LivingExpenseLabel->setHidden(true);
    ui->RedPacketLabel->setHidden(true);
    ui->BounsLabel->setHidden(true);
    ui->SalaryLabel->setHidden(true);
    ui->OtherLabel->setHidden(true);

    ui->NormalBtn->setHidden(true);
    ui->LivingExpenseBtn->setHidden(true);
    ui->RedPacketBtn->setHidden(true);
    ui->BounsBtn->setHidden(true);
    ui->SalaryBtn->setHidden(true);
    ui->OtherBtn->setHidden(true);
}

void accounting::ItemChange(){//获取用户界面中选择的类别


    QPushButton *button=qobject_cast<QPushButton *>(this->sender());
    if(ui->IncomeBtn==button){
        ui->NormalBtn->setHidden(false);
        ui->LivingExpenseBtn->setHidden(false);
        ui->RedPacketBtn->setHidden(false);
        ui->BounsBtn->setHidden(false);
        ui->SalaryBtn->setHidden(false);
        ui->OtherBtn->setHidden(false);

        ui->NormalBtn_2->setHidden(true);
        ui->DietBtn->setHidden(true);
        ui->ClothesBtn->setHidden(true);
        ui->MakeupBtn->setHidden(true);
        ui->ChemicalBtn->setHidden(true);
        ui->StudyBtn->setHidden(true);
        ui->TrafficBtn->setHidden(true);
        ui->EntertainmentBtn->setHidden(true);
        //ui->SocialBtn->setHidden(true);
        ui->DigitalBtn->setHidden(true);
        ui->CommunicationBtn->setHidden(true);
        ui->MedicalBtn->setHidden(true);
        ui->OtherBtn_2->setHidden(true);

        ui->NormalLabel->setHidden(false);
        ui->LivingExpenseLabel->setHidden(false);
        ui->RedPacketLabel->setHidden(false);
        ui->BounsLabel->setHidden(false);
        ui->SalaryLabel->setHidden(false);
        ui->OtherLabel->setHidden(false);

        ui->NormalLabel_2->setHidden(true);
        ui->DietLabel->setHidden(true);
        ui->ClothingLabel->setHidden(true);
        ui->MakeupLabel->setHidden(true);
        ui->ChemicalLabel->setHidden(true);
        ui->StudyLabel->setHidden(true);
        ui->TrafficLabel->setHidden(true);
        ui->EntertainmentLabel->setHidden(true);
        ui->DigitalLabel->setHidden(true);
        ui->CommunicationLabel->setHidden(true);
        ui->MedicalLabel->setHidden(true);
        ui->OtherLabel_2->setHidden(true);


        InOutcome = "收入";

    }
if (ui->OutcomeBtn==button){
    ui->NormalBtn->setHidden(true);
    ui->LivingExpenseBtn->setHidden(true);
    ui->RedPacketBtn->setHidden(true);
    ui->BounsBtn->setHidden(true);
    ui->SalaryBtn->setHidden(true);
    ui->OtherBtn->setHidden(true);

    ui->NormalBtn_2->setHidden(false);
    ui->DietBtn->setHidden(false);
    ui->ClothesBtn->setHidden(false);
    ui->MakeupBtn->setHidden(false);
    ui->ChemicalBtn->setHidden(false);
    ui->StudyBtn->setHidden(false);
    ui->TrafficBtn->setHidden(false);
    ui->EntertainmentBtn->setHidden(false);
    //ui->SocialBtn->setHidden(false);
    ui->DigitalBtn->setHidden(false);
    ui->CommunicationBtn->setHidden(false);
    ui->MedicalBtn->setHidden(false);
    ui->OtherBtn_2->setHidden(false);

    ui->NormalLabel->setHidden(true);
    ui->LivingExpenseLabel->setHidden(true);
    ui->RedPacketLabel->setHidden(true);
    ui->BounsLabel->setHidden(true);
    ui->SalaryLabel->setHidden(true);
    ui->OtherLabel->setHidden(true);

    ui->NormalLabel_2->setHidden(false);
    ui->DietLabel->setHidden(false);
    ui->ClothingLabel->setHidden(false);
    ui->MakeupLabel->setHidden(false);
    ui->ChemicalLabel->setHidden(false);
    ui->StudyLabel->setHidden(false);
    ui->TrafficLabel->setHidden(false);
    ui->EntertainmentLabel->setHidden(false);
    ui->DigitalLabel->setHidden(false);
    ui->CommunicationLabel->setHidden(false);
    ui->MedicalLabel->setHidden(false);
    ui->OtherLabel_2->setHidden(false);

    InOutcome = "支出";


    }
}
void accounting::ItemChoose(){
    QPushButton *button=qobject_cast<QPushButton *>(this->sender());
    if (ui->NormalBtn==button){
        ItemChosen = 0;
        StrItemChosen="一般";
        ui->NormalBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->LivingExpenseBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->RedPacketBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->BounsBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->SalaryBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->LivingExpenseBtn==button){
        ItemChosen = 1;
        StrItemChosen="生活费";
        ui->NormalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->LivingExpenseBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->RedPacketBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->BounsBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->SalaryBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->RedPacketBtn==button){
        ItemChosen = 2;
        StrItemChosen="红包";
        ui->NormalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->LivingExpenseBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->RedPacketBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->BounsBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->SalaryBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->BounsBtn==button){
        ItemChosen = 3;
        StrItemChosen="奖学金";
        ui->NormalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->LivingExpenseBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->RedPacketBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->BounsBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->SalaryBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn->setStyleSheet("QPushButton{border: 0;}");

    }
    if (ui->SalaryBtn==button){
        ItemChosen = 4;
        StrItemChosen="工资";
        ui->NormalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->LivingExpenseBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->RedPacketBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->BounsBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->SalaryBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->OtherBtn->setStyleSheet("QPushButton{border: 0;}");

    }
    if (ui->OtherBtn==button){
        ItemChosen = 5;
        StrItemChosen="其他";
        ui->NormalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->LivingExpenseBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->RedPacketBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->BounsBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->SalaryBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
    }
    if (ui->NormalBtn_2==button){
        ItemChosen = 6;
        StrItemChosen="一般";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->DietBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->DietBtn==button){
        ItemChosen = 7;
        StrItemChosen="饮食";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->ClothesBtn==button){
        ItemChosen = 8;
        StrItemChosen="服饰";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->MakeupBtn==button){
        ItemChosen = 9;
        StrItemChosen="化妆";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->ChemicalBtn==button){
        ItemChosen = 10;
        StrItemChosen="日化";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->StudyBtn==button){
        ItemChosen = 11;
        StrItemChosen="学习";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border:0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border:  1px solid #666;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->TrafficBtn==button){
        ItemChosen = 12;
        StrItemChosen="交通";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border:0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border:  0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->EntertainmentBtn==button){
        ItemChosen = 13;
        StrItemChosen="娱乐";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border:0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border:  0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }

    if (ui->DigitalBtn==button){
        ItemChosen = 14;
        StrItemChosen="社交";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border:0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border:  0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->CommunicationBtn==button){
        ItemChosen = 15;
        StrItemChosen="通讯";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border:0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border:  0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border: 1px solid #666;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->MedicalBtn==button){
        ItemChosen = 16;
        StrItemChosen="医疗";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border:0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border:  0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border:0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border:  1px solid #666;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 0;}");
    }
    if (ui->OtherBtn_2==button){
        ItemChosen = 17;
        StrItemChosen="其他";
        ui->NormalBtn_2->setStyleSheet("QPushButton{border: 0;}");
        ui->DietBtn->setStyleSheet("QPushButton{border:0 ;}");
        ui->ClothesBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->MakeupBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->ChemicalBtn->setStyleSheet("QPushButton{border:0;}");
        ui->StudyBtn->setStyleSheet("QPushButton{border:  0;}");
        ui->TrafficBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->EntertainmentBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->DigitalBtn->setStyleSheet("QPushButton{border: 0;}");
        ui->CommunicationBtn->setStyleSheet("QPushButton{border:0;}");
        ui->MedicalBtn->setStyleSheet("QPushButton{border:  0;}");
        ui->OtherBtn_2->setStyleSheet("QPushButton{border: 1px solid #666;}");
    }
}

void accounting::DateChoose(){//获取用户界面中选择的年月日
    Year    = ui->chooseYear->currentText().toInt();
    Month   = ui->chooseMonth->currentText().toInt();
    Day     = ui->chooseDay->currentText().toInt();
}
void accounting::change2Chart(){//跳转到图表页面

    chart *newChartPage=new chart();
    newChartPage->show();
    this->close();
    newChartPage->exec();
}
void accounting::change2AcountStatement(){//跳转到流水页面

    accountStatement *newAccountStatement=new accountStatement();
    newAccountStatement->show();
    newAccountStatement->DayChoose();
    this->close();
    newAccountStatement->exec();
}
void accounting::change2HomePage(){//跳转到首页
    Homepage_1 *newHomePage=new Homepage_1();
    newHomePage->show();
    this->close();
    newHomePage->exec();
}
void accounting::on_setBtn_clicked()//页面跳转
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
