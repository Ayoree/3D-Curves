#pragma once
#include <iostream>

class Point3D {
public:
	double x, y, z;
	friend std::ostream& operator<<(std::ostream& stream, const Point3D& pt) {
		std::cout << "(" << pt.x << ", " << pt.y << ", " << pt.z << ")";
		return stream;
	}
};


