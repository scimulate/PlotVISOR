#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    clicked = false;

    screen = QGuiApplication::primaryScreen();

    red = new QLineSeries();
    green = new QLineSeries();
    blue = new QLineSeries();

    chart = new QChart;
    ui->graphicsView->setChart(chart);
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
    QString text = "(" + QString::number(event->globalX()) + ", " + QString::number(event->globalY()) + ")";
    ui->labelPosition->setText(text);

    QPixmap something = screen->grabWindow(0, event->globalX(), event->globalY(), 1, 1);
    QColor pixelValue = something.toImage().pixel(0,0);
    ui->labelRGB->setPixmap(something);

    if(clicked)
    {
        path.append(QList<int>{event->globalX(), event->globalY()});
        colors.append(pixelValue);
    }
}

void MainWindow::on_pushButton_pressed()
{
    path.clear();
    colors.clear();
    red->clear();
    green->clear();
    blue->clear();

    clicked = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(clicked)
    {
//        ui->sliderUpper->setMaximum(path.length());
//        ui->sliderUpper->setValue(ui->sliderUpper->maximum());

//        ui->sliderLower->setMinimum(0);
//        ui->sliderLower->setMaximum(ui->sliderUpper->value());
//        ui->sliderLower->setValue(ui->sliderLower->minimum());

        //ui->sliderUpper->setMaximum(path.length());
        //ui->sliderLower->setMaximum(std::min(path.length(), ui->sliderUpper->maximum()));

        std::cout << colors.length() << std::endl;
        for(int ct = 0; ct < colors.length(); ct++)
        {
            //std::cout << path.at(ct).at(0) << '\t' << path.at(ct).at(1) << '\t' << colors.at(ct).red() << '\t' << colors.at(ct).green() << '\t' << colors.at(ct).blue() << std::endl;
            red->append(ct, colors.at(ct).red());
            green->append(ct, colors.at(ct).green());
            blue->append(ct, colors.at(ct).blue());
        }
        //ui->labelPixel->setText(QString::number(path.length()));

        red->setColor(Qt::red);
        green->setColor(Qt::green);
        blue->setColor(Qt::blue);

        //QChart *chart = new QChart;
        chart->addSeries(red);
        chart->addSeries(green);
        chart->addSeries(blue);
        chart->legend()->hide();
        //chart->setTitle("Test");
        //chart->createDefaultAxes();
        chart->createDefaultAxes();
        //QChartView *chartview = new QChartView(chart);

        ui->graphicsView->setChart(chart);
        clicked = false;

        lbound = 0;
        ubound = path.length();
        //ui->sliderLower->setMaximum(path.length());
    }
}
