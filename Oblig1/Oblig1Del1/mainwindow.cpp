#include <QtWidgets>
#include <QDebug>
#include <sstream>
#include <string>
#include "mainWindow.h"


MainWindow::MainWindow() : QMainWindow()
{
    // Resizes the window to an appropriate size
    resize(QDesktopWidget().availableGeometry(this).size() * 0.1);

    setWindowTitle("Oblig 1 Del 1");

    // Create the text editor for input and sorted text editor for output
    m_textEdit = new QTextEdit();
    m_sortedTextEdit = new QTextEdit();

    // Example text that pops up when program starts
    QString text("p o u n f d s u i e");
    m_textEdit->setPlainText(text);

    // To disable editing the output window
    m_sortedTextEdit->setEnabled(false);

    // The button that will start the sort
    m_sortButton = new QPushButton("Sort");

    // Radio buttons to toggle between ascending and descending sort defaulted to ascending
    m_ascendingButton = new QRadioButton("Ascending");
    m_ascendingButton->setChecked(true);
    m_descendingButton = new QRadioButton("Descending");

    // The layout to line up the buttons horizontally
    QHBoxLayout* hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(m_sortButton);
    hBoxLayout->addWidget(m_ascendingButton);
    hBoxLayout->addWidget(m_descendingButton);

    // The layout to vertically align the editors and button layout vertically
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_textEdit);
    layout->addWidget(m_sortedTextEdit);
    layout->addLayout(hBoxLayout);

    // The widget that holds the layout
    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);

    // Connecting the sort button to the sort function
    connect(m_sortButton, SIGNAL(clicked()), this, SLOT(sortClicked()));
}

void MainWindow::close()
{
    QMainWindow::close();
}

void MainWindow::sortClicked()
{
    // Get a vector from the input in text editor
    QString qString = m_textEdit->toPlainText();
    auto vector = stringToVector<Object<char>>(qString.toStdString());

    // Sort the vector
    bubbleSort(vector);

    // Convert the vector back into a string
    auto string = vectorToString(vector);

    // Output in sorted text editor
    m_sortedTextEdit->clear();
    m_sortedTextEdit->setText(QString::fromStdString(string));

}

// Converts a given string to a vector holding the data.
template <typename T>
std::vector<T>& MainWindow::stringToVector(std::string stringToConvert)
{
    std::stringstream ss(stringToConvert);
    auto v = new std::vector<Object<char>>();
    char temp;
    while(ss>>temp)
    {
        v->push_back(temp);
    }
    return *v;
}

template <typename T>
void MainWindow::bubbleSort(std::vector<T>& vector)
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
                if(vector[j] > vector[j+1])
                {
                    temp = vector[j]();
                    vector[j] = vector[j+1];
                    vector[j+1] = temp;
                    swapped = true;
                }
            }
            else
            {
                if(vector[j] < vector[j+1])
                {
                    temp = vector[j]();
                    vector[j] = vector[j+1];
                    vector[j+1] = temp;
                    swapped = true;
                }
            }
        }
        // Break if inner loop never swapped (vector is finished sorting before reaching the end)
        if(!swapped)
        {
            break;
        }
    }
}

// Converts a given vector of objects to a string ready to be outputted
template <typename T>
std::string MainWindow::vectorToString(const std::vector<T> &vectorToConvert)
{
    std::stringstream ss;

    for (auto it = vectorToConvert.begin(); it != vectorToConvert.end(); it++)
    {
        ss << *it;
        ss << " ";
    }

    return ss.str();
}
