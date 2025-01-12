#include "PhoneBook.h"

PhoneBook::PhoneBook(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    connectToDatabase();
    loadFromFile();
}

PhoneBook::~PhoneBook() {
    saveToFile(); // Сохраняем изменения в файл перед завершением программы

    // Закрываем соединение с базой данных
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
        qDebug() << "Соединение с базой данных закрыто.";
    }
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
    loadFromDbButton = new QPushButton("Загрузить из DB", this); // Новая кнопка

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
    buttonLayout->addWidget(loadFromDbButton); // Добавляем кнопку в макет

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
    connect(loadFromDbButton, &QPushButton::clicked, this, &PhoneBook::loadFromDatabase);
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

        // Сохраняем контакт в базе данных
        saveToDatabase(contact);

        // Сохряняем контакт в файл
        saveToFile();
    }
}



void PhoneBook::editContact() {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для редактирования.");
        return;
    }

    // Проверяем наличие данных в строке таблицы
    if (!table->item(row, 0) || !table->item(row, 1) || !table->item(row, 2)) {
        QMessageBox::warning(this, "Ошибка", "Данные контакта отсутствуют в таблице.");
        return;
    }

    // Получаем данные контакта из таблицы
    QString lastName = table->item(row, 0)->text();
    QString firstName = table->item(row, 1)->text();
    QString middleName = table->item(row, 2)->text();
    QStringList phoneNumbers = table->item(row, 3) ? table->item(row, 3)->text().split(", ") : QStringList();
    QString email = table->item(row, 4) ? table->item(row, 4)->text() : "";
    QString birthDate = table->item(row, 5) ? table->item(row, 5)->text() : "";

    // Создаем список данных для редактирования
    QStringList contactData = { lastName, firstName, middleName, phoneNumbers.join(", "), email, birthDate };

    // Отображаем диалог редактирования
    EditContactDialog dialog(contactData, this);
    if (dialog.exec() == QDialog::Accepted) {
        // Получаем обновленные данные
        QStringList updatedContactData = dialog.getContact();

        // Проверяем наличие обновленных данных
        if (updatedContactData.size() < 6) {
            QMessageBox::warning(this, "Ошибка", "Недостаточно данных для обновления контакта.");
            return;
        }

        // Обновляем данные в таблице
        table->setItem(row, 0, new QTableWidgetItem(updatedContactData[0])); // Фамилия
        table->setItem(row, 1, new QTableWidgetItem(updatedContactData[1])); // Имя
        table->setItem(row, 2, new QTableWidgetItem(updatedContactData[2])); // Отчество
        table->setItem(row, 3, new QTableWidgetItem(updatedContactData[3])); // Телефоны
        table->setItem(row, 4, new QTableWidgetItem(updatedContactData[4])); // Email
        table->setItem(row, 5, new QTableWidgetItem(updatedContactData[5])); // Дата рождения

        // Обновляем данные в карте контактов
        QString oldKey = lastName + " " + firstName + " " + middleName;
        QString newKey = updatedContactData[0] + " " + updatedContactData[1] + " " + updatedContactData[2];

        if (!contacts.contains(oldKey)) {
            QMessageBox::warning(this, "Ошибка", "Контакт не найден в локальном хранилище.");
            return;
        }

        // Убираем старую запись, если ключ изменился
        Contact contact = contacts[oldKey];
        if (oldKey != newKey) {
            contacts.remove(oldKey);
        }

        // Обновляем контакт
        contact.lastName = updatedContactData[0];
        contact.firstName = updatedContactData[1];
        contact.middleName = updatedContactData[2];
        contact.phoneNumbers = updatedContactData[3].split(", ").toVector();
        contact.email = updatedContactData[4];
        contact.birthDate = updatedContactData[5];
        contacts[newKey] = contact;

        // Обновляем данные в базе данных
        QSqlQuery query;
        query.prepare("UPDATE contacts SET last_name = :last_name, first_name = :first_name, middle_name = :middle_name, "
                      "phone_numbers = :phone_numbers, email = :email, birth_date = :birth_date "
                      "WHERE last_name = :old_last_name AND first_name = :old_first_name AND middle_name = :old_middle_name");
        query.bindValue(":last_name", contact.lastName);
        query.bindValue(":first_name", contact.firstName);
        query.bindValue(":middle_name", contact.middleName);
        query.bindValue(":phone_numbers", QStringList::fromVector(contact.phoneNumbers).join(","));
        query.bindValue(":email", contact.email);
        query.bindValue(":birth_date", contact.birthDate);
        query.bindValue(":old_last_name", lastName);
        query.bindValue(":old_first_name", firstName);
        query.bindValue(":old_middle_name", middleName);

        if (!query.exec()) {
            QMessageBox::warning(this, "Ошибка", "Не удалось обновить контакт в базе данных: " + query.lastError().text());
        } else {
            qDebug() << "Контакт успешно обновлен в базе данных!";
        }

        // Сохраняем изменения в файл
        saveToFile();
    }
}



void PhoneBook::deleteContact() {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для удаления.");
        return;
    }

    // Получаем ключ контакта (Фамилия + Имя + Отчество)
    QString contactKey = table->item(row, 0)->text() + " " +
                         table->item(row, 1)->text() + " " +
                         table->item(row, 2)->text();

    if (!contacts.contains(contactKey)) {
        QMessageBox::warning(this, "Ошибка", "Контакт не найден.");
        return;
    }

    // Удаляем из локального хранилища (файл)
    contacts.remove(contactKey);

    // Удаляем из базы данных
    deleteFromDatabase(contactKey);

    // Удаляем из таблицы
    table->removeRow(row);

    // Сохраняем изменения в файле
    saveToFile();

    QMessageBox::information(this, "Успех", "Контакт успешно удален.");
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



bool PhoneBook::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("contacts.db"); // Название файла базы данных

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных SQLite.");
        return false;
    }

    qDebug() << "Соединение с базой данных SQLite установлено!";
    return true;
}



void PhoneBook::saveToDatabase(const Contact &contact) {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS contacts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "last_name TEXT, first_name TEXT, middle_name TEXT, "
               "phone_numbers TEXT, email TEXT, birth_date TEXT)");

    query.prepare("INSERT INTO contacts (last_name, first_name, middle_name, phone_numbers, email, birth_date) "
                  "VALUES (:last_name, :first_name, :middle_name, :phone_numbers, :email, :birth_date)");
    query.bindValue(":last_name", contact.lastName);
    query.bindValue(":first_name", contact.firstName);
    query.bindValue(":middle_name", contact.middleName);
    query.bindValue(":phone_numbers", QStringList::fromVector(contact.phoneNumbers).join(","));
    query.bindValue(":email", contact.email);
    query.bindValue(":birth_date", contact.birthDate);

    if (!query.exec()) {
        qDebug() << "Ошибка сохранения в базу данных: " << query.lastError().text();
    } else {
        qDebug() << "Контакт успешно сохранен в базу данных!";
    }
}



void PhoneBook::loadFromDatabase() {
    QSqlQuery query("SELECT last_name, first_name, middle_name, phone_numbers, email, birth_date FROM contacts");

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные из базы данных.");
        return;
    }

    contacts.clear();
    table->setRowCount(0);

    while (query.next()) {
        Contact contact;
        contact.lastName = query.value(0).toString();
        contact.firstName = query.value(1).toString();
        contact.middleName = query.value(2).toString();
        contact.phoneNumbers = query.value(3).toString().split(",", Qt::SkipEmptyParts).toVector();
        contact.email = query.value(4).toString();
        contact.birthDate = query.value(5).toString();

        QString key = contact.lastName + " " + contact.firstName + " " + contact.middleName;
        contacts[key] = contact;

        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(contact.lastName));
        table->setItem(row, 1, new QTableWidgetItem(contact.firstName));
        table->setItem(row, 2, new QTableWidgetItem(contact.middleName));
        table->setItem(row, 3, new QTableWidgetItem(QStringList::fromVector(contact.phoneNumbers).join(", "))); // Отображаем номера через запятую
        table->setItem(row, 4, new QTableWidgetItem(contact.email));
        table->setItem(row, 5, new QTableWidgetItem(contact.birthDate));
    }
}



void PhoneBook::deleteFromDatabase(const QString &contactKey) {
    QSqlQuery query;

    // Формируем SQL-запрос для удаления контакта по уникальному ключу
    query.prepare("DELETE FROM contacts WHERE last_name || ' ' || first_name || ' ' || middle_name = :contact_key");
    query.bindValue(":contact_key", contactKey);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка удаления из базы данных: " << query.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить контакт из базы данных.");
    } else {
        qDebug() << "Контакт успешно удален из базы данных!";
    }
}
