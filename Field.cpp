//
// Created by song on 7/3/16.
//

#include <QtGui/QtGui>
#include "Field.h"

Field::Field(QWidget *parent) {
    col = 120;
    row = 80;
    ccol = 40;
    crow = 40;
    alpha = 2 / (1 + qSin(3.1415 / (col * row - 1)));
    point = new double *[row];

    for (int i = 0; i < row; ++i) {
        point[i] = new double[col];
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            point[i][j] = 0;
        }
    }

    for (int i = 20; i < 60; ++i) {
        for (int j = 40; j < 80; ++j) {
            point[i][j] = 100;
        }
    }


    iterate(1);


    chart = new QChart();


    QSplineSeries *series1 = new QSplineSeries();
    QSplineSeries *series = new QSplineSeries();
    QSplineSeries *series2 = new QSplineSeries();
    QSplineSeries *series3 = new QSplineSeries();

    QLineSeries *seriesRect = new QLineSeries();
    QList <QPointF> listR;
    listR << QPointF(40, 20) << QPointF(40, 60) << QPointF(80, 60) << QPointF(80, 20) << QPointF(40, 20);
    seriesRect->append(listR);
    chart->addSeries(seriesRect);


    plotField(35, 30);
//    plotElec(20,20,1);

    chart->legend()->hide();

    chart->createDefaultAxes();
    chart->setTitle(QString("Demo"));

    chart->axisY()->setRange(0, 80);
    chart->axisX()->setRange(0, 120);

    QChartView *chartView = new QChartView(chart);

    chartView->setRenderHints(QPainter::Antialiasing);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(chartView);
    resize(800, 600);


    print();

}

Field::~Field() {
    for (int j = 0; j < row; ++j) {
        delete[] point[j];
    }
    delete[] point;

}

void Field::print() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << std::setw(8) << std::setprecision(3) << point[i][j];
        }
        std::cout << std::endl;
    }
}

void Field::iterate(double threshold) {

    double sum = 0;
    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j < col - 1; ++j) {
            double tmp = 0;
            tmp = (point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4;
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }

    for (int i = 60; i < 79; ++i) {
        for (int j = 1; j < col - 1; ++j) {
            double tmp = 0;
            tmp = (point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4;
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }

    for (int i = 20; i < 60; ++i) {
        for (int j = 1; j < 40; ++j) {
            double tmp = 0;
            tmp = (point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4;
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }


    for (int i = 20; i < 60; ++i) {
        for (int j = 80; j < 119; ++j) {
            double tmp = 0;
            tmp = (point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4;
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }


    if (sum < threshold) {
        return;
    }
    iterate(threshold);

}

void Field::iterateI(double threshold) {
    double sum = 0;
    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j < col - 1; ++j) {
            double tmp = 0;
            tmp = point[i][j]
                  + alpha * ((point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4 - point[i][j]);
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }


    for (int i = 60; i < 79; ++i) {
        for (int j = 1; j < col - 1; ++j) {
            double tmp = 0;
            tmp = point[i][j]
                  + alpha * ((point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4 - point[i][j]);
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }

    for (int i = 20; i < 60; ++i) {
        for (int j = 1; j < 40; ++j) {
            double tmp = 0;
            tmp = point[i][j]
                  + alpha * ((point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4 - point[i][j]);
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }

    for (int i = 20; i < 60; ++i) {
        for (int j = 80; j < 119; ++j) {
            double tmp = 0;
            tmp = point[i][j]
                  + alpha * ((point[i - 1][j] + point[i + 1][j] + point[i][j + 1] + point[i][j - 1]) / 4 - point[i][j]);
            sum += std::abs(point[i][j] - tmp);
            point[i][j] = tmp;
        }
    }


    if (sum < threshold) {
        return;
    }
    iterateI(threshold);
}

QList <QPointF> Field::getLine(int row, int col) {

    QList <QPointF> list;
    double origin = point[row][col];
    qDebug() << origin;
    for (int i = 0; i < this->col; ++i) {
        for (int j = 0; j < this->row - 1; ++j) {

            if ((point[j][i] < origin && point[j + 1][i] > origin)
                || (point[j][i] > origin && point[j + 1][i] < origin)) {

                if (std::abs(point[j][i] - origin) < std::abs(point[j + 1][i] - origin)) {
                    QPointF pointF(i, this->row - j);
                    list << pointF;
                } else {
                    QPointF pointF(i, this->row - 1 - j);
                    list << pointF;
                }
                break;
            }


        }
    }
    return list;

}

Vector4d Field::solveLine(QList <QPointF> list) {
    MatrixXd m(4, 4);
    int size = list.size();
    long double contentx[7] = {0};
    long double contenty[4] = {0};

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < size; ++j) {
            contentx[i] += qPow(list.at(j).x(), i);
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < size; ++j) {
            contenty[i] += qPow(list.at(j).x(), i) * list.at(j).y();
        }
    }

    for (int k = 0; k < 7; ++k) {
        std::cout << contentx[k] << " ";
    }
    std::cout << std::endl;

    for (int k = 0; k < 4; ++k) {
        std::cout << contenty[k] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m(3 - i, 3 - j) = contentx[i + j];
        }
    }

    Vector4d v(contenty[3], contenty[2], contenty[1], contenty[0]);

    Vector4d solve = m.fullPivLu().solve(v);


    return solve;
}

void Field::getFieldLine(int row, int col, int id) {
    if (row >= this->row || col >= this->col || row <= 0 || col <= 0) {
        return;
    }
    double origin = point[row][col];

    if (id == 1) {
        fieldList1 << QPointF(col, this->row - row);
    }
    if (id == 2) {
        fieldList2 << QPointF(col, this->row - row);
    }
    if (id == 3) {
        fieldList3 << QPointF(col, this->row - row);
    }
    if (id == 4) {
        fieldList4 << QPointF(col, this->row - row);
    }
    if (id == 5) {
        fieldList5 << QPointF(col, this->row - row);
    }
    if (id == 6) {
        fieldList6 << QPointF(col, this->row - row);
    }


    qDebug() << QPointF(row, col);
    double left = origin - point[row][col - 1];
    double right = origin - point[row][col + 1];
    double up = origin - point[row - 1][col];
    double down = origin - point[row + 1][col];
    double x = point[row][col + 1] - point[row][col - 1];
    double y = point[row + 1][col] - point[row - 1][col];
    double slope = y / x;
    if (slope > 0) {
        double target = point[row][col + 1] + (origin - point[row][col + 1]) * slope;
        for (int i = row - 2; i < this->row - 1; ++i) {
            double debug1 = point[i][col + 1];
            double debug2 = point[i + 1][col + 1];
            if ((point[i][col + 1] < target && point[i + 1][col + 1] > target)
                || (point[i][col + 1] > target && point[i + 1][col + 1] < target)) {
                if (std::abs(point[i][col + 1] - target) < std::abs(point[i + 1][col + 1] - target)) {
                    getFieldLine(i, col + 1, id);
                } else {
                    getFieldLine(i + 1, col + 1, id);
                }
            }
        }
    } else {
        double target = point[row][col - 1] + (origin - point[row][col - 1]) * slope;
        for (int i = row - 2; i < this->row - 1; ++i) {
            if ((point[i][col - 1] < target && point[i + 1][col - 1] > target)
                || (point[i][col - 1] > target && point[i + 1][col - 1] < target)) {
                if (std::abs(point[i][col - 1] - target) < std::abs(point[i + 1][col - 1] - target)) {
                    getFieldLine(i, col - 1, id);
                } else {
                    getFieldLine(i + 1, col - 1, id);
                }
            }
        }
    }

}

void Field::plotField(int x, int y) {
    QSplineSeries *series = new QSplineSeries();
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    series->setPen(pen);
    QList <QPointF> listLine = getLine(x, y);
    Vector4d vector4d = solveLine(listLine);
    QList <QPointF> listsolve;
    for (int i = 0; i < this->col * 10; ++i) {
        double y =
                vector4d(0, 0) * qPow(i / 10.0, 3) + vector4d(1, 0) * qPow(i / 10.0, 2) +
                vector4d(2, 0) * qPow(i / 10.0, 1)
                + vector4d(3, 0);
        QPointF pointF(i / 10.0, y);
        listsolve << pointF;
    }
    series->append(listsolve);
    chart->addSeries(series);

}

void Field::plotElec(int x, int y, int id) {

    QSplineSeries *series = new QSplineSeries();
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    series->setPen(pen);
    Vector4d vector4d;
    getFieldLine(x, y, id);
    if (id == 1) {
        vector4d = solveLine(fieldList1);
    }
    if (id == 2) {
        vector4d = solveLine(fieldList2);
    }
    if (id == 3) {
        vector4d = solveLine(fieldList3);
    }
    if (id == 4) {
        vector4d = solveLine(fieldList4);
    }
    if (id == 5) {
        vector4d = solveLine(fieldList5);
    }
    if (id == 6) {
        vector4d = solveLine(fieldList6);
    }

    QList <QPointF> listsolve;
    for (int i = 0; i < this->col * 10; ++i) {
        double y =
                vector4d(0, 0) * qPow(i / 10.0, 3)
                + vector4d(1, 0) * qPow(i / 10.0, 2)
                + vector4d(2, 0) * qPow(i / 10.0, 1)
                + vector4d(3, 0);
        QPointF pointF(i / 10.0, y);
        listsolve << pointF;
    }
    series->append(listsolve);
    chart->addSeries(series);
}


