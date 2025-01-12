#ifndef EDITCONTACTDIALOG_H
#define EDITCONTACTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class EditContactDialog : public QDialog {
    Q_OBJECT

public:
    EditContactDialog(const QStringList &contact, QWidget *parent = nullptr);
    QStringList getContact() const;

private:
    QLineEdit *lastNameInput;
    QLineEdit *firstNameInput;
    QLineEdit *middleNameInput;
    QLineEdit *phoneInput;
    QLineEdit *emailInput;
    QLineEdit *birthDateInput;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    bool validateInput();
};

#endif // EDITCONTACTDIALOG_H
