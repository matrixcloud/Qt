#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define NOMINMAX

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QDialog>

#include "saversettingdialog.h"
#include "constant.h"
#include "windows.h"
#include "screensaver.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget* saver;
    QTimer* mTimer;

    //屏保状态
    bool isSaverStart;
    long waitTime;//sec
private slots:
    void fullScrSlot();
    void openSaverSetting();
    void updateSettingSlot();
    //更新响应
    void updateSlot();
    void wakeupSlot();
private:
    void keyPressEvent(QKeyEvent* event);
    void initConnects();
    void quitFullScr();

    void checkSaverState();
    void readSettings();
};

#endif // MAINWINDOW_H
