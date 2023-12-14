#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <string>
#include <iosfwd>

namespace pr {

class Socket {
	int fd;

public :
	Socket():fd(-1){}
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port){
		struct addrinfo * adr;
		const char * s = host.c_str();
		if (getaddrinfo (s, nullptr, nullptr, &adr)){
			perror("DNS");
		}
		struct in_addr ipv4;

		for (struct addrinfo * rp = adr ; rp != NULL ; rp = rp->ai_next){
			if (rp->ai_family == AF_INET && rp->ai_socktype == SOCK_STREAM){
				ipv4 = ((sockaddr_in * ) rp-> ai_addr) -> sin_addr;
				break;
			}

		}
		freeaddrinfo(adr);
		connect(ipv4,port);
	}


	void connect(in_addr ipv4, int port){
		fd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
		struct sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(port);
		server.sin_addr = ipv4;

		if (::connect (fd, ( struct sockaddr*) &server, sizeof(server)) < 0){
			fd = -1;
			perror("connect");
		}
	}

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close(){
		if (fd != -1){
			::close(fd);
			fd = -1;
		}
	}
};

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
	char host[1024];
	if (getnameinfo((struct sockaddr*) addr, sizeof (struct sockaddr_in), host, 1024, nullptr, 0,0)){
		os << "host : " << host << std::endl;
	}
	std::cout << inet_ntoa(addr -> sin_addr) << ":" << ntohs(addr->sin_port) << std::endl;
	return os;
}

#endif /* SRC_SOCKET_H_ */
