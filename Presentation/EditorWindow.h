#pragma once

#include <QMainWindow>

#include "TextEditWithLineNumbers.h"
#include <QTreeWidget>

#include "../Infrastructure/WorkspaceFilesManager.h"

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

    void createNewTabWithContent(QString content);

    void updateProfileBar();

public slots:
    void closeEditorTab(int tabIndex);
    void compileCurrentProject();

    void projectsListLoaded();
    void projectCompilationResultLoaded();


protected:
    QTabWidget *tabWidget;
    QTreeWidget *filesTreeWidget;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QMenuBar *mainMenuBar;

    QAction *profileInfoAction;
};
