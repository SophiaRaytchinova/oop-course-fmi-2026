#include "Shape.h"

Shape::Point::Point(int x, int y) : x(x), y(y) {}

double Shape::Point::getDistanceTo(const Point& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}

Shape::Shape(size_t pointsCount) {
    points.reserve(pointsCount);
}

void Shape::setPoint(size_t index, int x, int y) {
    if (index >= points.size()) {
        throw std::out_of_range("Index out of range!");
    }
    points[index].x = x;
    points[index].y = y;
}

double Shape::getPerimeter() const {
    if (points.size() < 3) {
        return 0.0;
    }
    double perimeter = 0;
    for (size_t i = 0; i < points.size() - 1; i++) {
        perimeter += points[i].getDistanceTo(points[i + 1]);
    }
    return perimeter + points[points.size() - 1].getDistanceTo(points[0]);
}

const Shape::Point& Shape::getPointAtIndex(size_t index) const {
    if (index >= points.size()) {
        throw std::out_of_range("Index out of range!");
    }
    return points[index];
}
