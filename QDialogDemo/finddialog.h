#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDebug>
#include <QtWidgets>

//前置声明(forward declaration)
//会告诉c++类已经存在编译器这些类已经存在，不用再包含其头文件。
//因下面定义的都是类的指针，没有必要访问整个头文件，这种方式可以编译更快。
class QLabel;
class QPushButton;
class QLineEdit;
class QCheckBox;


class FindDialog : public QDialog
{
    Q_OBJECT//对于所有定了信号和槽的类，在类的开始处的Q_OBJECT宏都是有必要的。

public:
    //典型窗口部件构造函数，其入参为其父窗口部件。这里默认为空指针，没有父对象
    FindDialog(QWidget *parent = 0);
//    ~FindDialog();
//Qt会在删除父对象时自动删除其所属的所有子对象
signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);//enum
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
private slots:
    void findClicked();
    void enableFindButton(const QString &str);
private:
    QLabel* label;
    QLineEdit* lineEdit;
    QCheckBox* caseCheckBox;
    QCheckBox* backwardCheckBox;
    QPushButton* findBtn;
    QPushButton* closeBtn;
};

#endif // FINDDIALOG_H
