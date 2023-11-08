#include "simple_shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info) {
  if (!info->environ || info->env_changed) {
    free(info->environ);
    info->environ = list_to_strings(info->env);
    info->env_changed = 0;
  }

  return info->environ;
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var) {
  if (!info->env || !var) {
    return 0;
  }

  int i = 0;
  list_t *node = info->env;
  list_t *prev = NULL;

  while (node) {
    if (starts_with(node->str, var) && node->str[strlen(var)] == '=') {
      if (prev) {
        prev->next = node->next;
      } else {
        info->env = node->next;
      }
      free(node->str);
      free(node);
      info->env_changed = 1;
      break;
    }

    prev = node;
    node = node->next;
    i++;
  }

  return info->env_changed;
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value) {
  if (!var || !value) {
    return 0;
  }

  size_t var_len = strlen(var);
  size_t value_len = strlen(value);

  char *buf = malloc(var_len + value_len + 3);
  if (!buf) {
    return 1;
  }

  strcpy(buf, var);
  strcat(buf, "=");
  strcat(buf, value);

  list_t *node = info->env;
  list_t *prev = NULL;

  while (node) {
    if (strncmp(node->str, var, var_len) == 0 && node->str[var_len] == '=') {
      free(node->str);
      node->str = buf;
      info->env_changed = 1;
      free(buf); // No need to free buf anymore, as it's now owned by the node
      return 0;
    }

    prev = node;
    node = node->next;
  }

  add_node_end(&(info->env), buf, 0);
  info->env_changed = 1;
  return 0;
}
