#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

/*
gcc -c unit_test.c s21_string.c
ar rc libtest.a s21_string.o     
ranlib libtest.a          
macos: gcc unit_test.o -L. -ltest -lcheck -o rezult
or
ubuntu: gcc unit_test.o -L. -ltest -lcheck -o rezult -lm -lrt -lpthread -lsubunit
./rezult
*/

///
///      https://libcheck.github.io/check/doc/check_html/check_3.html
///


#pragma region tests
// Это конкретный тест.
START_TEST(s21_strlen_test_1) {
    char str[15] = "Test work done!";
    int i = 0;
    i = s21_strlen(str);
    // самая главная строка, в ней происходит сам тест. ck_assert_... может быть много. Чек сравнивает ожидаемое и получаемое значение. 
    ck_assert_int_eq(s21_strlen(str), 15);
} END_TEST  

START_TEST(s21_strlen_test_2) {
    char str[15] = "";
    int i = 0;
    i = s21_strlen(str);
    ck_assert_int_eq(s21_strlen(str), 0);
} END_TEST

START_TEST(s21_strcat_test_1) {
    char str[50] = "";
    s21_strcat(str, "This ");
    s21_strcat(str, "Function ");
    s21_strcat(str, "Work!");
    ck_assert_str_eq(str, "This Function Work!");
} END_TEST

START_TEST(s21_strcat_test_2) {
    char str[50] = "test";
    s21_strcat(str, "");
    ck_assert_str_eq(str, "test");
} END_TEST

START_TEST(s21_strchr_test_1) {
    char *p;
    p = strchr ("this is a test", ' ');
    ck_assert_str_eq(" is a test", p);
} END_TEST

START_TEST(s21_strchr_test_2) {
    char *p;
    p = strchr ("This must be null", '9');
    ck_assert_ptr_eq(NULL, p);
} END_TEST

START_TEST(s21_strncat_test_1) {
    char s1[11] = "hello ", s2[5] = "there";
    ck_assert_str_eq(s21_strncat(s1, s2, 5), "hello there");
} END_TEST

START_TEST(s21_strncat_test_2) {
    char s3[7] = "hello ";
    char s4[5] = "there";
    ck_assert_str_eq(s21_strncat(s3,s4, 1), "hello t");
} END_TEST

START_TEST(s21_strncmp_test_1) {
    char s1[5] = "hello";
    char s2[5] = "hello";
    ck_assert_int_eq(s21_strncmp(s1, s2, 5), 0);
} END_TEST

START_TEST(s21_strncmp_test_2) {
    char s1[6] = "1234";
    char s2[6] = "123 ";
    ck_assert_int_gt(s21_strncmp(s1, s2, 4), 0);
} END_TEST

#pragma endregion


#pragma region suits
//Сьют - это набор тестов. Для каждой функции свой сьют с набором тестов описанных выше.
Suite *s21_strlen_suite(void) {
    Suite *s;
    TCase *tc_strlen;

    s = suite_create("strlen");
    tc_strlen = tcase_create("test1");

    tcase_add_test(tc_strlen, s21_strlen_test_1);
    tcase_add_test(tc_strlen, s21_strlen_test_2);
    suite_add_tcase(s, tc_strlen);

    return s;
}

Suite *s21_strcat_suite(void) {
    Suite *s;
    TCase *tc_strcat;

    s = suite_create("strcat");
    tc_strcat = tcase_create("test2");

    tcase_add_test(tc_strcat, s21_strcat_test_1);
    tcase_add_test(tc_strcat, s21_strcat_test_2);
    suite_add_tcase(s, tc_strcat);

    return s;
}

Suite *s21_strchr_suite(void) {
    Suite *s;
    TCase *tc_strchr;

    s = suite_create("strchr");
    tc_strchr = tcase_create("test3");

    tcase_add_test(tc_strchr, s21_strchr_test_1);
    tcase_add_test(tc_strchr, s21_strchr_test_2);
    suite_add_tcase(s, tc_strchr);

    return s;
}

Suite *s21_strncat_suite(void) {
    Suite *s;
    TCase *tc_strncat;

    s = suite_create("strncat");
    tc_strncat = tcase_create("test4");

    tcase_add_test(tc_strncat, s21_strncat_test_1);
    tcase_add_test(tc_strncat, s21_strncat_test_2);
    suite_add_tcase(s, tc_strncat);

    return s;
}

Suite *s21_strncmp_suit(void) {
    Suite *s;
    TCase *tc_strncmp;

    s = suite_create("strncmp");
    tc_strncmp = tcase_create("test5");

    tcase_add_test(tc_strncmp, s21_strncmp_test_1);
    tcase_add_test(tc_strncmp, s21_strncmp_test_2);
    suite_add_tcase(s, tc_strncmp);

    return s;
}

#pragma endregion

//В мейне вызов сьюта/-ов для проверок. 
int main(void) {
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = s21_strlen_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);   



    s = s21_strcat_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);



    s = s21_strchr_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);



    s = s21_strncat_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);



    s = s21_strncmp_suit();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;    
}
