/*socket tcp客户端*/
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
#include<mysql/mysql.h>
 
#define SERVER_PORT 5559
 
int main()
{

 	MYSQL mysql;
    if (NULL == mysql_init(&mysql)) {    
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }

    if (NULL == mysql_real_connect(&mysql,
                "localhost",
                "root",
                "qwer123456789",
                "ACARS_Original_MSG",
                3306,
                NULL,
                0)) {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }
 
    printf("Connected MySQL successful! \n");
    //mysql_close(&mysql);
   
   
	int clientSocket;
	struct sockaddr_in serverAddr;
	//char sendbuf[200];
	char recvbuf[4000];
	int iDataNum;
	if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}
 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);

	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("connect");
		return 1;
	}
 
	printf("connect with destination host...\n");

	char temp[400];
	char sqlstr[500];
	int flag_1=0,flag_2=0;
	

	
		
	while(1)
	{
	    //memset(recvbuf,'\0',sizeof(recvbuf));
		int ret = recv(clientSocket,recvbuf,4000,0);
		if(ret>0)
		{
			recvbuf[ret]='\0';
			//printf("recvbuf = %s",recvbuf);
			//printf("**********************************\n");
			char *p1=strstr(recvbuf,"SOH");
			char *p2=strstr(recvbuf,"ETX");
			//if(p1==NULL){printf("111111111111111111111111111111111111111111111111\n");}
			//if(p2==NULL){printf("222222222222222222222222222222222222222222222222\n");}
			while(p1!=NULL)
			{
			if(p2 ==NULL )
				{
					int i=0;
					printf("\nchangdu = %d\n",strlen(recvbuf)-(p1-recvbuf)-3);
				    int k=strlen(recvbuf)-(p1-recvbuf)-3;
					for(i =0; i< k;++i)
					{
					temp[i]=*(p1+i+3);
					printf("%c",*(p1+i+3));
					//printf("i=%d\n",i);
					}
					//printf("3333333333333333333333333333333333333333333333333");
					flag_1=i;
					flag_2=1; 
					p1=NULL;
					break;	
				}
				
				if(  p2!=NULL  & p1<p2)
				{   
					char *p = p1;
					int i;
					for(i=0; i< p2-p1-3; ++i)
					{
					temp[i]=*(p+3);
					p++;
					printf("%c",temp[i]);
					}
					flag_1=i;
					temp[flag_1]='\0';
					
					//flag_2=1;
					for(int p=0; p<flag_1;p++) {printf("%c",temp[p]);}
					printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
					sprintf(sqlstr, "INSERT INTO ACARS_Original_Msg (msg_content) VALUES('%s');", temp);
    				mysql_real_query(&mysql, sqlstr, strlen(sqlstr));
    				memset(sqlstr, 0, sizeof(sqlstr));
    				//memset(temp, 0, sizeof(temp));
    				char *p3=strstr(p2+3,"SOH");
    				char *p4=strstr(p2+3, "ETX");
    				p1=p3;
    				p2=p4;	
    				flag_1=0;	
    				flag_2=0;
				}
				
				if(p1 == NULL){break;}
				
				if(p2 != NULL & p1>p2)
				{
				int m;
				for(m=0; m <p2-recvbuf; ++m)
					{
						temp[flag_1+m] = *(recvbuf+m);
						printf("%c",temp[flag_1+m]);
					}
					flag_1= flag_1+m;
					temp[flag_1]='\0';
					
					for(int p=0; p<flag_1;p++) {printf("%c",temp[p]);}
					printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
					sprintf(sqlstr, "INSERT INTO ACARS_Original_Msg (msg_content) VALUES('%s');", temp);
    				mysql_real_query(&mysql, sqlstr, strlen(sqlstr));
    				memset(sqlstr, 0, sizeof(sqlstr));
    				flag_1=0;
    				p2=strstr(p1+3,"ETX");
			
				}
				
			
						
			}
		}
				
	}
	close(clientSocket);
	mysql_close(&mysql);
	//fclose(file1);
	//close(source);
	return 0;
}

