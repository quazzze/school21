// [2022] <sixtaleo/-/-> [legal/copyright]
#include "s21_string.h"

// WORKED // antinouse
void *s21_memchr(const void *str, int c, s21_size_t n) {
   char const *s = str;
   int counter = 0;
   while ((*s != (char)c) && (counter < n)) {
      counter++;
      s++;
   }
   if (*s != (char)c) return s21_NULL;
   else return (void*)s;
}
// WORKED // sixtaleo
s21_size_t s21_strlen(const char *str) {
    int len = 0;
    while (str[len] != 0) {
        len++;
    }
    return len;
}
// WORKED // sixtaleo
int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
// MAY BE WORKED // sixtaleo
char *s21_strcpy(char *dest, const char *src) {
    while (*dest) {
        *dest = *src;
        dest++;
        src++;
        if (*src == '\0') {
			break;
		}
    }
    *dest = '\0';
    return dest;
}

//------------------------------------------------------///
// WORKED // sixtaleo
char *s21_strcat(char *dest, const char *src) {
    int len1 = s21_strlen(dest);
    int len2 = s21_strlen(src);
    for (int i = 0; i < len2; i++) {
        dest[len1+i] = src[i];
    }
    dest[len1+len2] = '\0';
    return dest;
}
// WORKED // sixtaleo
char *s21_strchr(const char *str, int c) {
    while (*str != (char)c) {
        if(!*str++){
            return s21_NULL;
        }
    }
    return (char *)str;
}
// NEED TESTS // sixtaleo
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    int len1 = s21_strlen(dest);
    int len2 = s21_strlen(src);
    for (int i = 0; i < n; i++) {
        dest[len1+i] = src[i];
    }
    dest[len1+n] = '\0';
    return dest;
}
// NEED TESTS // sixtaleo
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    while (*str1 && *str1 == *str2 && n--) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
// FUNCTION BROKEN, NEED FULL REBUILD // BRITTNIS 

// NEED TESTS // sixtaleo
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    while (*dest && n) {
        *dest = *src;
        dest++;
        src++;
        n--;
        if (*src == '\0') {
			break;
		}
    }
    *dest = '\0';
    return dest;
}
// NEED TESTS // sixtaleo
s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t  result = 0, temp = 0;
    for (int i = 0; i < s21_strlen(str1); i++) {
        for (int j = 0; j < s21_strlen(str2); j++) {
            if (str1[i] == str2[j]) {
                temp++;
            }
        }
        if (temp == 0) {
            result++;
        } else {
            break;
        }
    }
    return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {

}