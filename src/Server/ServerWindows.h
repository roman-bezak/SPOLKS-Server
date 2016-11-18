#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

struct Session{

	FILE *d_file;
	std::string filename;
	std::string operation_status;
	int reciveSize;
	int sendigSize;
	int fileSize;

	Session(){
		d_file = NULL;
		operation_status = "DEFAULT";
		filename = " ";
		reciveSize = -1;
		sendigSize = -1;
		fileSize = -1;
	}

	void clear(){
		if(d_file != NULL){
			fclose(d_file);
			d_file = NULL;
		}
		operation_status = "DEFAULT";
		reciveSize = -1;
		sendigSize = -1;
		fileSize = -1;
		filename = " ";
	}
	void setSessionData(std::string file_name,std::string o_s, int file_size, int sending_size, int recive_size){
		filename = file_name;
		operation_status = o_s;
		fileSize = file_size;
		sendigSize = sending_size;
		reciveSize = recive_size;
	}
};

struct Client{

	SOCKET c_socket;
	std::string replyBuffer;
	sockaddr_in inf;
	Session c_session;

	Client(SOCKET s,sockaddr_in i){
		c_socket = s;
		inf = i;
		replyBuffer = "";
	}
	char* getIpAddress(){
		return inet_ntoa(this->inf.sin_addr);
	}
	int getPort(){
		return ntohs(this->inf.sin_port);
	}

};



class Server
{

	private:

		WSADATA wsa;
		SOCKET server_socket, udp_server_socket, client_socket, new_clientSocket;
		sockaddr_in serverInf, new_clientInf;
		std::vector<Session> udp_sessions;
		std::vector<Client> clients;
		int port;
		

	public:
		Server(int);
		bool start();
		int commandHandling(char*);
		bool HasConnectionDropped(SOCKET);
		std::string currentDateTime();
		void reciveFileProcessing(int);
		void commandDefaultRouting(int,char*,sockaddr_in);
		void uploadInit(int);
		void downloadInit(int);
		void downloadFileProcessing(int);
		bool searchEscapeChars(char*, int, int, std::string);
		void serverSetUp();

		~Server();
};

