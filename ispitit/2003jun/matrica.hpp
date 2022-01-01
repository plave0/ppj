#ifndef _MATRICA_HPP_
#define _MATRICA_HPP_

#include <vector>
#include <iostream>

using namespace std;

class Matrica {
	public:
		Matrica();
		Matrica(const vector<double> v);
		void dodajRed(const vector<double> v);
		unsigned visina() const;
		unsigned sirina() const;
		void pisi(ostream& izlaz) const;
		Matrica operator+(const Matrica &m) const;
		Matrica operator-(const Matrica &m) const;
		Matrica operator*(const Matrica &m) const;
		Matrica pm(const Matrica &m) const;
		Matrica trans() const;
	private:
		vector<vector<double>> _elementi;

};
ostream& operator<<(ostream& izlaz, const Matrica m);

#endif
