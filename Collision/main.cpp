#include "math.cpp"
#include <array>
#include <iostream>

const auto PI_OVER_4_MAT = radToMat(M_PI / 4.0);
const auto NEG_PI_OVER_4_MAT = radToMat(-M_PI / 4.0);

Vector2 rotationMatMethod(std::array<Vector2, 2> line1, std::array<Vector2, 2> line2) {
    // Ok, but what RotationMat do we use?
    // One strat: Push the line that is further away from the closest vertical towards horizontal.
    // But don't do any rotation when the lines are both very far away from vertical already.

    const double dx1 = line1[0].x - line1[1].x;
    const double dy1 = line1[0].y - line1[1].y;
    const double dx2 = line2[0].x - line2[1].x;
    const double dy2 = line2[0].y - line2[1].y;

    RotationMat mat, invMat;

    // cross multiplication comparison of the slopes
    if (std::abs(dy1 * dx2) > std::abs(dx1 * dy1)) {
        std::cout << "line1 is closer to vertical\n";
        
        if (dx2 < 0) {
            mat = PI_OVER_4_MAT;
            invMat = NEG_PI_OVER_4_MAT;
        } else {
            mat = NEG_PI_OVER_4_MAT;
            invMat = PI_OVER_4_MAT;
        }
    } else {
        std::cout << "line2 is closer to vertical\n";

        if (dx1 < 0) {
            mat = PI_OVER_4_MAT;
            invMat = NEG_PI_OVER_4_MAT;
        } else {
            mat = NEG_PI_OVER_4_MAT;
            invMat = PI_OVER_4_MAT;
        }
    }

    static auto rotateLine = [](std::array<Vector2, 2> line, RotationMat mat) -> std::array<Vector2, 2> {
        const auto pt1 = applyRotation(line[0], mat);
        const auto pt2 = applyRotation(line[1], mat);
        return { pt1, pt2 };
    };

    line1 = rotateLine(line1, mat);
    line2 = rotateLine(line2, mat);

    const auto movingPointLine = newLine(line1);
    const auto sideLine = newLine(line2);
    const double x = (movingPointLine.b - sideLine.b) / (sideLine.m - movingPointLine.m);
    const double y = sideLine.m * x + sideLine.b;

    return applyRotation({ x, y }, invMat);
}

// This is how I've been doing it so far, but it makes an assumption about veritcality and the more vertical something is without being detected as vertical, the more inaccurate the intersection is.

Vector2 verticalEdgeCaseMethod(const std::array<Vector2, 2> line1, const std::array<Vector2, 2> line2) {
    std::cout << line1[0].toString() << " " << line1[1].toString() << " " << line2[0].toString() << " " << line2[1].toString() << "\n";
     // To deal with if the side is vertical
    if (std::abs(line2[0].x - line2[1].x) / std::abs(line2[0].y - line2[1].y) < 0.01) {
        const auto movingPointLine = newLine(line1);
        const double x = line2[0].x;
        const double y = movingPointLine.m * x + movingPointLine.b;
        return { x, y };
    }

    const auto movingPointLine = newLine(line1);
    const auto sideLine = newLine(line2);
    const double x = (movingPointLine.b - sideLine.b) / (sideLine.m - movingPointLine.m);
    const double y = sideLine.m * x + sideLine.b;
    return { x, y };
}

void playingWithRotationMatrices();

int main() {
    /*
    std::cout << "The most iffy part of the rudimentary method of collision detection that I made up is the intersection of two lines.\n";
    std::cout << "Therefore this code is trying to make the intersection as mathematically sound as reasonable, since computers are not perfect calculators.\n";
    */

    // Playing with rotation matrices :P
    playingWithRotationMatrices();

    const std::array<const std::array<Vector2, 2>, 2> lineSegmentPairs[] = {
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
            { Vector2 { 0, 0 }, { 1, 1 } },
            { Vector2 { 0, 0 }, { 1, -1 } }
        },
    };

    for (const auto& lineSegmentPair : lineSegmentPairs) {
        const auto lineSegment1 = lineSegmentPair[0];
        const auto lineSegment2 = lineSegmentPair[1];

        std::cout << "verticalEdgeCaseMethod:\n";
        auto intersection = verticalEdgeCaseMethod(lineSegment1, lineSegment2);
        std::cout << "intersection at " << intersection.toString() << "\n";

        std::cout << "\nrotationMatMethod:\n";
        intersection = rotationMatMethod(lineSegment1, lineSegment2);
        std::cout << "intersection at " << intersection.toString() << "\n\n";
    }
}

void playingWithRotationMatrices() {
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
