#include <cmath>
#include <array>
#include <iostream>
#include <string>

typedef struct Vector2 {
    double x;
    double y;

    const Vector2 plus(const Vector2 vector) {
        return Vector2 { x + vector.x, y + vector.y }; 
    }

    const Vector2 minus(const Vector2 vector) {
        return Vector2 { x - vector.x, y - vector.y };
    }

    const Vector2 clone() {
        return Vector2 { x, y };
    }

    std::string toString() const {
        char sprinted[100];
        sprintf(sprinted, "<%.3f, %.3f>", x, y);
        return { sprinted };
    }
} Vector2;

typedef struct Line {
    double m;
    double b;

    std::string toString() const {
        char sprinted[100];
        sprintf(sprinted, "m = %.3f, b = %.3f", m, b);
        return { sprinted };
    }
} Line;

typedef std::array<std::array<double, 2>, 2> RotationMat;

RotationMat radToMat(const double rad) {
    RotationMat mat;
    mat[0][0] = std::cos(rad);
    mat[1][0] = -std::sin(rad);
    mat[0][1] = std::sin(rad);
    mat[1][1] = std::cos(rad);
    return mat;
}

const Vector2 applyRotation(const Vector2 toThis, const RotationMat mat) {
    return {
        toThis.x * mat[0][0] + toThis.y * mat[1][0],
        toThis.x * mat[0][1] + toThis.y * mat[1][1]
    };
}

std::string toString(const RotationMat mat) {
    char sprinted[100];
    sprintf(sprinted,
        "[ [%.3f] [%.3f]\n  [%.3f] [%.3f] ]",
        mat[0][0],
        mat[1][0],
        mat[0][1],
        mat[1][1]);
    return { sprinted };
}

Line newLine(const std::array<Vector2, 2> twoPoints) {
    const auto p1 = twoPoints[0];
    const auto p2 = twoPoints[1];

    const auto m = (p2.y - p1.y) / (p2.x - p1.x);
    const auto b = p1.y - m * p1.x;
    return { m, b };
}

/*
int main() {
    std::array<Vector2, 2> points = { Vector2 {0, 1}, {2, 3} };
    const auto line = newLine(points);
    for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++) {
        std::cout << points[i].toString() << "\n";
    }
    std::cout << line.toString() << "\n";
}
*/
