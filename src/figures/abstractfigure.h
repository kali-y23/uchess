#pragma once

#include <utility>
#include <array>
#include <memory>
#include <iostream>

enum class Type {
    Pawn, // Пешка
    Rook, // Ладья
    Knight, // Конь
    Bishop, // Офицер
    Queen, // Ферзь
    King // Король
};

enum class Side {
    White,
    Black
};

enum class Outcome {
    Invalid,
    Check,
    Mate,
    Move,
    Eat,
    Castles
};

struct Turn {
    Outcome outcome;
    const std::pair<int, int> *eaten; // coords of the figure that was eaten
};

class AbstractFigure {
protected:
    std::pair<int, int> m_coords;
    enum Type m_type;
    const enum Side m_side;
    
public:
    AbstractFigure(Type type, const std::pair<int, int>& coordinates, enum Side side);
    virtual ~AbstractFigure() {};

    virtual Turn move(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                         const std::pair<int, int>& coords);
    virtual Turn checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                            const std::pair<int, int>& coords) = 0;
    Side getSide() const;
    Type getType() const;
    std::pair<int, int> getCoords() const;
    bool checkObstacles(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                        std::pair<int, int> move_vector, std::pair<int, int> coords) const;
};
