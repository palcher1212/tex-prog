#include <iostream>
#include <cmath>
using namespace std;

// Абстрактный базовый класс Точка
class Point {
protected:
    double x, y; // Координаты точки
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    virtual ~Point() {}

    // Чисто виртуальные методы
    virtual void draw() const = 0;    // Нарисовать фигуру
    virtual void erase() const = 0;   // Стереть фигуру
    virtual void move(double dx, double dy) = 0; // Переместить
};

// Класс Vert, реализующий методы Point
class Vert : public Point {
public:
    Vert(double x = 0, double y = 0) : Point(x, y) {}

    void draw() const override {
        cout << "Рисуем точку в (" << x << "," << y << ")\n";
    }

    void erase() const override {
        cout << "Стираем точку из (" << x << "," << y << ")\n";
    }

    void move(double dx, double dy) override {
        x += dx; y += dy;
        cout << "Переместили точку на (" << dx << "," << dy << ")\n";
    }
};

// Базовый класс для всех фигур
class Shape {
public:
    Shape() {}

    // Виртуальный метод поворота
    virtual void rotate(double angle) {
        cout << "Поворот фигуры на " << angle << " градусов\n";
    }
};

// Класс Линия (наследуется от Shape)
class Line : public Shape {
protected:
    Vert start; // Начальная точка
    Vert end;   // Конечная точка
public:
    Line(double x1, double y1, double x2, double y2)
        : start(x1, y1), end(x2, y2) {}

    void draw() const {
        cout << "Рисуем линию от (" << start.x << "," << start.y
             << ") до (" << end.x << "," << end.y << ")\n";
    }

    void erase() const {
        cout << "Стираем линию от (" << start.x << "," << start.y
             << ") до (" << end.x << "," << end.y << ")\n";
    }

    void move(double dx, double dy) {
        start.move(dx, dy);
        end.move(dx, dy);
        cout << "Переместили линию на (" << dx << "," << dy << ")\n";
    }
};

// Класс Параллелограмм (наследуется от Shape)
class Parallelogram : public Shape {
protected:
    Vert topLeft;
    double side1, side2; // Длины сторон
public:
    Parallelogram(double x, double y, double s1, double s2)
        : topLeft(x, y), side1(s1), side2(s2) {}

    void draw() const {
        cout << "Рисуем параллелограмм в точке (" << topLeft.x << "," << topLeft.y
             << ") со сторонами " << side1 << " и " << side2 << endl;
    }

    void erase() const {
        cout << "Стираем параллелограмм из точки (" << topLeft.x << "," << topLeft.y << ")\n";
    }

    void move(double dx, double dy) {
        topLeft.move(dx, dy);
        cout << "Переместили параллелограмм на (" << dx << "," << dy << ")\n";
    }

    void rotate(double angle) override {
        // Преобразуем угол в радианы
        double rad = angle * M_PI / 180.0;

        // Центр фигуры
        double centerX = topLeft.x + side1 / 2;
        double centerY = topLeft.y + side2 / 2;

        // Поворачиваем каждую точку
        double newX = centerX + (topLeft.x - centerX) * cos(rad) - (topLeft.y - centerY) * sin(rad);
        double newY = centerY + (topLeft.x - centerX) * sin(rad) + (topLeft.y - centerY) * cos(rad);

        topLeft.x = newX;
        topLeft.y = newY;

        cout << "Повернули параллелограмм на " << angle << " градусов\n";
    }
};

// Класс Ромб (наследуется от Параллелограмма)
class Rhombus : public Parallelogram {
public:
    Rhombus(double x, double y, double side)
        : Parallelogram(x, y, side, side) {}

    void draw() const {
        cout << "Рисуем ромб в точке (" << topLeft.x << "," << topLeft.y
             << ") со стороной " << side1 << endl;
    }
};

// Класс Прямоугольник (наследуется от Параллелограмма)
class Rectangle : public Parallelogram {
public:
    Rectangle(double x, double y, double width, double height)
        : Parallelogram(x, y, width, height) {}

    void draw() const {
        cout << "Рисуем прямоугольник в точке (" << topLeft.x << "," << topLeft.y
             << ") шириной " << side1 << " и высотой " << side2 << endl;
    }
};

// Класс Квадрат (наследуется от Прямоугольника)
class Square : public Rectangle {
public:
    Square(double x, double y, double side)
        : Rectangle(x, y, side, side) {}

    void draw() const {
        cout << "Рисуем квадрат в точке (" << topLeft.x << "," << topLeft.y
             << ") со стороной " << side1 << endl;
    }
};

// Демонстрация работы с фигурами
void demo(Shape* shape) {
    shape->draw();
    shape->move(2, 3);
    shape->rotate(45);
    shape->erase();
    cout << "--------\n";
}

int main() {
    // Создаем фигуры
    Line line(0, 0, 4, 0);
    Parallelogram para(1, 1, 5, 3);
    Rhombus rhomb(2, 2, 4);
    Rectangle rect(3, 3, 6, 4);
    Square square(4, 4, 5);

    // Массив указателей на базовый класс
    Shape* shapes[] = {&line, &para, &rhomb, &rect, &square};

    // Демонстрация работы с фигурами
    for (Shape* shape : shapes) {
        demo(shape);
    }

    return 0;
}
