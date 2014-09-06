#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
private:
    Ui::FindDialog *ui;
private:
    void createConnets();
};

#endif // FINDDIALOG_H
