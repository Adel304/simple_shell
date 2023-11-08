#include "simple_shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num) {
  if (!head) {
    return NULL;
  }

  list_t *new_node = malloc(sizeof(list_t));
  if (!new_node) {
    return NULL;
  }

  memset(new_node, 0, sizeof(list_t));
  new_node->num = num;

  if (str) {
    new_node->str = strdup(str);
    if (!new_node->str) {
      free(new_node);
      return NULL;
    }
  }

  new_node->next = *head;
  *head = new_node;

  return new_node;
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num) {
  list_t *new_node, *node;

  if (!head) {
    return NULL;
  }

  new_node = malloc(sizeof(list_t));
  if (!new_node) {
    return NULL;
  }

  memset(new_node, 0, sizeof(list_t));
  new_node->num = num;

  if (str) {
    new_node->str = strdup(str);
    if (!new_node->str) {
      free(new_node);
      return NULL;
    }
  }

  if (*head) {
    node = *head;
    while (node->next) {
      node = node->next;
    }
    node->next = new_node;
  } else {
    *head = new_node;
  }

  return new_node;
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h) {
  size_t i = 0;

  while (h) {
    if (h->str) {
      printf("%s\n", h->str);
    } else {
      printf("(nil)\n");
    }

    h = h->next;
    i++;
  }

  return i;
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index) {
  if (!head || !*head) {
    return 0;
  }

  list_t *node = *head, *prev_node = NULL;
  unsigned int i = 0;

  if (!index) {
    *head = node->next;
    free(node->str);
    free(node);
    return 1;
  }

  while (node) {
    if (i == index) {
      prev_node->next = node->next;
      free(node->str);
      free(node);
      return 1;
    }

    i++;
    prev_node = node;
    node = node->next;
  }

  return 0;
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr) {
  if (!head_ptr || !*head_ptr) {
    return;
  }

  list_t *node;
  list_t *head = *head_ptr;

  while (head) {
    node = head;
    head = head->next;

    free(node->str);
    free(node);
  }

  *head_ptr = NULL;
}

