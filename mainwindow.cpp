#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QTableWidget>
#include<QTableWidgetItem>
#include<QMessageBox>
#include <QVBoxLayout>
#include<Qfile>
#include<QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TableWidgetDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::TableWidgetDisplay()
//{
//    QTableWidget *table = ui->tableWidget;//creating a table object
//    //setting up row number and columns
//    table->setRowCount(48);
//    table->setColumnCount(4);
//    //for row topics
//    QStringList hlabels;
//    hlabels<<"Name"<<"Roll no"<<"Marks"<<"Assignements";
//    table->setHorizontalHeaderLabels(hlabels);

//    //showcasing table in a whole windows
//    this->setCentralWidget(table);
//    QPushButton *button = ui->pushButton;
//    connect(button, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);


//    //    QTableWidgetItem *item;
//    //    item = new QTableWidgetItem();
//    //    item->setText("sangam");
//    //    table->setItem(1,0,item);
//}
void MainWindow::TableWidgetDisplay()
{
    QTableWidget *table = ui->tableWidget;//creating a table object
    //setting up row number and columns.

    table->setRowCount(48);
    table->setColumnCount(4);

    //for row topics
    QStringList hlabels;
    hlabels<<"Name"<<"Roll no"<<"Marks"<<"Assignements";
    table->setHorizontalHeaderLabels(hlabels);

    //showing table in a whole windows
    this->setCentralWidget(table);
    QPushButton *button = ui->pushButton;
    connect(button, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    QPushButton *lbutton = ui->loadButton;
    connect(lbutton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(button);
    hlayout->addWidget(lbutton);

    QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(table);
    layout->addLayout(hlayout);



    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);
}


void MainWindow::on_pushButton_clicked()
{
    //just checking if button works or not.
//    QTableWidget *table = ui->tableWidget;
//    QTableWidgetItem *item;
//    item = new QTableWidgetItem();
//    item->setText("sangam");
//    table->setItem(1,0,item);
    storeTableValues();

}


void MainWindow::on_loadButton_clicked()
{
    loadTableValues();
}

void MainWindow::storeTableValues()
{
    QTableWidget *table = ui->tableWidget;
    QFile file("table_values.csv");

    // Check for empty cells and set red border
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (!item || item->text().isEmpty()) {
                table->setItem(row, col, new QTableWidgetItem());
                table->item(row, col)->setBackground(QBrush(Qt::red));
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            } else {
                table->item(row, col)->setBackground(QBrush(Qt::white)); // Reset background color
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            }
        }
    }

    // Continue with saving if no empty cells are found
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Write header
        QStringList headers;
        for (int col = 0; col < table->columnCount(); ++col) {
            headers << table->horizontalHeaderItem(col)->text();
        }
        out << headers.join(",") << "\n";

        // Write data
        for (int row = 0; row < table->rowCount(); ++row) {
            QStringList rowData;
            for (int col = 0; col < table->columnCount(); ++col) {
                QTableWidgetItem *item = table->item(row, col);
                if (item) {
                    rowData << item->text();
                }
            }
            out << rowData.join(",") << "\n";
        }

        file.close();
        QMessageBox::information(this, "Table Values Saved", "The table values were successfully saved to a file called table_values.csv.");
    } else {
        QMessageBox::critical(this, "Error Saving Table Values", "An error occurred while trying to save the table values to a file.");
    }
}

void MainWindow::loadTableValues()
{
    QTableWidget *table = ui->tableWidget;
    QFile file("table_values.csv");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Read header
        QStringList headers = in.readLine().split(",");
        table->setColumnCount(headers.size());
        table->setHorizontalHeaderLabels(headers);

        // Clear existing data
        table->clearContents();
        table->setRowCount(0);

        // Read data
        while (!in.atEnd()) {
            QStringList rowData = in.readLine().split(",");
            int row = table->rowCount();
            table->insertRow(row);
            for (int col = 0; col < headers.size(); ++col) {
                if (col < rowData.size()) {
                    QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col));
                    table->setItem(row, col, item);
                } else {
                    // Handle the case where the data is missing for a column
                    QTableWidgetItem *item = new QTableWidgetItem("");
                    table->setItem(row, col, item);
                }
            }
        }

        file.close();
        QMessageBox::information(this, "Table Values Loaded", "The table values were successfully loaded from the file table_values.csv.");
    } else {
        QMessageBox::critical(this, "Error Loading Table Values", "An error occurred while trying to load the table values from the file table_values.csv.");
    }
}


