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

    colorMap["[1, 0, 0]"] =QPalette(Qt::green);
    colorMap["[0, 1, 0]"] =QPalette(QColor (128, 0, 128));
    colorMap["[0, 0, 1]"] =QPalette(Qt::magenta);
    colorMap["[-1, 0, 0]"] =QPalette(QColor (255, 165, 0));
    colorMap["[0, -1, 0]"] =QPalette(Qt::yellow);
    colorMap["[0, 0, -1]"] =QPalette(Qt::cyan);
    colorMap["[0, 0, 0]"] =QPalette(Qt::black);

    // bottom
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, -1]" ), ui->m1m1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, 0]" ), ui->m1m1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, -1]" ), ui->p1m1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, 1]" ), ui->p1m1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, -1, 0]" ), ui->p1m1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, -1]" ), ui->pm0m1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, 1]" ), ui->pm0m1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, -1, 0]" ), ui->pm0m1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, -1, 1]" ), ui->m1m1p1 ) );

    // mid
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, -1]" ), ui->m1pm0m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, 1]" ), ui->m1pm0p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 0, 0]" ), ui->m1pm0pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, -1]" ), ui->p1pm0m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, 1]" ), ui->p1pm0p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 0, 0]" ), ui->p1pm0pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, -1]" ), ui->pm0pm0m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, 1]" ), ui->pm0pm0p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 0, 0]" ), ui->pm0pm0pm0 ) );

    // top
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, -1]" ), ui->m1p1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, 1]" ), ui->m1p1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[-1, 1, 0]" ), ui->m1p1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, -1]" ), ui->p1p1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, 1]" ), ui->p1p1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[1, 1, 0]" ), ui->p1p1pm0 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, -1]" ), ui->pm0p1m1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, 1]" ), ui->pm0p1p1 ) );
    pixels.insert ( std::make_pair ( QString ( "[0, 1, 0]" ), ui->pm0p1pm0 ) );


    for ( auto &it:pixels ) it.second->clear();

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
