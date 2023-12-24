#include "math.cpp"
#include <array>
#include <iostream>

Vector2 rotationMatMethod(const std::array<Vector2, 2> p1, const std::array<Vector2, 2> p2) {
     const auto movingPointLine = newLine(p1);
     const auto sideLine = newLine(p2);
     const double x = (movingPointLine.b - sideLine.b) / (sideLine.m - movingPointLine.m);
     const double y = sideLine.m * x + sideLine.b;
     return { x, y };
}

// This is how I've been doing it so far, but it makes an assumption about veritcality and the more vertical something is without being detected as vertical, the more inaccurate the intersection is.

Vector2 verticalEdgeCaseMethod(const std::array<Vector2, 2> p1, const std::array<Vector2, 2> p2) {
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

const auto PI_OVER_4_MAT = radToMat(M_PI / 4.0);
const auto NEG_PI_OVER_4_MAT = radToMat(-M_PI / 4.0);

int main() {
    /*
    std::cout << "The most iffy part of the rudimentary method of collision detection that I made up is the intersection of two lines.\n";
    std::cout << "Therefore this code is trying to make the intersection as mathematically sound as reasonable, since computers are not perfect calculators.\n";
    */

    // Playing with rotation matrices :P
    {
        const std::array<Vector2, 2> lineSegments[] = {
            {
                Vector2 { 0, 0 },
                { 1, 0 }
            },
            {
                Vector2 { 0, 0 },
                { 0, 1 }
            },
            {
                Vector2 { 0, 1 },
                { 0, 0 }
            },
            {
                Vector2 { 0, 0 },
                { 0.707, 0.707 }
            },
        };
        for (const auto& lineSegment : lineSegments) {
            auto printLineSegment = [&lineSegment](const std::array<Vector2, 2>* segment = nullptr) {
                if (segment == nullptr) {
                    segment = &lineSegment;
                }
                std::cout << (*segment)[0].toString() << " " << (*segment)[1].toString() << "\n";
            };
            std::cout << "line segment ";
            printLineSegment();
            std::cout << "PI_OVER_4_MAT\n" << toString(PI_OVER_4_MAT) << "\n";

            // rotate that segment!
            {
                /*
                [0] [1 0]
                [1] [0 -1]
                 */
                const auto pt1 = applyRotation(lineSegment[0], PI_OVER_4_MAT);
                const auto pt2 = applyRotation(lineSegment[1], PI_OVER_4_MAT);
                const std::array<Vector2, 2> rotatedLineSegment = { pt1, pt2 };

                std::cout << "rotated lineSegment ";
                printLineSegment(&rotatedLineSegment);
                std::cout << "\n";
            }

            std::cout << "NEG_PI_OVER_4_MAT\n" << toString(NEG_PI_OVER_4_MAT) << "\n";
            const auto pt1 = applyRotation(lineSegment[0], NEG_PI_OVER_4_MAT);
            const auto pt2 = applyRotation(lineSegment[1], NEG_PI_OVER_4_MAT);
            const std::array<Vector2, 2> rotatedLineSegment = { pt1, pt2 };

            std::cout << "rotated lineSegment ";
            printLineSegment(&rotatedLineSegment);
            std::cout << "\n";
        }
    }

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
    const auto intersection = verticalEdgeCaseMethod(lineSegment1, lineSegment2);
    std::cout << "intersection at " << intersection.toString() << "\n";
}
