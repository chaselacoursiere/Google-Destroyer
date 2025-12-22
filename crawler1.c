#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

	int status, s;
	char ipstr[INET6_ADDRSTRLEN];
	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof hints); // makes sure hints is empty
	hints.ai_family = AF_UNSPEC; // dont care ip4 or ip6
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE; //fill in my IP for me
				 
	
	if ((status = getaddrinfo("www.sjoa.org", "443", &hints, &servinfo)) != 0) {
		printf("error\n");
		freeaddrinfo(servinfo);
		return 2;
	} 


	if ((s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1){
		printf("socket error\n");
		return 2;
	}
	
	if ((connect(s, servinfo->ai_addr, servinfo->ai_addrlen)) == -1){
		printf("connect error\n");
		freeaddrinfo(servinfo);
		return 2;
	}

	/*
	printf("IP addresses for www.sjoa.org:\n\n");

	for(p = servinfo; p!= NULL; p = p->ai_next){
		void *addr;
		char *ipver;
		struct sockaddr_in *ipv4;
		struct sockaddr_in6 *ipv6;

		if(p->ai_family == AF_INET) {
			ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf(" %s: %s\n", ipver, ipstr);
	}
	*/
	close(s);
	freeaddrinfo(servinfo);
	/*
	int domain = AF_INET; //set domain type to IP4
	int type = SOCK_STREAM; //set socket type to TCP
	int mySocket = socket(domain, type, 0); //creates socket
	
	if (mySocket < 0) 
		printf("Unable to open socket\n");
	else
		printf("socekt %d opened\n", mySocket);
	*/
	return 0;


}
