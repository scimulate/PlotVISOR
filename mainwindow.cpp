#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QString text = "Global Position (x,y) = (";
    text += QString::number(event->globalX());
    text += ", ";
    text += QString::number(event->globalY());
    text += ")";
    ui->labelPosition->setText(text);
    path.append(QList<int>{event->globalX(), event->globalY()});

    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap something = screen->grabWindow(0,  event->globalX(), event->globalY(), 1, 1);

    QColor pixelValue = something.toImage().pixel(0,0);

    text.clear();
    text = "Pixel Color (r, g, b) = (";
    text += QString::number(pixelValue.red());
    text += ", ";
    text += QString::number(pixelValue.green());
    text += ", ";
    text += QString::number(pixelValue.blue());
    text += ")";
    ui->labelRGB->setText(text);
    ui->labelPixel->setPixmap(something);
    //std::cout << pixelValue.red() << '\t' << pixelValue.green() << '\t' << pixelValue.blue() << std::endl;;

    //QColor color = something.toImage().color();
    //std::cout << something.toImage().pixel();
    //QPixmap something = QScreen::grabWindow(this->winId(), event->globalX(), event->globalY(), 1, 1);
}

void MainWindow::on_pushButton_pressed()
{
    path.clear();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << path.length() << std::endl;
    ui->labelPixel->setText(QString::number(path.length()));
}
