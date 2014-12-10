#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QPainter>

class DrawManager
{
  private:
    static DrawManager * p_instance;
    DrawManager();
    DrawManager( const DrawManager& ); // hide copy constructor
    DrawManager& operator=( DrawManager& ); // hide assign operation
    QColor color = Qt::black;
    int penWidth = 2;

  public:
    static DrawManager * getInstance()
    {
        if(!p_instance)
            p_instance = new DrawManager();
        return p_instance;
    }
    void DrawPoint(QPainter *p, int x, int y);
    void SetPen(QColor newCol, int newWidth);
    int oldX = 0, oldY = 0;
};

#endif // DRAWMANAGER_H
