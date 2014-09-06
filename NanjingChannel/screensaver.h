#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QSettings>
#include <QDir>
#include "constant.h"


namespace Ui {
class ScreenSaver;
}

class ScreenSaver : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenSaver(QWidget *parent = 0);
    ~ScreenSaver();
signals:
    void mouseClickSignal();
private:
    Ui::ScreenSaver *ui;
    QTimer* mTimer;
    QString dirPath;
    QStringList imgNameList;
    int curImgIndex;
private slots:
    void switchImgSlot();
    void updateSettingSlot();
private:
    void mousePressEvent(QMouseEvent * event);

    void readSettings();
    void init();
    void initImgs();
};

#endif // SCREENSAVER_H
