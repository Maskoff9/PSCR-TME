#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port)ServerSocket(int port){
		socketfd = socket(AF_INET, SOCK_STREAM, 0);
		if (socketfd <0){
			perror ("problème socket");
		}
		struct sockaddr_in adr;
		adr.sin_family = AF_INET;
		adr.sin_port = htons(port);
		adr.sin_addr.s_addr = INADDR_ANY ;
		std::cout << "Coucou je suis un serveur" << std::endl;
		if (bind (socketfd, (struct sockaddr *) &adr, sizeof adr) < 0){
			perror ("bind");
		}
		if (listen(socketfd, 10)<0){
			perror ("listen");
		}
	

	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	Socket accept(){
		struct sockaddr exp;
		socklen_t sz;
		int sc = ::accept(socketfd, &exp, &sz);	// On reçoit la taille !
		struct sockaddr_in expIn;
		std::cout << "connexion de "<< & expIn;
		return Socket(sc);
	}

	void close(){
		if (socketfd != -1){
			::close(socketfd);
			socketfd = -1;
		}
	}

	void close();
};

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
