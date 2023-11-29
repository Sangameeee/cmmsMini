#ifndef FILESWINDOW_H
#define FILESWINDOW_H

#include <QDialog>
#include"mainwindow.h"

namespace Ui {
class filesWindow;
}

class filesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit filesWindow(QWidget *parent = nullptr);
    ~filesWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::filesWindow *ui;
    void lineeditshow();
    QMainWindow *mainwindow;
};

#endif // FILESWINDOW_H
