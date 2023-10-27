#include "Banque.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
using namespace pr;

const int NB_THREAD = 10;
int main () {

	Banque b(10,10000);
	vector<thread> threads;
	threads.reserve(NB_THREAD);

//	for(int t =0;t<1000;t++){
//		auto i = ::rand()%10;
//		auto j = ::rand()%10;
//		auto m = ::rand()%100;
//		threads.push_back(thread(&Banque::transfert,&b,i,j,m));
//		auto r = ::rand()%20;
//		this_thread::sleep_for(chrono::milliseconds(r));
//	}

	for(int t =0;t<1000;t++){
			auto i = ::rand()%10;
			auto j = ::rand()%10;
			auto m = ::rand()%100;
			threads.push_back(thread(&Banque::transfert,&b,i,j,m));
			//8) cout<<b.comptabiliser(100000);
			//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
		}


	for (auto & t : threads) {
		t.join();
	}



	//7) non , car si le transfert se passe avec un compte deja utiliser dans comptabiliser , on aura pas la somme initiiale * nb_comptes

	return 0;
}
