#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    btn = new QPushButton(tr("click me to run"));
    connect(btn, SIGNAL(clicked()), this, SLOT(runCmd()));
    setCentralWidget(btn);
}

MainWindow::~MainWindow()
{

}

//前两个为阻塞式方法
void MainWindow::runCmd()
{
    qDebug("I'm running!");
    //linux c函数库()
    system("~/dev-tools/adb devices");
//    QProcess::execute("~/dev-tools/adb devices");//failure
      QProcess* proc = new QProcess();
      proc->start("~/dev-tools/adb devices");
    qDebug("I'm waiting so long!");
}
