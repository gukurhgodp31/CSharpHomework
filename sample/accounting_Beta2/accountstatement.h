#ifndef ACCOUNTSTATEMENT_H
#define ACCOUNTSTATEMENT_H

#include <QDialog>
#include <QtSql>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStandardItem>
#include "editpage.h"

namespace Ui {
class accountStatement;
}

class accountStatement : public QDialog
{
    Q_OBJECT

public:
    explicit accountStatement(QWidget *parent = 0);
    ~accountStatement();

private:
    Ui::accountStatement *ui;
    QSqlTableModel *model;

public slots:
    void DayChoose();
    void MonthChoose();
    void InOutcomeBoxChanged();
    void EditBtnClicked();
    void change2Chart();
    void change2Accounting();
    void change2HomePage();
    void on_setBtn_clicked();
};

#endif // ACCOUNTSTATEMENT_H
