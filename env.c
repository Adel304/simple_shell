#include "simple_shell.h"

int _myenv(info_t *info) {
  // Assuming print_list_str() exists and prints the list of environment variables
  print_list_str(info->env);

  // Return 0 indicating successful execution
  return 0;
}


/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name) {
  list_t *node = info->env;
  char *p;

  while (node) {
    if (starts_with(node->str, name)) {
      p = node->str + strlen(name) + 1;
      return p;
    }
    node = node->next;
  }

  return NULL;
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info) {
  if (info->argc != 3) {
    _eputs("Incorrect number of arguments\n");
    return 1;
  }

  if (setenv(info->argv[1], info->argv[2], 1) == -1) {
    return 1;
  }

  return 0;
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info) {
  int i;

  if (info->argc == 1) {
    _eputs("Too few arguments.\n");
    return 1;
  }

  for (i = 1; i < info->argc; i++) {
    if (unsetenv(info->argv[i]) == -1) {
      return 1;
    }
  }

  return 0;
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info) {
  list_t *node = NULL;
  size_t i;

  for (i = 0; environ[i]; i++) {
    node = add_node_end(node, environ[i], 0);
  }

  info->env = node;
  return 0;
}

