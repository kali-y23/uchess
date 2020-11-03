#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QResource>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFile>
#include <QList>
#include <QPointF>

#include <array>
#include <cmath>

#include "graphicsview.h"
#include "abstractfigure.h"

class GraphicsView;

#define TILE_SIZE 80

class GameWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *central_widget;
    GraphicsView *graphics_view;
    QGridLayout *layout;
    QPushButton *button_back_to_menu;
    QPushButton *button_restart;
    QLabel *label_status;
    QLabel *label_pl1;
    QLabel *label_pl2;

public:
    GameWindow();
    ~GameWindow();

public slots:
    void changeStatusLabel(const QString& new_label);
};