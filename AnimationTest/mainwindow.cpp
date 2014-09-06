#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStateMachine* machine = new QStateMachine;
    QState* state_1 = new QState(machine);
    //属性绑定
    state_1->assignProperty(ui->pushButton, "geometry", QRect(0, 0, 80, 30));
    machine->setInitialState(state_1);

    QState* state_2 = new QState(machine);
    state_2->assignProperty(ui->pushButton, "geometry", QRect(this->width()-30
                              , this->height() -80, 30, 80));
    QFont font = QFont("Airl", 12);
    state_2->assignProperty(ui->pushButton, "font", font);
    //动画效果-弹跳
    QPropertyAnimation* ani = new QPropertyAnimation(ui->pushButton, "geometry");
    ani->setDuration(2000);
    ani->setEasingCurve(QEasingCurve::OutBounce);

    QSignalTransition *transition1=state_1->addTransition(ui->pushButton,SIGNAL(clicked()),state_2);//动画触发信号
    transition1->addAnimation(ani);
    QSignalTransition *transition2=state_2->addTransition(ui->pushButton,SIGNAL(clicked()),state_1);
    transition2->addAnimation(ani);
    machine->start();     //开启状态机
}

MainWindow::~MainWindow()
{
    delete ui;
}
