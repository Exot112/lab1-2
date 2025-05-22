#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QLineEdit>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Создаем таблицу
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels({"Владелец", "Дата регистрации", "Стоимость", "Адрес", "Комнат"});
    mainLayout->addWidget(tableWidget);

    // Создаем кнопки
    buttonLoad = new QPushButton("Загрузить из файла", this);
    buttonAdd = new QPushButton("Добавить объект", this);
    buttonRemove = new QPushButton("Удалить объект", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonLoad);
    buttonLayout->addWidget(buttonAdd);
    buttonLayout->addWidget(buttonRemove);
    mainLayout->addLayout(buttonLayout);

    // Подключаем сигналы к слотам
    connect(buttonLoad, &QPushButton::clicked, this, &MainWindow::loadObjectsFromFile);
    connect(buttonAdd, &QPushButton::clicked, this, &MainWindow::addObject);
    connect(buttonRemove, &QPushButton::clicked, this, &MainWindow::removeObject);
}

MainWindow::~MainWindow() {}

void MainWindow::updateTable() {
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    const auto &objects = manager.getObjects();
    for (const auto &obj : objects) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(obj.owner)));

        // Преобразуем дату в строку
        std::ostringstream oss;
        oss << std::put_time(&obj.registrationDate, "%Y.%m.%d");
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(oss.str())));

        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(obj.estimatedCost)));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(obj.address)));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(obj.numberOfRooms)));
    }
}

void MainWindow::loadObjectsFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text files (*.txt)");
    if (filename.isEmpty()) {
        return;
    }

    try {
        manager.loadFromFile(filename.toStdString());
        updateTable();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::addObject() {
    bool ok;
    QString description = QInputDialog::getText(this, "Добавить объект", "Введите описание объекта:", QLineEdit::Normal, "", &ok);
    if (ok && !description.isEmpty()) {
        try {
            RealEstate realEstate;
            realEstate.parse(description.toStdString());
            manager.addObject(realEstate);
            updateTable();
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Ошибка", e.what());
        }
    }
}

void MainWindow::removeObject() {
    int row = tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите объект для удаления.");
        return;
    }

    try {
        manager.removeObject(row);
        updateTable();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}
