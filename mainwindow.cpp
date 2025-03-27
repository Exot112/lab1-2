#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем центральный виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создаем вертикальный макет для центрального виджета
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Создаем текстовое поле для ввода описания недвижимости
    textEditDescription = new QTextEdit(this);
    textEditDescription->setPlaceholderText("\"Влад Девяев\" 2000.10.01 1500000 \"Свободный пр-кт, д. 28а\" 5");
    mainLayout->addWidget(textEditDescription);

    // Создаем кнопку для обработки строки
    pushButtonParse = new QPushButton("Parse", this);
    mainLayout->addWidget(pushButtonParse);

    // Создаем горизонтальные макеты для меток и значений
    QHBoxLayout *layoutOwner = new QHBoxLayout;
    QHBoxLayout *layoutRegistrationDate = new QHBoxLayout;
    QHBoxLayout *layoutEstimatedCost = new QHBoxLayout;
    QHBoxLayout *layoutAddress = new QHBoxLayout;
    QHBoxLayout *layoutNumberOfRooms = new QHBoxLayout;

    // Создаем метки и значения для отображения результатов
    labelOwner = new QLabel("Владелец:", this);
    QLabel *valueOwner = new QLabel("", this);
    layoutOwner->addWidget(labelOwner);
    layoutOwner->addWidget(valueOwner);

    labelRegistrationDate = new QLabel("Дата постановки на учет:", this);
    QLabel *valueRegistrationDate = new QLabel("", this);
    layoutRegistrationDate->addWidget(labelRegistrationDate);
    layoutRegistrationDate->addWidget(valueRegistrationDate);

    labelEstimatedCost = new QLabel("Ориентировочная стоимость:", this);
    QLabel *valueEstimatedCost = new QLabel("", this);
    layoutEstimatedCost->addWidget(labelEstimatedCost);
    layoutEstimatedCost->addWidget(valueEstimatedCost);

    labelAddress = new QLabel("Адрес:", this);
    QLabel *valueAddress = new QLabel("", this);
    layoutAddress->addWidget(labelAddress);
    layoutAddress->addWidget(valueAddress);

    labelNumberOfRooms = new QLabel("Количество комнат:", this);
    QLabel *valueNumberOfRooms = new QLabel("", this);
    layoutNumberOfRooms->addWidget(labelNumberOfRooms);
    layoutNumberOfRooms->addWidget(valueNumberOfRooms);

    // Добавляем горизонтальные макеты в главный вертикальный макет
    mainLayout->addLayout(layoutOwner);
    mainLayout->addLayout(layoutRegistrationDate);
    mainLayout->addLayout(layoutEstimatedCost);
    mainLayout->addLayout(layoutAddress);
    mainLayout->addLayout(layoutNumberOfRooms);

    // Подключаем сигнал нажатия кнопки к слоту
    connect(pushButtonParse, &QPushButton::clicked, this, &MainWindow::on_pushButtonParse_clicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButtonParse_clicked()
{
    try {
        // Получаем текст из текстового поля
        std::string description = textEditDescription->toPlainText().toStdString();

        // Парсим описание
        realEstate.parse(description);

        // Преобразуем дату в строку для отображения
        std::ostringstream oss;
        oss << std::put_time(&realEstate.registrationDate, "%d.%m.%Y");

        // Обновляем метки с результатами
        labelOwner->setText(QString::fromStdString("Владелец: " + realEstate.owner));
        labelRegistrationDate->setText(QString::fromStdString("Дата постановки на учет: " + oss.str()));
        labelEstimatedCost->setText(QString::fromStdString("Ориентировочная стоимость: " + std::to_string(realEstate.estimatedCost)));
        labelAddress->setText(QString::fromStdString("Адрес: " + realEstate.address));
        labelNumberOfRooms->setText(QString::fromStdString("Количество комнат: " + std::to_string(realEstate.numberOfRooms)));
    } catch (const std::exception &e) {
        qDebug() << "Error parsing description:" << e.what();
    }
}
