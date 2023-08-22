#include "3DObjects.h"
#include "Ponit3D.h"

void Curve3D::print() const {
    std::cout << "Radius: " << getRadius();
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getStep() const {
    return 0.0;
}

void Circle::computePointAndDerivative(double t, Point3D* pt, Point3D* dpt) const {
    pt->x = radius * cos(t);
    pt->y = radius * sin(t);
    pt->z = 0.0;
    dpt->x = -radius * sin(t);
    dpt->y = radius * cos(t);
    dpt->z = 0.0;
}

double Ellipse::getRadius() const {
    return (radiusX + radiusY) / 2;
}

double Ellipse::getStep() const {
    return 0.0;
}

void Ellipse::computePointAndDerivative(double t, Point3D* pt, Point3D* dpt) const {
    pt->x = radiusX * cos(t);
    pt->y = radiusY * sin(t);
    pt->z = 0.0;
    dpt->x = -radiusX * sin(t);
    dpt->y = radiusY * cos(t);
    dpt->z = 0.0;
}

void Ellipse::print() const {
    std::cout << "Radius: (X: " << radiusX << ", Y: " << radiusY << ")";
}

double Helix::getRadius() const {
    return radius;
}

double Helix::getStep() const {
    return step;
}

void Helix::computePointAndDerivative(double t, Point3D* pt, Point3D* dpt) const {
    pt->x = radius * cos(t);
    pt->y = radius * sin(t);
    pt->z = step * t / (2 * M_PI);
    dpt->x = -radius * sin(t);
    dpt->y = radius * cos(t);
    dpt->z = step / (2 * M_PI);
}

void Helix::print() const {
    std::cout << "Radius: " << radius << ", Step: " << step;
}