#pragma once
#include <cmath>


struct Circle {
	int x, y, radius;
	char label;

	Circle(int, int, int, char);

	double distance_from_center_to_point(int, int) const;
	double distance_to_point(int, int) const;
	double distance_to_x_axis() const;
	double distance_to_circle_center(const Circle&) const;

	bool can_inscribe(const Circle&) const;
	bool is_intersected(const Circle&) const;
};


double distance_from_center_to_point(const Circle&, int, int);
double distance_to_point(const Circle&, int, int);
double distance_to_circle_center(const Circle&, const Circle&);
double distance_to_x_axis(const Circle&);

bool can_inscribe(const Circle&, const Circle&);
bool is_intersected(const Circle&, const Circle&);