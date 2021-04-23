#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>		// inet_ntoa
#include <time.h> 			// time

int error( int ern, const char *msg ){
    perror( msg );
    return ern;
}

int main( void ) {
	
	int  port   = 12345;
			
	int 		fd;
	char 		buffer[256];
	socklen_t 	socklen;
	char 		hex[200];
	
	struct 	sockaddr_in serv_addr, cli_addr;
	fd = socket( AF_INET, SOCK_DGRAM, 0 );		// tworzymy nowe gniazdo
	if (fd < 0) 
        return error( 1, "socket()" );
	bzero( ( char * )&serv_addr, sizeof(serv_addr));	// zapelniamy strukture zerami

	serv_addr.sin_family 	  	= AF_INET;			// typ gniazda 
	serv_addr.sin_addr.s_addr 	= INADDR_ANY;		// oczekujemy polaczen na kazdym adresie
	serv_addr.sin_port 			= htons(port);		// port, na ktorym nasluchujemy	

	if( bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) 
		return error( 2, "bind()" );
	listen( fd, 5 );	
	socklen = sizeof(cli_addr);	
	while(1) 
	{			
			bzero(buffer, 256);			
			recvfrom(fd, (char *)buffer, 255, MSG_WAITALL, (struct sockaddr *)&cli_addr, &socklen);
			printf("Address: %s Port: %d\n",  inet_ntoa( cli_addr.sin_addr ), cli_addr.sin_port );
			printf("Wiadomosc w hexa = %s\n",buffer);
			char msg[256];			

	}
	close(fd);	
	return 0; 
}
