#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow(QWidget *parent = 0);
    ~EditorWindow();
};

#endif // EDITORWINDOW_H
