#ifndef HOMEPAGE_1_H
#define HOMEPAGE_1_H

#include <QDialog>
#include <QtCharts>
using namespace QtCharts;

namespace Ui {
class Homepage_1;
}

class Homepage_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Homepage_1(QWidget *parent = 0);
    ~Homepage_1();
    QString income;
    QString output;
    QString remain;
    QChart *progressDonut(double budget);
    int password;

    void list();
private slots:
    void on_setBtn_clicked();
    void on_pushButton_clicked();
    void showProgressDonut();
    void on_pushButton_3_clicked();
    void change2AcountStatement();
    void change2Chart();

private:
    Ui::Homepage_1 *ui;

};

#endif // HOMEPAGE_1_H

