#include "PhoneBook.h"

PhoneBook::PhoneBook(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    loadFromFile();
}

PhoneBook::~PhoneBook() {
    saveToFile();
}

void PhoneBook::setupUI() {
    // Создаем таблицу
    table = new QTableWidget(this);
    table->setColumnCount(6); // Устанавливаем количество столбцов
    table->setHorizontalHeaderLabels(QStringList() << "Фамилия" << "Имя" << "Отчество"
                                                   << "Телефон" << "E-mail" << "Дата рождения");
    table->setSelectionBehavior(QAbstractItemView::SelectRows); // Выделение строк
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Запрет редактирования
    table->setSortingEnabled(true);  // Включаем сортировку для таблицы

    // Создаем кнопки
    addButton = new QPushButton("Добавить контакт", this);
    editButton = new QPushButton("Редактировать контакт", this);
    deleteButton = new QPushButton("Удалить контакт", this);
    searchButton = new QPushButton("Поиск контакта", this);
    loadButton = new QPushButton("Загрузить контакты", this);
    addPhoneNumberButton = new QPushButton("Добавить номер", this);

    // Создаем макеты
    QVBoxLayout *mainLayout = new QVBoxLayout();    // Основной вертикальный макет
    QHBoxLayout *buttonLayout = new QHBoxLayout();  // Макет для кнопок

    // Добавляем кнопки в макет кнопок
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(addPhoneNumberButton);

    // Добавляем таблицу и макет кнопок в основной макет
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);

    // Создаем центральный виджет для QMainWindow
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    // Устанавливаем центральный виджет в QMainWindow
    setCentralWidget(centralWidget);

    // Подключаем сигналы к слотам
    connect(addButton, &QPushButton::clicked, this, &PhoneBook::addContact);
    connect(editButton, &QPushButton::clicked, this, &PhoneBook::editContact);
    connect(deleteButton, &QPushButton::clicked, this, &PhoneBook::deleteContact);
    connect(searchButton, &QPushButton::clicked, this, &PhoneBook::searchContact);
    connect(loadButton, &QPushButton::clicked, this, &PhoneBook::loadFromFile);
    connect(addPhoneNumberButton, &QPushButton::clicked, this, &PhoneBook::addPhoneNumber);
}



void PhoneBook::addContact() {
    AddContactDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QStringList contactData = dialog.getContact();
        if (contactData.isEmpty()) return;

        Contact contact;
        contact.lastName = contactData[0];
        contact.firstName = contactData[1];
        contact.middleName = contactData[2];

        // Разделяем введённые номера телефонов через запятую и сохраняем как список
        QStringList phoneNumbersList = contactData[3].split(",", Qt::SkipEmptyParts);
        for (QString &phone : phoneNumbersList) {
            phone = phone.trimmed(); // Убираем лишние пробелы вокруг номеров
        }
        contact.phoneNumbers = phoneNumbersList.toVector();

        contact.email = contactData[4];
        contact.birthDate = contactData[5];

        QString key = contact.lastName + " " + contact.firstName + " " + contact.middleName;
        contacts[key] = contact;

        // Добавляем контакт в таблицу
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(contact.lastName));
        table->setItem(row, 1, new QTableWidgetItem(contact.firstName));
        table->setItem(row, 2, new QTableWidgetItem(contact.middleName));
        table->setItem(row, 3, new QTableWidgetItem(phoneNumbersList.join(", "))); // Отображаем все номера через запятую
        table->setItem(row, 4, new QTableWidgetItem(contact.email));
        table->setItem(row, 5, new QTableWidgetItem(contact.birthDate));

        saveToFile();
    }
}


void PhoneBook::editContact() {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для редактирования.");
        return;
    }

    // Получаем данные контакта из таблицы
    QString lastName = table->item(row, 0)->text();
    QString firstName = table->item(row, 1)->text();
    QString middleName = table->item(row, 2)->text();
    QStringList phoneNumbers = table->item(row, 3)->text().split(", "); // Разделяем номера по запятой
    QString email = table->item(row, 4)->text();
    QString birthDate = table->item(row, 5)->text();

    // Создаем список данных для передачи в диалог редактирования
    QStringList contactData = { lastName, firstName, middleName, phoneNumbers.join(", "), email, birthDate };

    // Вызываем диалог редактирования
    EditContactDialog dialog(contactData, this);
    if (dialog.exec() == QDialog::Accepted) {
        // Получаем отредактированные данные
        QStringList updatedContactData = dialog.getContact();

        // Обновляем контакт в таблице
        table->setItem(row, 0, new QTableWidgetItem(updatedContactData[0])); // Фамилия
        table->setItem(row, 1, new QTableWidgetItem(updatedContactData[1])); // Имя
        table->setItem(row, 2, new QTableWidgetItem(updatedContactData[2])); // Отчество
        table->setItem(row, 3, new QTableWidgetItem(updatedContactData[3])); // Номера телефонов (объединенные через запятую)
        table->setItem(row, 4, new QTableWidgetItem(updatedContactData[4])); // E-mail
        table->setItem(row, 5, new QTableWidgetItem(updatedContactData[5])); // Дата рождения

        // Обновляем данные в карте контактов
        QString key = lastName + " " + firstName + " " + middleName;
        Contact &contact = contacts[key];
        contact.lastName = updatedContactData[0];
        contact.firstName = updatedContactData[1];
        contact.middleName = updatedContactData[2];
        contact.phoneNumbers = updatedContactData[3].split(", ").toVector(); // Преобразуем QStringList в QVector<QString>
        contact.email = updatedContactData[4];
        contact.birthDate = updatedContactData[5];


        // Сохраняем изменения в файл
        saveToFile();
    }
}


void PhoneBook::deleteContact() {
    int row = table->currentRow(); // Получаем текущую выбранную строку
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для удаления.");
        return;
    }

    // Получаем ключ контакта (используем фамилию, имя и отчество для идентификации)
    QString key = table->item(row, 0)->text() + " " +
                  table->item(row, 1)->text() + " " +
                  table->item(row, 2)->text();

    // Удаляем контакт из словаря
    if (contacts.contains(key)) {
        contacts.remove(key);
    }

    // Удаляем строку из таблицы
    table->removeRow(row);

    // Сохраняем изменения в файл
    saveToFile();

    QMessageBox::information(this, "Успех", "Контакт успешно удален!");
}


void PhoneBook::searchContact() {
    SearchContactDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString searchTerm = dialog.getSearchTerm();
        for (int i = 0; i < table->rowCount(); ++i) {
            bool found = false;
            for (int j = 0; j < table->columnCount(); ++j) {
                if (table->item(i, j)->text().contains(searchTerm, Qt::CaseInsensitive)) {
                    found = true;
                    break;
                }
            }
            table->setRowHidden(i, !found);
        }
    }
}

void PhoneBook::loadFromFile() {
    QFile file("contacts.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    contacts.clear();
    table->setRowCount(0);

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("|");
        if (fields.size() < 6) continue;

        Contact contact;
        contact.lastName = fields[0].trimmed();
        contact.firstName = fields[1].trimmed();
        contact.middleName = fields[2].trimmed();
        contact.email = fields[4].trimmed();
        contact.birthDate = fields[5].trimmed();

        // Преобразуем номера телефонов из строки в QVector
        QStringList phoneNumbersList = fields[3].split(",", Qt::SkipEmptyParts);
        contact.phoneNumbers = phoneNumbersList.toVector();

        QString key = contact.lastName + " " + contact.firstName + " " + contact.middleName;
        contacts[key] = contact;

        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(contact.lastName));
        table->setItem(row, 1, new QTableWidgetItem(contact.firstName));
        table->setItem(row, 2, new QTableWidgetItem(contact.middleName));
        table->setItem(row, 3, new QTableWidgetItem(phoneNumbersList.join(", "))); // Отображаем все номера
        table->setItem(row, 4, new QTableWidgetItem(contact.email));
        table->setItem(row, 5, new QTableWidgetItem(contact.birthDate));
    }

    file.close();
}


void PhoneBook::saveToFile() {
    QFile file("contacts.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);
    for (const auto &contact : contacts) {
        out << contact.lastName << "|"
            << contact.firstName << "|"
            << contact.middleName << "|";

        // Объединяем номера телефонов через запятую
        QStringList phoneNumbersList = QStringList::fromVector(contact.phoneNumbers);
        out << phoneNumbersList.join(",") << "|";

        out << contact.email << "|"
            << contact.birthDate << "\n";
    }

    file.close();
}

void PhoneBook::addPhoneNumber() {
    int currentRow = table->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для добавления номера.");
        return;
    }

    QString newNumber = QInputDialog::getText(this, "Добавить номер телефона", "Введите номер телефона (+7XXXXXXXXXX):").trimmed();

    // Проверка формата номера
    QRegularExpression phoneRegex("^\\+7\\d{10}$");
    if (!phoneRegex.match(newNumber).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Телефон должен быть в формате +7XXXXXXXXXX.");
        return;
    }

    QString contactKey = table->item(currentRow, 0)->text() + " " +
                         table->item(currentRow, 1)->text() + " " +
                         table->item(currentRow, 2)->text();

    if (!contacts.contains(contactKey)) {
        QMessageBox::warning(this, "Ошибка", "Контакт не найден.");
        return;
    }

    Contact &contact = contacts[contactKey];

    if (contact.phoneNumbers.size() >= 100) {
        QMessageBox::warning(this, "Ошибка", "Нельзя добавить больше 100 номеров.");
        return;
    }

    contact.phoneNumbers.append(newNumber);

    // Обновляем отображение в таблице
    table->setItem(currentRow, 3, new QTableWidgetItem(QStringList::fromVector(contact.phoneNumbers).join(", "))); // Отображаем все номера

    saveToFile();

    QMessageBox::information(this, "Успех", "Номер телефона успешно добавлен!");
}


