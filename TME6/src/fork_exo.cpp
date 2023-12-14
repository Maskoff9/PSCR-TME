#include <iostream>
#include <unistd.h>

#include <sys/wait.h>

int main () {
	const int N = 3;
	int nbfils = 0;
	std::cout << "main pid=" << getpid() << std::endl;

	for (int i=1, j=N; i<=N && j==N; i++ ) {
		if(fork() == 0 ){
		nbfils=0;
		std::cout << " i:j " << i << ":" << j <<"de " << getpid()<< std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			nbfils++;
			if ( fork() == 0) {
				nbfils=0;
				j=0;
				std::cout << " k:j " << k << ":" << j <<" de " << getpid() << std::endl;
			}
		}

		}
		else{
			nbfils++;
			break;
		}
	}

	std::cout<< getpid() <<"nbfils : "<<nbfils<< std::endl;
	for (int p =0 ;p<nbfils;p++){
		if(wait(nullptr) == -1){
			std::cout<<"trop de wait de "<< getpid()<<std::endl;
		}
	 }
	if(wait(nullptr) != -1){
				std::cout<<" il en reste de "<< getpid()<<std::endl;
			}


	return 0;
}
//main pid=127918
//127918
// i:j 1:3
//127924
// k:j 1:0
//127925
// i:j 2:3
// k:j 1:0
//127927
// k:j 2:0
//127928
//127926
// i:j 3:3
// k:j 1:0
//127930
// k:j 2:0
//127931
//127929
// k:j 3:0
//127932

