#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>

namespace Ui {
class editPage;
}

class editPage : public QDialog
{
    Q_OBJECT

public:
    explicit editPage(QWidget *parent = 0);
    ~editPage();

private:
    Ui::editPage *ui;
    QSqlTableModel *model;
public slots:
    void DeleteBtnClicked();
    void CancelBtnClicked();
};

#endif // EDITPAGE_H
