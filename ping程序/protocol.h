#pragma once
#include<cstdint>
#include <string>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include<Windows.h>
#include<iostream>
#include<csignal>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//���ļ������˷���ICMPЭ�黹��IPЭ���һЩ���ݽṹ����
//�Լ�һЩPing������ĺ���
/*                       IP���ĸ�ʽ
0            8           16    19                   31
+------------+------------+-------------------------+
| ver + hlen |  ��������  |          �ܳ���         |
+------------+------------+----+--------------------+
|           ��ʶλ        |flag|    ��Ƭƫ��(13λ)  |
+------------+------------+----+--------------------+
|   ����ʱ�� | �߲�Э��� |        �ײ�У���       |
+------------+------------+-------------------------+
|                   Դ IP ��ַ                      |
+---------------------------------------------------+
|                  Ŀ�� IP ��ַ                     |
+---------------------------------------------------+
*/
//IPͷ
struct IPhead
{
	//����ʹ����C���Ե�λ��Ҳ����˵��version�������Ĵ�С���ڴ�����ռ4bit��������8bit
	uint8_t		version : 4; //IPЭ��汾
	uint8_t		headLength : 4;//�ײ�����
	uint8_t		serverce;//���ַ���
	uint16_t	totalLength;//�ܳ���
	uint16_t	flagbit;//��ʶ
	uint16_t	flag : 3;//��־
	uint16_t	fragmentOffset : 13;//Ƭƫ��
	char		timetoLive;//����ʱ�䣨������
	uint8_t		protocol;//ʹ��Э��
	uint16_t	headcheckSum;//�ײ�У���
	uint32_t	srcIPadd;//ԴIP
	uint32_t	dstIPadd;//Ŀ��IP
	//��ѡ�������ҾͲ�������
};
/*
ICMP ������
+--------+--------+---------------+
|  ����  |  ����   |      ����    |
+--------+--------+---------------+
|    8   |    0   |    ��������   |
+--------+--------+---------------+
|   10   |    0   |   ·��������  |
+--------+--------+---------------+
|   13   |    0   |   ʱ�������  |
+--------+--------+---------------+
|   15   |    0   | ��Ϣ����(����)|
+--------+--------+---------------+
|   17   |    0   | ��ַ��������  |
+--------+--------+---------------+

ICMP Ӧ����
+--------+--------+---------------+
|  ����  |  ����  |      ����     |
+--------+--------+---------------+
|    0   |    0   |    ���Իش�   |
+--------+--------+---------------+
|    9   |    0   |   ·�����ش�  |
+--------+--------+---------------+
|   14   |    0   |   ʱ����ش�  |
+--------+--------+---------------+
|   16   |    0   | ��Ϣ�ش�(����)|
+--------+--------+---------------+
|   18   |    0   | ��ַ����ش�  |
+--------+--------+---------------+

ICMPЭ������/�ش��ĸ�ʽ
0        8       16                32
+--------+--------+-----------------+
|  ����   |  ����   |     У���    |
+--------+--------+-----------------+
|      ��ʶ��      |      ���      |
+-----------------+-----------------+
|             ��������              |
+-----------------+-----------------+

*/
//ICMPЭ����ֻ����������/�ش��ܵı��ĸ�ʽ����Ϊ��ͬ�����ͺʹ��뱨�ĵ�������ɲ�һ��,ICMP�������ģ��ش��ģ�����ġ��������ûд��������Ϊ�ò���
//ICMP����
//ICMPͷ
struct ICMPhead
{
	uint8_t type;//����
	uint8_t code;//����
	uint16_t checkSum;//У���
	uint16_t ident;//���̱�ʶ��
	uint16_t seqNum;//���
};
//ICMP����������(������)
struct ICMPrecvReq
{
	ICMPhead icmphead;//ͷ��
	uint32_t timeStamp;//ʱ���
	char	 data[32];//����
};
//ICMPӦ����(������)
struct ICMPansReply
{
	IPhead iphead;//IPͷ
	ICMPrecvReq icmpanswer;//ICMP����
	char data[1024];//Ӧ����Я�������ݻ�����
};
//����У��ͣ�����1��Э��ͷ��ָ�룬��Ҫת���ɿ�ָ�롣����2�������Э�����͡�����У���
uint16_t getCheckSum(void* protocol,char* type);
//ping���򣬲���1��ΪĿ��IP��ַ�������Ƿ��ͳɹ�.����2��ֻ��д-t,���߲�д
bool ping(const char* dstIPaddr,const char* param='\0');
//����ICMP����ش��ģ�����1���׽���.����2��Ŀ�ĵ�ַ.����3����num�η���
bool sendICMPReq(SOCKET &mysocket, sockaddr_in &dstAddr, unsigned int num);
//��ȡICMPӦ���ģ�����1���׽���.����2�����շ���ַ.����3������
uint32_t readICMPanswer(SOCKET &mysocket, sockaddr_in &srcAddr, char &TTL);
//�ȴ�socket�Ƿ���������Ҫ��ȡ
int waitForSocket(SOCKET &mysocket);
//ִ��һ��ping����,����1���׽���.����2��Դ��ַ.����3��Ŀ�ĵ�ַ���ping�������
void doPing(SOCKET &mysocket,sockaddr_in &srcAddr,sockaddr_in &dstAddr,int num);

char* isParamEmpty(char *buffer, char *param);
//������ֹ�źź���
void get_ctrl_stop(int signal);

