#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setVisible(false);
    currFileName = "";

    setWindowTitle(currFileName);
    initConnects();

    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initConnects()
{
    connect(ui->newFileAct, SIGNAL(triggered()), this, SLOT(newFileSlot()));
    connect(ui->openFileAct, SIGNAL(triggered()), this, SLOT(openFileSlot()));
    connect(ui->saveAct, SIGNAL(triggered()), this, SLOT(saveSlot()));
    connect(ui->saveasAct, SIGNAL(triggered()), this, SLOT(saveAsSlot()));
    connect(ui->exitAct, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->undoAct, SIGNAL(triggered()), ui->textEdit, SLOT(undo()));
    connect(ui->cutAct, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    connect(ui->copyAct, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    connect(ui->pasteAct, SIGNAL(triggered()), ui->textEdit, SLOT(paste()));

    connect(ui->fontAct, SIGNAL(triggered()), this, SLOT(selectFontSlot()));

    connect(ui->statuBarAct, SIGNAL(triggered()), this, SLOT(changStatuBarSlot()));

    connect(ui->aboutAct, SIGNAL(triggered()), this, SLOT(openAboutSlot()));
    connect(ui->aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->findAct, SIGNAL(triggered()), this, SLOT(openFindDialog()));
    connect(ui->dateAct, SIGNAL(triggered()), this, SLOT(newDateSlot()));
}

void MainWindow::saveFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "open failed!\n";
        return;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << ui->textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    ui->statusBar->showMessage(tr("File saved"), 2000);
}

void MainWindow::newFileSlot()
{
   if(ui->textEdit->document()->isModified())
   {
       QMessageBox msgBox;
       msgBox.setText("The document has been modified.");
       msgBox.setInformativeText("Do you want to save your changes?");
       msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
       msgBox.setDefaultButton(QMessageBox::Save);
       int ret = msgBox.exec();

       if(ret == QMessageBox::Save)
       {
           QString fileName = QFileDialog::getSaveFileName(this);
           saveFile(fileName);
       }
       else if(ret == QMessageBox::Discard)
       {
           ui->textEdit->clear();
       }
   }
   else
   {
        ui->textEdit->clear();
   }
}

void MainWindow::openFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".",
                                                    tr("Text File(*.txt);;All File(*.*)"));

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "open error" << endl;
    }
    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());

    currFileName = fileName;
    setWindowTitle(currFileName);
}

void MainWindow::saveSlot()
{
   if(currFileName.isEmpty())
   {
       saveAsSlot();
   }
   else
   {
       saveFile(currFileName);
   }
}

void MainWindow::saveAsSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), ".",
                                                    tr("Text File(*.txt);;All File(*.*)"));
    currFileName = fileName;

    saveFile(fileName);
}

void MainWindow::newDateSlot()
{
    ui->textEdit->appendPlainText(QDate::currentDate().toString());
}

void MainWindow::selectFontSlot()
{
    bool ok;
    mFont = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->textEdit->setFont(mFont);
        QSettings settings("DreamTeam", "MyNotepad");
        settings.setValue("font.family", mFont.family());
        settings.setValue("font.size", mFont.pointSize());
        settings.setValue("font.bold", mFont.bold());
        settings.setValue("font.italic", mFont.italic());
//        qDebug() << mFont.toString();
    }
}

void MainWindow::readSettings()
{
    QSettings settings("DreamTeam", "MyNotepad");
    mFont.setFamily(settings.value("font.family", mFont.family()).toString());
    mFont.setPointSize(settings.value("font.size", mFont.pointSize()).toInt());
    mFont.setBold(settings.value("font.bold", mFont.bold()).toBool());
    mFont.setItalic(settings.value("font.italic", mFont.italic()).toBool());
    ui->textEdit->setFont(mFont);

    bool showStatuBar = settings.value("show.statubar", false).toBool();
    ui->statusBar->setVisible(showStatuBar);
    ui->statuBarAct->setChecked(showStatuBar);
}

void MainWindow::changStatuBarSlot()
{
    bool showStatuBar = ui->statusBar->isVisible();
    showStatuBar = (showStatuBar) ? false : true;

    ui->statusBar->setVisible(showStatuBar);

    QSettings settings("DreamTeam", "MyNotepad");
    settings.setValue("show.statubar", showStatuBar);
}

void MainWindow::openAboutSlot()
{
    QDialog* about = new About(this);
    about->show();
}

void MainWindow::openFindDialog()
{
    if(ui->textEdit->document()->isEmpty())
    {
        return;
    }
    QDialog* findDialog = new FindDialog(this);
    findDialog->show();
}

void MainWindow::findNextSlot()
{
}
