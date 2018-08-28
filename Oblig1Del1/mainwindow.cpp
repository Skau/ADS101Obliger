#include <QtWidgets>
#include <QDebug>
#include <algorithm>
#include <sstream>
#include <string>
#include "mainWindow.h"


MainWindow::MainWindow() : QMainWindow()
{
    // Resizes the window to an appropriate size
    resize(QDesktopWidget().availableGeometry(this).size() * 0.1);

    // Create the text editor for input and sorted text editor for output
    m_textEdit = new QTextEdit();
    m_sortedTextEdit = new QTextEdit();

    // Example text that pops up when program starts
    QString text("7 3 4 2 8 9 3 2 1 4");
    m_textEdit->setPlainText(text);

    // To disable editing the output window
    m_sortedTextEdit->setEnabled(false);

    // The button that will output the sorted text
    m_sortButton = new QPushButton("Sort");

    // Radio buttons to toggle between ascending and descending sort
    m_ascendingButton = new QRadioButton("Ascending");
    m_ascendingButton->setChecked(true);
    m_descendingButton = new QRadioButton("Descending");

    // The layout to line up the buttons
    QHBoxLayout* hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(m_sortButton);
    hBoxLayout->addWidget(m_ascendingButton);
    hBoxLayout->addWidget(m_descendingButton);

    // The layout to vertically align the editors and button layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_textEdit);
    layout->addWidget(m_sortedTextEdit);
    layout->addLayout(hBoxLayout);

    // The widget that holds the layout
    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);

    setWindowTitle("Oblig 1 Del 1");

    // Connecting the sort button to the sort function
    connect(m_sortButton, SIGNAL(clicked()), this, SLOT(sort()));
}

void MainWindow::close()
{
    QMainWindow::close();
}

void MainWindow::sort()
{
    // Get a vector from the input in text editor
    QString qString = m_textEdit->toPlainText();
    auto vector = stringToVector(qString.toStdString());

    // Sort the vector
    bubbleSort(vector);

    // Convert the vector back into a string
    auto string = vectorToString(vector);

    // Output in sorted text editor
    auto stringToShow = qString.fromStdString(string);
    m_sortedTextEdit->clear();
    m_sortedTextEdit->setText(stringToShow);
}

// Converts a given string to a vector of Object holding the data
std::vector<Object> MainWindow::stringToVector(const std::string& stringToConvert)
{
    std::vector<Object> v;

    std::stringstream ss(stringToConvert);
    int temp;

    while(ss>>temp)
    {
        v.push_back(Object(temp));
    }

    return v;
}

void MainWindow::bubbleSort(std::vector<Object>& vector)
{
    int n = vector.size();
    int temp = 0;
    bool swapped;
    for(int i = 0;  i < n - 1; i++)
    {
        swapped = false;
        for(int j = 0; j < n - i - 1; j++)
        {
            if(m_ascendingButton->isChecked())
            {
                if(vector[j] < vector[j+1])
                {
                    // Overloaded operator() to return m_data in object
                    temp = vector[j]();
                    vector[j] = vector[j+1];
                    vector[j+1] = temp;
                    swapped = true;
                }
            }
            else
            {
                if(vector[j] > vector[j+1])
                {
                    temp = vector[j]();
                    vector[j] = vector[j+1];
                    vector[j+1] = temp;
                    swapped = true;
                }
            }
        }
        // Break if inner loop never swapped (vector is sorted)
        if(!swapped)
        {
            break;
        }
    }
}

// Converts a given vector of objects to a string ready to be outputted
std::string MainWindow::vectorToString(const std::vector<Object> &vectorToConvert)
{
    std::stringstream ss;

    for (auto it = vectorToConvert.begin(); it != vectorToConvert.end(); it++)
    {
        ss << *it;
        ss << " ";
    }

    return ss.str();
}
