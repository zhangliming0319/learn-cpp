#include <iostream>
#include <memory>

// 抽象基类
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
};

// 具体形状：Circle
class Circle : public Shape {
public:
    Circle(int radius) : radius(radius) {}

    void draw() const override {
        std::cout << "Drawing a circle with radius " << radius << std::endl;
    }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }

private:
    int radius;
};

// 具体形状：Rectangle
class Rectangle : public Shape {
public:
    Rectangle(int width, int height) : width(width), height(height) {}

    void draw() const override {
        std::cout << "Drawing a rectangle with width " << width << " and height " << height << std::endl;
    }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }

private:
    int width, height;
};

int main() {
    // 创建形状对象
    std::unique_ptr<Shape> circle = std::make_unique<Circle>(5);
    std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(2, 4);

    // 创建形状副本
    std::unique_ptr<Shape> circle_copy = circle->clone();
    std::unique_ptr<Shape> rectangle_copy = rectangle->clone();

    // 绘制形状
    circle->draw();
    rectangle->draw();
    circle_copy->draw();
    rectangle_copy->draw();

    return 0;
}