#include "nmm3dpainter.h"
#include "ui_nmm3dpainter.h"
#include <QPalette>
#include <iostream>

NMM3DPainter::NMM3DPainter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NMM3DPainter),
    pm0m1pm0Pal( palette() ),
    pm0pm0pm0Pal( palette() ),
    pm0pm0m1Pal( palette() ),
    pm0pm0p1Pal( palette() ),
    m1pm0pm0Pal( palette() ),
    p1pm0pm0Pal( palette() ),
    pm0p1pm0Pal( palette() )
{
    ui->setupUi(this);
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, Qt::white );

    /*N1*/
    colorMap["[1, 0, 0]"] = QPalette(QColor (213, 255, 0));
    colorMap["[0, 1, 0]"] = QPalette(QColor (255, 0, 86));
    colorMap["[0, 0, 1]"] = QPalette(QColor (158, 0, 142));
    colorMap["[-1, 0, 0]"] = QPalette(QColor (14, 76, 161));
    colorMap["[0, -1, 0]"] = QPalette(QColor (0, 95, 57));
    colorMap["[0, 0, -1]"] = QPalette(QColor (0, 255, 0));
    colorMap["[0, 0, 0]"] = QPalette(Qt::black);
    /*N2*/
    colorMap["[1, 1, 0]"] = QPalette(QColor (149, 0, 58));
    colorMap["[1, 0, 1]"] = QPalette(QColor (255, 147, 126));
    colorMap["[0, 1, 1]"] = QPalette(QColor (164, 36, 0));
    colorMap["[-1, -1, 0]"] = QPalette(QColor (67, 0, 44));
    colorMap["[-1, 0, -1]"] = QPalette(QColor (145, 208, 203));
    colorMap["[0, -1, -1]"] = QPalette(QColor (107, 104, 130));
    colorMap["[-1, 1, 0]"] = QPalette(QColor (0, 0, 255));
    colorMap["[-1, 0, 1]"] = QPalette(QColor (0, 125, 181));
    colorMap["[1, -1, 0]"] = QPalette(QColor (106, 130, 108));
    colorMap["[1, 0, -1]"] = QPalette(QColor (0, 174, 126));
    colorMap["[0, -1, 1]"] = QPalette(QColor (194, 140, 159));
    colorMap["[0, 1, -1]"] = QPalette(QColor (190, 153, 112));
    /*N3*/
    colorMap["[1, 1, 1]"] = QPalette(QColor (0, 143, 156));
    colorMap["[-1, 1, 1]"] = QPalette(QColor (95, 173, 78));
    colorMap["[1, -1, 1]"] = QPalette(QColor (255, 0, 0));
    colorMap["[1, 1, -1]"] = QPalette(QColor (255, 0, 246));
    colorMap["[-1, -1, 1]"] = QPalette(QColor (255, 2, 157));
    colorMap["[-1, 1, -1]"] = QPalette(QColor (104, 61, 59));
    colorMap["[-1, -1, -1]"] = QPalette(QColor (255, 116, 163));
    colorMap["[1, -1, -1]"] = QPalette(QColor (150, 138, 232));

    // bottom -2
    pixels.insert ( std::make_pair ( QString ( "[-1, -2, -1]" ), ui->m1m2m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -2, 0]" ), ui->m1m2pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -2, -1]" ), ui->p1m2m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -2, 1]" ), ui->p1m2p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -2, 0]" ), ui->p1m2pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -2, -1]" ), ui->pm0m2m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -2, 1]" ), ui->pm0m2p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -2, 0]" ), ui->pm0m2pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -2, 1]" ), ui->m1m2p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -2, 2]" ), ui->m1m2p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -2, 2]" ), ui->pm0m2p2) );
    pixels.insert ( std::make_pair ( QString ( "[1, -2, 2]" ), ui->p1m2p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, -2, 1]" ), ui->p2m2p1) );
    pixels.insert ( std::make_pair ( QString ( "[2, -2, 0]" ), ui->p2m2pm0) );
    pixels.insert ( std::make_pair ( QString ( "[2, -2, -1]" ), ui->p2m2m1) );
    pixels.insert ( std::make_pair ( QString ( "[1, -2, -2]" ), ui->p1m2m2) );
    pixels.insert ( std::make_pair ( QString ( "[0, -2, -2]" ), ui->pm0m2m2) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -2, -2]" ), ui->m1m2m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -2, -1]" ), ui->m2m2m1) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -2, 0]" ), ui->m2m2pm0) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -2, 1]" ), ui->m2m2p1) );

    // bottom -1
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, -1]" ), ui->m1m1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, 0]" ), ui->m1m1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, -1]" ), ui->p1m1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, 1]" ), ui->p1m1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, 0]" ), ui->p1m1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, -1]" ), ui->pm0m1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, 1]" ), ui->pm0m1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, 0]" ), ui->pm0m1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, 1]" ), ui->m1m1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -1, 2]" ), ui->m2m1p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, 2]" ), ui->m1m1p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, 2]" ), ui->pm0m1p2) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, 2]" ), ui->p1m1p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, -1, 2]" ), ui->p2m1p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, -1, 1]" ), ui->p2m1p1) );
    pixels.insert ( std::make_pair ( QString ( "[2, -1, 0]" ), ui->p2m1pm0) );
    pixels.insert ( std::make_pair ( QString ( "[2, -1, -1]" ), ui->p2m1m1) );
    pixels.insert ( std::make_pair ( QString ( "[2, -1, -2]" ), ui->p2m1m2) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, -2]" ), ui->p1m1m2) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, -2]" ), ui->pm0m1m2) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, -2]" ), ui->m1m1m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -1, -2]" ), ui->m2m1m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -1, -1]" ), ui->m2m1m1) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -1, 0]" ), ui->m2m1pm0) );
    pixels.insert ( std::make_pair ( QString ( "[-2, -1, 1]" ), ui->m2m1p1) );

    // mid 0
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, -1]" ), ui->m1pm0m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, 1]" ), ui->m1pm0p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, 0]" ), ui->m1pm0pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, -1]" ), ui->p1pm0m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, 1]" ), ui->p1pm0p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, 0]" ), ui->p1pm0pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, -1]" ), ui->pm0pm0m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, 1]" ), ui->pm0pm0p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, 0]" ), ui->pm0pm0pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 0, 2]" ), ui->m2pm0p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, 2]" ), ui->m1pm0p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, 2]" ), ui->pm0pm0p2) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, 2]" ), ui->p1pm0p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, 0, 2]" ), ui->p2pm0p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, 0, 1]" ), ui->p2pm0p1) );
    pixels.insert ( std::make_pair ( QString ( "[2, 0, 0]" ), ui->p2pm0pm0) );
    pixels.insert ( std::make_pair ( QString ( "[2, 0, -1]" ), ui->p2pm0m1) );
    pixels.insert ( std::make_pair ( QString ( "[2, 0, -2]" ), ui->p2pm0m2) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, -2]" ), ui->p1pm0m2) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, -2]" ), ui->pm0pm0m2) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, -2]" ), ui->m1pm0m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 0, -2]" ), ui->m2pm0m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 0, -1]" ), ui->m2pm0m1) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 0, 0]" ), ui->m2pm0pm0) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 0, 1]" ), ui->m2pm0p1) );

    // top 1
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, -1]" ), ui->m1p1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, 1]" ), ui->m1p1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, 0]" ), ui->m1p1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, -1]" ), ui->p1p1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, 1]" ), ui->p1p1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, 0]" ), ui->p1p1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, -1]" ), ui->pm0p1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, 1]" ), ui->pm0p1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, 0]" ), ui->pm0p1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 1, 2]" ), ui->m2p1p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, 2]" ), ui->m1p1p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, 2]" ), ui->pm0p1p2) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, 2]" ), ui->p1p1p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, 1, 2]" ), ui->p2p1p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, 1, 1]" ), ui->p2p1p1) );
    pixels.insert ( std::make_pair ( QString ( "[2, 1, 0]" ), ui->p2p1pm0) );
    pixels.insert ( std::make_pair ( QString ( "[2, 1, -1]" ), ui->p2p1m1) );
    pixels.insert ( std::make_pair ( QString ( "[2, 1, -2]" ), ui->p2p1m2) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, -2]" ), ui->p1p1m2) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, -2]" ), ui->pm0p1m2) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, -2]" ), ui->m1p1m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 1, -2]" ), ui->m2p1m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 1, -1]" ), ui->m2p1m1) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 1, 0]" ), ui->m2p1pm0) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 1, 1]" ), ui->m2p1p1) );

    // top 2
    pixels.insert ( std::make_pair ( QString ( "[-1, 2, -1]" ), ui->m1p2m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 2, 1]" ), ui->m1p2p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 2, 0]" ), ui->m1p2pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 2, -1]" ), ui->p1p2m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 2, 1]" ), ui->p1p2p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 2, 0]" ), ui->p1p2pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 2, -1]" ), ui->pm0p2m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 2, 1]" ), ui->pm0p2p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 2, 0]" ), ui->pm0p2pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 2, 2]" ), ui->m1p2p2 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 2, 2]" ), ui->pm0p2p2) );
    pixels.insert ( std::make_pair ( QString ( "[1, 2, 2]" ), ui->p1p2p2) );
    pixels.insert ( std::make_pair ( QString ( "[2, 2, 1]" ), ui->p2p2p1) );
    pixels.insert ( std::make_pair ( QString ( "[2, 2, 0]" ), ui->p2p2pm0) );
    pixels.insert ( std::make_pair ( QString ( "[2, 2, -1]" ), ui->p2p2m1) );
    pixels.insert ( std::make_pair ( QString ( "[1, 2, -2]" ), ui->p1p2m2) );
    pixels.insert ( std::make_pair ( QString ( "[0, 2, -2]" ), ui->pm0p2m2) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 2, -2]" ), ui->m1p2m2) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 2, -1]" ), ui->m2p2m1) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 2, 0]" ), ui->m2p2pm0) );
    pixels.insert ( std::make_pair ( QString ( "[-2, 2, 1]" ), ui->m2p2p1) );

    for ( auto &it:pixels )
        it.second->clear();

    for (auto it = colorMap.cbegin(); it != colorMap.cend(); it++)
       pixels[it->first]->setValue(it->second);
}

NMM3DPainter::~NMM3DPainter()
{
    delete ui;
}

void NMM3DPainter::draw3DNMM(std::map<QString, QString>::const_iterator begin, std::map<QString, QString>::const_iterator end)
{
    for ( auto &it:pixels )
        it.second->clear();

    for (auto it = begin; it != end; it++)
       pixels[it->second]->setValue(colorMap[it->first]);
}
