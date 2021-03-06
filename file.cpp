#include <cmath>
#include <vector>
#include <memory>
#include <optional>
#include <iostream>

//static_cast - преобразование данных
//
//optional - данные, которые могут передаваться, а могут не передаваться
//
//unique_ptr - ля управления любым динамически выделенным объектом/ресурсом, 
//но с условием, что std::unique_ptr полностью владеет переданным ему объектом, а не делится «владением» еще с другими классами.
//
//constexpr - создавать переменные, функции и даже объекты, которые будут рассчитаны на этапе компиляции.





constexpr float pi() {
    return 4.0f * std::atan(1.0f);
}

class Point {
public:
    virtual ~Point() {}
    virtual void print() const = 0;
    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getZ() const {};
};

class Point2D : public Point {
protected:
    float m_x;
    float m_y;

public:
    Point2D(float x, float y) :
        m_x(x),
        m_y(y)
    {std::cout<<"Constructor called"<<std::endl;}

    Point2D(const Point2D& src) : Point2D(src.m_x, src.m_y) {std::cout<<"Constructor called"<<std::endl;}

    virtual ~Point2D() {std::cout<<"destructor called"<<std::endl;}

    virtual void print() const override {
        std::cout << m_x << "; " << m_y << std::endl;
    }

    float distance(const Point2D& other) const {
        return std::sqrt(
            (other.m_x - m_x) * (other.m_x - m_x) + 
            (other.m_y - m_y) * (other.m_y - m_y)
        );
    }

    virtual float getX() const { return m_x; };
    virtual float getY() const { return m_y; };
    //float getZ() const = delete;
};

class Point3D : public Point {
protected:
    float m_x;
    float m_y;
    float m_z;

public:
    Point3D(float x, float y, float z) :
        m_x(x),
        m_y(y),
        m_z(z)
    {}

    Point3D(const Point3D& src) : Point3D(src.m_x, src.m_y, src.m_z) {}

    virtual ~Point3D() {}

    virtual void print() const override {
        std::cout << m_x << "; " << m_y << "; " << m_z << std::endl;
    }

    float distance(const Point3D& other) const {
        return std::sqrt(
            (other.m_x - m_x) * (other.m_x - m_x) + 
            (other.m_y - m_y) * (other.m_y - m_y) +
            (other.m_z - m_z) * (other.m_z - m_z)
        );
    }
    virtual float getX() const { return m_x; };
    virtual float getY() const { return m_y; };
    virtual float getZ() const { return m_z; };
};

class Figure {
protected:
    std::vector<std::unique_ptr<Point>> m_points;
    std::string m_name;

public:
    virtual ~Figure() {}

    virtual std::optional<float> getPerimeter() const { return std::nullopt; };
    virtual std::optional<float> getSquare() const { return std::nullopt; };
    virtual std::optional<float> getVolume() const { return std::nullopt; };

    void print() const {
        for (const auto& point : m_points) {
            point->print();
        }
    }

    const std::vector<std::unique_ptr<Point>>& getPoints() const {
        return m_points;
    }

    const std::string& getName() const {
        return m_name;
    }
    float getX(int pos) const {
        float x = m_points[pos]->getX();
        return x;
    }
    float getY(int pos) const {
        float x = m_points[pos]->getY();
        return x;
    }
    float getZ(int pos) const {
        float x = m_points[pos]->getZ();
        return x;
    }

};

class Triangle : public Figure {
private:
    float getSegmentA() const {
        return static_cast<Point2D&>(*m_points[0]).distance(static_cast<Point2D&>(*m_points[1]));
    }

    float getSegmentB() const {
        return static_cast<Point2D&>(*m_points[1]).distance(static_cast<Point2D&>(*m_points[2]));
    }

    float getSegmentC() const {
        return static_cast<Point2D&>(*m_points[2]).distance(static_cast<Point2D&>(*m_points[0]));
    }

public:
    Triangle(const Point2D& p1, const Point2D& p2, const Point2D& p3) {
        m_name = "triangle";
        m_points.push_back(std::make_unique<Point2D>(p1));
        m_points.push_back(std::make_unique<Point2D>(p2));
        m_points.push_back(std::make_unique<Point2D>(p3));
    }

    virtual ~Triangle() {}

    virtual std::optional<float> getPerimeter() const override {
        return getSegmentA() + getSegmentB() + getSegmentC();
    }

    virtual std::optional<float> getSquare() const override {
        float a = getSegmentA();
        float b = getSegmentC();
        float c = getSegmentB();
        float p = 0.5f * (a + b + c);

        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class Rectangle: public Figure{
private:
    float getSegmentA() const{
        return static_cast<Point2D&>(*m_points[0]).distance(static_cast<Point2D&>(*m_points[1]));
    }
    float getSegmentB() const{
        return static_cast<Point2D&>(*m_points[1]).distance(static_cast<Point2D&>(*m_points[2]));
    }
public:
    Rectangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4){
        m_name = "rectangle";
        m_points.push_back(std::make_unique<Point2D>(p1));
        m_points.push_back(std::make_unique<Point2D>(p2));
        m_points.push_back(std::make_unique<Point2D>(p3));
        m_points.push_back(std::make_unique<Point2D>(p4));
    }

    virtual ~Rectangle(){}

    virtual std::optional<float> getPerimeter() const override {
        return 2*(getSegmentA() + getSegmentB());
    }
    virtual std::optional<float> getSquare() const override {
        return getSegmentA() * getSegmentB();
    }
};

class Circle : public Figure {
private:
    float getRadius() const {
        return static_cast<Point2D&>(*m_points[0]).distance(static_cast<Point2D&>(*m_points[1]));
    }

public:
    Circle(const Point2D& p1, const Point2D& p2) {
        m_name = "circle";
        m_points.push_back(std::make_unique<Point2D>(p1));
        m_points.push_back(std::make_unique<Point2D>(p2));
    }

    virtual std::optional<float> getPerimeter() const override {
        return 2.0f * pi() * getRadius();
    }

    virtual std::optional<float> getSquare() const override {
        float r = getRadius();
        return pi() * r * r;
    }
};

class Sphere : public Figure {
private:
    float getRadius() const {
        return static_cast<Point3D&>(*m_points[0]).distance(static_cast<Point3D&>(*m_points[1]));
    }

public:
    Sphere(const Point3D& p1, const Point3D& p2) {
        m_name = "sphere";
        m_points.push_back(std::make_unique<Point3D>(p1));
        m_points.push_back(std::make_unique<Point3D>(p2));
    }

    virtual std::optional<float> getSquare() const override {
        float r = getRadius();
        return 4.0f * pi() * r * r;
    }

    virtual std::optional<float> getVolume() const override {
        float r = getRadius();
        return 4.0f/ 3.0f * pi() * r * r * r;
    }
};

class Tetrahedron : public Figure {
private:
    float getSegmentA() const {
        return static_cast<Point3D&>(*m_points[0]).distance(static_cast<Point3D&>(*m_points[1]));
    }

    float getSegmentB() const {
        return static_cast<Point3D&>(*m_points[1]).distance(static_cast<Point3D&>(*m_points[2]));
    }

    float getSegmentC() const {
        return static_cast<Point3D&>(*m_points[2]).distance(static_cast<Point3D&>(*m_points[0]));
    }
    
    float getSegmentD() const {
        return static_cast<Point3D&>(*m_points[0]).distance(static_cast<Point3D&>(*m_points[3]));
    }

    float getSegmentE() const {
        return static_cast<Point3D&>(*m_points[1]).distance(static_cast<Point3D&>(*m_points[3]));
    }

    float getSegmentF() const {
        return static_cast<Point3D&>(*m_points[2]).distance(static_cast<Point3D&>(*m_points[3]));
    }

    float getDeterminant() const {
        float a[3][3] = {
        {this->getX(1)-this->getX(0),this->getY(1)-this->getY(0),this->getZ(1)-this->getZ(0)},
        {this->getX(2)-this->getX(1),this->getY(2)-this->getY(1),this->getZ(2)-this->getZ(1)},
        {this->getX(3)-this->getX(2),this->getY(3)-this->getY(2),this->getZ(3)-this->getZ(2)}
    };

    float d; // определитель
    
    // находим по правилу треугольника
    d=((a[0][0]*a[1][1]*a[2][2]) + (a[0][1]*a[1][2]*a[2][0])+ (a[1][0]*a[0][2]*a[2][1]) - (a[2][0]*a[1][1]*a[0][2]) - (a[0][0]*a[2][1]*a[1][2]) - (a[1][0]*a[0][1]*a[2][2]));
    return d/6.0f;
    }
public:
    Tetrahedron(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4) {
        m_name = "tetrahedron";
        m_points.push_back(std::make_unique<Point3D>(p1));
        m_points.push_back(std::make_unique<Point3D>(p2));
        m_points.push_back(std::make_unique<Point3D>(p3));
        m_points.push_back(std::make_unique<Point3D>(p4));
    }

    virtual std::optional<float> getVolume() const override {
    float a[3][3] = {
        {this->getX(1)-this->getX(0),this->getY(1)-this->getY(0),this->getZ(1)-this->getZ(0)},
        {this->getX(2)-this->getX(1),this->getY(2)-this->getY(1),this->getZ(2)-this->getZ(1)},
        {this->getX(3)-this->getX(2),this->getY(3)-this->getY(2),this->getZ(3)-this->getZ(2)}
    };
    float d; // определитель
    
    // находим по правилу треугольника
    d=((a[0][0]*a[1][1]*a[2][2]) + (a[0][1]*a[1][2]*a[2][0])+ (a[1][0]*a[0][2]*a[2][1]) - (a[2][0]*a[1][1]*a[0][2]) - (a[0][0]*a[2][1]*a[1][2]) - (a[1][0]*a[0][1]*a[2][2]));
    return d/6.0f;
    }

    virtual std::optional<float> getPerimeter() const override {
        return getSegmentA() + getSegmentB() + getSegmentC() + getSegmentD() + getSegmentE() + getSegmentF();
    }

};

class Parallelepiped : public Figure {
private:
    // down
    float getSegmentA() const {
        return static_cast<Point3D&>(*m_points[0]).distance(static_cast<Point3D&>(*m_points[1]));
    }

    float getSegmentB() const {
        return static_cast<Point3D&>(*m_points[1]).distance(static_cast<Point3D&>(*m_points[2]));
    }

    float getSegmentC() const {
        return static_cast<Point3D&>(*m_points[2]).distance(static_cast<Point3D&>(*m_points[3]));
    }
    
    float getSegmentD() const {
        return static_cast<Point3D&>(*m_points[3]).distance(static_cast<Point3D&>(*m_points[0]));
    }
    // up
    float getSegmentE() const {
        return static_cast<Point3D&>(*m_points[4]).distance(static_cast<Point3D&>(*m_points[5]));
    }

    float getSegmentF() const {
        return static_cast<Point3D&>(*m_points[5]).distance(static_cast<Point3D&>(*m_points[6]));
    }

    float getSegmentH() const {
        return static_cast<Point3D&>(*m_points[6]).distance(static_cast<Point3D&>(*m_points[7]));
    }

    float getSegmentI() const {
        return static_cast<Point3D&>(*m_points[7]).distance(static_cast<Point3D&>(*m_points[4]));
    }
    // borders
    float getSegmentJ() const {
        return static_cast<Point3D&>(*m_points[0]).distance(static_cast<Point3D&>(*m_points[4]));
    }

    float getSegmentK() const {
        return static_cast<Point3D&>(*m_points[1]).distance(static_cast<Point3D&>(*m_points[5]));
    }

    float getSegmentL() const {
        return static_cast<Point3D&>(*m_points[2]).distance(static_cast<Point3D&>(*m_points[6]));
    }

    float getSegmentM() const {
        return static_cast<Point3D&>(*m_points[3]).distance(static_cast<Point3D&>(*m_points[7]));
    }
public:
    Parallelepiped(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4, const Point3D& p5, const Point3D& p6, const Point3D& p7, const Point3D& p8) {
        m_name = "parallelepiped";
        m_points.push_back(std::make_unique<Point3D>(p1));
        m_points.push_back(std::make_unique<Point3D>(p2));
        m_points.push_back(std::make_unique<Point3D>(p3));
        m_points.push_back(std::make_unique<Point3D>(p4));
        m_points.push_back(std::make_unique<Point3D>(p5));
        m_points.push_back(std::make_unique<Point3D>(p6));
        m_points.push_back(std::make_unique<Point3D>(p7));
        m_points.push_back(std::make_unique<Point3D>(p8));
    }

    virtual std::optional<float> getVolume() const override {
        //1 4 3
        return getSegmentA()*getSegmentJ()*getSegmentD();
    }

    virtual std::optional<float> getPerimeter() const override {
        return getSegmentA() + getSegmentB() + getSegmentC() + getSegmentD() + getSegmentE() + getSegmentF() + getSegmentH() + getSegmentI() + getSegmentJ() + getSegmentK() + getSegmentL() + getSegmentM();
    }

};

void printFigureInfo(const Figure& figure) {
    std::cout << figure.getName() << " perimeter: ";
    if (auto perimeter = figure.getPerimeter()) {
        std::cout << *perimeter << std::endl;
    } else {
        std::cout << "NaN" << std::endl;
    }

    std::cout << figure.getName() << " square: ";
    if (auto square = figure.getSquare()) {
        std::cout << *square << std::endl;
    } else {
        std::cout << "NaN" << std::endl;
    }

    std::cout << figure.getName() << " volume: ";
    if (auto volume = figure.getVolume()) {
        std::cout << *volume << std::endl;
    } else {
        std::cout << "NaN" << std::endl;
    }

    std::cout << figure.getName() << " points: " << std::endl;
    figure.print();
    std::cout << std::endl;
}

int main() {
    printFigureInfo(Triangle(
        Point2D(0, 0),
        Point2D(1, 0),
        Point2D(0, 1)
    ));

    printFigureInfo(Circle(
        Point2D(0, 0),
        Point2D(1, 0)
    ));

    printFigureInfo(Sphere(
        Point3D(0, 0, 0),
        Point3D(1, 0, 0)
    ));
    printFigureInfo(Parallelepiped(
        Point3D(0,0,0),
        Point3D(1,0,0),
        Point3D(1,1,0),
        Point3D(0,1,0), 
        Point3D(0,1,0),
        Point3D(1,1,0),
        Point3D(1,1,1),
        Point3D(0,1,1)
    ));
    printFigureInfo(Tetrahedron(
        Point3D(2, -1, 1),
        Point3D(5, 5, 4),
        Point3D(3, 2, -1),
        Point3D(4, 1, 3)
    ));

    return 0;
}