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


//     QTableWidgetItem *item;
//     item = new QTableWidgetItem();
//     item->setText("sangam");
//     table->setItem(1,0,item);
//}
void MainWindow::TableWidgetDisplay()
{
    QTableWidget *table = ui->tableWidget;//creating a table object
    //setting up row number and columns.
    table->setRowCount(48);

    //rowValueAdd();
    //table->setRowCount(48);
    table->setColumnCount(5);

    //for row topics
    QStringList hlabels;
    hlabels<<"Name"<<"Roll no"<<"Marks"<<"Assignements"<<"Assessments"<<"Practicals";
    table->setHorizontalHeaderLabels(hlabels);

    //showing table in a whole windows
    this->setCentralWidget(table);
    buttonDisplays();


}

void MainWindow::buttonDisplays()
{
    QTableWidget *table = ui->tableWidget;
    QPushButton *button = ui->pushButton;
    //connect(button, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    QPushButton *lbutton = ui->loadButton;
    //connect(lbutton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);

    QLineEdit *rowEdit = ui->lineEditR;
    rowEdit->setPlaceholderText("No of rows");

    QPushButton *addRowButton = ui->addRowButton;
    // connect(addRowButtonbutton, &QPushButton::clicked, this, &MainWindow::on_addRowButton_clicked);
    QPushButton *addColumnButton = ui->columnAddButton;

    QLineEdit *columnEdit = ui->lineEditC;
    columnEdit->setPlaceholderText("Write Heading title..");

    QPushButton *subColumnButton = ui->buttonSub;

    QVBoxLayout *rowLayout = new QVBoxLayout;
    rowLayout->addWidget(addRowButton);
    rowLayout->addWidget(rowEdit);



    QHBoxLayout *columnHLayout = new QHBoxLayout;
    columnHLayout->addWidget(addColumnButton);
    columnHLayout->addWidget(subColumnButton);

    QVBoxLayout *columnLayout= new QVBoxLayout;
    columnLayout->addLayout(columnHLayout);
    columnLayout->addWidget(columnEdit);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(button);
    hlayout->addWidget(lbutton);
    hlayout->addLayout(rowLayout);
    hlayout->addLayout(columnLayout);





    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(table);
    layout->addLayout(hlayout);



    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);
}


void MainWindow::on_pushButton_clicked()
{
    storeTableValues();
}


void MainWindow::on_loadButton_clicked()
{
    loadTableValues();
}

void MainWindow::on_addRowButton_clicked()
{
    rowManipulation();
}

void MainWindow::on_columnAddButton_clicked()
{
    columnManipulation();
}

void MainWindow::on_buttonSub_clicked()
{
    columnRemover();
}



void MainWindow::rowManipulation()
{
    QTableWidget *table = ui->tableWidget;
    QLineEdit *rowEdit = ui->lineEditR;
    QString rowInput = rowEdit->text();
    QFile rowFile("row_value.txt");
    if (rowFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Create a QTextStream associated with the file
        QTextStream out(&rowFile);

        // Write the QLineEdit text to the file
        out << rowInput;

        // Close the file
        rowFile.close();
    } else {
        // Handle the case where the file could not be opened
        qDebug() << "Error: Could not open the file for writing.";
    }
    int rowValues = rowInput.toInt();
    table->setRowCount(rowValues);
}

void MainWindow::columnManipulation()
{
    QTableWidget *table = ui->tableWidget;
    QLineEdit *columnEdit = ui->lineEditC;
    QString columnInput = columnEdit->text();
    int columnNo = table->columnCount();

    QStringList oldTitle;
    for(int col = 0; col<columnNo;++col)
    {
        oldTitle<<table->horizontalHeaderItem(col)->text();
    }
    table->setColumnCount(columnNo+1);
    oldTitle<<columnInput;
    table->setHorizontalHeaderLabels(oldTitle);

}

void MainWindow::columnRemover()
{
    QTableWidget *table = ui->tableWidget;
    int columnNo = table->columnCount();
    table->setColumnCount(columnNo-1);
}

//void MainWindow::rowValueAdd()
//{
//    QTableWidget *table = ui->tableWidget;
//    QFile inFile("row_value.txt");
//    if((inFile.open(QIODevice::ReadOnly)&&inFile.open(QIODevice::ReadOnly)))
//    {
//        if(inFile.size()!=0)
//        {
//            QString readValue;
//            QTextStream in(&inFile);
//            in >> readValue;

//            // Attempt to convert the string to an integer
//            bool isNumeric;
//            int intValue = readValue.toInt(&isNumeric);

//            if (isNumeric) {
//                table->setRowCount(intValue);
//            } else {
//                table->setRowCount(48);
//            }


//        }

//        else
//        {
//            table->setRowCount(48);
//        }
//        inFile.close();
//    }

//    //inFile.close();
//}

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
        QMessageBox::information(this, "Table Values Saved", "The table values were successfully stored.");
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
        QMessageBox::information(this, "Table Values Loaded", "The table values were successfully loaded.");

    } else {
        QMessageBox::critical(this, "Error Loading Table Values", "An error occurred while trying to load the table values from the file table_values.csv.");
    }
}








