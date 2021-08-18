/*
 * assignment2_tester.c - automated test cases for grading the
 * student's llfifo and cbfifo implementations
 * 
 * Author: Howdy Pierce, howdy.pierce@colorado.edu
 * 
 * To use: You'll need to modify the student's assignment to isolate
 * out the student's llfifo and cbfifo test cases; hopefully this is
 * as simple as just isolating their llfifo.c and cbfifo.c files. Then
 * do:
 * 
 * gcc -Wall -Werror assignment2_tester.c cbfifo.c llfifo.c -o run-(studentname)
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "llfifo.h"

#define max(x,y) ((x) > (y) ? (x) : (y))

int g_tests_passed = 0;
int g_tests_total = 0;

#define test_assert(value) {                                            \
  g_tests_total++;                                                      \
  if (value) {                                                          \
    g_tests_passed++;                                                   \
  } else {                                                              \
    printf("ERROR: test failure at line %d\n", __LINE__);               \
  }                                                                     \
}

#define test_equal(value1, value2) {                                    \
  g_tests_total++;                                                      \
  long res1 = (long)(value1);                                           \
  long res2 = (long)(value2);                                           \
  if (res1 == res2) {                                                   \
    g_tests_passed++;                                                   \
  } else {                                                              \
    printf("ERROR: test failure at line %d: %ld != %ld\n", __LINE__, res1, res2); \
  }                                                                     \
}


static void
test_llfifo_one_iteration(int capacity)
{
  char *strs[] =
    { "To be, or not to be: that is the question:",
      "Whether 'tis nobler in the mind to suffer",
      "The slings and arrows of outrageous fortune,",
      "Or to take arms against a sea of troubles,",
      "And by opposing end them? To die, to sleep—",
      "No more—and by a sleep to say we end",
      "The heart-ache and the thousand natural shocks",
      "That flesh is heir to, 'tis a consummation",
      "Devoutly to be wish'd. To die, to sleep;",
      "To sleep: perchance to dream: ay, there's the rub;",
      "For in that sleep of death what dreams may come",
      "When we have shuffled off this mortal coil,",
      "Must give us pause."
    };

  const int strs_len = sizeof(strs) / sizeof(const char *);
  llfifo_t *fifo;

  fifo = llfifo_create(capacity);
  test_assert(fifo != NULL);

  test_equal(llfifo_capacity(fifo), capacity);
  test_equal(llfifo_length(fifo), 0);
  test_equal(llfifo_dequeue(fifo), NULL);

  // enqueue one element, then dequeue it, make sure it all matches
  test_equal(llfifo_enqueue(fifo, strs[0]), 1);
  test_equal(llfifo_capacity(fifo), max(capacity, 1));
  test_equal(llfifo_length(fifo), 1);
  //test_equal(llfifo_dequeue(fifo), strs[0]);
  char *ans = llfifo_dequeue(fifo);
  printf("return: %s",ans);

  test_equal(llfifo_capacity(fifo), max(capacity, 1));
  test_equal(llfifo_length(fifo), 0);

  // enqueue all the elements, then dequeue all
  for (int i=0; i<strs_len; i++) {
    test_equal(llfifo_enqueue(fifo, strs[i]), i+1);
    test_equal(llfifo_capacity(fifo), max(capacity, i+1));
    test_equal(llfifo_length(fifo), i+1);
  }
  for (int i=0; i<strs_len; i++) {
    test_equal(llfifo_dequeue(fifo), strs[i]);
    test_equal(llfifo_length(fifo), strs_len - i - 1);
    test_equal(llfifo_capacity(fifo), max(capacity, strs_len));
  }

  // should be empty now
  test_equal(llfifo_length(fifo), 0);
  test_equal(llfifo_dequeue(fifo), NULL);
  test_equal(llfifo_capacity(fifo), max(capacity, strs_len));

  // enqueue one, then enqueue one, dequeue one, etc, through the whole list
  test_equal(llfifo_enqueue(fifo, strs[0]), 1);
  for (int i=1; i<strs_len; i++) {
    test_equal(llfifo_enqueue(fifo, strs[i]), 2);
    test_equal(llfifo_length(fifo), 2);
    test_equal(llfifo_dequeue(fifo), strs[i-1]);
    test_equal(llfifo_length(fifo), 1);
    test_equal(llfifo_capacity(fifo), max(capacity, strs_len));
  }
  test_equal(llfifo_dequeue(fifo), strs[strs_len-1]);
  
  // should be empty now
  test_equal(llfifo_length(fifo), 0);
  test_equal(llfifo_dequeue(fifo), NULL);
  test_equal(llfifo_capacity(fifo), max(capacity, strs_len));

  // create a second fifo
  const int capacity2 = 3;
  llfifo_t *fifo2;

  fifo2 = llfifo_create(capacity2);
  test_assert(fifo2 != NULL);
  test_equal(llfifo_capacity(fifo2), capacity2);
  test_equal(llfifo_length(fifo2), 0);
  test_equal(llfifo_dequeue(fifo2), NULL);

  // enqueuing the even numbered strings onto the second fifo, and the
  // odd numbered strings onto the original fifo
  for (int i=0; i<strs_len; i++) {
    llfifo_t * this_fifo = (i & 0x1) ? fifo : fifo2;
    test_equal(llfifo_enqueue(this_fifo, strs[i]), (i/2)+1);
    test_equal(llfifo_length(this_fifo), (i/2)+1);
  }
  test_equal(llfifo_capacity(fifo), max(capacity, strs_len));
  test_equal(llfifo_capacity(fifo2), max(capacity2, strs_len/2 + 1));

  // now dequeue and make sure everything comes out correctly
  for (int i=0; i<strs_len; i++) {
    llfifo_t * this_fifo = (i & 0x1) ? fifo : fifo2;
    test_equal(llfifo_dequeue(this_fifo), strs[i]);
  }
  test_equal(llfifo_length(fifo), 0);
  test_equal(llfifo_length(fifo2), 0);
  test_equal(llfifo_dequeue(fifo), NULL);
  test_equal(llfifo_dequeue(fifo2), NULL);

  test_equal(llfifo_capacity(fifo), max(capacity, strs_len));
  test_equal(llfifo_capacity(fifo2), max(capacity2, strs_len/2 + 1));

  llfifo_destroy(fifo);
  llfifo_destroy(fifo2);
}


void
test_llfifo()
{
  g_tests_passed = 0;
  g_tests_total = 0;
  
  //test_llfifo_one_iteration(0);
  test_llfifo_one_iteration(1);
  test_llfifo_one_iteration(5);
  test_llfifo_one_iteration(20);

  printf("%s: passed %d/%d test cases (%2.1f%%)\n", __FUNCTION__,
      g_tests_passed, g_tests_total,
      100.0*g_tests_passed/g_tests_total);
}


int main(int argc, char **argv)
{
  test_llfifo();
  printf("all tests complete\n");
}