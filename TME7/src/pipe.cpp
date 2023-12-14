#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>


int main(int argc, char **argv){
    /*Scan de argv*/
    if (argc == 1)
    {
        std::cout << "Pas d'arguments" << std::endl;
        return 0;
    }

    char** arg1 = new char*[argc];
    char** arg2 = new char*[argc];
    int s = 0;

    // Initialisation des tableaux à NULL
    for (int i = 0; i < argc; ++i) {
        arg1[i] = nullptr;
        arg2[i] = nullptr;
    }

    //pr la gauche 
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "|") == 0) {
            s = i + 1;
            break;
        } else {
            arg1[i - 1] = argv[i];
        }
    }

    //pr la droite
    for (int i = 0; s < argc; ++s, ++i) {
    arg2[i] = argv[s];
    }



    int tubeDesc[2];
    int pid_fils1;
    int pid_fils2;

    //pr Pipe
    if (pipe (tubeDesc) == -1) {
        perror ("pipe");
        exit (1);
    }

    if ( (pid_fils1 = fork ( )) == -1 ){
        perror ("fork");
        exit (2);
    }

    if (pid_fils1 == 0) { /* fils 1 */

        dup2(tubeDesc[1],STDOUT_FILENO);
        close (tubeDesc[1]);
        close (tubeDesc[0]);

        if (execv(argv[1], &argv[1]) == -1){ 
            perror("execv");
            exit(3);
        }

    }


    if ( (pid_fils2 = fork ( )) == -1 ){
        perror ("fork");
        exit (2);
    }


    if (pid_fils2 == 0) { /* fils 2 */
        dup2(tubeDesc[0],STDIN_FILENO);
        close (tubeDesc[0]);
        close (tubeDesc[1]);

        
    }

    if (execv(arg2[0], arg2) == -1){ 
            perror("execv");
            exit(3);
        }

    delete[] arg1;
    delete[] arg2;

    close (tubeDesc[0]);
    close (tubeDesc[1]);

    wait(0);
    wait(0);
    return 0;
}