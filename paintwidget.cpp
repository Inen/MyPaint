#include "paintwidget.h"
#include <QPainter>
#include <QRect>
#include <QMouseEvent>

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, image, rect);
}

bool PaintWidget::openImage(QString fileName)
{
    QImage loadImg;
    if (!loadImg.load(fileName))
        return false;
    QSize newSize = loadImg.size().expandedTo(this->size());
    resizeImage(&loadImg, newSize);
    image = loadImg;
    modified = false;
    update();
    return true;
}

bool PaintWidget::saveImage(const QString fileName, const char *fileFormat)
{
    QImage visibleImg = image;
    resizeImage(&visibleImg, size());

    if (visibleImg.save(fileName, fileFormat))
    {
        modified = false;
        return true;
    } else
        return false;
}

void PaintWidget::setPenColor(QColor newColor)
{
    penColor = newColor;
}

void PaintWidget::setPenWidth(int newWidth)
{
    penWidth = newWidth;
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
            (drawingTypeFlag != byPen))
    {
        tempImg = image;
    }
    lastPoint = event->pos();
    drawFlag = true;
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton && drawFlag)
    {
        switch (drawingTypeFlag) {
        case byPen:
            drawByPen(event->pos());
            break;
        case line:
            drawLine(event->pos());
            break;
        case rect:
            drawRect(event->pos());
            break;
        case ellipse:
            drawEllpise(event->pos());
        default:
            break;
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton && drawFlag && drawingTypeFlag == byPen)
    {
        drawByPen(event->pos());
    }
    drawFlag = false;
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    if (this->width() > image.width() || height() > image.height())
    {
             int newWidth = qMax(width() + 128, image.width());
             int newHeight = qMax(height() + 128, image.height());
             resizeImage(&image, QSize(newWidth, newHeight));
             update();
    }
    QWidget::resizeEvent(event);
}

void PaintWidget::drawByPen(QPoint endPoint)
{
    QPainter painter(&image);
    QPen newPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(newPen);
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (penWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void PaintWidget::drawLine(QPoint endPoint)
{
    image = tempImg;
    QPainter painter(&image);
    QPen newPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(newPen);

    painter.drawLine(lastPoint, endPoint);
    modified = true;

    update();
}

void PaintWidget::drawRect(QPoint endPoint)
{
    image = tempImg;
    QPainter painter(&image);
    QPen newPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(newPen);

    QRect newRect(lastPoint, endPoint);
    painter.drawRect(newRect);
    modified = true;

    update();
}

void PaintWidget::drawEllpise(QPoint endPoint)
{
    image = tempImg;
    QPainter painter(&image);
    QPen newPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(newPen);

    QRect newRect(lastPoint, endPoint);
    painter.drawEllipse(newRect);
    modified = true;

    update();

}

void PaintWidget::resizeImage(QImage *image, QSize newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(Qt::white);

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void PaintWidget::clearImage()
{
         image.fill(Qt::white);
         modified = true;
         update();
}

bool PaintWidget::isModified()
{
    return modified;
}

void PaintWidget::setDrawingTypeFlag(int newType)
{
    drawingTypeFlag = newType;
}

QColor PaintWidget::getPenColor()
{
    return penColor;
}
