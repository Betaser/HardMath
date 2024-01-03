#include "math.cpp"
#include <array>
#include <iostream>

constexpr bool bigSlopeFirst(const Vector2 lineSeg1, const Vector2 lineSeg2) {
    // y1/x1 cmp y2/x2, use cross product.
    return lineSeg1.y * lineSeg2.x >= lineSeg2.y * lineSeg1.x;
}

bool isIntersecting(std::array<Vector2, 2> movingPointSeg, std::array<Vector2, 2> lineSeg) {
    const Vector2 displacement = movingPointSeg[1].minus(movingPointSeg[0]); 
    const Vector2 toDispHead1 = movingPointSeg[1].minus(lineSeg[0]);
    const Vector2 toDispHead2 = movingPointSeg[1].minus(lineSeg[1]);
    return bigSlopeFirst(toDispHead1, displacement) == bigSlopeFirst(displacement, toDispHead2);
}

int main() {
    const std::array<const std::array<Vector2, 2>, 2> lineSegPairs[] = {
        {
            std::array<Vector2, 2>
            { Vector2 { 0, 0 }, { 6, 8 } },
            { Vector2 { 3, -4 }, { 3, 5.1 } }
        },
        {
            std::array<Vector2, 2>
            { Vector2 { 0, 0 }, { 1, 1 } },
            { Vector2 { 1, -1 }, { 0, 0 } }
        },
        {
            std::array<Vector2, 2>
            { Vector2 { 0, 0 }, { -1, -1 } },
            { Vector2 { -1.5, -1 }, { -0.1, 0 } }
        }
    }; 

    for (const auto& lineSegPair : lineSegPairs) {
        const auto lineSeg1 = lineSegPair[0];
        const auto lineSeg2 = lineSegPair[1];

        bool intersecting;

        std::cout << "isIntersecting for " << 
            lineSeg1[0].toString() << " to " << lineSeg1[1].toString() << 
            " and " <<
            lineSeg2[0].toString() << " to " << lineSeg2[1].toString() << 
            ": " << (
            intersecting = isIntersecting(lineSeg1, lineSeg2),
            intersecting ? "true" : "false"
        ) << "\n";
    }
}
