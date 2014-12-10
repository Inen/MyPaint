#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QImage>
#include <drawmanager.h>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);

    bool openImage(QString fileName);
    bool saveImage(const QString fileName, const char *fileFormat);
    void setPenColor(QColor newColor);
    void setPenWidth(int newWidth);
    QColor getPenColor();
    bool isModified();
    int getPenWidth();
    void setDrawingTypeFlag(int newType);

    enum drawingType {byPen, line, rect, ellipse};

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void drawByPen(QPoint endPoint);
    void drawLine(QPoint endPoint);
    void drawRect(QPoint endPoint);
    void drawEllpise(QPoint endPoint);
    void resizeImage(QImage *image, QSize newSize);

    bool drawFlag = false;
    bool startDrawFlag = false;
    bool modified = false;
    QPoint lastPoint;
    int penWidth = 2;
    QColor penColor = Qt::black;
    QImage image;
    int drawingTypeFlag = byPen;
    QImage tempImg;

signals:

public slots:
    void clearImage();

};

#endif // PAINTWIDGET_H
