#ifndef SAVERSETTINGDIALOG_H
#define SAVERSETTINGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

#include "constant.h"


namespace Ui {
class SaverSettingDialog;
}

class SaverSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaverSettingDialog(QWidget *parent = 0);
    ~SaverSettingDialog();

private:
    Ui::SaverSettingDialog *ui;
    QString dirPath;
signals:
    void updateSaverSettingsSignal();
private slots:
    void openDirDialogSlot();
    void saveSlot();
private:
    void initConnects();
    void readSettings();
};

#endif // SAVERSETTINGDIALOG_H
