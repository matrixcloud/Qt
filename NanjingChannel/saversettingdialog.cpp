#include "saversettingdialog.h"
#include "ui_saversettingdialog.h"

SaverSettingDialog::SaverSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaverSettingDialog)
{
    setFixedSize(436, 197);
    ui->setupUi(this);
    readSettings();
    initConnects();
}

SaverSettingDialog::~SaverSettingDialog()
{
    delete ui;
}

void SaverSettingDialog::initConnects()
{
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(openDirDialogSlot()));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(saveSlot()));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void SaverSettingDialog::readSettings()
{
     QSettings settings(COMPANY, APP_NAME);
     dirPath = settings.value(IMG_PATH_KEY).toString();

     if(!dirPath.isEmpty())
     {
        ui->lineEdit->setText(dirPath);
     }

     int time = settings.value(WAIT_TIME_KEY).toInt();
     ui->spinBox->setValue(time);
}

void SaverSettingDialog::openDirDialogSlot()
{
    dirPath = QFileDialog::getExistingDirectory(this);
    if(!dirPath.isEmpty())
    {
        ui->lineEdit->setText(dirPath);
    }
}

void SaverSettingDialog::saveSlot()
{
    QSettings settings(COMPANY, APP_NAME);

    if(!dirPath.isEmpty())
    {
        settings.setValue(IMG_PATH_KEY, dirPath);
    }
    int time = ui->spinBox->value();
    settings.setValue(WAIT_TIME_KEY, time);
    emit updateSaverSettingsSignal();
}
