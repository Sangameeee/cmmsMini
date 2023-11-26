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
    QString username = ui->lineEdit_username2->text();
    QString password = ui->lineEdit_password2->text();
    QFile ufile("username.txt");
    QFile pfile("password.txt");

    if (!ufile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open the file for reading: " + ufile.errorString());
        return;
    }

    bool usernameExists = false;//SAURAV EDIT --- just creating a bool
    QTextStream instream(&ufile);
    while (!instream.atEnd()) //SAURAV EDIT --- opens files and checks the last line of the file
    {
        QString existingUsername = instream.readLine();//SAURAV EDIT ---reads the last line with read line() function
        if (existingUsername == username)
        {
            usernameExists = true;//SAURAV EDIT ---checks if existing username qstring form line 40 is equal to the string at line 26
            break;
        }
    }

    if (ufile.isOpen()) {
        ufile.close();
    }

    if (usernameExists) {
        QMessageBox::warning(this, "Error", "Username already exists. Please choose a different username.");//SAURAV EDIT ---form line 43 we get the value of bool usernameexists and if its true we execute this line
        return;
    }

    else if (!ufile.open(QIODevice::WriteOnly | QIODevice::Text))
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

    else if(username.isEmpty())
    {
        QMessageBox::information(this,"Error","Please enter a Username");//SAURAV EDIT ---if username text line is empty we execute this
    }


    else if (password.isEmpty())
    {
        QMessageBox::information(this,"Error","Please enter a Password");//SAURAV EDIT ---if password text line is empty we execute this
    }

    else if (!ufile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open the file for writing: " + ufile.errorString());
    }

    else
    {
        QTextStream stream(&pfile);
        stream << password;
        pfile.close();
        QMessageBox::about(this, "Username set", "Username written to file");
        close();
    }


}
