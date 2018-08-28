#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "object.h"

class QPushButton;
class QTextEdit;
class QRadioButton;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() = default;

public slots:
    void sort();
    void close();

signals:

protected:

private:

    std::vector<Object>stringToVector(const std::string &stringToConvert);

    std::string vectorToString(const std::vector<Object>& vectorToConvert);

    QTextEdit* m_textEdit;
    QTextEdit* m_sortedTextEdit;
    QPushButton* m_sortButton;
    QRadioButton* m_ascendingButton;
    QRadioButton* m_descendingButton;
    void bubbleSort(std::vector<Object>& vector);
};

#endif
