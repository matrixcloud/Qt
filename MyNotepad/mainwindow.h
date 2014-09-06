#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QSettings>
#include <QDate>
#include <string>
#include "about.h"
#include "finddialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    Ui::MainWindow *ui;
    QString currFileName;
    QFont mFont;
private:
    void initConnects();
    void saveFile(QString fileName);
    void readSettings();
private slots:
    void newFileSlot();
    void openFileSlot();
    void saveSlot();
    void saveAsSlot();

    void newDateSlot();

    void selectFontSlot();

    void changStatuBarSlot();

    void openAboutSlot();
    void openFindDialog();

    void findNextSlot();
};

#endif // MAINWINDOW_H
