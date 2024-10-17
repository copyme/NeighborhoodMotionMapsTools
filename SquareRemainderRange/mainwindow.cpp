#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RigidTransformation2D.h"
#include "tikzexport.h"

using namespace functors;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui ( new Ui::MainWindow ), torus ( QRect(20, 20, 700, 700) ),
    graph ( QRect(20, 20, 700, 700) ), neighbors(8)
{
    ui->setupUi(this);
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)),
            &torus, SLOT(angleChanged(double)));

    torus.setParent(ui->tab);
    graph.setParent(ui->tab_2);

    neighbors[0] = Point(0,1);
    neighbors[1] = Point(-1,0);
    neighbors[2] = Point(0,-1);
    neighbors[3] = Point(1,0);

    neighbors[4] = Point(1,1);
    neighbors[5] = Point(-1,1);
    neighbors[6] = Point(1,-1);
    neighbors[7] = Point(-1,-1);
    tilingToPoint.clear();

    adj = 4;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changedAngle(double angle)
{
    ForwardRigidTransformation2D<Space> forTrans (origin, angle, trans );

    for ( std::map<TilingWidget *, Point>::const_iterator it = tilingToPoint.cbegin(); it != tilingToPoint.cend(); ++it )
    {
        std::vector<Point>pointsMap(adj);
        for ( unsigned int i = 0; i < adj; i++ )
        {
            pointsMap[i] =  forTrans(neighbors[i] + (*it).second) - forTrans((*it).second);
        }
        //it will work only with modf. ver. of DGtal
        RealPoint realImage = forTrans(RealPoint((*it).second));
        Point intPoint ( std::round ( realImage[0] ), std::round ( realImage[1] ) );
        RealPoint map =  realImage - intPoint;
        (*(*it).first).colorChanged(pointsMap);
        torus.colorChanged(map, (*it).first );

        (*arrowsToPoint.at ( (*it).second )).colorChanged(pointsMap);
        graph.colorChanged ( intPoint, arrowsToPoint.at ( (*it).second ) );
    }
}

void MainWindow::addPoints()
{
    if ( ui->x1->text() == "" || ui->y1->text() == "" )
        return;
    else if ( ui->x2->text() == "" || ui->y2->text() == "" )
    {
        TilingWidget * cw = new TilingWidget ( QRect(500, 500, 50, 52), &torus,  (ui->x1->text() + ", "  + ui->y1->text() ).toStdString().c_str() );
        cw->setVisible(true);
        connect ( ui->checkBox, SIGNAL ( stateChanged ( int ) ), cw, SLOT ( setAdjacency (int) ) );
        tilingToPoint.insert ( std::pair<TilingWidget *, Point>(cw, Point ( ui->x1->text().toInt(), ui->y1->text().toInt() ) ) );

        ColorWidget * cc = new ColorWidget ( QRect(500, 500, 50, 50), &graph,  (ui->x1->text() + ", "  + ui->y1->text() ).toStdString().c_str() );
        cc->setVisible(true);
        arrowsToPoint.insert ( std::pair<Point, ColorWidget *> ( Point ( ui->x1->text().toInt(), ui->y1->text().toInt() ), cc ) );
    }
    else
    {
        Domain d (Point ( ui->x1->text().toInt(), ui->y1->text().toInt() ), Point ( ui->x2->text().toInt(), ui->y2->text().toInt() ));

        for ( Domain::ConstIterator it = d.begin(); it != d.end(); ++it )
        {
            std::stringstream st;
            st << (*it)[0] << ", " << (*it)[1];
            TilingWidget * cw = new TilingWidget ( QRect(500, 500, 50, 52), &torus,  st.str().c_str() );
            cw->setVisible(true);
            connect ( ui->checkBox, SIGNAL ( stateChanged ( int ) ), cw, SLOT ( setAdjacency ( int ) ) );
            tilingToPoint.insert ( std::pair<TilingWidget *, Point>(cw, (*it) ) );

            ColorWidget * cc = new ColorWidget ( QRect(500, 500, 50, 50), &graph,  st.str().c_str() );
            cc->setVisible(true);
            arrowsToPoint.insert ( std::pair< Point, ColorWidget *> ( (*it), cc ) );
        }
    }
    changedAngle( ui->doubleSpinBox->value() );
}

void MainWindow::changedOrigin()
{
    if ( ui->ox->text() == "" || ui->oy->text() == "" )
        return;
    origin[0] = ui->ox->text().toDouble();
    origin[1] = ui->oy->text().toDouble();
    changedAngle( ui->doubleSpinBox->value() );
}

void MainWindow::changedTranslation()
{
    trans[0] = ui->spinBoxX->value();
    trans[1] = ui->spinBoxY->value();

    torus.translationChanged( trans[0] - std::floor(trans[0] + 0.5f), trans[1] - std::floor(trans[1] + 0.5f) );
    changedAngle( ui->doubleSpinBox->value() );
}

void MainWindow::saveTorus()
{
    QString saveFilename = QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PNG(*.png)");

    QString saveExtension = "PNG";
    int pos = saveFilename.lastIndexOf('.');
    if (pos >= 0)
        saveExtension = saveFilename.mid(pos + 1);

    if(!torus.grab().save(saveFilename, qPrintable(saveExtension)))
    {
        QMessageBox::warning(this, "File could not be save", "ok", QMessageBox::Ok);
    }
}

void MainWindow::saveGraph()
{
    QString saveFilename = QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PNG(*.png)");

    QString saveExtension = "PNG";
    int pos = saveFilename.lastIndexOf('.');
    if (pos >= 0)
        saveExtension = saveFilename.mid(pos + 1);

    if(!graph.grab().save(saveFilename, qPrintable(saveExtension)))
    {
        QMessageBox::warning(this, "File could not be save", "ok", QMessageBox::Ok);
    }
}


void MainWindow::changedAdj ( int state )
{
    if ( state == Qt::Unchecked )
        adj = 4;
    else if ( state == Qt::Checked )
        adj = 8;

    changedAngle ( ui->doubleSpinBox->value() );
}

void MainWindow::exportTorusTiKZ()
{
    QString saveFilename = QFileDialog::getSaveFileName(this, "Open", "", "TiKZ(*.tikz)");
    std::ifstream input ( saveFilename.toStdString().c_str() );
    if(!input)
    {
        QMessageBox::warning(this, "File could not be open.", "ok", QMessageBox::Ok);
        return;
    }

    QFile file(saveFilename);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream ts(&file);
        QTikzPicture tikzPicture;
        tikzPicture.setStream(&ts,7);
        tikzPicture.begin("scale=4");
        torus.exportToTikz(tikzPicture);
        tikzPicture.end();
    }
    file.close();
}

