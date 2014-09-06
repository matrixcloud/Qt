#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    createConnets();
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::createConnets()
{
   connect(ui->findNextBtn, SIGNAL(clicked()), this->parent(), SLOT(findNextSlot()));
}
