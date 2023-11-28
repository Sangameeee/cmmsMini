#include "fileswindow.h"
#include "ui_fileswindow.h"

filesWindow::filesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filesWindow)
{
    ui->setupUi(this);
}

filesWindow::~filesWindow()
{
    delete ui;
}

void filesWindow::on_pushButton_clicked()
{
    hide();
    mainwindow = new MainWindow(this);
    mainwindow->show();
}

