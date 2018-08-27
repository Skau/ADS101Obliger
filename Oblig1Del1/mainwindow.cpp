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


    // Sort the vector (order depends on which radio button is toggled)
    int n = vector.size();
    int temp = 0;
    for(int i = 0;  i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(m_ascendingButton->isChecked())
            {
                if(vector[j] < vector[i])
                {
                    temp = vector[i].getData();
                    vector[i] = vector[j];
                    vector[j] = temp;
                }
            }
            else
            {
                if(vector[j] > vector[i])
                {
                    temp = vector[i].getData();
                    vector[i] = vector[j];
                    vector[j] = temp;
                }
            }
        }
    }

    // Convert the vector back to a string and output in sorted text editor
    auto stringToShow = qString.fromStdString(vectorToString(vector));
    m_sortedTextEdit->clear();
    m_sortedTextEdit->setText(stringToShow);
}

// Converts a given string to a vector of objects holding the data
std::vector<Object> MainWindow::stringToVector(std::string stringToConvert)
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

// Converts a given vector of objects to a string ready to be outputted
std::string MainWindow::vectorToString(std::vector<Object> vectorToConvert)
{
    std::stringstream ss;

    for (auto it = vectorToConvert.begin(); it != vectorToConvert.end(); it++)
    {
        ss << *it;
        ss << " ";
    }

    return ss.str();
}
