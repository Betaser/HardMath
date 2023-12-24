#include "math.cpp"
#include <array>
#include <iostream>

Vector2 rotationMatMethod(const std::array<Vector2, 2> p1, const std::array<Vector2, 2> p2) {
    std::cout << p1[0].toString() << " " << p1[1].toString() << " " << p2[0].toString() << " " << p2[1].toString() << "\n";
     // To deal with if the side is vertical
     if (std::abs(p2[0].x - p2[1].x) / std::abs(p2[0].y - p2[1].y) < 0.01) {
         const auto movingPointLine = newLine(p1);
         const double x = p2[0].x;
         const double y = movingPointLine.m * x + movingPointLine.b;
         return { x, y };
     }

     const auto movingPointLine = newLine(p1);
     const auto sideLine = newLine(p2);
     const double x = (movingPointLine.b - sideLine.b) / (sideLine.m - movingPointLine.m);
     const double y = sideLine.m * x + sideLine.b;
     return { x, y };
}

int main() {
    std::cout << toString(radToMat(M_PI / 2.0)) << "\n";
    std::cout << "The most iffy part of the rudimentary method of collision detection that I made up is the intersection of two lines.\n";
    std::cout << "Therefore this code is trying to make the intersection as mathematically sound as reasonable, since computers are not perfect calculators.\n";

    const std::array<Vector2, 2> lineSegment1 = {
        Vector2 { 0, 0 },
        { 6, 8 }
    };
    const std::array<Vector2, 2> lineSegment2 = {
        Vector2 { 3, -4 },
        { 3, 5.1 }
    };
    // lineSegment1 is a 6 8 10 triangle.
    // lineSegment2 is a vertical line intersecting with its halfway, 3 4 5.
    const auto intersection = rotationMatMethod(lineSegment1, lineSegment2);
    std::cout << "intersection at " << intersection.toString() << "\n";
}
