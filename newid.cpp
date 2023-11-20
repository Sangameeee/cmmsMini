#include "newid.h"
#include "ui_newid.h"
//#include<fstream>
//#include<iostream>
#include<QString>
//#include<string>
#include<QMessageBox>
#include<Qfile>
#include<QTextStream>


NewID::NewID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewID)
{
    ui->setupUi(this);
}

NewID::~NewID()
{
    delete ui;
}

void NewID::on_pushButton_clicked()
{

    /* QString username = ui->lineE
        QMessageBox::warning(this,"username notset"dit_username2->text();
    //QString password = ui->lineEdit_password2->text();
   /* std::string usernamec = username.toStdString();
    std::ofstream out("username.txt");
    if(out.is_open()){
      out<<usernamec;
        QMessageBox::about(this,"username set","written in file");
      out.close();
    }else{,"not written in file");
    }
    QFile file("username.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<username;
         QMessageBox::about(this,"username set","written in file");
        file.close();
    }
    else{
       QMessageBox::warning(this, "Error", "Failed to open the file for writing.");
    } */
    QString username = ui->lineEdit_username2->text();
    QString password = ui->lineEdit_password2->text();
    QFile ufile("username.txt");
    QFile pfile("password.txt");

    if (!ufile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QMessageBox::warning(this, "Error", "Failed to open the file for writing: " + ufile.errorString());
    }
    else
    {
        QTextStream stream(&ufile);
        stream << username;
        ufile.close();

    }
    if (!pfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QMessageBox::warning(this, "Error", "Failed to open the file for writing: " + pfile.errorString());
    }
    else
    {
        QTextStream stream(&pfile);
        stream << password;
        pfile.close();
        QMessageBox::about(this, "Username set", "Username written to file");
    }


}

