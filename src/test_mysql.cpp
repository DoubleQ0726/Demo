#include <iostream>
#include <string>
#include <mysql/mysql.h>

int main(int argc, char** argv)
{
    const char* host = "localhost";
    const char* user = "root";
    const char* password = "Sz960726";
    const char* db = "mysql";
    MYSQL* connect = mysql_init(nullptr);
    if (mysql_real_connect(connect, host, user, password, db, 3306, nullptr, 0) == nullptr)
    {
        std::cout << "mysql connect error\n";
        exit(1);
    }
    if(mysql_select_db(connect, "mysql") != 0)
    {
        printf("select db error.");
        exit(1);
    }
    if (mysql_query(connect, "show tables"))
    {
        std::cout << "mysql query error\n";
    }
    MYSQL_RES *res = mysql_use_result(connect);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr)
    {
        std::cout << row[0] << std::endl;
    }
    mysql_free_result(res);
    mysql_close(connect);
    return 0;
}