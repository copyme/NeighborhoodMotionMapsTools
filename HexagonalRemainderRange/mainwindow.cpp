#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hextools.h"
#include "RigidTransformation3D.h"

using namespace functors;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui ( new Ui::MainWindow ), torus ( QRect(20, 20, 700, 700) ), neighbors(6),
    axis ( 1. / std::sqrt(3.), 1. / std::sqrt(3.), 1. / std::sqrt(3.) )
{
    ui->setupUi(this);
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)),
            &torus, SLOT(angleChanged(double)));
        connect(ui->checkBoxNonInj, SIGNAL(toggled(bool)),
            &torus, SLOT(drawNonInjChanged(bool)));

    torus.setParent(ui->tab);
    //Coordinates in cube coordinate system system!!
    neighbors[0] = Z3i::Point(1,0,-1);
    neighbors[1] = Z3i::Point(0,1,-1);
    neighbors[2] = Z3i::Point(-1,1,0);
    neighbors[3] = Z3i::Point(-1,0,1);
    neighbors[4] = Z3i::Point(0,-1,1);
    neighbors[5] = Z3i::Point(1,-1,0);
    tilingToPoint.clear();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changedAngle(double angle)
{
    // we work in the cube coordinate system fixed to a plane which cuts 3D Cartesian grid
    ForwardRigidTransformation3D<Z3i::Space> forTrans ( origin, axis, angle, trans );

    for ( auto it:tilingToPoint)
    {
        std::vector<Z3i::Point>pointsMap(6);
        for ( unsigned int i = 0; i < 6; i++ )
        {
            pointsMap[i] =  HexTools::CubeRounding(forTrans(Z3i::RealPoint(neighbors[i] + it.second)))
                    - HexTools::CubeRounding(forTrans(Z3i::RealPoint(it.second)));
        }
        //it will work only with modf. ver. of DGtal
        Z3i::RealPoint realImage = forTrans ( Z3i::RealPoint ( it.second ) );
        Z3i::Point intPoint = HexTools::CubeRounding ( realImage );
        RealPoint map = HexTools::CubeToAxial(realImage - intPoint);
        map = HexTools::CartesianToHex ( map );
        (*it.first).colorChanged(pointsMap);
        torus.colorChanged(map, it.first );

    }
}

void MainWindow::addPoints()
{
    if ( ui->x1->text() == "" || ui->y1->text() == "" )
        return;
    else if ( ui->x2->text() == "" || ui->y2->text() == "" )
    {
        TilingWidget * cw = new TilingWidget ( QRect(350, 350, 50, 52), &torus,  (ui->x1->text() + ", "  + ui->y1->text() ).toStdString().c_str() );
        cw->setVisible(true);
        tilingToPoint.insert ( std::pair<TilingWidget *, Z3i::Point>(cw, Z3i::Point ( ui->x1->text().toInt(),
                                                                                      -ui->x1->text().toInt() - ui->y1->text().toInt(),
                                                                                      ui->y1->text().toInt() ) ) );

    }
    else
    {
        Domain d (Point ( ui->x1->text().toInt(), ui->y1->text().toInt() ), Point ( ui->x2->text().toInt(), ui->y2->text().toInt() ));

        for ( Domain::ConstIterator it = d.begin(); it != d.end(); ++it )
        {
            std::stringstream st;
            st << (*it)[0] << ", " << (*it)[1];
            TilingWidget * cw = new TilingWidget ( QRect(350, 350, 50, 52), &torus,  st.str().c_str() );
            cw->setVisible(true);
            tilingToPoint.insert ( std::pair<TilingWidget *, Z3i::Point> ( cw, Z3i::Point ( (*it)[0], -(*it)[0] - (*it)[1], (*it)[1] ) ) );
        }
    }
    changedAngle( ui->doubleSpinBox->value() );
}

void MainWindow::changedOrigin()
{
    if ( ui->ox->text() == "" || ui->oy->text() == "" )
        return;
    origin[0] = ui->ox->text().toDouble();
    origin[2] = ui->oy->text().toDouble();
    origin[1] = - origin[0] - origin[1];
    changedAngle( ui->doubleSpinBox->value() );
}

void MainWindow::changedTranslation()
{
    // convert translation to translation in plane x+y+z=0
    RealPoint t(ui->spinBoxX->value(), ui->spinBoxY->value());
    t = HexTools::HexToCartesian(t);
    trans[0] = t[0];
    trans[2] = t[1];
    trans[1] = -trans[0] - trans[2];

    changedAngle( ui->doubleSpinBox->value() );
}

void MainWindow::saveTorus()
{
    QString saveFilename = QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PNG(*.png)");

    QString saveExtension = "PNG";
    int pos = saveFilename.lastIndexOf('.');
    if (pos >= 0)
        saveExtension = saveFilename.mid(pos + 1);

    if(!QPixmap::grabWidget(&torus).save(saveFilename, qPrintable(saveExtension)))
    {
        QMessageBox::warning(this, "File could not be save", "ok", QMessageBox::Ok);
    }
}
