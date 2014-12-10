#include "drawmanager.h"

DrawManager *DrawManager::p_instance = nullptr;

DrawManager::DrawManager()
{
}

void DrawManager::DrawPoint(QPainter *p, int x, int y)
{
    QPen pen(color, penWidth, Qt::SolidLine);
    p->setPen(pen);
    p->drawPoint(x, y);
}

void DrawManager::SetPen(QColor newCol, int newWidth)
{
    color = newCol;
    penWidth = newWidth;
}
