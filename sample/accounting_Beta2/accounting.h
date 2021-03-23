#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include <QDialog>

namespace Ui {
class accounting;
}

class accounting : public QDialog
{
    Q_OBJECT

public:
    explicit accounting(QWidget *parent = 0);
    ~accounting();
    void HiddenIncome();

private:
    Ui::accounting *ui;

public slots:
    void SaveClicked();
    void ItemChange();
    void ItemChoose();
    void DateChoose();
    void ClearSavedText();
    void change2Chart();
    void change2AcountStatement();
    void change2HomePage();
    void on_setBtn_clicked();
};

#endif // ACCOUNTING_H
