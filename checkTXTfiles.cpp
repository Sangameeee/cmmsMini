#include "checkTXTfiles.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

CheckTXTFiles::CheckTXTFiles(QObject *parent) : QObject(parent) {}

bool CheckTXTFiles::isPasswordFileEmpty() {
    QFile passwordFile("password.txt");
    if (!passwordFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open password.txt";
        return true; // Return true assuming it's empty in case of an error
    }

    QTextStream in(&passwordFile);
    bool isEmpty = in.atEnd();
    passwordFile.close();

    return isEmpty;
}

bool CheckTXTFiles::isUsernameFileEmpty() {
    QFile usernameFile("username.txt");
    if (!usernameFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open username.txt";
        return true; // Return true assuming it's empty in case of an error
    }

    QTextStream in(&usernameFile);
    bool isEmpty = in.atEnd();
    usernameFile.close();

    return isEmpty;
}
