#pragma once
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

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
    void on_manualThrottleButton_clicked();

    void on_ESTOPButton_clicked();

    void on_scmSPButton_clicked();

private:
    Ui::MainWindow *ui;
};
