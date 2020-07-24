#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <cstdio>
#include <vector>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;

const int PORT = 8888;//����ӿ�
#define buf_size 100
vector<int> sockets;   //�洢scoket

// �̻߳ص����������տͻ��˵���Ϣ��
DWORD WINAPI ThreadServer(LPVOID lp)	
{
	SOCKET* ClientSocket = (SOCKET*)lp;	// ת��
	sockets.push_back(*ClientSocket);
	char r_buff[buf_size];
	int r_length = 0;
	int s_length = 0;
	while (1)	// һֱҪ��������ͻ��˵�����
	{
		
		r_length = recv(*ClientSocket, r_buff, sizeof(r_buff), 0);
		cout << "receive��" << r_buff << endl;
		cout<<"	from��" << *ClientSocket << endl;
		if (*ClientSocket == sockets[0])
		{
			s_length = send(sockets[1], r_buff, sizeof(r_buff), 0);
			cout << "send to:" << sockets[1] << endl;
		}
		if (*ClientSocket == sockets[1])
		{
			s_length = send(sockets[0], r_buff, sizeof(r_buff), 0);
			cout << "send to:" << sockets[0] << endl;
		}
		if (s_length < 0)
		{
			cout << "send failed" << endl;
			break;
		}
		memset(r_buff, 0, sizeof(r_buff));

	}
	closesocket(*ClientSocket);
	free(ClientSocket);
	return 0;
}

int main(int argc, char* argv[])
{
	WSADATA	w_data;	
	int error;
	int error2;
	SOCKADDR_IN ServerAddr;	// ����˵�ַ
	if ((error = WSAStartup(MAKEWORD(2, 2), &w_data)) != 0)
	{
		cout << "initialization failed" << endl;
		return 0;
	}
	
	
	SOCKET lis_socket;// ����˵�socket 
	SOCKET ClientSocket;// �ͻ��˵�socket
	if ((lis_socket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
	{
		cout << "socket established failed" << endl;
		WSACleanup();	
		return 0;
	}
	ServerAddr.sin_family = AF_INET;	// ��ַ��ʽ
	ServerAddr.sin_port = htons(PORT);	// �˿� 
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// ��������ip���͵�ַ
	error2 = bind(lis_socket, (LPSOCKADDR)& ServerAddr, sizeof(ServerAddr));//�� 
	if (error2 == SOCKET_ERROR)
	{
		cout << "bind failed " << endl;
		WSACleanup();
		return 0;
	}

	
	if (listen(lis_socket, 3) == SOCKET_ERROR)
	{
		cout << "listen failed" << endl;
		WSACleanup();
		return 0;
	}

	// ��ʾ��Ϣ
	cout << "Server Listening..." << endl;

	while (1)	
	{
		SOCKET* ClientSocket = new SOCKET;	
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));// ��������
		int SockAddrlen = sizeof(sockaddr);
		*ClientSocket = accept(lis_socket, 0, 0);
		cout << "a client ha connect to the server: " << *ClientSocket << endl;
		CreateThread(NULL, 0, &ThreadServer, ClientSocket, 0, NULL);//�����߳� 
	}
	closesocket(lis_socket);
	WSACleanup();
	return 0;

}
