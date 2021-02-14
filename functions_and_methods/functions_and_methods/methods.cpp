#include "Circle.h"


Circle::Circle(int _x, int _y, int _radius, char _label)
	: x(_x), y(_y), label(_label) {
	if (_radius > 0) radius = _radius;
	else throw;
}


double Circle::distance_from_center_to_point(int point_x, int point_y) const {
	return std::sqrt((x - point_x)*(x - point_x) + (y - point_y)* (y - point_y));
}

double Circle::distance_to_point(int px, int py) const {
	return abs(distance_from_center_to_point(px, py) - radius);
}

double Circle::distance_to_x_axis() const {
	double dis1 = abs(x - radius);
	double dis2 = abs(x + radius);
	return dis1 > dis2 ? dis2 : dis1;
}

double Circle::distance_to_circle_center(const Circle& circle) const {
	return distance_from_center_to_point(circle.x, circle.y);
}


bool Circle::can_inscribe(const Circle& circle) const {
	return radius < circle.radius;
}

bool Circle::is_intersected(const Circle& circle) const {
	return distance_to_circle_center(circle) <= (radius + circle.radius);
}