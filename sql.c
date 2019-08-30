#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<mysql/mysql.h>
//gcc -o Sql sql.c `mysql_config --cflags --libs`
int main()
{
 	MYSQL mysql;
    if (NULL == mysql_init(&mysql)) {    
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }
    if (NULL == mysql_real_connect(&mysql,
                "192.168.100.24",   //ip or host
                "root",             // name
                "root",				//password
                "information_schema",  //databases name
                3306,					//port
                NULL,
                0)) {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }
    printf("Connected MySQL successful! \n");
    return 0;
}
