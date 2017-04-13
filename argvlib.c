#include <string.h>
#include <stdlib.h>

#include "argv.h"

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifndef HAVE_STRTOK_R
extern char *
strtok_r(char *s, const char *delim, char **save_ptr);
#endif

#ifndef HAVE_ESTRTOK_R
extern char *
estrtok_r(char *s, const char *delim, char **save_ptr);
#endif

static char *(*FUNC_STRTOK_R)(char *, const char *, char **);

/**
 * Make argv array (*arvp) for tokens in s which are separated by
 * delimiters. Return -1 on error or the number of tokens otherwise.
 */
int
makeargv(const char *s, const char *delimiters, int flag, char ***argvp)
{
  if (flag == NOTOKENS) {
    FUNC_STRTOK_R = &strtok_r;
  }
  else {
    FUNC_STRTOK_R = &estrtok_r;
  }

  int argc;
  char *t, *next;
  int i;

  if ((t = (char *) calloc(strlen(s) + 1, sizeof(char))) == NULL) {
    *argvp = NULL;
    return -1;
  }

  strcpy(t, s);

  if ((*FUNC_STRTOK_R)(t, delimiters, &next) == NULL) {
    argc = 0;
  }
  else {
    for (argc = 1; (*FUNC_STRTOK_R)(NULL, delimiters, &next) != NULL; argc++)
      ;
  }

  free(t);
  if ((t = (char *) calloc(strlen(s) + 1, sizeof(char))) == NULL) {
    *argvp = NULL;
    return -1;
  }

  strcpy(t, s);

  if ((*argvp = (char **) calloc(argc + 1, sizeof(char *))) == NULL) {
    free(t);
    *argvp = NULL;
    return -1;
  }

  if (argc == 0) {
    free(t);
    **argvp = NULL;
    return 0;
  }

  **argvp = (*FUNC_STRTOK_R)(t, delimiters, &next);
  for (i = 1; i <= argc; i++) {
    *((*argvp) + i) = (*FUNC_STRTOK_R)(NULL, delimiters, &next);
  }

  return argc;
}

void
freeargv(char ***argvp)
{
  if (**argvp != NULL) {
    free(**argvp);
    **argvp = NULL;
  }

  if (*argvp != NULL) {
    free(*argvp);
    *argvp = NULL;
  }
}
