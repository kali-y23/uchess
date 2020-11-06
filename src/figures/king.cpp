#include "king.h"

#include <iostream>

King::King(const std::pair<int, int>& coordinates, enum Side side) : AbstractFigure(Type::King, coordinates, side) {
    madeTurn =  false;
}

Turn King::checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                          const std::pair<int, int>& coords) {
    if (coords.first > 7 || coords.second > 7)
        return {Outcome::Invalid, nullptr};

    if (std::abs(coords.first - m_coords.first) <= 1 && std::abs(coords.second - m_coords.second) <= 1) {
        if (field[coords.second][coords.first] && field[coords.second][coords.first]->getSide() != m_side) {
            madeTurn = true;
            return {Outcome::Eat, &coords};
        } 
        else if (!field[coords.second][coords.first]) {
            madeTurn = true;
            return {Outcome::Move, nullptr};
        }
    }
    else if (coords.second == m_coords.second && std::abs(coords.first - m_coords.first) == 2) {
        int *sign;
        std::pair<int, int> rook_coords = checkCastling(field, coords, sign);

        if (rook_coords.first != -1) {
            Rook *rook = reinterpret_cast<Rook *>(field[rook_coords.second][rook_coords.first]);
            rook->setCoords({m_coords.first + *sign, m_coords.second});
            rook->madeTurn = true;
            field[rook_coords.second][rook_coords.first] = nullptr;
            field[m_coords.second][m_coords.first + *sign] = rook;

            return {Outcome::Castles, new std::pair<int, int>(rook_coords)};
        }
    }

    return {Outcome::Invalid, nullptr};
}

std::pair<int, int> King::checkCastling(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                        std::pair<int, int> to, int *sign) {
    int king_y = m_coords.second;
    *sign = to.first > m_coords.first ? 1 : -1;
    std::pair<int, int> rook_coords = to.first > m_coords.first ? std::make_pair<int, int>(7, std::move(king_y))
                                                                : std::make_pair<int, int>(0, std::move(king_y));

    if (!field[rook_coords.second][rook_coords.first] || field[rook_coords.second][rook_coords.first]->getType() != Type::Rook)
        return {-1, -1};

    Rook *rook = reinterpret_cast<Rook *>(field[rook_coords.second][rook_coords.first]);

    if (rook->madeTurn || madeTurn)
        return {-1, -1};
    if (!rook->checkObstacles(field, rook->makeMoveVector(m_coords), m_coords))
        return {-1, -1};
    if (!checkCheckWrapper(field, m_coords, m_coords).empty() ||
        !checkCheckWrapper(field, m_coords, {m_coords.first + *sign, m_coords.second}).empty() ||
        !checkCheckWrapper(field, m_coords, {m_coords.first + (2 * *sign), m_coords.second}).empty()) {
        return {-1, -1};
    }
    return rook->getCoords();
}

std::vector<AbstractFigure *> King::checkCheckWrapper(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                                      const std::pair<int, int>& from,
                                                      const std::pair<int, int>& to) {
    AbstractFigure *figure_from = field[from.second][from.first];
    AbstractFigure *figure_to = field[to.second][to.first];
    std::pair<int, int> king_coords = figure_from->getType() == Type::King ? to : m_coords;

    field[from.second][from.first] = nullptr;
    field[to.second][to.first] = figure_from;

    std::vector<AbstractFigure *> check_figures = checkCheck(field, king_coords);

    field[from.second][from.first] = figure_from;
    field[to.second][to.first] = figure_to;

    return check_figures;
}

std::vector<AbstractFigure *> King::checkCheck(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                               const std::pair<int, int>& king_coords) {
    Turn turn;
    std::vector<AbstractFigure *> check_figures;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            AbstractFigure *figure = field[i][j];

            if (figure && figure->getSide() != m_side) {
                turn = figure->checkMove(field, king_coords);

                if (turn.outcome == Outcome::Eat)
                    check_figures.push_back(figure);
            }
        }
    }

    return check_figures;
}


