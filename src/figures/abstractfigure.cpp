#include "abstractfigure.h"

#include <iostream>

AbstractFigure::AbstractFigure(Type type, const std::pair<int, int>& coordinates, enum Side side) : m_side(side) {
    m_coords = coordinates;
    m_type = type;
}

enum Side AbstractFigure::getSide() const {
    return m_side;
}

enum Type AbstractFigure::getType() const {
    return m_type;
}

std::pair<int, int> AbstractFigure::getCoords() const {
    return m_coords;
}

Turn AbstractFigure::move(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                             const std::pair<int, int>& coords) {
    Turn outcome = checkMove(field, coords);

    if (outcome.outcome == Outcome::Invalid)
        return outcome;

    if (outcome.outcome == Outcome::Eat) {
        delete field[outcome.eaten->second][outcome.eaten->first];
        field[outcome.eaten->second][outcome.eaten->first] = nullptr;
    }

    field[coords.second][coords.first] = this;
    field[m_coords.second][m_coords.first] = nullptr;

    m_coords = coords;

    return outcome;
}

bool AbstractFigure::checkObstacles(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                    std::pair<int, int> move_vector, std::pair<int, int> coords) const {
    int x_coord = m_coords.first + move_vector.first;
    int y_coord = m_coords.second + move_vector.second;

    while (x_coord != coords.first || y_coord != coords.second) {
        if (field[y_coord][x_coord])
            return false;

        x_coord += move_vector.first;
        y_coord += move_vector.second;
    }

    return true;
}
