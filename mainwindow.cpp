#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    /*
    QLineSeries *series = new QLineSeries();
    series->append(0.0, 0.6);
    series->append(1.0, 1.25);
    series->append(2.5, 1.25);
    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Test");
    chart->createDefaultAxes();
    QChartView *chartview = new QChartView(chart);

    ui->graphicsView->setChart(chart);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QString text = "(";
    text += QString::number(event->globalX());
    text += ", ";
    text += QString::number(event->globalY());
    text += ")";
    ui->labelPosition->setText(text);
    path.append(QList<int>{event->globalX(), event->globalY()});

    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap something = screen->grabWindow(0,  event->globalX(), event->globalY(), 1, 1);

    QColor pixelValue = something.toImage().pixel(0,0);
    colors.append(pixelValue);

    text.clear();
    text = "Pixel Color (r, g, b) = (";
    text += QString::number(pixelValue.red());
    text += ", ";
    text += QString::number(pixelValue.green());
    text += ", ";
    text += QString::number(pixelValue.blue());
    text += ")";
    //ui->labelRGB->setText(text);
    ui->labelRGB->setPixmap(something);
    //std::cout << pixelValue.red() << '\t' << pixelValue.green() << '\t' << pixelValue.blue() << std::endl;;
}

void MainWindow::on_pushButton_pressed()
{
    path.clear();
    colors.clear();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    ui->sliderUpper->setMaximum(path.length());
    ui->sliderLower->setMaximum(std::min(path.length(), ui->sliderUpper->maximum()));

    QLineSeries *red = new QLineSeries();
    QLineSeries *green = new QLineSeries();
    QLineSeries *blue = new QLineSeries();

    std::cout << colors.length() << std::endl;
    for(int ct = 0; ct < colors.length(); ct++)
    {
        std::cout << path.at(ct).at(0) << '\t' << path.at(ct).at(1) << '\t' << colors.at(ct).red() << '\t' << colors.at(ct).green() << '\t' << colors.at(ct).blue() << std::endl;
        //series->append(path.at(ct).at(1), colors.at(ct).red());
        red->append(ct, colors.at(ct).red());
        green->append(ct, colors.at(ct).green());
        blue->append(ct, colors.at(ct).blue());
    }
    //ui->labelPixel->setText(QString::number(path.length()));

    red->setColor(Qt::red);
    green->setColor(Qt::green);
    blue->setColor(Qt::blue);

    QChart *chart = new QChart;
    chart->addSeries(red);
    chart->addSeries(green);
    chart->addSeries(blue);
    chart->legend()->hide();
    //chart->setTitle("Test");
    //chart->createDefaultAxes();
    chart->createDefaultAxes();

    //QChartView *chartview = new QChartView(chart);

    ui->graphicsView->setChart(chart);
}

void MainWindow::on_sliderLower_valueChanged(int value)
{
    //ui->labelTemp->setText(QString::number(ui->sliderLower->maximum() - ui->sliderLower->value()));
    ui->sliderUpper->setMinimum(ui->sliderLower->value());

}

void MainWindow::on_sliderUpper_valueChanged(int value)
{
    //ui->labelTemp_2->setText(QString::number(ui->sliderUpper->value()));
    ui->sliderLower->setMaximum(ui->sliderUpper->value());
}
