#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

#include "TextEditWithLineNumbers.h"
#include <QTreeView>

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

    void createNewTabWithContent(QString content);

protected:
    QTabWidget *tabWidget;
    QTreeView *filesTreeView;
};

#endif // EDITORWINDOW_H
