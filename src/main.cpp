#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;

    QFile File(":/style.qss");
    QString StyleSheet;
    File.open(QFile::ReadOnly);
    StyleSheet = QLatin1String(File.readAll());
    a.setStyleSheet(StyleSheet);

    w.setMaximumWidth(TILE_SIZE * 8 + 25);
    w.setMinimumHeight(TILE_SIZE * 8 + 180);
    w.show();

    return a.exec();
}
