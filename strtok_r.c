/* Reentrant string tokenizer.  Generic version.
 Copyright (C) 1991-2016 Free Software Foundation, Inc.
 This file is part of the GNU C Library.

 The GNU C Library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 The GNU C Library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with the GNU C Library; if not, see
 <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifndef HAVE_STRTOK_R
#include <string.h>
#include <stdio.h>

#undef strtok_r

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
    char s[] = "-abc-=-def";
    char *sp;
    x = strtok_r(s, "-", &sp);	// x = "abc", sp = "=-def"
    x = strtok_r(NULL, "-=", &sp);	// x = "def", sp = NULL
    x = strtok_r(NULL, "=", &sp);	// x = NULL
    // s = "abc\0-def\0"
 */
char *
strtok_r(char *s, const char *delim, char **save_ptr)
{
  char *token;

  if (s == NULL)
    s = *save_ptr;

  /* Scan leading delimiters.  */
  s += strspn(s, delim);
  if (*s == '\0') {
    *save_ptr = s;
    return NULL;
  }

  /* Find the end of the token.  */
  token = s;
  s = strpbrk(token, delim);
  if (s == NULL)
    /* This token finishes the string.  */
    *save_ptr = strchr(token, '\0');
  else {
    /* Terminate the token and make *SAVE_PTR point past it.  */
    *s = '\0';
    *save_ptr = s + 1;
  }
  return token;
}
#endif /* HAVE_STRTOK_R */