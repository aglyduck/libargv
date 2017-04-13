#ifndef _ARGVLIB_H
#define _ARGVLIB_H 1

#define EMPTYTOKENS 1 /* Token for consecutive delims */
#define NOTOKENS 0 /* No token for consecutive delims */

#ifdef __cplusplus
extern "C"
{
#endif
extern int makeargv(const char *s, const char *delimiters, int flag, char ***argvp);
extern void freeargv(char ***argvp);
#ifdef __cplusplus
}
#endif
#endif /* _ARGVLIB_H */
