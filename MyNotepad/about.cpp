#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QMovie* movie = new QMovie(":animation/test.gif");
    ui->movieLabel->setMovie(movie);
    movie->start();
}

About::~About()
{
    delete ui;
}
