#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
	char str[100];

	//file descriptors to be used
	int listen_fd, comm_fd;
	
	//struct to hold IP address and port numbers
	struct sockaddr_in servaddr;

	//creates a socket with AF_INET (IP Addressing) and of type SOCK_STREAM
	listen_fd = socket (AF_INET, SOCK_STREAM, 0);

	//clear servaddr (mandatory)
	bzero (&servaddr, sizeof (servaddr));

	//set addressing scheme to 
	servaddr.sin_family = AF_INET;
	//allow any IP to connect
	servaddr.sin_addr.s_addr = htons (INADDR_ANY);
	//listen on port 22000
	servaddr.sin_port = htons (22000);

	//prepare to listen for connections from address/port specified in sockaddr
	bind (listen_fd, (struct sockaddr *) &servaddr, sizeof (servaddr));

	//start listening for connections, keep at most 10 connection requests
	listen (listen_fd, 10);

	//accept connection from any device who is willing to connect
	comm_fd = accept (listen_fd, (struct sockaddr *) NULL, NULL);

	while (1) {
		bzero (str, 100); //clear str
		read (comm_fd, str, 100); //read at most 100 bytes into str
		printf ("Echoing back -%s", str); //display what it reads
		write (comm_fd, str, strlen(str) + 1); //send back str+1
	}
}
