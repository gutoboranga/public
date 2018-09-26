// testecli.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define	SOCKET	int
#define INVALID_SOCKET  ((SOCKET)~0)
#endif

#define PORTA_CLI 2345

char server_ip[25];
int server_port;

void get_parameters(int argc, char *argv[]) {
	int i;

	if (argc < 5) { printf("Utilizacao:\nclient -i <ip> -p <porta>\n"); exit(1); }

	for(i=1; i<argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			i++;
			strcpy(server_ip, argv[i]);
		}
		else if (strcmp(argv[i], "-p") == 0) {
			i++;
			server_port = atoi(argv[i]);
		} else {
			printf("Parametro invalido %d: %s\n", i, argv[i]);
			exit(1);
		}
	}
}

int main(int argc, char* argv[]) {
	SOCKET sock;
	struct sockaddr_in  s_cli, s_serv;

	#ifdef _WIN32
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		printf("Erro no startup do socket\n");
		exit(1);
	}
	#endif

	get_parameters(argc, argv);

	// abre socket TCP
	if ((sock = socket(AF_INET, SOCK_STREAM, 0))==INVALID_SOCKET)
	{
		printf("Erro iniciando socket\n");
		return(0);
	}

	// seta informacoes IP/Porta locais
	s_cli.sin_family = AF_INET;
	s_cli.sin_addr.s_addr = htonl(INADDR_ANY);
	s_cli.sin_port = htons(PORTA_CLI);

	// associa configuracoes locais com socket
	if ((bind(sock, (struct sockaddr *)&s_cli, sizeof(s_cli))) != 0)
	{
		printf("erro no bind\n");
		close(sock);
		return(0);
	}

	printf("> Vou conectar no ip: %s na porta %d\n", server_ip, server_port);

	// seta informacoes IP/Porta do servidor remoto
	s_serv.sin_family = AF_INET;
	s_serv.sin_addr.s_addr = inet_addr(server_ip);
	s_serv.sin_port = htons(server_port);



	// connecta socket aberto no cliente com o servidor
	if(connect(sock, (struct sockaddr*)&s_serv, sizeof(s_serv)) != 0) {
		//printf("erro na conexao - %d\n", WSAGetLastError());
		printf("erro na conexao");
		close(sock);
		exit(1);
	}

	// recebe do teclado e envia ao servidor
	char buff[1250];

    double sleep_time;

    time_t timer = time(NULL);
	time_t start_time = timer;
	long data_sent = 0;

	while(1) {
        
        int bytes_sent;

		bytes_sent = send(sock, buff, sizeof(buff), 0);
		data_sent += bytes_sent * 8;
        
        if (difftime(time(NULL), timer) >= 1.0) {
			timer = time(NULL);
			printf("%.0f\t%5ld\n", difftime(timer, start_time), data_sent);
			data_sent = 0;
		}
	}

	// fecha socket e termina programa
	printf("Fim da conexao\n");
	close(sock);
	return 0;
}
