#include <array>
#include <iostream>
#include <string>

typedef struct Vector2 {
    double x;
    double y;

    const Vector2 plus(Vector2 vector) {
        return Vector2 { x + vector.x, y + vector.y }; 
    }

    const Vector2 minus(Vector2 vector) {
        return Vector2 { x - vector.x, y - vector.y };
    }

    const Vector2 clone() {
        return Vector2 { x, y };
    }

    std::string toString() const {
        char sprinted[100];
        sprintf(sprinted, "<%.3f, %.3f>", x, y);
        return std::string(sprinted);
    }
} Vector2;

typedef struct Line {
    double m;
    double b;

    std::string toString() const {
        char sprinted[100];
        sprintf(sprinted, "m = %.3f, b = %.3f", m, b);
        return std::string(sprinted);
    }
} Line;

Line newLine(std::array<Vector2, 2> twoPoints) {
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