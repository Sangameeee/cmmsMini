#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include<QString>
#include<QMessageBox>
#include<Qfile>
#include<QTextStream>
#include "encryption.h"
forgotpassword::forgotpassword(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::forgotpassword)
{
    ui->setupUi(this);
}

forgotpassword::~forgotpassword()
{
    delete ui;
}

void forgotpassword::on_resetButton_clicked()
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
    //ask message
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(this, "Confirmation", "Do you want to reset the password?",
                                         QMessageBox::Yes | QMessageBox::No);

    if (confirmation == QMessageBox::Yes)
    {
        QFile pfile("password.txt");
        if (!pfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Failed: " + pfile.errorString());
        } else {
            QTextStream stream(&pfile);
            stream << password;
            pfile.close();

            // Set file permissions to hide the file
            QFile::setPermissions("password.txt", QFile::ReadOwner | QFile::WriteOwner);
            QMessageBox::about(this, "Password Reset", "New Password is created");
        }
    }
    else
        // User chose not to reset the password
        QMessageBox::information(this, "Info", "Password reset cancelled");
}

