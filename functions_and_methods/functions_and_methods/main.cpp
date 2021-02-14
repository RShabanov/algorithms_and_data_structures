#include <iostream>
#include "Circle.h"
using namespace std;


int main() {

	Circle fst_circle(4, 6, 3, 'A'),
		snd_circle(6, 4, 2, 'B');

	cout << "Methods:\n";
	cout << "Distance from circle center to the origin: "
		<< fst_circle.distance_from_center_to_point(0, 0) << endl
		<< "Distance between circles' centers: "
		<< fst_circle.distance_to_circle_center(snd_circle) << endl
		<< "Distance to x axis: " << fst_circle.distance_to_x_axis() << endl
		<< "Can fst_circle be inscribed in snd_circle?: "
		<< boolalpha << fst_circle.can_inscribe(snd_circle) << endl
		<< "Are fst_circle and snd_circle intersected?: "
		<< fst_circle.is_intersected(snd_circle) << endl << endl;

	cout << "Functions:\n";
	cout << "Distance from circle center to the origin: "
		<< distance_from_center_to_point(fst_circle, 0, 0) << endl
		<< "Distance between circles' centers: "
		<< distance_to_circle_center(fst_circle, snd_circle) << endl
		<< "Distance to x axis: " << distance_to_x_axis(fst_circle) << endl
		<< "Can fst_circle be inscribed in snd_circle?: "
		<< boolalpha << can_inscribe(fst_circle, snd_circle) << endl
		<< "Are fst_circle and snd_circle intersected?: "
		<< is_intersected(fst_circle, snd_circle) << endl << endl;

	cin.get();
	return 0;
}