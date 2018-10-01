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
    void sortClicked();
    void close();

signals:

protected:

private:

    QTextEdit* m_textEdit;
    QTextEdit* m_sortedTextEdit;
    QPushButton* m_sortButton;
    QRadioButton* m_ascendingButton;
    QRadioButton* m_descendingButton;

    // Cannot return templated vector, as it cannot be deduced by the compiler.
    // Instead an out parameter is used.
    template <typename T>
    std::vector<T>& stringToVector(std::string stringToConvert);

    template <typename T>
    std::string vectorToString(const std::vector<T> &vectorToConvert);

    template <typename T>
    void bubbleSort(std::vector<T> &vector);
};

#endif
