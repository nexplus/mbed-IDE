 #include "LoginWindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "EditorWindow.h"
#include "Infrastructure/AuthenticationManager.h"

LoginWindow::LoginWindow(QWidget *parent)  : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    loginButton = new QPushButton(tr("Enter"));
    connect(loginButton, SIGNAL(clicked()), this, SLOT(tryToLogin()));
    loginButton->setMinimumSize(240, 50);
    loginButton->setFocusPolicy(Qt::StrongFocus);
    loginButton->setStyleSheet(tr("color:black;"));


    loginLineEdit = new QLineEdit;
    loginLineEdit->setPlaceholderText(tr("login"));
    loginLineEdit->setAlignment(Qt::AlignCenter);
    loginLineEdit->setMinimumSize(240, 29);

    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setPlaceholderText(tr("password"));
    passwordLineEdit->setAlignment(Qt::AlignCenter);
    passwordLineEdit->setMinimumSize(240, 29);
    passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    //DEBUG
    loginLineEdit->setText("");
    passwordLineEdit->setText("");

    saveFormCheckBox = new QCheckBox(tr("Save login and password"));


    QLabel *label = new QLabel(tr("Please, enter login and password."));
    QFont font = label->font();
    //font.setItalic(true);
    label->setFont(font);

    layout->addWidget(label, 1, Qt::AlignCenter);
    layout->addWidget(loginLineEdit, 1, Qt::AlignCenter);
    layout->addWidget(passwordLineEdit, 1, Qt::AlignCenter);
    layout->addWidget(saveFormCheckBox, 1, Qt::AlignCenter);
    layout->addWidget(loginButton, 1, Qt::AlignCenter);

    loginLineEdit->setFocus();

    setLayout(layout);
    setWindowTitle(tr("MBed authorization"));

    connect(AuthenticationManager::sharedObject(), SIGNAL(authenticationResultReceived(QString)), this, SLOT(authenticationResultReceived(QString)));

    resize(350, 250);
}

void LoginWindow::tryToLogin()
{
    if ((loginLineEdit->text().length() == 0) || (passwordLineEdit->text().length() == 0))
        QMessageBox::critical(this, tr("Error"), tr("Error: login and password can't be empty!"));
    else
    {
        loginButton->setEnabled(false);
        loginLineEdit->setEnabled(false);
        passwordLineEdit->setEnabled(false);
        saveFormCheckBox->setEnabled(false);

        AuthenticationManager::sharedObject()->tryToAuthenticate(loginLineEdit->text(), passwordLineEdit->text());
    }
}

void LoginWindow::authenticationResultReceived(QString data)
{
    loginButton->setEnabled(true);
    loginLineEdit->setEnabled(true);
    passwordLineEdit->setEnabled(true);
    saveFormCheckBox->setEnabled(true);

    if (data.isEmpty())
    {
        EditorWindow *editorWindow = new EditorWindow;
        editorWindow->show();

        close();
    }
    else
        QMessageBox::critical(this, tr("Error"), tr("Error: ") + data);
}
