#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void load();

private:
    void createMenu();
    void buildCentralWidget();

private slots:
    void updateValues();

private:
    QTextEdit* m_pTE;
    QLineEdit* m_pLE;

};

#endif // MAINWINDOW_H
