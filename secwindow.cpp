#include "secwindow.h"
#include "ui_secwindow.h"
#include<QMessageBox>
#include<Qfile>
#include<QTextStream>

secWindow::secWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secWindow)
{
    ui->setupUi(this);
}

secWindow::~secWindow()
{
    delete ui;
}

void secWindow::on_pushButton_clicked()
{

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QFile urfile("username.txt");
    QFile prfile("password.txt");
    if(!(urfile.open(QIODevice::ReadOnly)&&prfile.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(this, "Error", "Failed to open the file for Reading: ");
    }
    else{
        QTextStream stream(&urfile);
        QTextStream pstream(&prfile);
        QString userwrittenname = stream.readLine();
        QString userwrittenpassword = pstream.readLine();
        urfile.close();
        prfile.close();

        if(username == userwrittenname && password == userwrittenpassword)
        {
//
//            hide();
//            secDialog = new secdialog(this);
//            secDialog->setWindowTitle("logined");
//            secDialog->show();
            hide();
            mainwindow = new MainWindow(this);
            mainwindow->show();

        }else
        {
            if(username != userwrittenname && password != userwrittenpassword ){
                QMessageBox::warning(this,"Login","Wrong password and username");
            }else if(password != userwrittenpassword){
                QMessageBox::warning(this,"Login","passowrd is incorrect");
            }else{
                QMessageBox::warning(this,"Login","username is incorrect");
            }
        }
    }

}


void secWindow::on_pushButton_2_clicked()
{
    newId = new NewID(this);
    newId->setWindowTitle("Create Username and Id");
    newId->show();
}

