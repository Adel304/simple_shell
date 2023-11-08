#include "simple_shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h) {
  size_t len = 0;

  while (h) {
    len++;
    h = h->next;
  }

  return len;
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head) {
  list_t *node;
  size_t list_length = list_len(head);

  if (!head || !list_length) {
    return NULL;
  }

  char **strings = malloc(sizeof(char *) * (list_length + 1));
  if (!strings) {
    return NULL;
  }

  for (node = head, size_t i = 0; node; node = node->next, i++) {
    size_t str_length = strlen(node->str) + 1;
    char *string = malloc(str_length);

    if (!string) {
      for (size_t j = 0; j < i; j++) {
        free(strings[j]);
      }

      free(strings);
      return NULL;
    }

    strcpy(string, node->str);
    strings[i] = string;
  }

  strings[list_length] = NULL;
  return strings;
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h) {
  size_t i = 0;

  while (h) {
    printf("%d: %s\n", h->num, h->str ? h->str : "(nil)");
    h = h->next;
    i++;
  }

  return i;
}


/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c) {
  while (node) {
    char *match = starts_with(node->str, prefix);
    if (match && ((c == -1) || (*match == c))) {
      return node;
    }
    node = node->next;
  }
  return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node) {
  size_t index = 0;

  while (head) {
    if (head == node) {
      return index;
    }

    head = head->next;
    index++;
  }

  return -1; // Node not found
}

