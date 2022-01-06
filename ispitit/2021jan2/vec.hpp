#ifndef _vec_h_
#define _vec_h_

class Vec {
	private:
		double x, y;
	public:
		Vec();
		Vec(double x, double y);
		Vec(double x1, double y1, double x2, double y2);
		Vec(const Vec& v);
		void print();
		Vec sum(Vec v);
		Vec sub(Vec v);
		Vec mul(double x);
		Vec inv();
		Vec refX();
		Vec refY();
		Vec sim();
};
#endif
