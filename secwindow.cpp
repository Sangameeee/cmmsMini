#include "secwindow.h"
#include "ui_secwindow.h"
#include<QMessageBox>
#include<Qfile>
#include<QTextStream>
#include"fileswindow.h"
#include<QFileInfo>

secWindow::secWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secWindow)
{
    ui->setupUi(this);
    createButtonDisplays();
}

secWindow::~secWindow()
{
    delete ui;
}
void secWindow::createButtonDisplays()
{
    QPushButton *createButton = ui->createButton;
    createButton->hide();
    QFile urfile("username.txt");
    QFile prfile("password.txt");
    QFileInfo urinfo(urfile);
    QFileInfo prinfo(prfile);
    if(urinfo.size()==0 && prinfo.size()==0)
    {
        createButton->show();
    }
    else
    {
    createButton->hide();
    }

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
            hide();
            mainwindow = new MainWindow(this);
            mainwindow->show();
//            hide();
//            filesWindow *filewindow = new filesWindow(this);
//            filewindow->setWindowTitle("class");
//            filewindow->show();

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






void secWindow::on_createButton_clicked()
{
    newId = new NewID(this);
    newId->setWindowTitle("Create Username and Id");
    newId->show();
}

