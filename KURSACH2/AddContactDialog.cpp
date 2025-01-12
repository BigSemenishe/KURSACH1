#include "AddContactDialog.h"
#include "QRegularExpression"
#include "QDate"

AddContactDialog::AddContactDialog(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    lastNameInput = new QLineEdit(this);
    firstNameInput = new QLineEdit(this);
    middleNameInput = new QLineEdit(this);
    phoneInput = new QLineEdit(this);
    emailInput = new QLineEdit(this);
    birthDateInput = new QLineEdit(this);

    lastNameInput->setPlaceholderText("Фамилия");
    firstNameInput->setPlaceholderText("Имя");
    middleNameInput->setPlaceholderText("Отчество");
    phoneInput->setPlaceholderText("Телефон");
    emailInput->setPlaceholderText("E-mail");
    birthDateInput->setPlaceholderText("Дата рождения (DD-MM-YYYY)");

    addButton = new QPushButton("Добавить", this);
    cancelButton = new QPushButton("Отмена", this);

    connect(addButton, &QPushButton::clicked, this, [this]() {
        if (validateInput()) accept();
    });

    connect(cancelButton, &QPushButton::clicked, this, &AddContactDialog::reject);

    mainLayout->addWidget(new QLabel("Фамилия:", this));
    mainLayout->addWidget(lastNameInput);
    mainLayout->addWidget(new QLabel("Имя:", this));
    mainLayout->addWidget(firstNameInput);
    mainLayout->addWidget(new QLabel("Отчество:", this));
    mainLayout->addWidget(middleNameInput);
    mainLayout->addWidget(new QLabel("Телефон:", this));
    mainLayout->addWidget(phoneInput);
    mainLayout->addWidget(new QLabel("E-mail:", this));
    mainLayout->addWidget(emailInput);
    mainLayout->addWidget(new QLabel("Дата рождения:", this));
    mainLayout->addWidget(birthDateInput);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
}

QStringList AddContactDialog::getContact() const {
    return {lastNameInput->text(), firstNameInput->text(), middleNameInput->text(),
            phoneInput->text(), emailInput->text(), birthDateInput->text()};
}

// Проверка корректности ввода данных
bool AddContactDialog::validateInput() {
    // Регулярное выражение для проверки фамилии, имени, отчества
    QRegularExpression nameRegex("^[A-Z]+([ -]?[A-Za-z0-9]+)*$");
    if (!nameRegex.match(lastNameInput->text().trimmed()).hasMatch() ||
        !nameRegex.match(firstNameInput->text().trimmed()).hasMatch() ||
        !nameRegex.match(middleNameInput->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Фамилия, имя и отчество должны начинаться с буквы, "
                                             "могут содержать дефис, пробел и цифры, но не могут заканчиваться или начинаться на дефис.");
        return false;
    }

    // Регулярное выражение для проверки телефона
    QRegularExpression phoneRegex("^\\+7\\d{10}$");
    if (!phoneRegex.match(phoneInput->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Телефон должен быть в формате +7XXXXXXXXXX, где X — цифры.");
        return false;
    }

    // Получение введенного e-mail из соответствующего текстового поля
    QString email = emailInput->text().trimmed(); // Удаляем лишние пробелы

    // Регулярное выражение для проверки e-mail
    QRegularExpression emailRegex("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "E-mail должен быть в формате example@domain.com.");
        return false;
    }

    // Проверка наличия имени пользователя в e-mail
    QString emailUserName = email.split('@').first(); // Получаем имя пользователя из e-mail (до @)
    if (!emailUserName.contains(firstNameInput->text().trimmed(), Qt::CaseInsensitive)) {
        QMessageBox::warning(this, "Ошибка", "Имя пользователя в e-mail должно содержать имя контакта.");
        return false;
    }

    // Проверка даты рождения
    QDate birthDate = QDate::fromString(birthDateInput->text().trimmed(), "dd-MM-yyyy");
    if (!birthDate.isValid() || birthDate >= QDate::currentDate()) {
        QMessageBox::warning(this, "Ошибка", "Дата рождения должна быть корректной и меньше текущей даты.");
        return false;
    }

    return true;
}
