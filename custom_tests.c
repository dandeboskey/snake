#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function.
  char c = 'w';
  bool output_1 = is_tail(c);
  if (!assert_true("output_1", output_1)) {
    printf("test not working\n");
    return false;
  }
  char c2 = 'W';
  bool output2 = is_tail(c2);
  if(!assert_false("output2", output2)){
    return false;
  }
  return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  char c = 'A';
  bool output_1 = is_head(c);
  if (!assert_true("output_1", output_1)) {
    printf("test not working\n");
    return false;
  }
  char c2 = 'a';
  bool output2 = is_head(c2);
  if(!assert_false("output2", output2)) {
    return false;
  }
  return true;
}

bool test_is_snake() {
  // TODO: Implement this function.
  char c = '>';
  bool output_1 = is_snake(c);
  if (!assert_true("output_1", output_1)) {
    printf("test not working\n");
    return false;
  }
  char c2 = ' ';
  bool output2 = is_snake(c2);
  if(!assert_false("output2", output2)){
    return false;
  }
  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  char c = '>';
  char output_1 = body_to_tail(c);
  if ('d' != output_1) {
    printf("test not working\n");
    return false;
  }
  char c2 = 'o';
  char output2 = body_to_tail(c2);
  if('?' != output2){
    return false;
  }
  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  char c = 'D';
  char output_1 = head_to_body(c);
  if ('>' != output_1) {
    printf("test not working\n");
    return false;
  }
  char c2 = 'd';
  char output2 = head_to_body(c2);
  if('?' != output2){
    return false;
  }
  return true;
}

bool test_get_next_x() {
  // TODO: Implement this function.
  char testcase_next_x = 'v';
  char testcase_wrong = '>';
  unsigned int crow = 5;
  unsigned int output_next_x = get_next_row(crow, testcase_next_x);
  unsigned int output_wrong = get_next_row(crow, testcase_wrong);
  if (6 != output_next_x) { 
    printf("test not working\n");
    return false; 
  } if (5 != output_wrong) { 
    printf("test not working\n");
    return false; 
  }
  printf("test works\n");
  return true;
}

bool test_get_next_y() {
  // TODO: Implement this function.
  char testcase_next_y = 'd';
  char testcase_wrong = 'v';
  unsigned int ccol = 5;
  unsigned int output_next_y = get_next_col(ccol, testcase_next_y);
  unsigned int output_wrong = get_next_col(ccol, testcase_wrong);
  if (6 != output_next_y) { 
    printf("test not working\n");
    return false; 
  } if (5 != output_wrong) { 
    printf("test not working\n");
    return false; 
  }
  printf("test works\n");
  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_x()) {
    printf("%s\n", "test_get_next_x failed");
    return false;
  }
  if (!test_get_next_y()) {
    printf("%s\n", "test_get_next_y failed");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
