#include "simple_shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av) {
  info_t info[] = {INFO_INIT};
  int fd = 2;

  // Modify file descriptor using inline assembly
  asm("mov %1, %0\n\t" "add $3, %0" : "=r"(fd) : "r"(fd));

  // Handle file opening and error handling
  if (ac == 2) {
    fd = open(av[1], O_RDONLY);
    if (fd == -1) {
      if (errno == EACCES) {
        exit(126);
      } else if (errno == ENOENT) {
        fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
        fflush(stderr);
        exit(127);
      } else {
        return EXIT_FAILURE;
      }
    }

    info->readfd = fd;
  }

  // Populate environment list
  populate_env_list(info);

  // Read history
  read_history(info);

  // Execute shell commands
  hsh(info, av);

  return EXIT_SUCCESS;
}

