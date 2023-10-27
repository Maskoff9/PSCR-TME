#include <iostream>
#include <unistd.h>

#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"


int pv= 3;
void ff(int){
	pv--;
	std::cout<< "point de vie "<<pv<<std::endl;
	if(pv==0){
		exit(0);
	}
}

void attaque (pid_t adversaire){
	struct sigaction sa;
	sa.sa_handler = &ff;
	sa.sa_flags=0;
	sigaction(SIGINT,&sa,NULL);

}

void defense(){
	signal(SIGINT,SIG_IGN);
	randsleep();
}

void combat(pid_t adversaire){
	while(true){
		defense();
		attaque(adversaire);
	}
}
int main(){
	if (fork() ==0 ){
		if(fork() == 0){
			combat(getppid());
		}

	}
	return 0;
}

