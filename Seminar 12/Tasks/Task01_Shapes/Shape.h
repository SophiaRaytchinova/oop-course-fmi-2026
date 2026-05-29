#pragma once
#include <iostream>
#include <vector>

class Shape {
public:
    explicit Shape(size_t pointsCount);

    void setPoint(size_t index, int x, int y);

    virtual double getArea() const = 0;
    virtual double getPerimeter() const;
    virtual bool isPointInside(int x, int y) const = 0;
    virtual ~Shape() = default;

protected:
    struct Point {
        int x = 0;
        int y = 0;

        Point() = default;
        Point(int x, int y);

        double getDistanceTo(const Point& other) const;
    };

    const Point& getPointAtIndex(size_t index) const;

private:
    std::vector<Point> points;
};
