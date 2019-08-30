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
 

 
int main()
{
/*
    const char *filename="/mnt/hgfs/F/2019/20196TA002.txt";
    char line[100];
	FILE *file=NULL;
	file = fopen(filename,"r+" );
		if(!file)
		{
			perror("open error");
			exit(1);
		}
		//char string_1[8]="to_date";
	char string_1[2]="";
	char string_11[12]="str_to_date";
	//char string_2[10]="DD-MON-RR", string_22[12]="%d-%m月 -%y";
	char string_2[10]="DD-MON-RR", string_22[12]="%d-%m -%y";

    char temp_2[1000]; 
    char temp_3[1000];
    int m=0; 
    
    while(!feof(file))//only read three times
    {
    	
    	//if(m==50) break;
    	fgets(temp_2,1000,file);
    	m++;
    	int len_temp = strlen(temp_2);
    	char *p1=strstr(temp_2, "to_date");
    	
    	
          
    if(p1 != NULL)
    {
    	
    	int len_p1=p1- temp_2;
   
    	char *p2=strstr(p1,"),");
    	char *p3=strstr(p2, "'");
    	strcpy(temp_3,p3);
    	
    	int k=13;
    	
    	char *p=p1;
   		char temp_5[40];
   		temp_5[0]='s';
   		temp_5[1]='t';
   		temp_5[2]='r';
   		temp_5[3]='_';
   		int l=4;
    	while(p != p2)
    	{
    		temp_5[l]=*p;
    		p++;
    		l++;
    		
    	}
    	temp_5[l++]=')';
    	temp_5[l]=',';
    	for(int k=0; k<l+4;k++)
    	{
    	if(temp_5[k]<0) temp_5[k]=' ';
    	}
    	printf("temp_5=%s",temp_5);
    	
    	char *p5=strstr(temp_5,"DD-MON-RR");
    	*p5='%';
    	p5++;
    	*p5='d';
    	p5++; p5++;
    	*p5='%';
    	p5++;
    	*p5='m';
    	p5++;
    	*p5=' ';
    	p5++;
    	p5++;
    	*p5='%';
    	p5++;
    	*p5='y';
    	//printf("temp_5=%s",temp_5);
    	int strlen_temp5=strlen(temp_5);
    	for(int h=0; h<strlen_temp5;h++)
    	{
    		temp_2[len_p1]=temp_5[h];
    		len_p1++;
    	}
    	for(int i=0; i<strlen(temp_3); i++)
    	{
    		temp_2[len_p1]=temp_3[i];
    		len_p1++;
    	}

    }
    
    char line[100];
	FILE *file_2=NULL;
	file_2 = fopen("/mnt/hgfs/F/2019/2.txt","ab" );
		if(!file_2)
		{
			perror("open error");
			exit(1);
		}
	fwrite(temp_2,1,strlen(temp_2),file_2);
	memset(temp_2,0,sizeof(temp_2));
	memset(temp_3,0,sizeof(temp_3));
	fclose(file_2); 
    }                      
    fclose(file);
  */  
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

   char strstr_s[5000];
    char temp_2[3200];
    FILE *file_2=NULL;
	file_2 = fopen("/mnt/hgfs/F/2019/2.txt","r" );
	if(!file_2)
	{
		perror("open error");
		exit(1);
	}
	int label=0;
	int number=0;
	while(!feof(file_2))//only read three times
    {
    	//if(number==300) break;
    	fgets(temp_2,3200,file_2);
    	char *p1=strstr(temp_2,"Insert");
    	if(p1 == temp_2)
    	{	
    		strcat(strstr_s,temp_2);
    		fgets(temp_2,3200,file_2);
    		if(feof(file_2)) break;
    		char *p2=strrchr(temp_2,';');
    		while(!p2)
    		{
    		strcat(strstr_s,temp_2);
    		//printf("strstr_s=%s",strstr_s);
    		fgets(temp_2,3200,file_2);
    		p2=strrchr(temp_2,';');	
    		}
    		/*
    		if(p2 != NULL)
    		{
    		  
    			strrchr(temp_2,';');
    			strcat(strstr_s,temp_2);
    			
    			//mysql_real_query(&mysql, strstr_s, strlen(strstr_s));
    			printf("strstr_s=%s",strstr_s);
    			memset(strstr_s,0,sizeof(strstr_s));	
    		}
    		*/	
    		while(p2 != NULL)
    		{
    			p2--;
    			if(*p2==')')
    			{
    				strcat(strstr_s,temp_2);
    			
    			    mysql_real_query(&mysql, strstr_s, strlen(strstr_s));
    				printf("strstr_s=%s",strstr_s);
    				memset(strstr_s,0,sizeof(strstr_s));
    				break;	
    			}
    			else
    			{
    				strcat(strstr_s,temp_2);
    				fgets(temp_2,3200,file_2);
    				p2=strrchr(temp_2,';');	
    				
    			}
    		  
    			
    		}
    		
    	}
    	//number++;
    }
    mysql_close(&mysql);
    printf("okokokokokokokokokokokokok\n");
    

	return 0;
}

