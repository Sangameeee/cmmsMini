#include "secwindow.h"
#include "mainwindow.h"
#include "ui_secwindow.h"
#include<QMessageBox>
#include<Qfile>
#include<QTextStream>
#include<QFileInfo>
#include"fileswindow.h"
#include"encryption.h"

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
    QPushButton *createButton = ui->pushButton_2;
    this->setWindowTitle("LOGIN");
    QFile urfile("username.txt");
    QFile prfile("password.txt");
    QFileInfo urinfo(urfile);
    QFileInfo prinfo(prfile);

    if(urinfo.size() == 0 || prinfo.size() == 0)
    {
        createButton->show();
    }
    else
    {
         createButton->hide();
    }
}

// void secWindow::createButtonDisplays()
// {
//     QPushButton *createButton = ui->pushButton_2;
//     createButton->hide();
//     this->setWindowTitle("LOGIN");
//     QFile urfile("username.txt");
//     QFile prfile("password.txt");
//     QFileInfo urinfo(urfile);
//     QFileInfo prinfo(prfile);
//     if(urinfo.size()==0 && prinfo.size()==0)
//     {
//         createButton->show();
//     }
//     else
//     {
//         createButton->hide();
//     }
// }


void secWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QFile urfile("username.txt");
    QFile prfile("password.txt");

    bool usernameExists = urfile.exists();
    bool passwordExists = prfile.exists();

    if (!(urfile.open(QIODevice::ReadOnly) && prfile.open(QIODevice::ReadOnly))) {
        QMessageBox::warning(this, "Error", "Failed to open the file for Reading: ");
    } else {
        QTextStream stream(&urfile);
        QTextStream pstream(&prfile);
        QString userwrittenname = stream.readLine();
        QString userwrittenpassword = pstream.readLine();
        urfile.close();
        prfile.close();

        decrypt(userwrittenpassword); // Decrypt the stored password for comparison

        if (username == userwrittenname && password == userwrittenpassword) {
            // Login successful
            hide();
            mainwindow = new MainWindow(this);
            mainwindow->show();
        } else {
            // Show appropriate error message for failed login attempts
            if (username != userwrittenname || password != userwrittenpassword) {
                QMessageBox::warning(this, "Login", "Wrong password or username");
            } else {
                QMessageBox::warning(this, "Login", "Username or password is incorrect");
            }

            // Show or hide the forgotPasswordButton based on username/password existence
            QPushButton *forgotPasswordButton = findChild<QPushButton*>("forgotPasswordButton");

            if (forgotPasswordButton) {
                if (!usernameExists || !passwordExists) {
                    forgotPasswordButton->show();
                } else {
                    forgotPasswordButton->show();
                }
            }
        }
    }

    encrypt(password);
}


void secWindow::on_pushButton_2_clicked()
{
    newId = new NewID(this);
    newId->setWindowTitle("Create Username and Id");
    newId->show();
}



void secWindow::on_forgotPasswordButton_clicked()
{

    // Create a new instance of NewID dialog
    forgotpassword *forgot = new forgotpassword(this);
    forgot->setWindowTitle("Create New Password");

    // Show the NewID dialog
    forgot->show();
}
