#include "gamewindow.h"

GameWindow::GameWindow() {
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    graphics_view = new GraphicsView(central_widget);

    layout = new QGridLayout(central_widget);

    button_back_to_menu = new QPushButton("Back to menu", central_widget);
    button_restart = new QPushButton("Restart", central_widget);
    label_status = new QLabel("<b>White's move</b>");
    label_pl1 = new QLabel("Player 1", central_widget);
    label_pl2 = new QLabel("Player 2", central_widget);

    label_status->setTextFormat(Qt::RichText);
    label_status->setObjectName("label_status");

    layout->addWidget(button_back_to_menu, 0, 0, 1, 1);
    layout->addWidget(button_restart, 0, 1, 1, 1);
    layout->addWidget(label_status, 1, 0, 1, 1);
    layout->addWidget(label_pl2, 2, 0, 1, 1);
    layout->addWidget(graphics_view, 3, 0, 2, 2);
    layout->addWidget(label_pl1, 5, 0, 1, 1);

    QObject::connect(graphics_view, SIGNAL(changeStatusLabel(const QString&)), SLOT(changeStatusLabel(const QString&)));
}

GameWindow::~GameWindow() {
    delete central_widget;
}

void GameWindow::changeStatusLabel(const QString& new_label) {
    label_status->setText(new_label);
}
