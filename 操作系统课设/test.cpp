#include <iostream>
#include<string>
#include <malloc.h>
using namespace std;

struct MFD//用户数据结构
{
	string username;//用户名
	string password;//密码
	struct USER_UFD* next;//指向用户文件的指针
};

struct UFD//文件夹数据结构
{
	struct file_message//文件数据结构
	{
		string filename;//文件名
		int protect_code;//文件保护码
		int length;//文件长度
		int addr;//文件起始地址
	}ufd[16];//一个文件夹最对可以有16个文件
	string directname;//文件夹名字
	int cur_file_size = 0;//当前该文件夹含有的文件数量
};

struct UOF//打开文件数据结构
{
	struct uof
	{
		string filename;//文件名字
		int pointer;//文件长度
		int protect_code;//文件保护码
		int addr;//文件其实地址
	}uof[16];//最多可以同时打开16个文件
	int cur_openfilesize = 0;//当前打开的文件数量
};

struct fat
{
	int next = -1;
	int used = 0;
}fat[64];

struct USER_UFD//用户文件数据结构
{
	struct UFD direct[16];//一个用户最多可以有16个文件夹
	int cur_user_direct_size = 0;//当前拥有的文件夹数量
};

int mark = 1;
struct USER_UFD cur_user_all_direct_array[16];//用户文件数组
int max_usersize = 16;//最多用户数量
int max_openfilesize = 16;//最多文件同时打开数量
struct MFD cur_user;//当前用户
struct UOF* cur_opentable;//指向打开文件数组的指针
char* fdisk;//模拟磁盘指针
struct UOF openfile[16];//每一个用户对应一个文件打开表对象，
MFD mfd[16]; //16个用户
int cur_user_size = 0;//记录当前用户的人数
string path;

int REGISTER();//注册用户
int LOGIN();//登录用户
int CREATE(string name);//创建文件
int DELETE(string name);//删除文件
int OPEN(string name);//打开文件
int WRITE(string name);//写文件
int READ(string name);//读文件
int CLOSE(string name);//关闭文件
int CD();//更改当前目录
int MKDIR(string name);//创建文件夹
int DIR();//显示当前目录的子目录
int SET(string name, int protectcode);//设置保护码
void INPUT_OPERATION();//指令输入

int REGISTER()
{
	cout << "请输入用户名：";
	string username;
	cin >> username;
	cout << "请输入密码：";
	string password;
	cin >> password;
	for (int i = 0; i < 16; i++)
	{
		if (mfd[i].username == username)
		{
			cout << "注册失败，该用户名已存在" << endl;
			return 0;
		}
	}
	mfd[cur_user_size].username = username;
	mfd[cur_user_size].password = password;
	cur_user_size++;
	cout << "注册成功" << endl;
	return 1;
}

int LOGIN()
{
	cout << "请输入用户名：";
	string username;
	cin >> username;
	cout << "请输入密码：";
	string password;
	cin >> password;
	int i;
	for (i = 0; i < cur_user_size; i++)
	{
		if (mfd[i].username == username)
		{
			if (mfd[i].password != password)
			{
				cout << "密码错误" << endl;
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
		cout << "没有此用户" << endl;
		return 0;
	}
	mfd[i].next = &(cur_user_all_direct_array[i]);
	cur_user = mfd[i];
	cur_user.next->cur_user_direct_size = mfd[i].next->cur_user_direct_size;
	cur_user_size++;
	cur_opentable = &openfile[cur_user_size]; //指针指向文件打开表对象
	cur_opentable->cur_openfilesize = 0;
	path = "";
	return 1;
}

int CREATE(string name)
{
	int index;
	if (path == "")
	{
		cout << "请在文件夹中创建文件" << endl;
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
		cout << "文件名重复" << endl;
		return 0;
	}
	if (cur_user.next->direct[index].cur_file_size == 16)
	{
		cout << "该文件夹文件已达到16个" << endl;
		return 0;
	}
	int j;
	for (j = 0; j < 64; j++)//判断是否有空闲块
	{
		if (fat[j].used == 0)
			break;
	}
	if (j >= 64)
	{
		cout << "磁盘没有空闲块了" << endl;
		return 0;
	}
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].filename = name;
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].addr = j; //文件起始盘块号
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].length = 0;
	cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size].protect_code = 2; //表示可读可写
	cur_user.next->direct[index].cur_file_size++;//用户文件数量加1
	return 1;
}

int DELETE(string name)
{
	if (path == "")
	{
		cout << "请在文件夹中删除文件" << endl;
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
		cout << "没有该文件" << endl;
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
		cout << "该文件已被打开，无法删除" << endl;
		return 0;
	}
	//更新当前用户目录下文件数组信息,就是将最后一个文件的信息替换到要删除的文件的位置
	fat[cur_user.next->direct[index].ufd[i].addr].used = 0; //没有使用
	cur_user.next->direct[index].ufd[i].filename = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].filename;
	cur_user.next->direct[index].ufd[i].addr = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].addr;
	cur_user.next->direct[index].ufd[i].length = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].length;
	cur_user.next->direct[index].ufd[i].protect_code = cur_user.next->direct[index].ufd[cur_user.next->direct[index].cur_file_size - 1].protect_code;
	cur_user.next->direct[index].cur_file_size--;
	//将该文件的占用的磁盘空间清空
	int temp = fat[cur_user.next->direct[index].ufd[i].addr].next;
	while (temp != -1)
	{
		fat[temp].used = 0;
		temp = fat[temp].next;
	}
	cout << "删除文件成功" << endl;
	return 1;
}

int OPEN(string name)
{
	string AllName = path + '/' + name;//设置该变量的原因是防止出现打开文件数组中存在文件夹名不同而文件同名的情况
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
		cout << "该用户没有这个文件" << endl;
		return 0;
	}
	if (cur_opentable->cur_openfilesize == max_openfilesize)
	{
		cout << "文件打开数量已经达到最大值" << endl;
		return 0;
	}
	if (path == "")
	{
		cout << "请在文件夹中打开文件" << endl;
		return 0;
	}
	for (int j = 0; i < cur_opentable->cur_openfilesize; j++)
	{
		if (cur_opentable->uof[i].filename == AllName)
		{
			cout << "该文件已经打开" << endl;
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
	cur_opentable->cur_openfilesize++; //文件打开数量加1
	cout << "文件打开成功" << endl;
	return k; //返回文件在文件打开表中的第几项
}

int WRITE(string name)
{
	int index; //标识当前目录在direct数组中第几个
	for (index = 0; index < cur_user.next->cur_user_direct_size; index++)
	{
		if (path == cur_user.next->direct[index].directname)
		{
			break;
		}
	}
	int i;
	//判读文件是否打开
	for (i = 0; i < cur_opentable->cur_openfilesize; i++)
	{
		if (cur_opentable->uof[i].filename == path + '/' + name)
			break;
	}
	if (i >= cur_opentable->cur_openfilesize)
	{
		cout << "文件没有打开， 无法写入" << endl;
		return -1;
	}
	int fd = i; //获取文件描述字
	//判断读文件的合法性
	if (cur_opentable->uof[fd].protect_code != 2)
	{
		cout << "文件不可写" << endl;
		return -1;
	}
	else
	{
		string content;
		cin.ignore();
		cout << "请输入文件要写入的内容: " << endl;;
		getline(cin, content); //读入一整行内容
		char buf[512];
		int len = content.length();
		int times = len / 512;
		int offset = len % 512;
		if (offset != 0)
			times++;
		for (int time = 0; i < times; i++)
		{
			if (time == times - 1) //注意这里不能写成times-- o.o!!!
			{
				for (int j = 0; j < offset; j++)
					buf[j] = content[j];
			}
			else
			{
				for (int j = 0; j < 512; j++)
					buf[j] = content[j];
			}
			int temp; //保存当前所写的文件在用户文件目录表的第几项，为了后面修改文件的大小
			int first_block = cur_opentable->uof[fd].addr; //用户文件存放的第一个磁盘块
			for (int k = 0; k < cur_user.next->direct[index].cur_file_size; k++)
			{
				if (cur_user.next->direct[index].ufd[k].addr == first_block)
				{
					temp = k;
					break;
				}
			}
			//追加写
			//找到该文件存放的最后一个磁盘块
			while (fat[first_block].next != -1)
			{
				first_block = fat[first_block].next;
			}
			//计算该文件存放的最后一个地址
			char* first;
			first = fdisk + first_block * 512 + cur_opentable->uof[fd].pointer % 512;
			//如果最后一个文件剩下的空间大于要写入的长度
			if (len <= 512 - cur_opentable->uof[fd].pointer % 512)
			{
				//strcpy(first, buf);  这句代码出现问题，可能是由于buf没有					读满，后面的值被访问了，非法！
				for (int i = 0; i < len; i++)
				{
					first[i] = buf[i];//将缓冲区的内容写入虚拟磁盘中
				}
				cur_opentable->uof[fd].pointer = cur_opentable->uof[fd].pointer + len;  //更新文件打开表
				cur_user.next->direct[index].ufd[temp].length = cur_user.next->direct[index].ufd[temp].length + len; //更新用户目录文件表
			}
			else  //如果剩下的空间不足写入
			{
				for (i = 0; i < 512 - cur_opentable->uof[fd].pointer % 512; i++)
				{ 	//写入一部分的内容到最后一个磁盘块的剩余空间
					first[i] = buf[i];
				}
				//计算分配完最后一个磁盘的剩余空间后，还剩下多少字节没有存储
				int last_size = len - (512 - cur_opentable->uof[fd].pointer % 512);
				int need_block_size = last_size / 512;
				int need_offset_size = last_size % 512;
				if (need_offset_size > 0)
					need_block_size++; //总共需要这么磁盘块
				int unused_block_size = 0; //记录没有使用过的磁盘块的个			数
				//int first_unused_block; //记录第一个没有被使用过的磁盘
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
					cout << "磁盘没有空间存放了" << endl;
					return 0;
				}
				else
				{
					int item = cur_opentable->uof[fd].addr;
					for (int p = 0; p < need_block_size; p++) //执行多次寻找空闲磁盘的操作，
					{
						for (int i = 0; i < 64; i++)
						{
							if (fat[i].used == 0) //没有被使用
							{
								first = fdisk + i * 512; //当前要写入的磁盘块的起始地址
								fat[i].used = 1; //标记被使用
								fat[item].next = i; //标记下一个磁盘
								item = i;
								break;
							}
						}
						if (p == need_block_size - 1)
						{
							for (int k = 0; k < need_offset_size; k++)  //将文件的偏移量写入最后一个文件中
								first[k] = buf[k];
							//更新最后一个磁盘块的next值
							fat[i].next = -1;
						}
						else  //如果不是最后一个空闲块
						{ //待解决问题，就是如果更新fat的next值
							for (int k = 0; k < 512; k++)
								first[k] = buf[k];
						}
					}
					cur_opentable->uof[fd].pointer = cur_opentable->uof[fd].pointer + last_size;  //更新文件打开表
					cur_user.next->direct[index].ufd[temp].length = cur_user.next->direct[index].ufd[temp].length + last_size; //更新用户目录文件表
				}
			}
		}
	}
	cout << "文件写入成功" << endl;
	return 0;
}

int READ(string name)
{
	int index1; //标识当前目录在direct数组中第几个
	for (index1 = 0; index1 < cur_user.next->cur_user_direct_size; index1++)
	{
		if (path == cur_user.next->direct[index1].directname)
		{
			break;
		}
	}
	int a;
	for (a = 0; a < cur_user.next->direct[index1].cur_file_size; a++)    //判断文件是否存在
	{
		if (cur_user.next->direct[index1].ufd[a].filename == name)
			break;
	}
	if (a >= cur_user.next->direct[index1].cur_file_size)
	{
		cout << "没有这个文件" << endl;
		return 0;
	}
	int i;
	//判读文件是否打开
	for (i = 0; i < cur_opentable->cur_openfilesize; i++)
	{
		if (cur_opentable->uof[i].filename == path + '/' + name)
			break;
	}
	if (i >= cur_opentable->cur_openfilesize)
	{
		cout << "文件没有打开， 无法读取" << endl;
		return -1;
	}
	int fd = i; //获取文件描述字
	//判断读文件的合法性
	if (cur_opentable->uof[fd].protect_code == 0) //我们创建的文件都是默认可读可写的。。。
	{
		cout << "文件不可读" << endl;
		return 0;
	}
	else
	{
		int len = cur_opentable->uof[fd].pointer; //文件的长度
		int block_size = len / 512; //磁盘的个数
		int offset = len % 512; //偏移量
		if (offset != 0)
			block_size++;
		//如果我用一个文件表示磁盘的引导块，用另一个文件表示磁盘的	数据块，那么我们计算文件的起始位置就不用加上磁盘的引导块了吧。。
		//关于文件的存放文件，我们char *fdisk表示一整个磁盘，然后不		同文件的内容存放在这个指针所指向的不同字符段
		char* first = fdisk + cur_opentable->uof[fd].addr * 512; //文件的起始地址
		char* buf = (char*)malloc(513 * sizeof(char)); //缓冲区
		cout << "文件的内容为 :";
		for (int k = 0; k < block_size; k++)
		{
			if (k == block_size - 1)  //则是最后一个磁盘块
			{
				int j;
				for (j = 0; j < len - k * 512; j++)  //赋值文件剩余的字符，其实就是偏移量
				{
					buf[j] = first[j];
				}
				buf[j] = '\0';
				printf("%s\n", buf); //输出文件的内容
			}
			else //不在最后一个磁盘块，也就是在其他已经读满的磁盘块
			{
				cout << "i:" << i << " " << len - i * 512 << " " << endl;
				int j;
				for (j = 0; j < 512; j++)
					buf[j] = first[j]; //缓冲区读满就输出内容
				buf[j] = '\0';
				printf("%s", buf); //输出文件的内容
				int next_block = fat[cur_opentable->uof[fd].addr].next; 				//读完一个磁盘块后，在接着读下一个磁盘块
				first = fdisk + next_block * 512;
			}
		}
		cout << endl;
		cout << "文件读取成功" << endl;
		free(buf); //释放缓冲区
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
		cout << "该文将未打开" << endl;
		return 0;
	}
	//更新当前用户打开文件数组信息,就是将最后一个打开文件的信息替换到要关闭的打开文件的位置
	cur_opentable->uof[fd].filename = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].filename;
	cur_opentable->uof[fd].pointer = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].pointer;
	cur_opentable->uof[fd].protect_code = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].protect_code;
	cur_opentable->uof[fd].addr = cur_opentable->uof[cur_opentable->cur_openfilesize - 1].addr;
	cur_opentable->cur_openfilesize--;
	cout << "文件关闭成功" << endl;
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
		cout << "没有此目录" << endl;
		return 0;
	}
	path = temp_path;
	return 1;
}

int MKDIR(string name)
{
	if (cur_user.next->cur_user_direct_size == 16)
	{
		cout << "用户目录数量已经达到最大值" << endl;
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
		cout << "该目录名已存在" << endl;
		return 0;
	}
	cur_user.next->direct[cur_user.next->cur_user_direct_size].directname = name;
	cur_user.next->direct[cur_user.next->cur_user_direct_size].cur_file_size = 0; //新创建的目录里面的文件个数为0
	cur_user.next->cur_user_direct_size++;
	cout << "创建目录成功" << endl;
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
		cout << "请先退出该文件夹" << endl;
		return 0;
	}
	for (int i = 0; i < cur_user.next->direct[index].cur_file_size; i++)
	{
		for (int j = 0; i < cur_opentable->cur_openfilesize; j++)
			if (name + '/' + cur_user.next->direct[index].ufd[i].filename == cur_opentable->uof[j].filename)
			{
				cout << "请先关闭所有文件" << endl;
				return 0;
			}
	}
	//删除该文件夹的所有文件
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
	cur_user.next->direct[index].cur_file_size = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].cur_file_size;  //注意这里	需要减一，由于本身结构的限制
	cur_user.next->direct[index].directname = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].directname;
	for (int i = 0; i < cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].cur_file_size; i++)  //注意这里的减一
	{
		cur_user.next->direct[index].ufd[i].addr = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].addr;
		cur_user.next->direct[index].ufd[i].filename = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].filename;
		cur_user.next->direct[index].ufd[i].length = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].length;
		cur_user.next->direct[index].ufd[i].protect_code = cur_user.next->direct[cur_user.next->cur_user_direct_size - 1].ufd[i].protect_code;
	}
	cur_user.next->cur_user_direct_size--; //目录数量减1
	cout << "删除目录成功" << endl;
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
		cout << "  目录名" << endl;
		for (int i = 0; i < cur_user.next->cur_user_direct_size; i++)
		{
			cout << "  " << cur_user.next->direct[i].directname << endl;
		}
	}
	else
	{
		cout << "\t文件名\t文件保护码\t文件长度\t文件起始盘块号" << endl;
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
		cout << "该用户没有这个文件" << endl;
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
		cout << "请先关闭该文件" << endl;
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
		cout << cur_user.username << "@localhost  home/" << path << "：";
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
		cout << "命令错误，请重新输入" << endl;
	}
}

int main()
{
	cur_user.username = "";
	path = "";
	fdisk = (char*)malloc(1024 * 1024 * sizeof(int));

	cout << "*******************欢迎使用二级文件系统*******************" << endl;
	cout << "        命令格式                说明                      " << endl;
	cout << "        register                注册用户                  " << endl;
	cout << "        login                   登录                      " << endl;
	cout << "        cd 目录名               更改当前目录              " << endl;
	cout << "        mkdir 目录名            创建子目录                " << endl;
	cout << "        rmdir 目录名            删除子目录                " << endl;
	cout << "        dir                     显示当前目录的子目录      " << endl;
	cout << "        create 文件名           创建文件                  " << endl;
	cout << "        del 文件名              删除文件                  " << endl;
	cout << "        open 文件名             打开文件                  " << endl;
	cout << "        close                   关闭文件                  " << endl;
	cout << "        read                    读文件                    " << endl;
	cout << "        write                   写文件                    " << endl;
	cout << "        set 文件名 文件保护码   设置文件保护码            " << endl;
	cout << "        exit                    退出系统                  " << endl;

	while (mark)
		INPUT_OPERATION();
	free(fdisk);
	return 0;
}