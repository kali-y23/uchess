#include "pawn.h"

#include <iostream>

Pawn::Pawn(const std::pair<int, int>& coordinates, enum Side side) : AbstractFigure(Type::Pawn, coordinates, side) {}

Turn Pawn::checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                        const std::pair<int, int>& coords) {
    if (coords.first > 7 || coords.second > 7)
        return {Outcome::Invalid, nullptr};
    
    int sign = m_side == Side::Black ? 1 : -1;

    m_first_turn = false;
    if (field[coords.second][coords.first] == nullptr && coords.first == m_coords.first) {
        // basic turn, one step forward
        if (coords.second == m_coords.second + sign)
            return {Outcome::Move, nullptr};
        // initial turn, two steps ahead, for a black pawn
        else if (m_coords.second == 1 && coords.second == m_coords.second + (2 * sign) && !field[m_coords.second + sign][m_coords.first]) {
            m_first_turn = true;
            return {Outcome::Move, nullptr};
        }
        // initial turn, two steps ahead, for a white pawn
        else if (m_coords.second == 6 && coords.second == m_coords.second + (2 * sign) && !field[m_coords.second + sign][m_coords.first]) {
            m_first_turn = true;
            return {Outcome::Move, nullptr};
        }
    }
    // pawn eats a figure
    else if (field[coords.second][coords.first] && field[coords.second][coords.first]->getSide() != getSide()) {
        if (coords.second == m_coords.second + (1 * sign) &&
            (coords.first == m_coords.first + 1 || coords.first == m_coords.first - 1))
            return {Outcome::Eat, &coords};
    }
    else {
        const std::pair<int, int> *eaten_coords = enPassant(field, coords);
        if (eaten_coords)
            return {Outcome::Eat, eaten_coords};
    }
    return {Outcome::Invalid, nullptr};
}

void Pawn::setType(enum Type type) {
    m_type = type;
}

bool Pawn::getFirstTurn() const {
    return m_first_turn;
}

const std::pair<int, int> *Pawn::enPassant(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                      const std::pair<int, int>& coords) {
    Pawn *pawn = nullptr;
    int sign = m_side == Side::Black ? -1 : 1;

    // check if there's another pawn next to this pawn
    if (m_coords.first > 0 && field[m_coords.second][m_coords.first + 1]
        && field[m_coords.second][m_coords.first + 1]->getType() == Type::Pawn) {
        pawn = reinterpret_cast<Pawn *>(field[m_coords.second][m_coords.first + 1]);
    }
    else if (m_coords.first < 7 && field[m_coords.second][m_coords.first - 1]
             && field[m_coords.second][m_coords.first - 1]->getType() == Type::Pawn) {
        pawn = reinterpret_cast<Pawn *>(field[m_coords.second][m_coords.first - 1]);
    }

    if (!pawn)
        return nullptr;

    // check if the pawn has made more than one turn and the two pawns are on opposide sides    
    if (!pawn->getFirstTurn() || pawn->getSide() == m_side)
        return nullptr;

    // make sure this pawn makes a turn to beat another pawn
    if (coords.first == pawn->getCoords().first
        && coords.second + sign == pawn->getCoords().second) {
        const std::pair<int, int> *eaten_coords = new std::pair<int, int>(pawn->getCoords());

        return eaten_coords;
    }

    return nullptr;
}
