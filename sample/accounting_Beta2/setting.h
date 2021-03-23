#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();
    int spassword;
    int password;
    int xinmima;

private slots:
   // void gaimi();
    //void to();
    //void set();
    //void on_pushButton_2_clicked();
     void on_pushButton_4_clicked();
     void on_cancelBtn_clicked();
private:
    Ui::Setting *ui;
};

#endif // SETTING_H
