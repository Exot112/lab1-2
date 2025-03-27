#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "realestate.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonParse_clicked();

private:
    QTextEdit *textEditDescription;
    QPushButton *pushButtonParse;
    QLabel *labelOwner;
    QLabel *labelRegistrationDate;
    QLabel *labelEstimatedCost;
    QLabel *labelAddress;
    QLabel *labelNumberOfRooms;

    RealEstate realEstate;
};

#endif // MAINWINDOW_H
