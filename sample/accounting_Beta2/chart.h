#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include <QtCharts>
using namespace QtCharts;

namespace Ui {
class chart;
}

class chart : public QDialog
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = 0);
    ~chart();
    void defaultChart();
    int getYear();
    int getMonth();
    void showInOutCmpBar();
    void showInCmpBar();
    void showOutCmpBar();
    void showInOutCmpDonut();
private:
    Ui::chart *ui;
public slots:
    void selectChart();
    void change2Accounting();
    void change2AcountStatement();
    void change2HomePage();
    void on_setBtn_clicked();
};

#endif // CHART_H
