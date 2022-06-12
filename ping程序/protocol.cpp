#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "protocol.h"

static volatile int keepping = 1;
//������ֹ�źź���,ר�Ŵ�������pingʱ�Ĳ���
void get_ctrl_stop(int signal)
{
	if (signal == SIGINT)
	{
		keepping = 0;
	}
}


uint16_t getCheckSum(void * protocol, char * type)
{
	uint32_t checkSum = 0;
	uint16_t* word = (uint16_t*)protocol;
	uint32_t size = 0;
	if (type == "ICMP") {//�����ж��ٸ��ֽ�
		size = (sizeof(ICMPrecvReq));
	}
	while (size >1)//��32λ������������ΪҪ�洢16λ����ӿ��ܷ�����������������������λ���ӵ�16λ�����λ��
	{
		checkSum += *word++;
		size -=2;
	}
	if (size == 1) 
	{
		checkSum += *(uint8_t*)word;
	}
	//�����Ʒ���������㣬��ȡ������Ӻ��������ȡ���Ľ����һ���ģ�������ȫ�������ȡ��
	//������������Ľ��
	while (checkSum >> 16) checkSum = (checkSum >> 16) + (checkSum & 0xffff);
	//ȡ��
	return (~checkSum);
}

bool ping(const char * dstIPaddr,const char* param)
{
	SOCKET		rawSocket;//socket
	sockaddr_in srcAddr;//socketԴ��ַ
	sockaddr_in dstAddr;//socketĿ�ĵ�ַ
	int			Ret;//����״ֵ̬
	char		TTL = '0';//����
	
	//����һ���׽���
	//TCP/IPЭ����,RAWģʽ��ICMPЭ��
	//RAW��������һ��ԭʼ�׽��֣���Ϳ��Է��ʵ�������·������ݣ�Ҳ����˵��������IPͷ������Ҳ�����õ��ˡ�
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	//����Ŀ��IP��ַ
	dstAddr.sin_addr.S_un.S_addr = inet_addr(dstIPaddr);
	//�˿�
	dstAddr.sin_port = htons(0);
	//Э����
	dstAddr.sin_family = AF_INET;

	//��ʾ��Ϣ
	std::cout << "���� Ping " << inet_ntoa(dstAddr.sin_addr) << " ���� " << sizeof(ICMPrecvReq::data) << " �ֽڵ�����:" << std::endl;
	if(!strcmp(param,"-t"))
	{
		uint32_t i=0;
		
		while (keepping)
		{
			//����ִ��ping����
			doPing(rawSocket, srcAddr, dstAddr,i);
			//˯��1ms
			Sleep(1000);
			i++;
		}
		keepping = 1;
	}
	else if(!strcmp(param,"no_param"))
	{	//ִ��4��ping
		for (int i = 0; i < 4; i++)
		{
			doPing(rawSocket, srcAddr, dstAddr, i);
			Sleep(1000);
		 }
	}
	
	Ret = closesocket(rawSocket);
	if (Ret == SOCKET_ERROR)
	{
		std::cerr << "socket�ر�ʱ��������:" << WSAGetLastError() << std::endl;
	}
	
	return true;
}

bool sendICMPReq(SOCKET &mysocket,sockaddr_in &dstAddr,unsigned int num)
{
	//����ICMP������Ա���
	//���û�������
	ICMPrecvReq myIcmp;//ICMP������
	myIcmp.icmphead.type = 8;
	myIcmp.icmphead.code = 0;
	//���ó�ʼ�����Ϊ0
	myIcmp.icmphead.checkSum = 0;
	//���һ�����̱�ʶ���������ܹ�����У����ʶ����յ����ǲ���������̷���ȥ��ICMP����
	myIcmp.icmphead.ident = (uint16_t)GetCurrentProcessId();
	//���õ�ǰ���Ϊ0
	myIcmp.icmphead.seqNum = ++num;
	//���淢��ʱ��
	myIcmp.timeStamp = GetTickCount();
	//���㲢�ұ���У���
	myIcmp.icmphead.checkSum = getCheckSum((void*)&myIcmp, "ICMP");
	//���ͱ���
	int Ret = sendto(mysocket, (char*)&myIcmp, sizeof(ICMPrecvReq), 0, (sockaddr*)&dstAddr, sizeof(sockaddr_in));
	
	if (Ret == SOCKET_ERROR)
	{
		std::cerr << "socket ���ʹ���:" <<WSAGetLastError()<< std::endl;
		return false;
	}
	return true;
}

uint32_t readICMPanswer(SOCKET &mysocket, sockaddr_in &srcAddr, char &TTL)
{
	ICMPansReply icmpReply;//����Ӧ����
	int addrLen = sizeof(sockaddr_in);
	//����Ӧ��
	int Ret = recvfrom(mysocket, (char*)&icmpReply, sizeof(ICMPansReply), 0, (sockaddr*)&srcAddr, &addrLen);
	if (Ret == SOCKET_ERROR)
	{
		std::cerr << "socket ���մ���:" << WSAGetLastError() << std::endl;
		return false;
	}
	//��ȡУ�鲢���¼���Ա�
	uint16_t checkSum = icmpReply.icmpanswer.icmphead.checkSum;
	//��Ϊ����ȥ��ʱ������У�����0
	icmpReply.icmpanswer.icmphead.checkSum = 0;
	//���¼���
	if (checkSum== getCheckSum((void*)&icmpReply.icmpanswer, "ICMP")) {
		//��ȡTTLֵ
		TTL = icmpReply.iphead.timetoLive;
		return icmpReply.icmpanswer.timeStamp;
	}
	
	return -1;
}

int waitForSocket(SOCKET &mysocket)
{
	//5S �ȴ��׽����Ƿ�������
	timeval timeOut;
	fd_set	readfd;
	readfd.fd_count = 1;
	readfd.fd_array[0] = mysocket;
	timeOut.tv_sec = 5;
	timeOut.tv_usec = 0;
	return (select(1, &readfd, NULL, NULL, &timeOut));
}

void doPing(SOCKET & mysocket, sockaddr_in & srcAddr, sockaddr_in & dstAddr, int num)
{
	uint32_t	timeSent;//����ʱ��ʱ��
	uint32_t	timeElapsed;//�ӳ�ʱ��
	char		TTL;//����
	//����ICMP��������
	sendICMPReq(mysocket, dstAddr, num);
	//�ȴ�����
	int Ret = waitForSocket(mysocket);
	if (Ret == SOCKET_ERROR)
	{
		std::cerr << "socket��������:" << WSAGetLastError() << std::endl;
		return;
	}
	if (!Ret)
	{
		std::cout << "����ʱ:" << std::endl;
		return;
	}
	timeSent = readICMPanswer(mysocket, srcAddr, TTL);
	if (timeSent != -1) {
		timeElapsed = GetTickCount() - timeSent;
		//�����Ϣ��ע��TTLֵ��ASCII�룬Ҫ����ת��
		std::cout << "���� " << inet_ntoa(srcAddr.sin_addr) << " �Ļظ�: �ֽ�= " << sizeof(ICMPrecvReq::data) << " ʱ��= " << timeElapsed << "ms TTL= " << fabs((int)TTL) << std::endl;
	}
	else {
		std::cout << "����ʱ" << std::endl;
	}
	
}

char *isParamEmpty(char *buffer, char *param)
{
	char *temp = NULL;
	temp = buffer;
	while (*temp != '\0')
	{
		if (*temp == ' ')
		{
			*temp = '\0';
			param = ++temp;
		}
		temp++;
	}
	return param;
}


