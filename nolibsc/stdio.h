#ifndef _STDIO_h
#define _STDIO_H

#define SYSEXIT 60
#define SYSWRITE 1
#define SYSREAD 0

typedef unsigned long size_t;

void sysexit(int err)     
{
        asm volatile                
        (                                                                
                "syscall"                                                
                :   
                :"a"(SYSEXIT),"d"(err)                                   
        );                          
}

// write (nolibsC)
void write(int fd, const char *buf, size_t len)
{
    asm volatile
    (
        "syscall"
        :
        :"a"(SYSWRITE),"D"(fd),"S"(buf),"d"(len)
    );
}

// read
void read(int fd, char *buf, size_t len)
{
    asm volatile
    (
        "syscall"
        :"=S"(buf)
        :"a"(SYSREAD),"D"(fd),"d"(len)
    );
}

// Wrapper for write
void print(const char *buf)
{
    const size_t len = strlen(buf);

    write(1, buf, len);
}

size_t strlen(const char *buf)
{
    size_t size = 0;
    while(buf[size] != '\0')
        ++size;

    return size;
}

void int_to_str(int num, char *str) 
{
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0) 
    {
        is_negative = 1;
        num = -num;
    }

    // Handle 0 separately
    if (num == 0) 
    {
        str[i++] = '0';
    }

    // Convert each digit from right to left
    while (num != 0) 
    {
        int digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    }

    // Add negative sign if necessary
    if (is_negative) 
    {
        str[i++] = '-';
    }


    // Reverse the string
    int j = 0;
    while (j < i / 2) 
    {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
        j++;
    }

    str[i++] = '\n';

    // Null-terminate the string
    str[i] = '\0';
}

#endif
