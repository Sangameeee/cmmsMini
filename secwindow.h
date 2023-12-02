#ifndef SECWINDOW_H
#define SECWINDOW_H

#include <QDialog>
#include"newid.h"
#include"mainwindow.h"
#include"fileswindow.h"

namespace Ui {
class secWindow;
}

class secWindow : public QDialog
{
    Q_OBJECT

public:
    explicit secWindow(QWidget *parent = nullptr);
    ~secWindow();

private slots:
    void on_pushButton_clicked();


    void on_createButton_clicked();

private:
    Ui::secWindow *ui;
    NewID *newId;
    QMainWindow *mainwindow;
    void createButtonDisplays();
    //filesWindow *filewindow;
};

#endif // SECWINDOW_H
