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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    mouseClicked = false;
    ui->statusbar->showMessage("PlotVISOR by Scimulate LLC", 5000);

    QMenu *fileMenu = ui->menubar->addMenu(tr("&File"));
    QMenu *helpMenu = ui->menubar->addMenu(tr("&Help"));

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon,
                                           tr("E&xit"),
                                           this,
                                           &QWidget::close);
    exitAct->setStatusTip(tr("Close Application"));

    QAction *aboutAct = helpMenu->addAction(tr("&About PlotVISOR..."), this, &MainWindow::About);
    aboutAct->setStatusTip(tr("PlotVISOR is a visual assistant for interpreting contour plots..."));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt.."), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("PlotVISOR was developed using Qt technologies..."));

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
    else if(colors.length() > 0)
    {
        int low = std::min(ui->spinLBound->value(), ui->spinUBound->value());
        int high = std::max(ui->spinLBound->value(), ui->spinUBound->value());
        int current;
        int diff = 255;

        // Breakdown lineLegend into discrete legend values.
        QStringList text = ui->lineLegend->text().split(",");

        int N = text.length();

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

        if(diff < 3.0*256.0/(N-1))
        {
            ui->pushButton_2->setText(text.at(index) + " ??? " + text.at(index+1));
        }
        else
        {
            ui->pushButton_2->setText("???");
        }
    }
}

void MainWindow::on_pushButton_pressed()
{
    path.clear();
    colors.clear();
    ui->spinLBound->setValue(0);
    ui->spinLBound->setMaximum(0);
    ui->spinUBound->setValue(0);
    ui->spinUBound->setMinimum(0);
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
        red->append(ct, colors.at(ct).red());
        green->append(ct, colors.at(ct).green());
        blue->append(ct, colors.at(ct).blue());
    }

    red->setPen(Qt::DashLine);
    red->setColor(Qt::red);
    red->setName("Red (---)");

    green->setColor(Qt::green);
    green->setName("Green (???)");

    blue->setPen(Qt::DotLine);
    blue->setColor(Qt::blue);
    blue->setName("Blue (??????)");

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
    if(colors.length() > 0)
    {
        plot();
    }
}

void MainWindow::on_spinUBound_valueChanged(int arg1)
{
    if(colors.length() > 0)
    {
        plot();
    }
}

void MainWindow::About()
{
    QMessageBox::about(this, tr("About Application"),
                       tr("<b>PlotVISOR</b> is a visual assistant for contour plots.<br><br>"
                          "By following the instructions (1) to (4) in the program window, users can map the legend of any contour plot and use it to identify values otherwise difficult to interpret.<br><br>"
                          "If \"???\" is displayed instead of a valid result, disable lighting enhancements (within your host software) and/or remap the calibration curve. PlotVISOR has been configured to accommodate mild lighting variation from rendering, but this may affect results by ??1 legend increment.<br><br>"
                          "Please visit our <a href=\"https://www.scimulate.com\">website</a> and follow us on <a href=\"https://www.linkedin.com/company/scimulate-llc\">LinkedIn</a>!<br><br>"
                          "PlotVISOR is made available to you under the terms of the <a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">GPLv3</a>. You are not granted any trademark rights or licenses to the trademarks of Scimulate LLC.<br><br>"));
}
