#include "protocol.h"
int main(int argc, char* argv[])
{

	char dstAddr[20];
	char *noparam = "no_param";
	char *param =NULL;

	WSAData wsadata;
	WORD	versionreq = MAKEWORD(2, 2);//ʹ��WINsock2.2
	if (WSAStartup(versionreq, &wsadata))//��ʼ��WINsock
	{
		std::cout << "��ʼ��WINsockʧ��" << std::endl;
	}

	if (versionreq != wsadata.wVersion)
	{
		std::cout << "WINsock �汾��֧��" << std::endl;
	}

	signal(SIGINT, get_ctrl_stop);//ע���źź���
	while (1) {
			std::cout << "pingһ����ַ�� ";
			dstAddr[0] = '\0';
			std::cin.getline(dstAddr, 20);
			if ((param = isParamEmpty(dstAddr, param)) == NULL) param = noparam;
			ping(dstAddr, param);
			std::cin.clear();
			std::cin.sync();
	}

	WSACleanup();
	
	
	
	//�ر�WSA
	
	system("pause");
	return 0;
}

