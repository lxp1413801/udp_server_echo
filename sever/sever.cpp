// sever.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"

#include<Winsock2.h>
#pragma comment(lib,"Wsock32.lib")
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//CString str;
//������ʹ�õĶ˿ں�Ϊ5050
#define DEFAULT_PORT 2200
char cilent_ip[16];
char cilent_port[8];

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned short port;
	int        iPort=DEFAULT_PORT;
	WSADATA        wsaData;
	SOCKET        sSocket;
	//�ͻ���ַ����
	int            iLen;
	//���͵����ݳ���
	int            iSend;
	//Ҫ���͸��ͻ�����Ϣ
	char        send_buf[ ]="Hello��I am a server";
	char        rece_buf[1024*8];
	//�������Ϳͻ��ĵ�ַ
	struct sockaddr_in    ser,	cli;
	printf("-------------------------------\n");
	printf("Server waiting\n");
	printf("-------------------------------\n");
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n ");
		return 0;
	}
	//�������������׽ӿ�
	sSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(sSocket==INVALID_SOCKET)
	{
		printf("socket( )Failed:%d\n", 

		WSAGetLastError( ));
		return 0;
	}
		//���½����������˵�ַ
	ser.sin_family=AF_INET;
	//htons( )������һ��˫�ֽ������ֽ�˳�����ת��Ϊ������

	ser.sin_port=htons(iPort);
	//htonl( )������һ�����ֽ������ֽ�˳�����ת��Ϊ��

	//ʹ��ϵͳָ����IP��ַINADDR_ANY
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sSocket,(LPSOCKADDR)&ser,sizeof(ser))	==SOCKET_ERROR)
	{
		printf("bind  Failed: %d\n", 

		WSAGetLastError( ));
		return 0;
	}

	//��ʼ���ͻ���ַ���Ȳ���
	iLen=sizeof(cli);
	//����һ������ѭ�����ȴ��ͻ�����������
	while(1)
	{
		int rece=recvfrom(sSocket,rece_buf,sizeof(rece_buf),0,(struct sockaddr*)&cli,&iLen);
		if(rece==0)
		break;
		else if(rece==SOCKET_ERROR)
		{
			printf("recv  Failed:%d\n", WSAGetLastError( ));
			break;
		}
		printf("receided len=%d\r\n",rece);
		rece_buf[rece]='\0';
		//get_cilent_ip_addr(cli.sin_addr.S_un.S_addr);
		#define _CLI_1 cli.sin_addr.S_un.S_un_b.s_b1
		#define _CLI_2 cli.sin_addr.S_un.S_un_b.s_b2
		#define _CLI_3 cli.sin_addr.S_un.S_un_b.s_b3
		#define _CLI_4 cli.sin_addr.S_un.S_un_b.s_b4
		//port=cli.sin_port;
		//port<<=8;
		//port|=((cli.sin_port)>>8);
		port=htons(cli.sin_port);
		printf("received data from cilent:%s\n",rece_buf);
		printf("client ip:%d.%d.%d.%d\r\n",_CLI_1,_CLI_2,_CLI_3,_CLI_4);
		printf("client port:%d\r\n",port);
		printf("-------------------------------\n");
		//�����ӵĿͻ�������Ϣ
		//rece
		//iSend=sendto(sSocket,send_buf,sizeof(send_buf),0,(struct sockaddr*)&cli,sizeof(cli));
		Sleep(100);
		iSend=sendto(sSocket,rece_buf,rece,0,(struct sockaddr*)&cli,sizeof(cli));
		if(iSend==SOCKET_ERROR)
		{    
			printf("send  Failed.:%d\n",WSAGetLastError( ));
			break;
		}
		else    if(iSend==0)
		{
			break;
		}
		else
		{
			printf("send  byte:%d\n",iSend);
			printf("-----------------------------\n");
		}
        
	}
	closesocket(sSocket);
	WSACleanup( );
	return 0;
}
