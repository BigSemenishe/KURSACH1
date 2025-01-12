#include "DeleteContactDialog.h"

DeleteContactDialog::DeleteContactDialog(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *warningLabel = new QLabel("Вы уверены, что хотите удалить выбранный контакт?", this);
    QPushButton *deleteButton = new QPushButton("Удалить", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);

    connect(deleteButton, &QPushButton::clicked, this, &DeleteContactDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &DeleteContactDialog::reject);

    mainLayout->addWidget(warningLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
}
