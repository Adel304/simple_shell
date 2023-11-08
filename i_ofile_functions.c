#include "simple_shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *dir = _getenv(info, "HOME=");
	if (!dir)
		return NULL;

	size_t dir_len = _strlen(dir);
	size_t hist_file_len = _strlen(HIST_FILE);
	char *buf = malloc(sizeof(char) * (dir_len + hist_file_len + 2));
	if (!buf)
	{
		free(dir);
		return NULL;
	}

	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	free(dir);
	return buf;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	if (!filename)
		return -1;

	int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return -1;

	list_t *node = info->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return 1;
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
 int read_history(info_t *info)
{
    int linecount = 0;
    ssize_t rdlen;
    struct stat st;
    char *buf = NULL;
    char *filename = get_history_file(info);

    if (!filename)
        return 0;

    int fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;

    if (fstat(fd, &st) == -1)
    {
        close(fd);
        return 0;
    }

    off_t fsize = st.st_size;
    if (fsize < 2)
    {
        close(fd);
        return 0;
    }

    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
    {
        close(fd);
        return 0;
    }

    rdlen = read(fd, buf, fsize);
    buf[fsize] = '\0';
    close(fd);

    if (rdlen <= 0)
    {
        free(buf);
        return 0;
    }

    int last = 0;
    for (int i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != fsize)
    {
        build_history_list(info, buf + last, linecount++);
    }

    free(buf);

    info->histcount = linecount;

    while (info->histcount >= HIST_MAX)
    {
        delete_node_at_index(&(info->history), 0);
        info->histcount--;
    }

    renumber_history(info);

    return info->histcount;
}

============
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
void build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = malloc(sizeof(list_t));
    if (node == NULL) {
        // Handle memory allocation error
        return;
    }
    
    node->buf = buf;
    node->linecount = linecount;
    node->next = NULL;
    
    if (info->history == NULL) {
        info->history = node;
    } else {
        list_t *current = info->history;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;
    
    while (node != NULL) {
        node->num = i++;
        node = node->next;
    }
    
    info->histcount = i;
    return i;
}
