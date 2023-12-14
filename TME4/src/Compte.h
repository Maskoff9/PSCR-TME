#pragma once
#include <thread>
#include <mutex>

namespace pr {

class Compte {
	mutable std::mutex m;
	int solde;
	 bool vu;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const  ;
	bool EstVu() const;  
    void SetVu();
};

}
