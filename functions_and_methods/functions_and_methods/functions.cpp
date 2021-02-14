#include "Circle.h"


double distance_from_center_to_point(const Circle& circle, 
									int px, int py) {
	return std::sqrt((circle.x - px)*(circle.x - px) + (circle.y - py)* (circle.y - py));
}

double distance_to_point(const Circle& circle, int px, int py) {
	return abs(distance_from_center_to_point(circle, px, py) - circle.radius);
}

double distance_to_circle_center(const Circle& c1, const Circle& c2) {
	return distance_from_center_to_point(c1, c2.x, c2.y);
}

double distance_to_x_axis(const Circle& circle) {
	double dis1 = abs(circle.x - circle.radius);
	double dis2 = abs(circle.x + circle.radius);
	return dis1 > dis2 ? dis2 : dis1;
}

bool can_inscribe(const Circle& c1, const Circle& c2) {
	return c1.radius < c2.radius;
}

bool is_intersected(const Circle& c1, const Circle& c2) {
	return distance_to_circle_center(c1, c2) <= (c1.radius + c2.radius);
}