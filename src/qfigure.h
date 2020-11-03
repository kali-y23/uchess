#pragma once

#include "gamewindow.h"

#include <iostream>

#define TILE_SIZE 80

class QFigure : public QObject, public QGraphicsPixmapItem 
{
    Q_OBJECT

    QPointF m_coords;
    AbstractFigure *m_figure;

public:
    QFigure(AbstractFigure *figure, QPixmap map, QPointF coords);

    QPointF getCoords(void) const;
    void setCoords(QPointF coords);
    Side getSide() const;

signals:
    void playerMove(QFigure *figure, const QPointF& from, const QPointF& to);

public slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};