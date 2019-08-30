/*socket tcp服务器端*/
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 5554


int main()
{
	
	int serverSocket;
	int sendSocket;

	struct sockaddr_in server_addr;
	struct sockaddr_in clientAddr;
	int addr_len = sizeof(clientAddr);
	int client;
	char buffer[20];
	int iDataNum;
	
	int k;  //后面加上去的
	//socket函数，失败返回-1
	int socket(int domain, int type, int protocol);
	//第一个参数表示使用的地址类型，一般都是ipv4，AF_INET
	//第二个参数表示套接字类型：tcp：面向连接的稳定数据传输SOCK_STREAM
	//第三个参数设置为0
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}

	bzero(&server_addr, sizeof(server_addr));
	//初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	//ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//对于bind，accept之类的函数，里面套接字参数都是需要强制转换成(struct sockaddr *)
	//bind三个参数：服务器端的套接字的文件描述符，
	if (bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("connect");
		return 1;
	}
	//设置服务器上的socket为监听状态
	if (listen(serverSocket, 5) < 0)
	{
		perror("listen");  
		return 1;
	}

	while (1)
	{
	
		client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
		if (client < 0)
		{
			perror("accept");
			continue;
		}
		//inet_ntoa   ip地址转换函数，将网络字节序IP转换为点分十进制IP
		//表达式：char *inet_ntoa (struct in_addr);
		printf("IP is %s\n", inet_ntoa(clientAddr.sin_addr));
		printf("Port is %d\n", htons(clientAddr.sin_port));
	
		/*
		while (1)
		{
			char buffer1[200];
			printf("请输入：");
			scanf("%s", buffer1);
			printf("buffer = %s",buffer1);
			send(client,buffer1,strlen(buffer1),0);

		};
		*/
	
		
		
		//首先发送文件名字
		const char *file="/mnt/hgfs/F/2019/20196TA002.txt";
		int source;
		if((source = open(file,O_RDONLY )) <0)
		{
			perror("open error");
			exit(1);
		}
		//write(source, file,strlen(file));  //可以向文件进行写操作
		//read(source,buffer,20);           //从文件读取20个字符 存到buffer中 再从buffer中取出5个send出去
		//send(client, buffer,5,0);
		//send(client, buffer,5,0);         //这个与上面发送的内容是一样的
		//k=read (source, buffer,20 );
		//send(client,buffer,20,0);
		//k=read (source, buffer,20 );        //这里读的确是接着后面那个继续读的
		//send(client,buffer,20,0);              
		
		while( ( k=read(source,buffer,20))>0)
		{
			send(client,buffer,20,0);
		}
		
		//printf("ok");
		close(client);
		
       
	}
	
	
	return 0;
}

