#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <process.h>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <cstdio>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
const int PORT = 8888;//�����˶˿�һ�� 
const int buf_size=200;

void init()
{//��ʼ��������Ϣ 
	WSADATA wsd_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsd_data) != 0)
	{
		cout << "Initialization error" << endl;
		exit;
	}
	else{
		cout<<"Initialization success"<<endl;
	}
	
} 

bool login(){//��¼��֤ 
        bool result=false;
		cout << "username: ";
		char username[20];
		char password[20];
		cin.getline(username, 20);
		if (strcmp(username, "yyp") == 0 || strcmp(username, "zt") == 0)
		{
			cout << "password��";
			cin.getline(password, 100);
			if (strcmp(username, "yyp") == 0)
			{
				if (strcmp(password, "111") == 0)
				{
					cout << "success" << endl;
					result=true;
				}
				else
				{
					cout << "wrong password" << endl;
				    result=false;
				}
			}
			if (strcmp(username, "zt") == 0)
			{
				if (strcmp(password, "222") == 0)
				{
					cout << "success" << endl;
					result=true;
				}
				else
				{
					cout << "wrong password" << endl;
				    result=false;
				}

			}
		}
		else
		{
			cout << "user not exist" << endl;
		    result=false;
		}
		return result;
}

int main()
{
    init(); 
	SOCKADDR_IN ServerAddr;	// ����˵�ַ
	SOCKET SocketClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketClient == SOCKET_ERROR)
	{
		cout << "Socket connection failed" << endl;
		WSACleanup();
	}
	ServerAddr.sin_family = AF_INET; //���������Ϣ
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(PORT);

	char send_buf[buf_size]; //����buffer 
	char recv_buf[buf_size];
	memset(send_buf, 0, sizeof(send_buf));//buffer��ʼ�� 
	memset(recv_buf, 0, sizeof(recv_buf));

	cout << "Connecting" << endl;
	if (connect(SocketClient, (SOCKADDR*)& ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "Connecting failed " << endl;
		WSACleanup();
		return 0;
	}
	else{
		cout << "Successfully Connected" << endl;
	} 
	
    bool flag=login();
	while(flag!=true){//��¼��֤ 
		flag=login();
	}
	
	cout << "input send to send message first or other to receive" << endl;
	char mess[20];
	cin.getline(mess, 20);
	if (strcmp(mess, "send") == 0)
	{
		while (1)
		{
			int result;
			cout << "send��";
			cin.getline(send_buf, 100);
			result = send(SocketClient, send_buf, sizeof(send_buf), 0);
			if (result == SOCKET_ERROR)
			{
				cout << "send failed "<< endl;
				break;
			}
			memset(send_buf, 0, buf_size);//���send�Ļ��� 
			result = recv(SocketClient, recv_buf, buf_size, 0);
			if (recv_buf != 0)
			{ 
				cout << "receive��" << recv_buf << endl;//recv���治Ϊ��ʱ������Ϣ 
			} 
			memset(recv_buf, 0, sizeof(recv_buf));//������Ϣ����ջ��� 

		}

	}
	else
	{
		while (1)
		{
			int result;
			result = recv(SocketClient, recv_buf, buf_size, 0);
			if (recv_buf != 0)
				cout << "receive��"  << recv_buf << endl;
			memset(recv_buf, 0, sizeof(recv_buf));
			cout << "send��";
			cin.getline(send_buf, 100);
			result = send(SocketClient, send_buf, sizeof(send_buf), 0);
			if (result == SOCKET_ERROR)
			{
				cout << "send failed" << endl;
				break;
			}
			memset(send_buf, 0, buf_size);

		}

	}
	closesocket(SocketClient);
	WSACleanup();
	return 0;

}
