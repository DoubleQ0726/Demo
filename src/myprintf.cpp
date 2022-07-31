#include <iostream>
#include <stdarg.h>

//C 风格
static void MyPrintf(const char* format...)
{
    va_list va;
    va_start(va, format);
    char ch;
    while (*format)
    {
        ch = *format;
        if (ch == '%')
        {
            ch = *(++format);
            if (ch == 's')
            {
                const char* arg = va_arg(va, const char*);
                std::cout << arg;
            }
            else if (ch == 'd')
            {
                int arg = va_arg(va, int);
                std::cout << arg;
            }
            else if (ch == 'f')
            {
                double arg = va_arg(va, double);
                std::cout << arg;
            }
            ch = *(++format);
        }
        std::cout << ch;
        ++format;
    }
    va_end(va);
}

int main()
{
    std::string name = "SzQ";
    int age = 25;
    float grades = 99.8888f;
    MyPrintf("my name is %s and my age is %d years old! I get %f grades\n", name.c_str(), age, grades);
    std::cout << time(0) << std::endl;
    return 0;
}