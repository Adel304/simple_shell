#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
    char *dest_ptr = dest;
    
    while ((*dest_ptr++ = *src++))
        ;
    
    return dest;
}

#include <stdlib.h>

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
    if (str == NULL)
        return NULL;

    int length = 0;
    const char *temp = str;

    while (*temp++)
        length++;

    char *ret = malloc(sizeof(char) * (length + 1));

    if (!ret)
        return NULL;

    for (int i = 0; i <= length; i++)
        ret[i] = str[i];

    return ret;
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(const char *str)
{
    if (!str)
        return;

    int i = 0;

    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

#include <unistd.h>

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\n'
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE] = {0};

    if (c != BUF_FLUSH)
    {
        buf[i++] = c;
        if (i >= WRITE_BUF_SIZE)
        {
            write(1, buf, i);
            i = 0;
        }
    }
    else
    {
        write(1, buf, i);
        i = 0;
    }
    
    return 1;
}
