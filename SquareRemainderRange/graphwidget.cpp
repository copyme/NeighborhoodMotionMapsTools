#include "graphwidget.h"

GraphWidget::GraphWidget(QRectF rec, QWidget *parent) : QWidget ( parent )
{
    setGeometry ( rec.x(), rec.y(), rec.width(), rec.height() );
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, Qt::white );
    setAutoFillBackground ( true );
    setPalette ( pal );
}

void GraphWidget::colorChanged(Point point, ColorWidget *w)
{
    QPointF p ( (point[0] + width()/2 + point[0] * w->width()), height() - (point[1] + height()/2 + point[1] * w->height() ) );
    w->setGeometry( QRect( p.x() - w->width()/2, p.y() - w->height()/2, w->width(), w->height()) );
    w->labelTransformedPoint((std::to_string(point[0]) + "," + std::to_string(point[1])).c_str());
    update();
}
