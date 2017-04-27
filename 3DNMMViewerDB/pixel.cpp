#include <QPoint>
#include "pixel.h"
#include "ui_pixel.h"

Pixel::Pixel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pixel)
{
    ui->setupUi(this);
    ui->widget_1->setAutoFillBackground ( true );
    ui->widget_2->setAutoFillBackground ( true );
    ui->widget_3->setAutoFillBackground ( true );
    ui->widget_4->setAutoFillBackground ( true );
    index = 0;
}

void Pixel::setValue(QPalette &pallete)
{
    if (index == 0)
    {
        ui->widget_1->setPalette ( pallete );
        ui->widget_2->setPalette ( pallete );
        ui->widget_3->setPalette ( pallete );
        ui->widget_4->setPalette ( pallete );
        index++;
    }
    else if (index == 1)
    {
        ui->widget_2->setPalette ( pallete );
        index++;
    }
    else if (index == 2)
    {
        ui->widget_3->setPalette ( pallete );
        index++;
    }
    else if (index == 3)
    {
        ui->widget_4->setPalette ( pallete );
        index = 0;
    }
}

void Pixel::clear()
{
    QPalette pallete( palette() );
    pallete.setColor( QPalette::Background, Qt::white );
    ui->widget_1->setPalette ( pallete );
    ui->widget_2->setPalette ( pallete );
    ui->widget_3->setPalette ( pallete );
    ui->widget_4->setPalette ( pallete );
    index = 0;
}

Pixel::~Pixel()
{
    delete ui;
}
