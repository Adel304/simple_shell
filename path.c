#include "simple_shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(const char *path) {
  struct stat st;

  if (!path || stat(path, &st)) {
    return 0;
  }

  if (S_ISREG(st.st_mode)) {
    return 1;
  }

  return 0;
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(const char *pathstr, int start, int stop) {
  static char buf[1024];
  int i = 0;

  for (i = 0; i < stop - start; i++) {
    if (pathstr[start + i] != ':') {
      buf[i] = pathstr[start + i];
    }
  }

  buf[i] = '\0';
  return buf;
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(const info_t *info, const char *pathstr, const char *cmd) {
  if (!pathstr) {
    return NULL;
  }

  int path_len = strlen(cmd);
  if (path_len > 2 && strncmp(cmd, "./", 2) == 0) {
    if (is_cmd(info, cmd)) {
      return strdup(cmd);
    }
  }

  int i = 0, curr_pos = 0;
  char *path;

  while (1) {
    if (!pathstr[i] || pathstr[i] == ':') {
      path = dup_chars(pathstr, curr_pos, i);
      if (!*path) {
        strcat(path, cmd);
      } else {
        strcat(path, "/");
        strcat(path, cmd);
      }

      if (is_cmd(info, path)) {
        return path;
      }

      if (!pathstr[i]) {
        break;
      }

      curr_pos = i;
    }

    i++;
  }

  return NULL;
}

