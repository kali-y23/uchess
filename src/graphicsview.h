#pragma once

#define COORD_FROM_INDEX(x) ((x * TILE_SIZE) + 5)

#include <map>

#include "gamewindow.h"
#include "gamemanager.h"
#include "abstractfigure.h"
#include "qfigure.h"

class AbstractFigure;
class GameManager;
class QFigure;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

    friend class GameWindow;

    QGraphicsScene *scene;
    std::map<std::pair<Type, Side>, QPixmap> pixmaps;
    GameManager *manager;
    QList<QFigure *> figure_list;

    GraphicsView(QWidget *widget);
    ~GraphicsView(void);

public slots:
    void playerMove(QFigure *figure, const QPointF& from, const QPointF& to);

signals:
    void changeStatusLabel(const QString& new_label);

private:
    void createField(void);
    void loadImages(void);
    void drawFigures(const std::array<std::array<AbstractFigure *, 8>, 8>& field);
    void updateFigure(QFigure *figure, const QPointF& coords);
    void updateLabel(Outcome outcome, Side side);
};