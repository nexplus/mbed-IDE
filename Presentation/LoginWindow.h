#pragma once

#include <QDialog>

#include "TextEditWithLineNumbers.h"
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

#include "../Infrastructure/WorkspaceFilesManager.h"

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = 0);

public slots:
    void tryToLogin();
    void authenticationResultReceived(QString data);

protected:
    QPushButton *loginButton;
    QLineEdit *loginLineEdit, *passwordLineEdit;
    QCheckBox *saveFormCheckBox;
};
