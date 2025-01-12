#ifndef SEARCHCONTACTDIALOG_H
#define SEARCHCONTACTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class SearchContactDialog : public QDialog {
    Q_OBJECT

public:
    SearchContactDialog(QWidget *parent = nullptr);
    QString getSearchTerm() const;

private:
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QPushButton *cancelButton;
};

#endif // SEARCHCONTACTDIALOG_H
