#include <iostream>
#include<string>
#include <malloc.h>
using namespace std;

struct MFD//�û����ݽṹ
{
	string username;//�û���
	string password;//����
	struct USER_UFD* next;//ָ���û��ļ���ָ��
};

struct UFD//�ļ������ݽṹ
{
	struct file_message//�ļ����ݽṹ
	{
		string filename;//�ļ���
		int protect_code;//�ļ�������
		int length;//�ļ�����
		int addr;//�ļ���ʼ��ַ
	}ufd[16];//һ���ļ�����Կ�����16���ļ�
	string directname;//�ļ�������
	int cur_file_size = 0;//��ǰ���ļ��к��е��ļ�����
};

struct UOF//���ļ����ݽṹ
{
	struct uof
	{
		string filename;//�ļ�����
		int pointer;//�ļ�����
		int protect_code;//�ļ�������
		int addr;//�ļ���ʵ��ַ
	}uof[16];//������ͬʱ��16���ļ�
	int cur_openfilesize = 0;//��ǰ�򿪵��ļ�����
};

struct fat
{
	int next = -1;
	int used = 0;
}fat[64];

struct USER_UFD//�û��ļ����ݽṹ
{
	struct UFD direct[16];//һ���û���������16���ļ���
	int cur_user_direct_size = 0;//��ǰӵ�е��ļ�������
};

int mark = 1;
struct USER_UFD cur_user_all_direct_array[16];//�û��ļ�����
int max_usersize = 16;//����û�����
int max_openfilesize = 16;//����ļ�ͬʱ������
struct MFD cur_user;//��ǰ�û�
struct UOF* cur_opentable;//ָ����ļ������ָ��
char* fdisk;//ģ�����ָ��
struct UOF openfile[16];//ÿһ���û���Ӧһ���ļ��򿪱����
MFD mfd[16]; //16���û�
int cur_user_size = 0;//��¼��ǰ�û�������
string path;

int REGISTER();//ע���û�
int LOGIN();//��¼�û�
int CREATE(string name);//�����ļ�
int DELETE(string name);//ɾ���ļ�
int OPEN(string name);//���ļ�
int WRITE(string name);//д�ļ�
int READ(string name);//���ļ�
int CLOSE(string name);//�ر��ļ�
int CD();//���ĵ�ǰĿ¼
int MKDIR(string name);//�����ļ���
int DIR();//��ʾ��ǰĿ¼����Ŀ¼
int SET(string name, int protectcode);//���ñ�����
void INPUT_OPERATION();//ָ������

int REGISTER()
{
	cout << "�������û�����";
	string username;
	cin >> username;
	cout << "���������룺";
	string password;
	cin >> password;
	for (int i = 0; i < 16; i++)
	{
		if (mfd[i].username == username)
		{
			cout << "ע��ʧ�ܣ����û����Ѵ���" << endl;
			return 0;
		}
	}
	mfd[cur_user_size].username = username;
	mfd[cur_user_size].password = password;
	cur_user_size++;
	cout << "ע��ɹ�" << endl;
	return 1;
}

int LOGIN()
{
	cout << "�������û�����";
	string username;
	cin >> username;
	cout << "���������룺";
	string password;
	cin >> password;
	int i;
	for (i = 0; i < cur_user_size; i++)
	{
		if (mfd[i].username == username)
		{
			if (mfd[i].password != password)
			{
				cout << "�������" << endl;
				return 0;
			}
			else
			{
				break;
			}
		}
	}
	if (i == cur_user_size)
	{
		cout << "û�д��û�" << endl;
		return 0;
	}
	mfd[i].next = &(cur_user_all_direct_array[i]);
	cur_user = mfd[i];
	cur_user.next->cur_user_direct_size = mfd[i].next->cur_user_direct_size;
	cur_user_size++;
	cur_opentable = &openfile[cur_user_size]; //ָ��ָ���ļ��򿪱����
	cur_opentable->cur_openfilesize = 0;
	path = "";
	return 1;
}

int CREATE(string name)
{
	int index;
	if (path == "")
	{
		cout << "�����ļ����д����ļ�" << endl;
		return 0;
	}
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (path == cur_user.next->direct[index].directname)
		{
			break;
		}
	}
	int i;
	for (i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
	{
		if (name == cur_user.next->direct[index].ufd[i].filename)
		{
			break;
		}
	}
	if (i < cur_user.next->direct[index].cur_file_size)
	{
		cout << "�ļ����ظ�" << endl;
		return 0;
	}
	if (cur_user.next->direct[index].cur_file_size == 16)
	{
		cout << "���ļ����ļ��Ѵﵽ16��" << endl;
		return 0;
	}
	int j;
	for (j = 0; j < 64; j++)//�ж��Ƿ��п��п�
	{
		if (fat[j].used == 0)
			break;
	}
	if (j >= 64)
	{
		cout << "����û�п��п���" << endl;
		return 0;
	}
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].filename = name;
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].addr = j; //�ļ���ʼ�̿��
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].length = 0;
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].protect_code = 2; //��ʾ�ɶ���д
	cur_user.next->direct[index].cur_file_size++;//�û��ļ�������1
	return 1;
}

int DELETE(string name)
{
	if (path == "")
	{
		cout << "�����ļ�����ɾ���ļ�" << endl;
		return 0;
	}
	int index;
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (path == cur_user.next->direct[index].directname)
		{
			break;
		}
	}
	int i;
	for (i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
	{
		if (cur_user.next->direct[index].ufd[i].filename == name)
		{
			break;
		}
	}
	if (i >= cur_user.next->direct[index].cur_file_size)
	{
		cout << "û�и��ļ�" << endl;
		return 0;
	}
	int j;
	for (j = 0; i < cur_opentable->cur_openfilesize; j++)
	{
		if (cur_opentable->uof[j].filename == name)
			break;
	}
	if (j < cur_opentable->cur_openfilesize)
	{
		cout << "���ļ��ѱ��򿪣��޷�ɾ��" << endl;
		return 0;
	}
	//���µ�ǰ�û�Ŀ¼���ļ�������Ϣ,���ǽ����һ���ļ�����Ϣ�滻��Ҫɾ�����ļ���λ��
	fat[cur_user.next->direct[index].ufd[i].addr].used = 0; //û��ʹ��
	cur_user.next->direct[index].ufd[i].filename = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].filename;
	cur_user.next->direct[index].ufd[i].addr = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].addr;
	cur_user.next->direct[index].ufd[i].length = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].length;
	cur_user.next->direct[index].ufd[i].protect_code = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].protect_code;
	cur_user.next->direct[index].cur_file_size--;
	//�����ļ���ռ�õĴ��̿ռ����
	int temp = fat[cur_user.next->direct[index].ufd[i].addr].next;
	while (temp != -1)
	{
		fat[temp].used = 0;
		temp = fat[temp].next;
	}
	cout << "ɾ���ļ��ɹ�" << endl;
	return 1;
}

int OPEN(string name)
{
	string AllName = path + '/' + name;//���øñ�����ԭ���Ƿ�ֹ���ִ��ļ������д����ļ�������ͬ���ļ�ͬ�������
	int index;
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (path == cur_user.next->direct[index].directname)
		{
			break;
		}
	}
	int i = 0;
	for (i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
	{
		if (name == cur_user.next->direct[i].ufd[i].filename)
			break;
	}
	if (i >= cur_user.next->direct[index].cur_file_size)
	{
		cout << "���û�û������ļ�" << endl;
		return 0;
	}
	if (cur_opentable->cur_openfilesize == max_openfilesize)
	{
		cout << "�ļ��������Ѿ��ﵽ���ֵ" << endl;
		return 0;
	}
	if (path == "")
	{
		cout << "�����ļ����д��ļ�" << endl;
		return 0;
	}
	for (int j = 0; i < cur_opentable->cur_openfilesize; j++)
	{
		if (cur_opentable->uof[i].filename == AllName)
		{
			cout << "���ļ��Ѿ���" << endl;
			return 0;
		}
	}
	int k;
	for (k = 0; k < cur_user.next->direct[index].cur_file_size; k++)
	{
		if (cur_user.next->direct[index].ufd[k].filename == name)
			break;
	}
	cur_opentable->uof[cur_opentable->cur_openfilesize].filename = AllName;
	cur_opentable->uof[cur_opentable->cur_openfilesize].protect_code = cur_user.next->direct[index].ufd[k].protect_code;
	cur_opentable->uof[cur_opentable->cur_openfilesize].pointer = cur_user.next->direct[index].ufd[k].length;
	cur_opentable->uof[cur_opentable->cur_openfilesize].addr = cur_user.next->direct[index].ufd[k].addr;
	cur_opentable->cur_openfilesize++; //�ļ���������1
	cout << "�ļ��򿪳ɹ�" << endl;
	return k; //�����ļ����ļ��򿪱��еĵڼ���
}

int WRITE(string name)
{
	int index; //��ʶ��ǰĿ¼��direct�����еڼ���
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (path == cur_user.next->direct[index].directname)
		{
			break;
		}
	}
	int i;
	//�ж��ļ��Ƿ��
	for (i = 0; i < cur_opentable->cur_openfilesize; i++)
	{
		if (cur_opentable->uof[i].filename == path + '/' + name)
			break;
	}
	if (i >= cur_opentable->cur_openfilesize)
	{
		cout << "�ļ�û�д򿪣� �޷�д��" << endl;
		return -1;
	}
	int fd = i; //��ȡ�ļ�������
	//�ж϶��ļ��ĺϷ���
	if (cur_opentable->uof[fd].protect_code != 2)
	{
		cout << "�ļ�����д" << endl;
		return -1;
	}
	else
	{
		string content;
		cin.ignore();
		cout << "�������ļ�Ҫд�������: " << endl;;
		getline(cin, content); //����һ��������
		char buf[512];
		int len = content.length();
		int times = len / 512;
		int offset = len % 512;
		if (offset != 0)
			times++;
		for (int time = 0; i < times; i++)
		{
			if (time == times - 1) //ע�����ﲻ��д��times-- o.o!!!
			{
				for (int j = 0; j < offset; j++)
					buf[j] = content[j];
			}
			else
			{
				for (int j = 0; j < 512; j++)
					buf[j] = content[j];
			}
			int temp; //���浱ǰ��д���ļ����û��ļ�Ŀ¼��ĵڼ��Ϊ�˺����޸��ļ��Ĵ�С
			int first_block = cur_opentable->uof[fd].addr; //�û��ļ���ŵĵ�һ�����̿�
			for (int k = 0; k < cur_user.next->direct[index].cur_file_size; k++)
			{
				if (cur_user.next->direct[index].ufd[k].addr == first_block)
				{
					temp = k;
					break;
				}
			}
			//׷��д
			//�ҵ����ļ���ŵ����һ�����̿�
			while (fat[first_block].next != -1)
			{
				first_block = fat[first_block].next;
			}
			//������ļ���ŵ����һ����ַ
			char* first;
			first = fdisk + first_block * 512 + cur_opentable->uof[fd].pointer % 512;
			//������һ���ļ�ʣ�µĿռ����Ҫд��ĳ���
			if (len <= 512 - cur_opentable->uof[fd].pointer % 512)
			{
				//strcpy(first, buf);  ������������⣬����������bufû��					�����������ֵ�������ˣ��Ƿ���
				for (int i = 0; i < len; i++)
				{
					first[i] = buf[i];//��������������д�����������
				}
				cur_opentable->uof[fd].pointer = cur_opentable->uof[fd].pointer + len;  //�����ļ��򿪱�
				cur_user.next->direct[index].ufd[temp].length = cur_user.next->direct[index].ufd[temp].length + len; //�����û�Ŀ¼�ļ���
			}
			else  //���ʣ�µĿռ䲻��д��
			{
				for (i = 0; i < 512 - cur_opentable->uof[fd].pointer % 512; i++)
				{ 	//д��һ���ֵ����ݵ����һ�����̿��ʣ��ռ�
					first[i] = buf[i];
				}
				//������������һ�����̵�ʣ��ռ�󣬻�ʣ�¶����ֽ�û�д洢
				int last_size = len - (512 - cur_opentable->uof[fd].pointer % 512);
				int need_block_size = last_size / 512;
				int need_offset_size = last_size % 512;
				if (need_offset_size > 0)
					need_block_size++; //�ܹ���Ҫ��ô���̿�
				int unused_block_size = 0; //��¼û��ʹ�ù��Ĵ��̿�ĸ�			��
				//int first_unused_block; //��¼��һ��û�б�ʹ�ù��Ĵ���
				int flag = 0;
				for (int i = 0; i < 64; i++)
				{
					if (fat[i].used == 0)
					{
						unused_block_size++;
					}
				}
				if (unused_block_size < need_block_size)
				{
					cout << "����û�пռ�����" << endl;
					return 0;
				}
				else
				{
					int item = cur_opentable->uof[fd].addr;
					for (int p = 0; p < need_block_size; p++) //ִ�ж��Ѱ�ҿ��д��̵Ĳ�����
					{
						for (int i = 0; i < 64; i++)
						{
							if (fat[i].used == 0) //û�б�ʹ��
							{
								first = fdisk + i * 512; //��ǰҪд��Ĵ��̿����ʼ��ַ
								fat[i].used = 1; //��Ǳ�ʹ��
								fat[item].next = i; //�����һ������
								item = i;
								break;
							}
						}
						if (p == need_block_size - 1)
						{
							for (int k = 0; k < need_offset_size; k++)  //���ļ���ƫ����д�����һ���ļ���
								first[k] = buf[k];
							//�������һ�����̿��nextֵ
							fat[i].next = -1;
						}
						else  //����������һ�����п�
						{ //��������⣬�����������fat��nextֵ
							for (int k = 0; k < 512; k++)
								first[k] = buf[k];
						}
					}
					cur_opentable->uof[fd].pointer = cur_opentable->uof[fd].pointer + last_size;  //�����ļ��򿪱�
					cur_user.next->direct[index].ufd[temp].length = cur_user.next->direct[index].ufd[temp].length + last_size; //�����û�Ŀ¼�ļ���
				}
			}
		}
	}
	cout << "�ļ�д��ɹ�" << endl;
	return 0;
}

int READ(string name)
{
	int index1; //��ʶ��ǰĿ¼��direct�����еڼ���
	for (index1 = 0; index1 < cur_user.next->cur_user_direct_size; index1++)
	{
		if (path == cur_user.next->direct[index1].directname)
		{
			break;
		}
	}
	int a;
	for (a = 0; a < cur_user.next->direct[index1].cur_file_size; a++)    //�ж��ļ��Ƿ����
	{
		if (cur_user.next->direct[index1].ufd[a].filename == name)
			break;
	}
	if (a >= cur_user.next->direct[index1].cur_file_size)
	{
		cout << "û������ļ�" << endl;
		return 0;
	}
	int i;
	//�ж��ļ��Ƿ��
	for (i = 0; i < cur_opentable->cur_openfilesize; i++)
	{
		if (cur_opentable->uof[i].filename == path + '/' + name)
			break;
	}
	if (i >= cur_opentable->cur_openfilesize)
	{
		cout << "�ļ�û�д򿪣� �޷���ȡ" << endl;
		return -1;
	}
	int fd = i; //��ȡ�ļ�������
	//�ж϶��ļ��ĺϷ���
	if (cur_opentable->uof[fd].protect_code == 0) //���Ǵ������ļ�����Ĭ�Ͽɶ���д�ġ�����
	{
		cout << "�ļ����ɶ�" << endl;
		return 0;
	}
	else
	{
		int len = cur_opentable->uof[fd].pointer; //�ļ��ĳ���
		int block_size = len / 512; //���̵ĸ���
		int offset = len % 512; //ƫ����
		if (offset != 0)
			block_size++;
		//�������һ���ļ���ʾ���̵������飬����һ���ļ���ʾ���̵�	���ݿ飬��ô���Ǽ����ļ�����ʼλ�þͲ��ü��ϴ��̵��������˰ɡ���
		//�����ļ��Ĵ���ļ�������char *fdisk��ʾһ�������̣�Ȼ��		ͬ�ļ������ݴ�������ָ����ָ��Ĳ�ͬ�ַ���
		char* first = fdisk + cur_opentable->uof[fd].addr * 512; //�ļ�����ʼ��ַ
		char* buf = (char*)malloc(513 * sizeof(char)); //������
		cout << "�ļ�������Ϊ :";
		for (int k = 0; k < block_size; k++)
		{
			if (k == block_size - 1)  //�������һ�����̿�
			{
				int j;
				for (j = 0; j < len - k * 512; j++)  //��ֵ�ļ�ʣ����ַ�����ʵ����ƫ����
				{
					buf[j] = first[j];
				}
				buf[j] = '\0';
				printf("%s\n", buf); //����ļ�������
			}
			else //�������һ�����̿飬Ҳ�����������Ѿ������Ĵ��̿�
			{
				cout << "i:" << i << " " << len - i * 512 << " " << endl;
				int j;
				for (j = 0; j < 512; j++)
					buf[j] = first[j]; //�������������������
				buf[j] = '\0';
				printf("%s", buf); //����ļ�������
				int next_block = fat[cur_opentable->uof[fd].addr].next; 				//����һ�����̿���ڽ��Ŷ���һ�����̿�
				first = fdisk + next_block * 512;
			}
		}
		cout << endl;
		cout << "�ļ���ȡ�ɹ�" << endl;
		free(buf); //�ͷŻ�����
		return 0;
	}
}

int CLOSE(string name)
{
	int fd = 100;
	for (int i = 0; i < cur_opentable->cur_openfilesize; i++)
	{
		if (cur_opentable->uof[i].filename == path + '/' + name)
		{
			fd = i;
			break;
		}
	}
	if (fd >= cur_opentable->cur_openfilesize)
	{
		cout << "���Ľ�δ��" << endl;
		return 0;
	}
	//���µ�ǰ�û����ļ�������Ϣ,���ǽ����һ�����ļ�����Ϣ�滻��Ҫ�رյĴ��ļ���λ��
	cur_opentable->uof[fd].filename = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].filename;
	cur_opentable->uof[fd].pointer = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].pointer;
	cur_opentable->uof[fd].protect_code = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].protect_code;
	cur_opentable->uof[fd].addr = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].addr;
	cur_opentable->cur_openfilesize--;
	cout << "�ļ��رճɹ�" << endl;
	return 1;
}

int CD()
{
	string temp_path;
	cin >> temp_path;
	if (temp_path == "..")
	{
		path = "";
		return 1;
	}
	int i;
	for (i = 0; i < cur_user.next->cur_user_direct_size; i++)
	{
		if (temp_path == cur_user.next->direct[i].directname)
			break;
	}
	if (i >= cur_user.next->cur_user_direct_size)
	{
		cout << "û�д�Ŀ¼" << endl;
		return 0;
	}
	path = temp_path;
	return 1;
}

int MKDIR(string name)
{
	if (cur_user.next->cur_user_direct_size == 16)
	{
		cout << "�û�Ŀ¼�����Ѿ��ﵽ���ֵ" << endl;
		return 0;
	}
	int i;
	for (i = 0; i < cur_user.next->cur_user_direct_size; i++)
	{
		if (cur_user.next->direct[i].directname == name)
			break;
	}
	if (i < cur_user.next->cur_user_direct_size)
	{
		cout << "��Ŀ¼���Ѵ���" << endl;
		return 0;
	}
	cur_user.next->direct[cur_user.next->cur_user_direct_size].directname = name;
	cur_user.next->direct[cur_user.next->cur_user_direct_size].cur_file_size = 0; //�´�����Ŀ¼������ļ�����Ϊ0
	cur_user.next->cur_user_direct_size++;
	cout << "����Ŀ¼�ɹ�" << endl;
	return 1;
}

int RMDIR(string name)
{
	int index;
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (name == cur_user.next->direct[index].directname)
			break;
	}
	if (name == path)
	{
		cout << "�����˳����ļ���" << endl;
		return 0;
	}
	for (int i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
	{
		for (int j = 0; i < cur_opentable->cur_openfilesize; j++)
			if (name + '/' + cur_user.next->direct[index].ufd[i].filename == cur_opentable->uof[j].filename)
			{
				cout << "���ȹر������ļ�" << endl;
				return 0;
			}
	}
	//ɾ�����ļ��е������ļ�
	for (int i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
	{
		fat[cur_user.next->direct[index].ufd[i].addr].used = 0;
		int temp = fat[cur_user.next->direct[index].ufd[i].addr].next;
		while (temp != -1)
		{
			fat[temp].used = 0;
			temp = fat[temp].next;
		}
	}
	cur_user.next->direct[index].cur_file_size = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].cur_file_size;  //ע������	��Ҫ��һ�����ڱ���ṹ������
	cur_user.next->direct[index].directname = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].directname;
	for (int i = 0; i < cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].cur_file_size; i++)  //ע������ļ�һ
	{
		cur_user.next->direct[index].ufd[i].addr = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].addr;
		cur_user.next->direct[index].ufd[i].filename = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].filename;
		cur_user.next->direct[index].ufd[i].length = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].length;
		cur_user.next->direct[index].ufd[i].protect_code = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].protect_code;
	}
	cur_user.next->cur_user_direct_size--; //Ŀ¼������1
	cout << "ɾ��Ŀ¼�ɹ�" << endl;
	return 1;
}

int DIR()
{
	int index;
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (path == cur_user.next->direct[index].directname)
		{
			break;
		}
	}
	if (path == "")
	{
		cout << "  Ŀ¼��" << endl;
		for (int i = 0; i < cur_user.next->cur_user_direct_size; i++)
		{
			cout << "  " << cur_user.next->direct[i].directname << endl;
		}
	}
	else
	{
		cout << "\t�ļ���\t�ļ�������\t�ļ�����\t�ļ���ʼ�̿��" << endl;
		for (int i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
		{
			cout << "\t" << cur_user.next->direct[index].ufd[i].filename << "\t" << cur_user.next->direct[index].ufd[i].protect_code << "\t" << "\t" << cur_user.next->direct[index].ufd[i].length << "\t" << "\t" << cur_user.next->direct[index].ufd[i].addr << endl;
		}
	}
	return 1;
}

int SET(string name, int protectcode)
{
	int index;
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (path == cur_user.next->direct[index].directname)
		{
			break;
		}
	}
	int i = 0;
	for (i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
	{
		if (name == cur_user.next->direct[i].ufd[i].filename)
			break;
	}
	if (i >= cur_user.next->direct[index].cur_file_size)
	{
		cout << "���û�û������ļ�" << endl;
		return 0;
	}
	int j;
	for (j = 0; i < cur_opentable->cur_openfilesize; j++)
	{
		if (cur_opentable->uof[j].filename == path + "/" + name)
			break;
	}
	if (j < cur_opentable->cur_openfilesize)
	{
		cout << "���ȹرո��ļ�" << endl;
		return 0;
	}
	cur_user.next->direct[index].ufd[i].protect_code = protectcode;
	return 1;
}

void INPUT_OPERATION()
{
	if (cur_user.username == "")
		cout << "localhost :";
	else
		cout << cur_user.username << "@localhost  home/" << path << "��";
	string operaton;
	cin >> operaton;
	if (operaton == "login")
	{
		LOGIN();
	}
	else if (operaton == "create")
	{
		string filename;
		cin >> filename;
		CREATE(filename);
	}
	else if (operaton == "del")
	{
		string name;
		cin >> name;
		DELETE(name);
	}
	else if (operaton == "open")
	{
		string name;
		cin >> name;
		OPEN(name);
	}
	else if (operaton == "close")
	{
		string name;
		cin >> name;
		CLOSE(name);
	}
	else if (operaton == "write")
	{
		string content;
		string name;
		cin >> name;
		WRITE(name);
	}
	else if (operaton == "read")
	{
		string name;
		cin >> name;
		READ(name);
	}
	else if (operaton == "exit")
	{
		exit(0);
	}
	else if (operaton == "cd")
	{
		CD();
	}
	else if (operaton == "dir")
	{
		DIR();
	}
	else if (operaton == "mkdir")
	{
		string name;
		cin >> name;
		MKDIR(name);
	}
	else if (operaton == "register")
	{
		REGISTER();
	}
	else if (operaton == "exit")
	{
		mark = 0;
	}
	else if (operaton == "set")
	{
		string name;
		int protextcode;
		cin >> name;
		cin >> protextcode;
		SET(name, protextcode);
	}
	else if (operaton == "rmdir")
	{
		string name;
		cin >> name;
		RMDIR(name);
	}
	else
	{
		cout << "�����������������" << endl;
	}
}

int main()
{
	cur_user.username = "";
	path = "";
	fdisk = (char*)malloc(1024 * 1024 * sizeof(int));

	cout << "*******************��ӭʹ�ö����ļ�ϵͳ*******************" << endl;
	cout << "        �����ʽ                ˵��                      " << endl;
	cout << "        register                ע���û�                  " << endl;
	cout << "        login                   ��¼                      " << endl;
	cout << "        cd Ŀ¼��               ���ĵ�ǰĿ¼              " << endl;
	cout << "        mkdir Ŀ¼��            ������Ŀ¼                " << endl;
	cout << "        rmdir Ŀ¼��            ɾ����Ŀ¼                " << endl;
	cout << "        dir                     ��ʾ��ǰĿ¼����Ŀ¼      " << endl;
	cout << "        create �ļ���           �����ļ�                  " << endl;
	cout << "        del �ļ���              ɾ���ļ�                  " << endl;
	cout << "        open �ļ���             ���ļ�                  " << endl;
	cout << "        close                   �ر��ļ�                  " << endl;
	cout << "        read                    ���ļ�                    " << endl;
	cout << "        write                   д�ļ�                    " << endl;
	cout << "        set �ļ��� �ļ�������   �����ļ�������            " << endl;
	cout << "        exit                    �˳�ϵͳ                  " << endl;

	while (mark)
		INPUT_OPERATION();
	free(fdisk);
	return 0;
}