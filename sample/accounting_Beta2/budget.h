#ifndef BUDGET_H
#define BUDGET_H

#include <QDialog>
#include "homepage_1.h"

namespace Ui {
class Budget;
}

class Budget : public QDialog
{
    Q_OBJECT

public:
    explicit Budget(QWidget *parent = 0);
    ~Budget();
private slots:
    void on_setBtn_clicked();
    void on_pushButton_clicked();
private:
    Ui::Budget *ui;
};

#endif // BUDGET_H
