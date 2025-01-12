#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include "QFile"
#include "QTextStream"
#include <QRegularExpression>
#include <QStringList>
#include "AddContactDialog.h"
#include "EditContactDialog.h"
#include "DeleteContactDialog.h"
#include "SearchContactDialog.h"

struct Contact {
    QString lastName;
    QString firstName;
    QString middleName;
    QString email;
    QString birthDate;
    QVector<QString> phoneNumbers; // Список номеров телефона (до 100 номеров)
};


class PhoneBook : public QMainWindow {
    Q_OBJECT

public:
    PhoneBook(QWidget *parent = nullptr);
    ~PhoneBook();

private slots:
    void addContact();
    void editContact();
    void deleteContact();
    void searchContact();
    void loadFromFile();
    void saveToFile();
    void addPhoneNumber();

private:
    QTableWidget *table;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *searchButton;
    QPushButton *loadButton;
    QPushButton *addPhoneNumberButton;

    QMap<QString, Contact> contacts;  // Контакты хранятся в QMap

    void setupUI();
};

#endif // PHONEBOOK_H
