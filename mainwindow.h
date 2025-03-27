#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "realestatemanager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTable();
    void loadObjectsFromFile();
    void addObject();
    void removeObject();

private:
    QTableWidget *tableWidget;
    QPushButton *buttonLoad;
    QPushButton *buttonAdd;
    QPushButton *buttonRemove;

    RealEstateManager manager;
};

#endif // MAINWINDOW_H
