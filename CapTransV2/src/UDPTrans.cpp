/*
 * UDPTrans.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: tla001
 */

#include "UDPTrans.h"

UDPTrans::UDPTrans() {
	// TODO Auto-generated constructor stub

}

UDPTrans::~UDPTrans() {
	// TODO Auto-generated destructor stub
}
void UDPTrans::initUDPTrans()
{
	//1.����һ��socket
	confd=socket(AF_INET,SOCK_DGRAM,0);
	//2.��ʼ����������ַ
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	//
	inet_pton(AF_INET,SEVER_IP,&serveraddr.sin_addr.s_addr);
	serveraddr.sin_port =htons(SERVER_PORT);
}
void UDPTrans::sendUDPdata(void *datas,unsigned int size)
{
	size_t len,i;//�ֳ�1800�� ÿ��512
	char tempflag;
	udptransbuf data;
	for(i=0;i<24;i++){
		memcpy(data.buf,datas+i*BLOCKSIZE,BLOCKSIZE);
//		for(j=0;j<BLOCKSIZE;j++)
//			data.buf[j]= (unsigned char*)(datas+i*BLOCKSIZE+j);
		if(i==0){
			tempflag='a';
			data.flag=tempflag;
		}
		else{
			tempflag++;
			data.flag=tempflag;
		}
		//3��������������
		len=sendto(confd,(void*)&data,sizeof(data),0,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
		if(len<0)
			printf("UDP send failed\n");
	}
	//char udpSendbuf[MAXLINE]="125wwew3332354#@$#";
}
void UDPTrans::recUDPdata(char *udpRecbuf)//����Ҫ����������飬Ҫ��ָ����Ҫ�޸�
{
	size_t len;
	len=recvfrom(confd,udpRecbuf,sizeof(udpRecbuf),0,NULL,0);
	write(STDIN_FILENO,udpRecbuf,len);
}
void UDPTrans::closeUDPtrans()
{
	close(confd);
}

