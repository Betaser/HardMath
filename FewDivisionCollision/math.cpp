#include <string>

typedef struct Vector2 {
    double x, y;

    const Vector2 plus(const Vector2 vector) {
        return { x + vector.x, y + vector.y };
    }

    const Vector2 minus(const Vector2 vector) {
        return { x - vector.x, y - vector.y };
    }

    std::string toString() const {
        char buf[100];
        sprintf(buf, "<%.3f, %.3f>", x, y);
        return { buf };
    }
} Vector2;
