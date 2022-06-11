#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"ws2_32.lib")

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0

#define ICMP_MIN 8                                           // minimum 8 byte icmp packet (just header)

/* The IP header */
typedef struct iphdr
{
    unsigned int h_len : 4; // length of the header
    unsigned int version : 4; // Version of IP
    unsigned char tos; // Type of service
    unsigned short total_len; // total length of the packet
    unsigned short ident; // unique identifier
    unsigned short frag_and_flags; // flags
    unsigned char ttl;
    unsigned char proto; // protocol (TCP, UDP etc)
    unsigned short checksum; // IP checksum
    unsigned int sourceIP;
    unsigned int destIP;
} IpHeader;

//
// ICMP header
//
typedef struct _ihdr
{
    BYTE i_type;     //��Ϣ����
    BYTE i_code;     //����  /* type sub code */
    USHORT i_cksum;  //У���
    USHORT i_id;     //ID��
    USHORT i_seq;    //���к�
    ULONG timestamp; //ʱ���  /* This is not the std header, but we reserve space for time */
} IcmpHeader;        //ICMP����  ������ͷ������

#define STATUS_FAILED 0xFFFF
#define DEF_PACKET_SIZE 32
#define MAX_PACKET 1024

#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p) HeapFree (GetProcessHeap(),0,(p))

void fill_icmp_data(char*, int);
USHORT checksum(USHORT*, int);
void decode_resp(char*, int, struct sockaddr_in*);

int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET sockRaw;
    struct sockaddr_in dest;
    struct hostent* hp;
    int bread, datasize;
    int timeout = 1000;
    char* dest_ip;
    char* icmp_data;
    char* recvbuf;
    unsigned int addr = 0;
    USHORT seq_no = 0;
    struct sockaddr_in from;
    int fromlen = sizeof(from);

    if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
    {
        fprintf(stderr, "WSAStartup failed: %d\n", GetLastError());
        ExitProcess(STATUS_FAILED);
    }

    /*
    Ϊ��ʹ�÷��ͽ��ճ�ʱ����(������SO_RCVTIMEO, SO_SNDTIMEO)��
    //    ���뽫��־λ��ΪWSA_FLAG_OVERLAPPED !
    */
    sockRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, WSA_FLAG_OVERLAPPED);                    //����һ��ԭʼ�׽���
    //sockRaw = WSASocket (AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0,0);

    if (sockRaw == INVALID_SOCKET)
    {
        fprintf(stderr, "WSASocket() failed: %d\n", WSAGetLastError());
        ExitProcess(STATUS_FAILED);
    }

    timeout = 1000;   //���ý��ճ�ʱʱ��
    bread = setsockopt(sockRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)); //RECVTIMEO�ǽ��ճ�ʱʱ��
    if (bread == SOCKET_ERROR)
    {
        fprintf(stderr, "failed to set recv timeout: %d\n", WSAGetLastError());
        ExitProcess(STATUS_FAILED);
    }

    timeout = 1000;   //���÷��ͳ�ʱʱ��
    bread = setsockopt(sockRaw, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)); //SNDTIMEO�Ƿ��ͳ�ʱʱ��
    if (bread == SOCKET_ERROR)
    {
        fprintf(stderr, "failed to set send timeout: %d\n", WSAGetLastError());
        ExitProcess(STATUS_FAILED);
    }
    memset(&dest, 0, sizeof(dest));            //Ŀ���ַ����

    hp = gethostbyname("www.baidu.com");      //ͨ������������������ȡIP��ַ
    if (!hp)  //ʧ�ܷ���NULL
    {
        ExitProcess(STATUS_FAILED);
    }
    else
    {
        addr = inet_addr("14.215.177.37");    //www.baidu.com��ip��ַ
    }

    if ((!hp) && (addr == INADDR_NONE))        //�Ȳ�������Ҳ���ǵ��ʮ���Ƶ�IP��ַ
    {
        ExitProcess(STATUS_FAILED);
    }

    if (hp != NULL)                           //��ȡ��������
        memcpy(&(dest.sin_addr), hp->h_addr, hp->h_length);   //��hostent�õ��ĶԷ�ip��ַ
    else
        dest.sin_addr.s_addr = addr;

    if (hp)
        dest.sin_family = hp->h_addrtype;    //sin_family����һ��ֻ����AF_INET��
    else
        dest.sin_family = AF_INET;

    addr = inet_addr("39.101.201.13");
    dest.sin_addr.s_addr = addr;
    //addr = inet_addr("14.215.177.37");

    dest_ip = inet_ntoa(dest.sin_addr);        //Ŀ��IP��ַ

    datasize = DEF_PACKET_SIZE;             //ICMP�����ݴ�С�趨Ϊ32

    datasize += sizeof(IcmpHeader);         //�������ICMP���İ�ͷ ��ʵ��ͷռ12���ֽ�

    icmp_data = (char*)xmalloc(MAX_PACKET);//����icmp_data���ݰ��ڴ�
    recvbuf = (char*)xmalloc(MAX_PACKET);  //��Ž��յ�������

    if (!icmp_data)                         //�����ڴ�
    {
        ExitProcess(STATUS_FAILED);
    }

    memset(icmp_data, 0, MAX_PACKET);
    fill_icmp_data(icmp_data, datasize);         //ֻ�����ICMP��

    fprintf(stdout, "\nPinging %s ....\n\n", dest_ip);

    while (1)
    {
        int bwrote;

        ((IcmpHeader*)icmp_data)->i_cksum = 0;
        ((IcmpHeader*)icmp_data)->timestamp = GetTickCount(); //ʱ���

        ((IcmpHeader*)icmp_data)->i_seq = seq_no++;           //ICMP�����к�
        ((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, datasize);   //icmpУ��λ

        //������������������� ��������ֻ��ICMP���ݰ��������յ�������ʱ����ipͷ�� Ҳ���Ƿ��ͺͽ��ղ��Ե�
        //������sockRaw �趨��Э��Ϊ IPPROTO_ICMP
        bwrote = sendto(sockRaw, icmp_data, datasize, 0, (struct sockaddr*)&dest, sizeof(dest));
        if (bwrote == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAETIMEDOUT)     //����ʱ�䳬ʱ
            {
                printf("timed out\n");
                continue;
            }

            fprintf(stderr, "sendto failed: %d\n", WSAGetLastError());
            ExitProcess(STATUS_FAILED);
        }

        if (bwrote < datasize)
        {
            fprintf(stdout, "Wrote %d bytes\n", bwrote);
        }

        bread = recvfrom(sockRaw, recvbuf, MAX_PACKET, 0, (struct sockaddr*)&from, &fromlen);
        if (bread == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAETIMEDOUT)
            {
                printf("timed out\n");
                continue;
            }
            fprintf(stderr, "recvfrom failed: %d\n", WSAGetLastError());
            ExitProcess(STATUS_FAILED);
        }
        decode_resp(recvbuf, bread, &from);

        Sleep(1000);
    }

    WSACleanup();
    system("pause");

    return 0;
}

/*
The response is an IP packet. We must decode the IP header to locate
the ICMP data
*/
void decode_resp(char* buf, int bytes, struct sockaddr_in* from)
{
    IpHeader* iphdr;
    IcmpHeader* icmphdr;
    unsigned short iphdrlen;

    iphdr = (IpHeader*)buf;      //���յ������ݾ���ԭʼ��IP���ݱ�

    iphdrlen = iphdr->h_len * 4; // number of 32-bit words *4 = bytes

    if (bytes < iphdrlen + ICMP_MIN)
    {
        printf("Too few bytes from %s\n", inet_ntoa(from->sin_addr));
    }

    icmphdr = (IcmpHeader*)(buf + iphdrlen);

    if (icmphdr->i_type == 3)
    {
        printf("network unreachable -- Response from %s.\n", inet_ntoa(from->sin_addr));
        return;
    }

    if (icmphdr->i_id != (USHORT)GetCurrentProcessId())
    {
        fprintf(stderr, "someone else's packet!\n");
        return;
    }
    printf("%d bytes from %s:", bytes, inet_ntoa(from->sin_addr));
    printf(" icmp_seq = %d ", icmphdr->i_seq);
    printf(" time: %d ms ", GetTickCount() - icmphdr->timestamp);
    printf(" ttl: %d", iphdr->ttl);
    printf("\n");
}

//���ICMP��У��
USHORT checksum(USHORT* buffer, int size)
{
    unsigned long cksum = 0;

    while (size > 1)
    {
        cksum += *buffer++;
        size -= sizeof(USHORT);
    }

    if (size)
    {
        cksum += *(UCHAR*)buffer;
    }

    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >> 16);
    return (USHORT)(~cksum);
}

/*
Helper function to fill in various stuff in our ICMP request.
*/
void fill_icmp_data(char* icmp_data, int datasize)
{

    IcmpHeader* icmp_hdr;
    char* datapart;

    icmp_hdr = (IcmpHeader*)icmp_data;

    icmp_hdr->i_type = ICMP_ECHO;                   //ICMP_ECHOҪ���յ����������ظ���ICMP��
    icmp_hdr->i_code = 0;
    icmp_hdr->i_id = (USHORT)GetCurrentProcessId(); //id�ǰ���̵�id
    icmp_hdr->i_cksum = 0;
    icmp_hdr->i_seq = 0;

    datapart = icmp_data + sizeof(IcmpHeader);
    //
    // Place some junk in the buffer.
    //
    memset(datapart, 'E', datasize - sizeof(IcmpHeader));  //�����һЩ����
}

