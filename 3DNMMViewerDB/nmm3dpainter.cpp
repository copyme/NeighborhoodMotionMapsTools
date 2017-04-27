#include "nmm3dpainter.h"
#include "ui_nmm3dpainter.h"
#include <QPalette>

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

    pm0m1pm0Pal.setColor( QPalette::Background, Qt::yellow );
    pm0pm0pm0Pal.setColor( QPalette::Background, Qt::black );
    pm0pm0m1Pal.setColor( QPalette::Background, Qt::cyan );
    pm0pm0p1Pal.setColor( QPalette::Background, Qt::magenta );
    m1pm0pm0Pal.setColor( QPalette::Background, QColor (255, 165, 0) );
    p1pm0pm0Pal.setColor( QPalette::Background, Qt::green );
    pm0p1pm0Pal.setColor( QPalette::Background, QColor (128, 0, 128) );

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

    // bottom
    ui->pm0m1pm0->setValue ( pm0m1pm0Pal );
    // mid
    ui->pm0pm0m1->setValue ( pm0pm0m1Pal );
    ui->pm0pm0p1->setValue ( pm0pm0p1Pal );
    ui->pm0pm0pm0->setValue ( pm0pm0pm0Pal );
    ui->m1pm0pm0->setValue ( m1pm0pm0Pal );
    ui->p1pm0pm0->setValue ( p1pm0pm0Pal );
    // top
    ui->pm0p1pm0->setValue ( pm0p1pm0Pal );
}

NMM3DPainter::~NMM3DPainter()
{
    delete ui;
}

void NMM3DPainter::draw3DNMM(QString N1, QString N2, QString N3, QString N4, QString N5, QString N6, QString N7)
{
    for ( auto &it:pixels )
        it.second->clear();

    auto it = pixels.find ( N7 );
    if ( it == pixels.end() )
        throw std::runtime_error ( "Unrecognized 3D NMM." );
    it->second->setValue ( pm0pm0pm0Pal );

    it = pixels.find ( N1 );
    if ( it == pixels.end() )
        throw std::runtime_error ( "Unrecognized 3D NMM." );
    it->second->setValue ( p1pm0pm0Pal );

    it = pixels.find ( N2 );
    if ( it == pixels.end() )
        throw std::runtime_error ( "Unrecognized 3D NMM." );
    it->second->setValue ( pm0p1pm0Pal );

    it = pixels.find ( N3 );
    if ( it == pixels.end() )
        throw std::runtime_error ( "Unrecognized 3D NMM." );
    it->second->setValue ( pm0pm0p1Pal );

    it = pixels.find ( N4 );
    if ( it == pixels.end() )
        throw std::runtime_error ( "Unrecognized 3D NMM." );
    it->second->setValue ( m1pm0pm0Pal );

    it = pixels.find ( N5 );
    if ( it == pixels.end() )
        throw std::runtime_error ( "Unrecognized 3D NMM." );
    it->second->setValue ( pm0m1pm0Pal );

    it = pixels.find ( N6 );
    if ( it == pixels.end() )
        throw std::runtime_error ( "Unrecognized 3D NMM." );
    it->second->setValue ( pm0pm0m1Pal );
}
