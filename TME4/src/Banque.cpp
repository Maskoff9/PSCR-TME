#include "Banque.h"

#include <iostream>
#include <algorithm>

using namespace std;

namespace pr {
mutex m ;
void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	std::unique_lock<std::mutex> g(m);

	//q10
	if (std::find(comptesVus.begin(), comptesVus.end(), deb) != comptesVus.end()) {
        
        return;
    }

	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}

	debiteur.SetVu();
    comptesVus.push_back(deb);

}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
mutex & getMutexB(){
	return m;
}



}
