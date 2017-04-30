#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <map>
#include <DGtal/helpers/StdDefs.h>
#include "torus2d.h"
#include "graphwidget.h"
#include "tilingwidget.h"

using namespace DGtal;
using namespace Z2i;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changedAngle(double angle);
    void addPoints();
    void changedOrigin();
    void changedTranslation();
    void saveTorus();
    void saveGraph();
    void changedAdj ( int );
    void exportTorusTiKZ ();
private:
    Ui::MainWindow *ui;
    Torus2D torus;
    GraphWidget graph;
    unsigned int adj;
    std::vector<Point>neighbors;
    std::map<TilingWidget *, Point>tilingToPoint;
    std::map<Point, ColorWidget *>arrowsToPoint;
    RealPoint origin;
    RealVector trans;

};

#endif // MAINWINDOW_H
