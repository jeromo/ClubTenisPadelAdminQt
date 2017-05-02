#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>


namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private:
    void showError(const QSqlError &err);
    QSqlRelationalTableModel *model;
    int playerIdx, genreIdx;
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H


