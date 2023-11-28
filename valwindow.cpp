#include "valwindow.h"
#include "ui_valwindow.h"

ValWindow::ValWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValWindow)
{
    ui->setupUi(this);
}

ValWindow::~ValWindow()
{
    delete ui;
}
