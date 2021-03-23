#include "editpage.h"
#include "ui_editpage.h"
#include <QDate>
#include <QString>
#include <QTableView>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>

editPage::editPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editPage)
{
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinMaxButtonsHint;
        flags |=Qt::WindowCloseButtonHint;
        setWindowFlags(flags);

    ui->setupUi(this);
    connect(ui->DeleteBtn,SIGNAL(clicked(bool)),this,SLOT(DeleteBtnClicked()));

    model = new QSqlTableModel(this);
    model->setTable("account");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->removeColumn(2);
    model->setHeaderData(0, Qt::Horizontal, tr("编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("类别"));
    model->setHeaderData(2, Qt::Horizontal, tr("收入/支出"));
    model->setHeaderData(3, Qt::Horizontal, tr("年"));
    model->setHeaderData(4, Qt::Horizontal, tr("月"));
    model->setHeaderData(5, Qt::Horizontal, tr("日"));
    model->setHeaderData(6, Qt::Horizontal, tr("金额"));
    model->setHeaderData(7, Qt::Horizontal, tr("备注"));


    ui->tableView->setModel(model);

}
void editPage::DeleteBtnClicked(){//删除选中行
    int curRow = ui->tableView->currentIndex().row();

    model->removeRow(curRow);

    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗?"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No){
     model->revertAll(); //如果不删除，则撤销
        }
    else model->submitAll(); //否则提交，在数据库中删除该行
    }
void editPage::CancelBtnClicked(){//关闭界面，回到流水页面
    this->close();
}

editPage::~editPage()
{
    delete ui;
}
