#include "SearchContactDialog.h"

SearchContactDialog::SearchContactDialog(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("Введите текст для поиска");

    searchButton = new QPushButton("Поиск", this);
    cancelButton = new QPushButton("Отмена", this);

    connect(searchButton, &QPushButton::clicked, this, &SearchContactDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &SearchContactDialog::reject);

    mainLayout->addWidget(new QLabel("Поиск по контактам:", this));
    mainLayout->addWidget(searchInput);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
}

QString SearchContactDialog::getSearchTerm() const {
    return searchInput->text().trimmed();
}
