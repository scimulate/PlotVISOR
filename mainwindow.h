/*
PlotVISOR is a visual assistant for interpreting colored contour plots.
Copyright (C) 2022 Scimulate LLC (Samuel Jacobs)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QList>
#include <QMainWindow>
//#include <QMenuBar>
#include <QMouseEvent>
#include <QPoint>
#include <QPixmap>
#include <QRgb>
#include <QScreen>

#include <QtCharts>

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
    //void Calibrate();
    void on_pushButton_pressed();
    void on_spinLBound_valueChanged(int arg1);
    void on_spinUBound_valueChanged(int arg1);
    void About();

    //void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<QColor> colors;
    QList<QList<int>> path;
    bool mouseClicked;
    void plot();
};
#endif // MAINWINDOW_H
