#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class AddContactDialog : public QDialog {
    Q_OBJECT

public:
    AddContactDialog(QWidget *parent = nullptr);
    QStringList getContact() const;

private:
    QLineEdit *lastNameInput;
    QLineEdit *firstNameInput;
    QLineEdit *middleNameInput;
    QLineEdit *phoneInput;
    QLineEdit *emailInput;
    QLineEdit *birthDateInput;
    QPushButton *addButton;
    QPushButton *cancelButton;

    bool validateInput();
};

#endif // ADDCONTACTDIALOG_H
