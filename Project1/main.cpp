#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <omp.h>
#include "Ponit3D.h"
#include "3DObjects.h"

int main() {
    std::vector<Curve3D*> curves;

    // Populate the curves container with random curves
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> radiusDist(1.0, 10.0);
    std::uniform_real_distribution<> stepDist(0.1, 1.0);
    std::uniform_int_distribution<> numOfObj(0, 2);

    for (int i = 0; i < 10; ++i) {
        double radius = radiusDist(gen);
        double step = stepDist(gen);

        int curveType = i % 3; // Alternating between Circle, ellipse, and helix
        if (curveType == 0)
            curves.push_back(new Circle(radius));
        else if (curveType == 1)
            curves.push_back(new Ellipse(radius, radius * 1.5));
        else
            curves.push_back(new Helix(radius, step));
    }

    // Print coordinates and derivatives at t=PI/4
    double t = M_PI / 4;
    for (const auto& curve : curves) {
        Point3D* pt = new Point3D();
        Point3D* dpt = new Point3D();

        curve->computePointAndDerivative(t, pt, dpt);

        std::cout << typeid(*curve).name() << std::endl;
        std::cout << *curve << std::endl;
        std::cout << "Point: " << *pt << std::endl;
        std::cout << "Derivative of point: " << *dpt << std::endl;
        std::cout << std::endl;

        delete pt;
        delete dpt;
    }

    // Populate a second container with Circles from the first container
    std::vector<Circle*> circleContainer;
    for (const auto& curve : curves) {
        if (dynamic_cast<Circle*>(curve) != nullptr) {
            circleContainer.push_back(static_cast<Circle*>(curve));
        }
    }

    // Sort the second container in ascending order of radii
    std::sort(circleContainer.begin(), circleContainer.end(),
        [](const Circle* c1, const Circle* c2) {
            return c1->getRadius() < c2->getRadius();
        });
   
    // Compute the total sum of radii in the second container
    double totalRadiiSum = 0.0;

    // Use OpenMP to parallelize the sum computation
    #pragma omp parallel for reduction(+:totalRadiiSum)
    for (int i = 0; i < circleContainer.size(); ++i) {
        totalRadiiSum += circleContainer[i]->getRadius();
    }

    std::cout << "Total sum of circles radii: " << totalRadiiSum << std::endl;

    // Cleanup memory
    for (const auto& curve : curves) {
        delete curve;
    }

    return 0;
}
