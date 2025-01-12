#ifndef DELETECONTACTDIALOG_H
#define DELETECONTACTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class DeleteContactDialog : public QDialog {
    Q_OBJECT

public:
    DeleteContactDialog(QWidget *parent = nullptr);
};

#endif // DELETECONTACTDIALOG_H
