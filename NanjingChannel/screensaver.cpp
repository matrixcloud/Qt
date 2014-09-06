#include "screensaver.h"
#include "ui_screensaver.h"

ScreenSaver::ScreenSaver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenSaver)
{
    curImgIndex = 0;

    ui->setupUi(this);
    setCursor(Qt::BlankCursor);
    showFullScreen();


    mTimer = new QTimer();
    connect(mTimer, SIGNAL(timeout()), this, SLOT(switchImgSlot()));
    mTimer->setInterval(SAVER_SPEED);

    init();
//    readSettings();
//    initImgs();

//    if(imgNameList.empty())
//    {
//       ui->imgLabel->setText("请先设置屏保图片路径");
//       QFont font;
//       font.setPixelSize(24);
//       ui->imgLabel->setFont(font);
//       ui->imgLabel->setAlignment(Qt::AlignCenter);
//       return;
//    }
//    else
//    {
//        QPixmap defaultPix;
//        defaultPix.load(dirPath + "/" + imgNameList[curImgIndex]);
//        ui->imgLabel->setPixmap(defaultPix);
//    }

//    mTimer = new QTimer();
//    connect(mTimer, SIGNAL(timeout()), this, SLOT(switchImgSlot()));
//    mTimer->setInterval(SAVER_SPEED);
//    mTimer->start();
}

ScreenSaver::~ScreenSaver()
{
    delete ui;
}

void ScreenSaver::switchImgSlot()
{
//    if(imgNameList.empty()) return;
    curImgIndex++;
    if(curImgIndex == imgNameList.size())
    {
        curImgIndex = 0;
    }
    QPixmap pixmap;
    pixmap.load(dirPath + "/" + imgNameList[curImgIndex]);
    pixmap = pixmap.scaled(ui->imgLabel->width(), ui->imgLabel->height(), Qt::IgnoreAspectRatio);
    ui->imgLabel->setPixmap(pixmap);
}

void ScreenSaver::updateSettingSlot()
{
    qDebug() << "saver------>>updateSettingSlot()" << endl;

//    readSettings();
    imgNameList.clear();
    curImgIndex = 0;
    init();
//    initImgs();
}

void ScreenSaver::mousePressEvent(QMouseEvent * event)
{
    emit mouseClickSignal();
}

void ScreenSaver::readSettings()
{
    QSettings settings(COMPANY, APP_NAME);
    dirPath = settings.value(IMG_PATH_KEY).toString();
    qDebug() << "path = " << dirPath;
}

void ScreenSaver::init()
{

    readSettings();
    initImgs();

    if(imgNameList.empty())
    {
       if(mTimer->isActive())
       {
           mTimer->stop();
       }
       ui->imgLabel->setText("请先设置屏保图片路径");
       QFont font;
       font.setPixelSize(24);
       ui->imgLabel->setFont(font);
       ui->imgLabel->setAlignment(Qt::AlignCenter);
       return;
    }
    else
    {
        QPixmap defaultPix;
        defaultPix.load(dirPath + "/" + imgNameList[curImgIndex]);
        ui->imgLabel->setPixmap(defaultPix);
        if(!mTimer->isActive())
        {
            mTimer->start();
        }
    }
}

void ScreenSaver::initImgs()
{
    if(dirPath.isEmpty()) return;
    QDir dir(dirPath);
    if(dir.exists())
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        QStringList list = dir.entryList();
        for(int i = 0; i < list.size(); i++)
        {
           if(list[i].contains(".jpg", Qt::CaseInsensitive))
           {
               qDebug() << list[i] << endl;
               imgNameList.push_back(list[i]);
           }
        }
    }
    qDebug() << "imgNameList = " << imgNameList.size();
}
