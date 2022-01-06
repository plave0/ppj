#include "angle.hpp"
#include <iostream>

using namespace std;

Angle::Angle() {
	this->deg = 0;
	this->min = 0;
	this->sec = 0;
}
Angle::Angle(int deg, int min, int sec) {

	sec = deg * 3600 + min * 60 + sec;
	if(sec < 0) 
		sec = (sec + MAX_SEC) % MAX_SEC;
	else
		sec = sec % MAX_SEC;

	this->deg = sec / 3600;
	sec = sec % 3600;
	this->min = sec / 60;
	sec = sec % 60;
	this->sec = sec;
}
Angle::Angle(int sec) {

	if(sec < 0) 
		sec = (sec + MAX_SEC) % MAX_SEC;
	else
		sec = sec % MAX_SEC;

	this->deg = sec / 3600;
	sec = sec % 3600;
	this->min = sec / 60;
	sec = sec % 60;
	this->sec = sec;
}

void Angle::print() {
	cout << '<' << deg << ", " << min  << ", " << sec << ">";
}
Angle* Angle::sum(Angle* a) {

	int this_sec = this->to_sec();
	int a_sec = a->to_sec();
	
	return new Angle(this_sec + a_sec);
}
Angle* Angle::sub(Angle* a) {

	int this_sec = this->to_sec();
	int a_sec = a->to_sec();
	
	return new Angle(this_sec - a_sec);
}

Angle* Angle::mul(int x) {

	int this_sec = this->to_sec();
	return new Angle(this_sec * x);
}

int Angle::to_sec() {

	int ret_val = this->deg * 60 * 60 + this->min * 60 + this->sec;
	return ret_val % MAX_SEC;
}
