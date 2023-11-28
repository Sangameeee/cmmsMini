#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QTableWidget>
#include<QTableWidgetItem>
#include<QMessageBox>
#include <QVBoxLayout>
#include<Qfile>
#include<QTextStream>
#include"secwindow.h"
#include"valwindow.h"

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

void MainWindow::TableWidgetDisplay()
{
    this->setWindowTitle("Table");
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

    QPushButton *clearButton = ui->clearButton;
    QPushButton *calButton = ui->calButton;

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
    hlayout->addWidget(clearButton);
    hlayout->addWidget(calButton);




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


void MainWindow::on_clearButton_clicked()
{
    removeAll();
}
void MainWindow::on_calButton_clicked()
{
    //calculateValues();

    ValWindow valuesWin(ui->tableWidget);
    valuesWin.setWindowTitle("Values");
    valuesWin.setModal(true);
    valuesWin.exec();
}



void MainWindow::rowManipulation()
{
    QTableWidget *table = ui->tableWidget;
    QLineEdit *rowEdit = ui->lineEditR;
    QString rowInput = rowEdit->text();
    QString inputText = ui->lineEditR->text();

    bool ok;
    int intValue = inputText.toInt(&ok);

    if (rowInput.isEmpty())
    {
        // Handle empty input
        QMessageBox::warning(this,"Error","Please Enter a value");
    }
    else if (!ok)
    {
        // Handle non-numeric input
        QMessageBox::warning(this,"Error","Please Enter a Numeric value");
    }
    else
    {
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
        int currentRowCount = table->rowCount();
        if (rowValues < currentRowCount) {

            QMessageBox::StandardButton reply = QMessageBox::question(this, "Warning", "Decreasing Row count may cause loss of data. Do you want to proceed?", QMessageBox::Yes | QMessageBox::No);
            //this ask user iff he want to continue despite data loss or no

            if (reply == QMessageBox::Yes) {
                // Set the row count if user confirms
                table->setRowCount(rowValues);
            } else {
                // Do not change the row count if user cancels
                qDebug() << "No of row wasnt reduced!!!";
            }
        } else {
            // No need for confirmation if row count is not being reduced
            table->setRowCount(rowValues);
        }

    }

}

void MainWindow::columnManipulation()
{
    QTableWidget *table = ui->tableWidget;
    QLineEdit *columnEdit = ui->lineEditC;
    QString columnInput = columnEdit->text();
    int columnNo = table->columnCount();
    if (columnInput.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Column heading cannot be empty");
        return;
    }

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



void MainWindow::removeAll()//makes whole window blank
{
//    QTableWidget *table = ui->tableWidget;
//    table->hide();
    QWidget *centralWidget = this->centralWidget();
    centralWidget->hide();

}

void MainWindow::calculateValues()
{
    QTableWidget *table = ui->tableWidget;

    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);

            // Convert the header text to lowercase for case-insensitive comparison
            QString headerText = table->horizontalHeaderItem(col)->text().toLower();

            // Check if the header is "marks" or "assessments" and the item is an integer
            if ((headerText == "marks" || headerText == "assessments") && isInteger(item->text())) {
                // Reduce the value by 10 times
                int originalValue = item->text().toInt();
                item->setText(QString::number(originalValue / 10));
            }
        }
    }

    QMessageBox::information(this, "Calculation Completed", "Values under 'Marks' and 'Assessments' headers reduced by 10 times.");
}

bool MainWindow::isInteger(const QString &text)
{
    bool isNumeric;
    text.toInt(&isNumeric);
    return isNumeric;
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
                }
                else
                {
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









