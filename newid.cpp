#include "newid.h"
#include "ui_newid.h"
//#include<fstream>
//#include<iostream>
#include<QString>
//#include<string>
#include<QMessageBox>
#include<Qfile>
#include<QTextStream>
#include "encryption.h"

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


    QString username = ui->lineEdit_username2->text();
    QString password = ui->lineEdit_password2->text();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username cannot be empty");
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty");
        return;
    }

    // Encrypt the password before saving
    encrypt(password);
    QFile ufile("username.txt");
    QFile pfile("password.txt");

    if (!ufile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QMessageBox::warning(this, "Error", "Failed: " + ufile.errorString());
    }
    else
    {
        QTextStream stream(&ufile);
        stream << username;
        ufile.close();

    }
    if (!pfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QMessageBox::warning(this, "Error", "Failed: " + pfile.errorString());
    }
    else
    {
        QTextStream stream(&pfile);
        stream << password;
        pfile.close();
        QMessageBox::about(this, "Username set", "Username and Password created");
    }


}
