#include "Compte.h"

using namespace std;

namespace pr {
mutex mu;
void Compte::crediter (unsigned int val) {
	unique_lock<mutex> g(m);
	solde+=val ;
}
bool Compte::debiter (unsigned int val) {
	unique_lock<mutex> g(m);
	bool doit = solde >= val;
	if (doit) {
		solde-=val ;
	}
	return doit;
}
int Compte::getSolde() const  {
	unique_lock<mutex> g(m);
	return solde;
}
// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte & other) {
	other.m.lock();
	solde = other.solde;
	other.m.unlock();
	vu = false;
}

mutex & getMutexC(){
	return mu;
}

bool Compte::EstVu() const {
    return vu;
}

void Compte::SetVu() {
    vu = true;
}


}


