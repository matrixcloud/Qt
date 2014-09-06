#include "mainwindow.h"
#include "ui_mainwindow.h"

const int UPDATE_SPEED = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    isSaverStart = false;
    readSettings();

    saver = new ScreenSaver;
    saver->setVisible(false);

    mTimer = new QTimer();
    mTimer->setInterval(UPDATE_SPEED);
    mTimer->start();

    ui->setupUi(this);
    initConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSettings()
{
    QSettings settings(COMPANY, APP_NAME);

    waitTime = settings.value(WAIT_TIME_KEY).toInt();
    waitTime *= 60;
}

void MainWindow::initConnects()
{
    connect(ui->fullScrAct, SIGNAL(triggered()), this, SLOT(fullScrSlot()));
    connect(ui->saverSettingAct, SIGNAL(triggered()), this, SLOT(openSaverSetting()));
    connect(ui->aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateSlot()));
    connect(saver, SIGNAL(mouseClickSignal()), this, SLOT(wakeupSlot()));
}

void MainWindow::fullScrSlot()
{
    ui->menuBar->setVisible(false);
    this->showFullScreen();
}

void MainWindow::updateSlot()
{
    checkSaverState();
    if(isSaverStart)
    {
        saver->show();
        this->setVisible(false);
        mTimer->stop();
    }
}

void MainWindow::wakeupSlot()
{
    saver->setVisible(false);
    this->setVisible(true);
    mTimer->start();
}

void MainWindow::updateSettingSlot()
{
    readSettings();
}

void MainWindow::openSaverSetting()
{
    QDialog* dialog = new SaverSettingDialog();
    connect(dialog, SIGNAL(updateSaverSettingsSignal()), this, SLOT(updateSettingSlot()));
    connect(dialog, SIGNAL(updateSaverSettingsSignal()), saver, SLOT(updateSettingSlot()));

    dialog->show();
}

void MainWindow::quitFullScr()
{
    ui->menuBar->setVisible(true);
    this->showNormal();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_F10)
    {
        quitFullScr();
    }
}

void MainWindow::checkSaverState()
{
    LASTINPUTINFO lastInputInfo;
    lastInputInfo.cbSize = sizeof(LASTINPUTINFO);
    if(!GetLastInputInfo(&lastInputInfo))
    {
        qDebug()<<"get error";
    }
    unsigned long ulTickTimes = GetTickCount() - lastInputInfo.dwTime;
    int timeInt = 0;//键盘鼠标空闲等待的时间
    timeInt=ulTickTimes/1000;

    if(timeInt > waitTime)
    {
        isSaverStart = true;
    }
    else
    {
        isSaverStart = false;
    }
}
