#include "matrica.hpp"

Matrica::Matrica() {
	_elementi.resize(0);
}

Matrica::Matrica(const vector<double> v) {
	_elementi.resize(0);
	_elementi.push_back(v);
}

void Matrica::dodajRed(const vector<double> v) {
	if(sirina() != v.size())
		throw "Neuskladjena velicina";
	_elementi.push_back(v);
}

unsigned Matrica::visina() const {
	return _elementi.size();
}

unsigned Matrica::sirina() const {
	return _elementi[0].size();
}

void Matrica::pisi(ostream& izlaz) const {
	for(unsigned i = 0; i < visina(); i++) {
		for(unsigned j = 0; j < sirina(); j++)
			izlaz << "\t" << _elementi[i][j];
		izlaz << endl;
	}
}

Matrica Matrica::operator+(const Matrica &m) const {

	return *this;
}

Matrica Matrica::operator-(const Matrica &m) const {

	return *this;
}

Matrica Matrica::operator*(const Matrica &m) const {

	return *this;
}

ostream& operator<<(ostream& izlaz, const Matrica m) {
	m.pisi(izlaz);
	return izlaz;
}

Matrica Matrica::pm(const Matrica &m) const{

	return *this;
}

Matrica Matrica::trans() const{

	return *this;
}
