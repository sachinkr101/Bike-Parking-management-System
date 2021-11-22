#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mydb.h"
#include "book.h"
#include "cancel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Show();


private slots:
    void on_btnCancel_clicked();

    void on_btnBook_clicked();

private:
    Ui::MainWindow *ui;
    void updateUI();

    Book *ptrBook;
    Cancel *ptrCancel;
};

#endif // MAINWINDOW_H
