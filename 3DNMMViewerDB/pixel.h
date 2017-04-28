#ifndef PIXEL_H
#define PIXEL_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Pixel;
}

class Pixel : public QWidget
{
    Q_OBJECT

public:
    explicit Pixel(QWidget *parent = 0);
    void setValue(const QPalette & pallete );
    void clear();
    ~Pixel();


private:
    Ui::Pixel *ui;
    uint index = 0;
};

#endif // PIXEL_H
