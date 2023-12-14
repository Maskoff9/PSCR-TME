#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"

int pv = 3;

void gestionpv(int s) {
    if (s == SIGUSR1) {
        pv--;
        std::cout << "Attaque de " << getpid() << ", point de vie " << pv << std::endl;
        if (pv == 0) {
            std::cout << "MORT de " << getpid() << std::endl;
            exit(1);
        }
    }
}

void attaque(pid_t adversaire) {
    if (kill(adversaire, SIGUSR1) < 0) {
        std::cout << "Mort de l'adversaire " << adversaire << std::endl;
        exit(0);
    }
    randsleep();
}

void defense() {
    // Ignorer le signal SIGUSR1 pendant la phase de défense
    signal(SIGUSR1, SIG_IGN);
    randsleep();
    // Rétablir le gestionnaire par défaut du signal SIGUSR1 après la phase de défense
    signal(SIGUSR1, gestionpv);
}

void combat(pid_t adversaire) {
    signal(SIGUSR1, gestionpv);

    while (true) {
        std::cout << "Défense de " << getpid() << std::endl;
        defense();
        std::cout << "Attaque : " << getpid() << " sur l'adversaire " << adversaire << std::endl;
        attaque(adversaire);
    }
}

int main() {
    pid_t p = getpid();
    pid_t fils = fork();
	srand(0);
    if (fils == 0) {
        combat(p);
    } else {
        combat(fils);
        // Attendre que l'enfant se termine avant de quitter le processus parent
        wait(nullptr);
        exit(0);
    }

    return 0;

	//Le coup est tout le temps paré
}
