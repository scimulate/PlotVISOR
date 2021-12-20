#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QList>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QPixmap>
#include <QRgb>
#include <QScreen>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    //void on_pushButton_pressed();
    //void on_pushButton_released();
    //void on_pushButton_clicked();

    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
    QList<QList<int>> path;
};
#endif // MAINWINDOW_H
