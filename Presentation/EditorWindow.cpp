#include "EditorWindow.h"
#include <QHBoxLayout>

EditorWindow::EditorWindow(QWidget *parent)  : QMainWindow(parent)
{
    tabWidget = new QTabWidget;
    filesTreeView = new QTreeView;
    filesTreeView->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(filesTreeView, 1);
    hboxLayout->addWidget(tabWidget, 3);

    QWidget *layoutWidget = new QWidget;
    layoutWidget->setLayout(hboxLayout);
    setCentralWidget(layoutWidget);

    setWindowTitle(tr("MBed IDE"));

    createNewTabWithContent("qqqq");
    createNewTabWithContent("www");
}

EditorWindow::~EditorWindow()
{

}

void EditorWindow::createNewTabWithContent(QString content)
{
   TextEditWithLineNumbers * textWidget = new TextEditWithLineNumbers;
   textWidget->setText(content);
    tabWidget->addTab(textWidget, tr("хаха.cpp"));
}
