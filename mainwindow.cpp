#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    mouseClicked = false;
    ui->statusbar->showMessage("PlotVISOR by Scimulate LLC", 5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QString text = "(" + QString::number(event->globalX()) + ", "
                       + QString::number(event->globalY()) + ")";
    ui->labelPosition->setText(text);

    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap something = screen->grabWindow(0, event->globalX(), event->globalY(), 1, 1);
    QColor pixelValue = something.toImage().pixel(0,0);
    ui->labelRGB->setPixmap(something);

    if(mouseClicked)
    {
        path.append(QList<int>{event->globalX(), event->globalY()});
        colors.append(pixelValue);
    }
    else
    {
        int low = std::min(ui->spinLBound->value(), ui->spinUBound->value());
        int high = std::max(ui->spinLBound->value(), ui->spinUBound->value());

        int current;
        int diff = 255;
        int index = high;

        for(int ct = low; ct < high; ct++)
        {
            current = abs(pixelValue.red()-colors.at(ct).red()) + abs(pixelValue.green()-colors.at(ct).green()) + abs(pixelValue.blue()-colors.at(ct).blue());
            if(current < diff)
            {
                diff = current;
                index = ct;
            }
        }

        double value = ui->lineLegendMin->text().toDouble();
        value += double(index-low)/double(high-low)*(ui->lineLegendMax->text().toDouble()-ui->lineLegendMin->text().toDouble());

        ui->labelValue->setText(QString::number(value, 'e', 4));
    }
}

void MainWindow::on_pushButton_pressed()
{
    path.clear();
    colors.clear();
    ui->spinLBound->setValue(0);
    ui->spinLBound->setMaximum(0);
    ui->spinUBound->setValue(0);
    ui->spinUBound->setMaximum(0);
    mouseClicked = true;
}

void MainWindow::plot()
{
    QChart *chart = new QChart();
    QLineSeries *red = new QLineSeries();
    QLineSeries *green = new QLineSeries();
    QLineSeries *blue = new QLineSeries();

    int low = std::min(ui->spinLBound->value(), ui->spinUBound->value());
    int high = std::max(ui->spinLBound->value(), ui->spinUBound->value());

    for(int ct = low; ct < high; ct++)
    {
        //std::cout << path.at(ct).at(0) << '\t' << path.at(ct).at(1) << '\t' << colors.at(ct).red() << '\t' << colors.at(ct).green() << '\t' << colors.at(ct).blue() << std::endl;
        //red->append(path.at(ct).at(ui->radioVert->isChecked()), colors.at(ct).red());
        //green->append(path.at(ct).at(ui->radioVert->isChecked()), colors.at(ct).green());
        //blue->append(path.at(ct).at(ui->radioVert->isChecked()), colors.at(ct).blue());
        red->append(ct, colors.at(ct).red());
        green->append(ct, colors.at(ct).green());
        blue->append(ct, colors.at(ct).blue());
    }

    red->setPen(Qt::DashLine);
    red->setColor(Qt::red);
    red->setName("Red (---)");

    green->setColor(Qt::green);
    green->setName("Green (—)");

    blue->setPen(Qt::DotLine);
    blue->setColor(Qt::blue);
    blue->setName("Blue (···)");

    chart->addSeries(red);
    chart->addSeries(green);
    chart->addSeries(blue);
    chart->createDefaultAxes();
    ui->graphicsView->setChart(chart);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouseClicked)
    {
        ui->spinLBound->setMaximum(colors.length());
        ui->spinUBound->setMaximum(colors.length());
        ui->spinUBound->setValue(ui->spinUBound->maximum());
        plot();
        mouseClicked = false;
    }
}
void MainWindow::on_spinLBound_valueChanged(int arg1)
{
    plot();
}

void MainWindow::on_spinUBound_valueChanged(int arg1)
{
    plot();
}
