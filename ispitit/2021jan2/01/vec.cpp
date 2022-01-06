#include "vec.hpp"
#include <iostream>

using namespace std;

Vec::Vec() {
	this->x = 0;
	this->y = 0;
}

Vec::Vec(double x1, double y1, double x2, double y2) {
	this->x = x2 - x1;
	this->y = y2 - y1;
}

Vec::Vec(double x, double y) {
	this->x = x;
	this->y = y;
}

Vec::Vec(const Vec& v) {
	this->x = v.x;
	this->y = v.y;
}

void Vec::print() {
	cout << "<" << this->x << "," << this->y << ">" << endl;
}

Vec Vec::sum(Vec v) {

	double new_x = this->x + v.x;
	double new_y = this->y + v.y;
	return Vec(new_x, new_y);
}
Vec Vec::sub(Vec v) {

	double new_x = this->x - v.x;
	double new_y = this->y - v.y;
	return Vec(new_x, new_y);
}
Vec Vec::inv() {
	return Vec(-this->x, -this->y);
}
Vec Vec::mul(double x) {
	return Vec(x * this->x, x * this->y);
}
Vec Vec::refX() {
	return Vec(this->x, -this->y);
}
Vec Vec::refY() {
	return Vec(-this->x, this->y);
}
Vec Vec::sim() {
	return Vec(-this->x, -this->y);
}
