#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <map>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sortButton_clicked();

    void on_quickCheckBox_stateChanged(int arg1);

    void on_insertionCheckBox_stateChanged(int arg1);

    void on_mergeCheckBox_stateChanged(int arg1);

    void on_heapCheckBox_stateChanged(int arg1);

    void on_stlCheckBox_stateChanged(int arg1);

    void on_binaryTreeCheckBox_stateChanged(int arg1);

    void on_selectionCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    void updateTimeTakenList(std::vector<std::pair<double, std::string>> times);

    template <typename T>
    std::vector<T> generateRandomData(int length);

    bool selection, insertion, merge, quick, stl, binarytree, heap;
};

#endif // MAINWINDOW_H
