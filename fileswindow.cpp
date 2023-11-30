#include "fileswindow.h"
#include "ui_fileswindow.h"
#include<QFile>
#include<QMessageBox>
#include<QTextStream>

filesWindow::filesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filesWindow)
{
    ui->setupUi(this);
    lineeditshow();

}

filesWindow::~filesWindow()
{
    delete ui;
}
void filesWindow::lineeditshow()
{
    QLineEdit *filesValue = ui->lineEditf;

    filesValue->setPlaceholderText("Enter a name");
}

void filesWindow::on_pushButton_clicked()
{

    QLineEdit *filesValue = ui->lineEditf;


    if (filesValue->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "enter a name it cannot be empty");
    }
    else{
        hide();
        QFile ufile("files.txt");

        if (!ufile.open(QIODevice::WriteOnly | QIODevice::Text))
        {

            QMessageBox::warning(this, "Error", "Failed: " + ufile.errorString());
        }
        else
        {
            QTextStream stream(&ufile);
            stream << filesValue->text() ;
            ufile.close();

        }
        mainwindow = new MainWindow(this);
        mainwindow->show();
    }
}



