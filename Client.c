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
 
#define SERVER_PORT 5554
 
int main()
{



 	MYSQL mysql;
    if (NULL == mysql_init(&mysql)) {    
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }

    if (NULL == mysql_real_connect(&mysql,
                "192.168.100.24",
                "root",
                "root",
                "test",
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
	char recvbuf[1000];
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
	int number=1;
	char str_a;	
	char *p1=NULL,*p2=NULL;
	
	
while(1)
	{
		int ret = recv(clientSocket,recvbuf,1000,0);
		if(ret>0)
		{
			recvbuf[ret]='\0';
			
			printf("recvbuf = %s",recvbuf);
			//printf("**********************************\n");
		}
	}
	
	/*
	
	
	while(1)
	{
	    //memset(recvbuf,'\0',sizeof(recvbuf));
	   
		int ret = recv(clientSocket,recvbuf,400,0);
		
		
		if(ret>0)
		{
			recvbuf[ret]='\0';
			//printf("temp[0]_27=%c\n",temp[0]);  ok
			printf("recvbuf = %s",recvbuf);
			//printf("**********************************\n");
	
			//printf("temp[0]_25=%c\n",temp[0]);   //false
			
			p1=strstr(recvbuf,"SOH");
			p2=strstr(recvbuf,"ETX");
			
			if( ((p1 ==NULL) & (p2 ==NULL)) &(flag_2==1))
			{
				int i;
				for(i=0; i< strlen(recvbuf); i++)
				{
					temp[flag_1+i] = recvbuf[i];
				}
				flag_1 = flag_1+i;
			}
			
			while(p1!=NULL)
			{
				if(p2 ==NULL )
				{
					int i=0;
				    int k=strlen(recvbuf)-(p1-recvbuf)-3;
					for(i =0; i< k;i++)
					{
						temp[i]=*(p1+i+3);
					}
	
					flag_1=i;
					flag_2=1; 
					str_a=temp[0];
					p1=NULL;
					break;					
				}
				if((p2!=NULL) &(p1<p2))
				{   
					char *p = p1;
					int i;
					for(i=0; i< p2-p1-3; i++)
					{
						temp[i]=*(p+3);
						p++;
					}
					temp[i]='\0';
					flag_1=0;	
    				flag_2=0;
					//printf("temp[0]_2=%c\n",temp[0]);
					//temp[0]=str_a;
					//for(int b=1; b< i;b++){printf("%c",temp[b]);}
					sprintf(sqlstr, "INSERT INTO arinc620_dn_raw_msg (msg_content) VALUES('%s');", temp);
    				mysql_real_query(&mysql, sqlstr, strlen(sqlstr));
    				memset(sqlstr, '\0', sizeof(sqlstr));
    				memset(temp,'\0',sizeof(temp));
    				
    				char *p3=strstr(p2+2,"SOH");
    				char *p4=strstr(p2+2, "ETX");
    				p1=p3;
    				p2=p4;	
    				
				}
				
				if(p1 == NULL){break;}
				
				if( (p2 != NULL) & (p1>p2))
				{
					int m;
					//printf("temp[0]_9=%c\n",temp[0]);
					for(m=0; m <p2-recvbuf; m++)
					{
						temp[flag_1+m] = *(recvbuf+m);
						//printf("%c",temp[flag_1+m]);
					}
					
					//printf("flag_1=%d\n",flag_1);
					temp[m]='\0';
					//temp[0]=str_a;
					//for(int b=1; b< m;b++){printf("%c",temp[b]);}
					sprintf(sqlstr, "INSERT INTO arinc620_dn_raw_msg (msg_content) VALUES('%s');", temp);
    				mysql_real_query(&mysql, sqlstr, strlen(sqlstr));
    				memset(sqlstr, '\0', sizeof(sqlstr));
    				memset(temp,'\0',sizeof(temp));
    				flag_1=0;
    				flag_2=0;
    				p2=strstr(p1+2,"ETX");
    				//printf("temp[0]_10=%c\n",temp[0]);
			
				}
									
			}
			
			if(p1 == NULL & p2 !=NULL)
			{
			
				int m;
				//printf("temp[0]_5=%c\n",temp[0]);
				for(m=0; m <p2-recvbuf; m++)
					{
						temp[flag_1+m] = *(recvbuf+m);
					}
				flag_1= flag_1+m;
				temp[flag_1]='\0';
				//temp[0]=str_a;
				//for(int b=1; b< flag_1;b++){printf("%c",temp[b]);}
				sprintf(sqlstr, "INSERT INTO arinc620_dn_raw_msg (msg_content) VALUES('%s');", temp);
    			mysql_real_query(&mysql, sqlstr, strlen(sqlstr));
    			memset(sqlstr, '\0', sizeof(sqlstr));
    			memset(temp,'\0',sizeof(temp));
    			flag_1=0;
    			flag_2=0;
			}
			
		}
		//number++;		
	}
	close(clientSocket);
	mysql_close(&mysql);
	//fclose(file1);
	//close(source);
	*/
	return 0;
}

