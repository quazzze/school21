#ifndef SRC_S21_STRING_H
#define SRC_S21_STRING_H

#define s21_NULL    (void *)0

typedef unsigned s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t n);

s21_size_t s21_strlen(const char *str);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *dest, const char *src);
char  *s21_strchr(const char *str, int c);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);

#endif // SRC_S21_STRING_H_
