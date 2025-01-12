#include "EditContactDialog.h"

EditContactDialog::EditContactDialog(const QStringList &contact, QWidget *parent) : QDialog(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    lastNameInput = new QLineEdit(contact[0], this);
    firstNameInput = new QLineEdit(contact[1], this);
    middleNameInput = new QLineEdit(contact[2], this);
    phoneInput = new QLineEdit(contact[3], this);
    emailInput = new QLineEdit(contact[4], this);
    birthDateInput = new QLineEdit(contact[5], this);

    saveButton = new QPushButton("Сохранить", this);
    cancelButton = new QPushButton("Отмена", this);

    connect(saveButton, &QPushButton::clicked, this, [this]() {
        if (validateInput()) accept();
    });

    connect(cancelButton, &QPushButton::clicked, this, &EditContactDialog::reject);

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
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
}

QStringList EditContactDialog::getContact() const {
    return {lastNameInput->text(), firstNameInput->text(), middleNameInput->text(),
            phoneInput->text(), emailInput->text(), birthDateInput->text()};
}

bool EditContactDialog::validateInput() {
    if (lastNameInput->text().isEmpty() || firstNameInput->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Фамилия и имя не могут быть пустыми.");
        return false;
    }
    return true;
}
