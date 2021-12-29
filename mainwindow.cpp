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

        // Breakdown lineLegend into discrete legend values.
        QStringList text = ui->lineLegend->text().split(",");
        int N = text.at(2).toInt();
        double step = (text.at(1).toDouble() - text.at(0).toDouble())/(N-1);

        QList<double> steps;
        for(int ct = 0; ct < N; ct++)
        {
            steps.push_back(text.at(0).toInt() + step*ct);
            std::cout << steps.at(ct) << ' ';
        }
        std::cout << std::endl;

        int chunk = (high-low)/(N-1);

        int index = 0;
        for(int n = 0; n < N-1; n++)
        {
            current = abs(pixelValue.red()-colors.at(low+n*chunk+chunk/2).red()) + abs(pixelValue.green()-colors.at(low+n*chunk+chunk/2).green()) + abs(pixelValue.blue()-colors.at(low+n*chunk+chunk/2).blue());
            if(current < diff)
            {
                diff = current;
                index = n;
            }
        }
        ui->labelValue->setText(QString::number(steps.at(index)) + "\t" + QString::number(steps.at(index+1)));
        //std::cout << index << '\t' << index+1 << std::endl;

        /*
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
        */



        //        ui->labelValue->setText(QString::number(step));

        //        ui->labelValue->setText(QString::number(steps.at(N)));
        //        //std::cout << std::endl;
        //        QList<int> keys;

        //        int chunk = (ui->spinUBound->value()-ui->spinLBound->value())/(N-1);
        //        double chunk = (high-low)/(N-1);
        //        ui->labelValue->setText(QString::number(chunk));

        //        while(index-low < chunk*ct)
        //        {
        //            ct++;
        //        }
        //std::cout << ct-1 << '\t' << ct << std::endl;

        //std::cout << 1.0/chunk*(index-low) << std::endl;

        //        if(index != high )
        //        {
        //        int something = 1+(index-low)/chunk;
        //        std::cout << index << '\t' << low << '\t' << steps.at(something) << '\t' << steps.at(something+1) << std::endl;
        //        //ui->labelValue->setText(QString::number(steps.at(something-1)) + "\t" + QString::number(steps.at(something)));
        //        }
        //        int ct = 0;
        //        std::cout << index << '\t' << low+ct*chunk << std::endl;
        //        ct++;
        //        std::cout << index << '\t' << low+ct*chunk << std::endl;
        //        while(index < low+ct*chunk)
        //        {
        //            std::cout << index << '\t' << low+ct*chunk << std::endl;
        //            ct++;
        //        }

        //ui->labelValue->setText(QString::number(ct));

        //
        //ui->labelValue->setText(QString::number(index/chunk - low/chunk));

        //        int ct = 0;
        //        while(index > ui->spinLBound->text().toDouble()+chunk*ct)
        //        {
        //            ct++;
        //        }
        //        ui->labelValue->setText(legend.at(ct) + "\t" + legend.at(ct+1));
        //ui->labelValue->setText(QString::number(chunk));

        //double value = ui->lineLegendMin->text().toDouble();
        //value += double(index-low)/double(high-low)*(ui->lineLegendMax->text().toDouble()-ui->lineLegendMin->text().toDouble());

        //ui->labelValue->setText(QString::number(value, 'e', 4));
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
