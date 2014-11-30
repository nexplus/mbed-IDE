#include "EditorWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QLabel>
#include "LoginWindow.h"

EditorWindow::EditorWindow(QWidget *parent)  : QMainWindow(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeEditorTab(int)));

    filesTreeWidget = new QTreeWidget;
    filesTreeWidget->setFocusPolicy(Qt::NoFocus);
    filesTreeWidget->setHeaderLabel(tr("My projects"));

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(filesTreeWidget, 1);
    hboxLayout->addWidget(tabWidget, 3);

    toolBar = new QToolBar;
    toolBar->addAction(QIcon(":/Icons/new.png"), tr("New"));
    toolBar->addAction(QIcon(":/Icons/save.png"), tr("Save"));
    toolBar->addAction(QIcon(":/Icons/saveas.png"), tr("Save all"));
    toolBar->addSeparator();
    QAction *compileAction = toolBar->addAction(QIcon(":/Icons/build.png"), tr("Compile"));
    connect(compileAction, SIGNAL(triggered()), this, SLOT(compileCurrentProject()));
    toolBar->addAction(QIcon(":/Icons/player_start.png"), tr("Compile + Flash"));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/Icons/upload.png"), tr("Commit"));
    toolBar->addAction(QIcon(":/Icons/bookmark.png"), tr("History"));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/Icons/undo.png"), tr("Undo"));
    toolBar->addAction(QIcon(":/Icons/forward.png"), tr("Redo"));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/Icons/print.png"), tr("Print"));
    toolBar->addSeparator();
    //toolBar->addAction(tr("Format code"));
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    toolBar->addWidget(spacerWidget);
    toolBar->addSeparator();
    QLabel *imageLabel  =new QLabel;
    imageLabel->setPixmap(QPixmap(":/Icons/avatar_placeholder.png"));
    toolBar->addWidget(imageLabel);
   profileInfoAction =  toolBar->addAction(tr("nexplus\n                         "));

    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setFixedHeight(55);

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(toolBar, 0);
    vboxLayout->addLayout(hboxLayout, 1);

    QWidget *layoutWidget = new QWidget;
    layoutWidget->setLayout(vboxLayout);
    setCentralWidget(layoutWidget);

    setWindowTitle(tr("MBed IDE"));

    createNewTabWithContent("qqqq");
    createNewTabWithContent("www");

    statusBar = new QStatusBar();
    setStatusBar(statusBar);

    /*mainMenuBar = new QMenuBar;
    QMenu *fileMenu = new QMenu(tr("File"));
    fileMenu->addAction(tr("New"));
    mainMenuBar->addMenu(fileMenu);
    //mainMenuBar->addAction(tr("Edit"));
    //mainMenuBar->addAction(tr("Project"));
   // mainMenuBar->addMenu(tr("My profile"));
    //mainMenuBar->setFixedHeight(20);
    //setMenuBar(mainMenuBar);
    //mainMenuBar->show();
    vboxLayout->addWidget(mainMenuBar);*/

    statusBar->showMessage(tr("Last saved 2 minutes ago")); //DEBUG

    connect(WorkspaceFilesManager::sharedObject(), SIGNAL(projectsListLoaded()), this, SLOT(projectsListLoaded()));
    WorkspaceFilesManager::sharedObject()->loadProjectsList();

    connect(WorkspaceFilesManager::sharedObject(), SIGNAL(projectCompiled()), this, SLOT(projectCompilationResultLoaded()));

    resize(1050, 700);
}

EditorWindow::~EditorWindow()
{

}

void EditorWindow::compileCurrentProject()
{
    if (filesTreeWidget->currentItem())
    {
        QString activeProjectName = filesTreeWidget->currentItem()->text(0);
        qDebug() << activeProjectName;
        WorkspaceFilesManager::sharedObject()->compileProject(activeProjectName);
        //TODO: lock buttons
    }
}

void EditorWindow::projectCompilationResultLoaded()
{
    //TODO ...
}

void EditorWindow::projectsListLoaded()
{
    filesTreeWidget->clear();
    foreach (QString projectName, WorkspaceFilesManager::sharedObject()->getProjectsList())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(projectName));
        filesTreeWidget->addTopLevelItem(item);
    }
    updateProfileBar();
}

void EditorWindow::updateProfileBar()
{
    int projectsCount = WorkspaceFilesManager::sharedObject()->getProjectsList().count();
    profileInfoAction->setText(tr("%1\n%2 project%3, %4").arg("nexplus").arg(projectsCount).arg((projectsCount > 1) ? tr("s") : tr("")).arg(tr("mbed LPC1768")));
}

void EditorWindow::createNewTabWithContent(QString content)
{
   TextEditWithLineNumbers * textWidget = new TextEditWithLineNumbers;
   textWidget->setText(content);
    tabWidget->addTab(textWidget, tr("хаха.cpp"));
    textWidget->setFocus();
}

void EditorWindow::closeEditorTab(int tabIndex)
{
    QObject *tabPane = tabWidget->widget(tabIndex);
    tabWidget->removeTab(tabIndex);
    tabPane->deleteLater();
}
