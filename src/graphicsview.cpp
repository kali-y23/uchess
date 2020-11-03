#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *widget) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, TILE_SIZE * 8, TILE_SIZE * 8);

    loadImages();
    createField();

    manager = new GameManager();
    drawFigures(manager->getField());

    setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setGeometry(0, 0, TILE_SIZE * 8, TILE_SIZE * 8);
    setScene(scene);
}

GraphicsView::~GraphicsView() {
    delete manager;
}

void GraphicsView::createField(void) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            QPixmap map;
            if (i % 2 == 0 && j % 2 == 0 || i % 2 == 1 && j % 2 == 1)
                map.load(":/white_tile.png");
            else
                map.load(":/black_tile.png");
            QGraphicsPixmapItem *tile = new QGraphicsPixmapItem(map);
            tile->setPos(i * TILE_SIZE, j * TILE_SIZE);
            scene->addItem(tile);
        }
    }
}

void GraphicsView::loadImages(void) {
    std::map<std::pair<Type, Side>, QPixmap> map = {
        {{Type::Pawn, Side::White}, QPixmap(":/white_pawn.png")},
        {{Type::Pawn, Side::Black}, QPixmap(":/black_pawn.png")},

        {{Type::Rook, Side::White}, QPixmap(":/white_rook.png")},
        {{Type::Rook, Side::Black}, QPixmap(":/black_rook.png")},

        {{Type::Knight, Side::White}, QPixmap(":/white_knight.png")},
        {{Type::Knight, Side::Black}, QPixmap(":/black_knight.png")},

        {{Type::Bishop, Side::White}, QPixmap(":/white_bishop.png")},
        {{Type::Bishop, Side::Black}, QPixmap(":/black_bishop.png")},

        {{Type::Queen, Side::White}, QPixmap(":/white_queen.png")},
        {{Type::Queen, Side::Black}, QPixmap(":/black_queen.png")},

        {{Type::King, Side::White}, QPixmap(":/white_king.png")},
        {{Type::King, Side::Black}, QPixmap(":/black_king.png")}
    };

    pixmaps = map;
}

void GraphicsView::drawFigures(const std::array<std::array<AbstractFigure *, 8>, 8>& field) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if (!field[i][j])
                continue;
            QPixmap map = pixmaps[std::make_pair(field[i][j]->getType(), field[i][j]->getSide())];

            QFigure *figure = new QFigure(field[i][j], map, {static_cast<qreal>(j), static_cast<qreal>(i)});
            if (field[i][j]->getSide() == Side::Black)
                figure->setEnabled(false);
            figure->setFlag(QGraphicsItem::ItemIsMovable);
            figure->setPos(COORD_FROM_INDEX(j), COORD_FROM_INDEX(i));
            QObject::connect(figure, SIGNAL(playerMove(QFigure *, const QPointF&, const QPointF&)), SLOT(playerMove(QFigure *, const QPointF&, const QPointF&)));
            scene->addItem(figure);
            figure_list.push_back(figure);
        }
    }
}

void GraphicsView::playerMove(QFigure *figure, const QPointF& from, const QPointF& to) {
    Turn turn = manager->makeTurn(std::make_pair(from.x(), from.y()),
                                  std::make_pair(to.x(), to.y()));

    if (turn.outcome == Outcome::Invalid) {
        updateFigure(figure, from);
        return;
    }

    updateFigure(figure, to);
    Side side = manager->whoseTurn();

    for (const auto& f : figure_list) {
        if (turn.eaten && f->getCoords().x() == turn.eaten->first &&
            f->getCoords().y() == turn.eaten->second && 
            f->getSide() != figure->getSide()) {
            scene->removeItem(f);
            continue;
        }
        if (turn.outcome == Outcome::Mate || f->getSide() != side)
            f->setEnabled(false);
        else
            f->setEnabled(true);
    }

    updateLabel(turn.outcome, side);
}

void GraphicsView::updateFigure(QFigure *figure, const QPointF& coords) {
    figure->setCoords({coords.x(), coords.y()});
    figure->setPos(COORD_FROM_INDEX(coords.x()), COORD_FROM_INDEX(coords.y()));
}

void GraphicsView::updateLabel(Outcome outcome, Side side) {
    if (outcome == Outcome::Mate) {
        emit changeStatusLabel("<b>Check Mate! Game over.</b>");
        return;
    }

    QString whoseTurn = side == Side::White ? "White's" : "Black's";
    QString special = "";

    if (outcome == Outcome::Check) {
        special = "Check! ";
    }

    emit changeStatusLabel("<b>" + special + whoseTurn + " move.</b>");
}
