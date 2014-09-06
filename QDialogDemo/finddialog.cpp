#include "finddialog.h"

//the shortcut is useless
FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    //shortcut(Alt+W)
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit();
    //伙伴可以在按下标签快捷键时接受焦点
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match case"));
    backwardCheckBox = new QCheckBox(tr("Find backward"));

    //&操作符定义了快捷键（Alt+F）
    findBtn = new QPushButton(tr("&Find"));
    findBtn->setDefault(true);
    findBtn->setEnabled(false);

    closeBtn = new QPushButton(tr("Close"));
    //由于QObject是FindDialog的父类之一，可以是省略connect()函数前面的QObject::前缀
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
    connect(findBtn, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findBtn);
    rightLayout->addWidget(closeBtn);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("FindDialogDemo"));
    setFixedHeight(sizeHint().height());//让对话框有一个固定的高度
}

void FindDialog::findClicked()
{
    qDebug("------------->>findClicked()");
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive
                                             : Qt::CaseSensitive;
    if(backwardCheckBox->isChecked())
    {
        //emit是Qt中的关键字，像其他Qt扩展一样，它会被C++与预理器转换成标准c++代码
        emit findPrevious(text, cs);
    }
    else
    {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString &str)
{
    findBtn->setEnabled(!str.isEmpty());
}
