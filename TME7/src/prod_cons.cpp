#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>  // permissions/constantes des modes
#include <sys/mman.h>
#include <vector>
#include <fcntl.h> 
#include <csignal>

using namespace std;
using namespace pr;

#define N 5 // nombre de producteurs
#define M 10 // nombre de consommateurs

vector<pid_t> tokill;

void killThem(int) {
	for(pid_t p : tokill) {
		kill(p, SIGINT);
	}
}

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consommateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}



int main () {
	size_t shmsize = sizeof(Stack <char>);
	int fd;
	void *addr;
	bool useAnonymous = false;
	tokill.reserve(M);

	if (useAnonymous) {
		addr = mmap(nullptr, shmsize, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
		if (addr == MAP_FAILED) {
			perror("mmap error");
			exit(1);
		}
	} else {
		fd = shm_open("/monsem", O_CREAT|O_EXCL|O_RDWR, 0666);
		if (fd < 0) {
			perror("sem_open error");
			exit(1);
		}
		if (ftruncate(fd, shmsize) != 0) {
			perror("ftruncate error");
			return 1;
		}
		addr = mmap(nullptr, shmsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		if (addr == MAP_FAILED) {
			perror("mmap error");
			exit(1);
		}
	}

	Stack<char> * s = new (addr) Stack<char>();

	for (int i=0; i<N; i++) { // N producteurs
		pid_t pp = fork();
		if (pp == 0) {
			producteur(s);
			return 0;
		}
	}
	

	for (int i=0; i<M; i++) { // M consommateurs
		pid_t pc = fork();
		if (pc == 0) {
			consommateur(s);
			return 0;
		} else {
			tokill.push_back(pc);
		}
	}

	signal(SIGINT, killThem);
	for (int i=0; i<N; i++) {
		wait(0);
	}
	for (int i=0; i<M; i++) {
		wait(0);
	}

	s->~Stack();

	if (munmap(addr, shmsize) != 0) {
		perror("munmap error");
		exit(1);
	}
	if (!useAnonymous) {
		if (shm_unlink("/monsem") != 0) {
			perror("unlink error");
			exit(1);
		}
	}

	return 0;
}
