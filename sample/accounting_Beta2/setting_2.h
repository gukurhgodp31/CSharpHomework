#ifndef SETTING_2_H
#define SETTING_2_H

#include <QDialog>
#include<QCoreApplication>
#include "homepage_1.h"

namespace Ui {
class Setting_2;
}

class Setting_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Setting_2(QWidget *parent = 0);
    ~Setting_2();
    /*int spassword;
    int password;
    int xinmima;
    int yanzheng;*/

private slots:

    //void to();
    //void set();
    void on_pushButton_2_clicked();
     void on_pushButton_clicked();

private:
    Ui::Setting_2 *ui;
};

#endif // SETTING_2_H
