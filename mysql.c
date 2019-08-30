
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<mysql.h>
 
#define SERVER_PORT 5550
 
 
int main()
{
   MYSQL mysql;
    if (NULL == mysql_init(&mysql)) {    //分配和初始化MYSQL对象
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }
 //尝试与运行在主机上的MySQL数据库引擎建立连接
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
 
    mysql_close(&mysql);

return 0;
}

