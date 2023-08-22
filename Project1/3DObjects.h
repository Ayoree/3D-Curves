#pragma once
#define _USE_MATH_DEFINES

#include <iostream>

class Point3D;

class Curve3D {
private:
    virtual void print() const;
public:
    virtual double getRadius() const = 0;
    virtual double getStep() const = 0;
    virtual void computePointAndDerivative(double t, Point3D* pt, Point3D* dpt) const = 0;

    friend std::ostream& operator<<(std::ostream& stream, const Curve3D& curve) {
        curve.print();
        return stream;
    }
};

class Circle : public Curve3D {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double getRadius() const override;
    double getStep() const override;
    void computePointAndDerivative(double t, Point3D* pt, Point3D* dpt) const override;
};


class Ellipse : public Curve3D {
private:
    double radiusX, radiusY;
    void print() const override;
public:
    Ellipse(double rx, double ry) : radiusX(rx), radiusY(ry) {}

    double getRadius() const override;
    double getStep() const override;
    void computePointAndDerivative(double t, Point3D* pt, Point3D* dpt) const override;
};


class Helix : public Curve3D {
private:
    double radius, step;
    void print() const override;
public:
    Helix(double r, double s) : radius(r), step(s) {}

    double getRadius() const override;
    double getStep() const override;
    void computePointAndDerivative(double t, Point3D* pt, Point3D* dpt) const override;
};

