#ifndef _angle_h_
#define _angle_h_

#define MAX_SEC 1296000

class Angle {
	private:
		int deg;
		int min;
		int sec;
	public:
		Angle();
		Angle(int deg, int min, int sec);
		Angle(int sec);
		void print();
		Angle* sum(Angle* a);
		Angle* sub(Angle* a);
		Angle* mul(int x);
		int to_sec();	
};
#endif
