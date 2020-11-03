#include "qfigure.h"

QFigure::QFigure(AbstractFigure *figure, QPixmap map, QPointF coords) : QGraphicsPixmapItem(map), m_coords(coords), m_figure(figure) {}

void QFigure::setCoords(QPointF coords) {
    m_coords = coords;
}

void QFigure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    float x = scenePos().x() / TILE_SIZE - std::round(scenePos().x() / TILE_SIZE);
    float y = scenePos().y() / TILE_SIZE - std::round(scenePos().y() / TILE_SIZE);

    if (std::abs(x) < 0.30 && std::abs(y) < 0.30 && scenePos().x() > 0 && scenePos().y() > 0) {
        QPointF new_coords = {std::round(scenePos().x() / TILE_SIZE), std::round(scenePos().y() / TILE_SIZE)};

        emit playerMove(this, m_coords, new_coords);
    }
    else
        setPos(COORD_FROM_INDEX(m_coords.x()), COORD_FROM_INDEX(m_coords.y()));
}

Side QFigure::getSide() const {
    return m_figure->getSide();
} 

QPointF QFigure::getCoords(void) const {
    return m_coords;
}