#include "abstractfigure.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"

#include <iostream>
using namespace std;

ostream& operator<<(ostream& s, Outcome outcome) {
    if (outcome == Outcome::Eat) {
        s << "Eat";
    }
    else if (outcome == Outcome::Move) {
        s << "Move";
    }
    else {
        s << "Invalid";
    }

    return s;
}

ostream& operator<<(ostream& s, Side side) {
    if (side == Side::White) {
        s << "White";
    }
    else {
        s << "Black";
    }

    return s;
}

ostream& operator<<(ostream& s, Type type) {
    if (type == Type::Pawn)
        s << "Pawn";
    else if (type == Type::Rook)
        s << "Rook";
    else
        s << "Other";

    return s;
}

ostream& operator<<(ostream& s, std::array<std::array<AbstractFigure *, 8>, 8> field) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            if (!field[i][j])
                s << field[i][j] << " ";
            else
                s << field[i][j]->getType() <<" (" << field[i][j]->getSide() << ") ";
        }
        s << std::endl;
    }

    return s;
}

void pawnTests(void) {
    std::array<std::array<AbstractFigure *, 8>, 8> field = 
        {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
        };

    Pawn *pawn = new Pawn(std::make_pair<int, int>(1, 1), Side::White);

    field[1][1] = pawn;
    field[5][2] = new Pawn(std::make_pair<int, int>(2, 5), Side::Black);

    cout << field << std::endl << "==============" << std::endl;

    cout << pawn->move(field, std::make_pair<int, int>(1, 3)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    cout << pawn->move(field, std::make_pair<int, int>(1, 5)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    cout << pawn->move(field, std::make_pair<int, int>(2, 4)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    cout << pawn->move(field, std::make_pair<int, int>(1, 4)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    cout << pawn->move(field, std::make_pair<int, int>(2, 5)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    field = 
        {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
        };

    Pawn *white = new Pawn(std::make_pair<int, int>(0, 1), Side::White);
    Pawn *black = new Pawn(std::make_pair<int, int>(1, 3), Side::Black);

    field[1][0] = white;
    field[3][1] = black;

    cout << field << std::endl << "==============" << std::endl;

    cout << white->move(field, std::make_pair<int, int>(0, 3)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    cout << black->move(field, std::make_pair<int, int>(0, 2)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;
}

void rookTests(void) {
    std::array<std::array<AbstractFigure *, 8>, 8> field = 
        {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
        };

    Rook *white = new Rook(std::make_pair<int, int>(2, 0), Side::White);
    Rook *black = new Rook(std::make_pair<int, int>(2, 6), Side::Black);

    field[0][2] = white;
    field[6][2] = black;

    cout << field << std::endl << "==============" << std::endl;

    cout << white->move(field, std::make_pair<int, int>(2, 7)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    cout << white->move(field, std::make_pair<int, int>(2, 5)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

    cout << white->move(field, std::make_pair<int, int>(2, 6)) << std::endl;
    cout << field << std::endl << "==============" << std::endl;

}

void knightTests() {
    std::array<std::array<AbstractFigure *, 8>, 8> field = 
        {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
        };

    Knight *white = new Knight(std::make_pair<int, int>(3, 0), Side::White);
    Rook *black = new Rook(std::make_pair<int, int>(5, 5), Side::Black);

    field[0][3] = white;
    field[5][5] = black;

    cout << field << std::endl << "==============" << std::endl;
}

int main() {
    // pawnTests();
    // rookTests();
    knightTests();
}
