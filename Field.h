//
// Created by song on 7/3/16.
//

#ifndef FIELD_FIELD_H
#define FIELD_FIELD_H
#include <QWidget>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <iomanip>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QDebug>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
using namespace Eigen;
QT_CHARTS_USE_NAMESPACE
class Field:public QWidget
{
Q_OBJECT

private:

    double **point;
    int col;
    int row;
    int ccol;
    int crow;
    double alpha;
    QChart *chart;

    QList<QPointF> fieldList1;
    QList<QPointF> fieldList2;
    QList<QPointF> fieldList3;
    QList<QPointF> fieldList4;
    QList<QPointF> fieldList5;
    QList<QPointF> fieldList6;


public:
    Field(QWidget *parent =0);
    void print();
    virtual ~Field();
    void iterate(double threshold);
    void iterateI(double threshold);
    QList<QPointF> getLine(int row,int col);
    Vector4d solveLine(QList<QPointF>);
    void  getFieldLine(int row,int col,int id);

    void plotField(int x,int y);
    void plotElec(int x,int y,int id);
};


#endif //FIELD_FIELD_H
