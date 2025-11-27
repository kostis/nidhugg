// nidhuggc: -sc -optimal

#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int x = 0;
atomic_int y = 0;

int a = -1;
int b = -1;

void *thread_1(void *unused) {
  x = 1;
  a = y;
  return NULL;
}

void *thread_2(void *unused) {
  y = 1;
  b = x;
  return NULL;
}

int main() {
  pthread_t t1, t2;
  if (pthread_create(&t1, NULL, thread_1, NULL)) abort();
  if (pthread_create(&t2, NULL, thread_2, NULL)) abort();
  if (pthread_join(t1, NULL)) abort();
  if (pthread_join(t2, NULL)) abort();
  assert(a == 1 || b == 1);
  return 0;
}
