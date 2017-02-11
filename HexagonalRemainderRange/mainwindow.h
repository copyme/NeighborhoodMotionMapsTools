#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <map>
#include <DGtal/helpers/StdDefs.h>
#include "torus2d.h"
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
private:
    Ui::MainWindow *ui;
    Torus2D torus;
    std::vector<Z3i::Point>neighbors;
    std::map<TilingWidget *, Z3i::Point>tilingToPoint;
    Z3i::RealPoint origin;
    Z3i::RealVector trans;
    Z3i::RealVector axis;

};

#endif // MAINWINDOW_H
