// nidhuggc: -sc -optimal

#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

atomic_int x = 0;
atomic_int y = 0;

void *thread_1(void *unused) {
  atomic_store_explicit(&x, 1, memory_order_relaxed);
  atomic_thread_fence(memory_order_seq_cst);
  int a = atomic_load_explicit(&y, memory_order_relaxed);
  return NULL;
}

void *thread_2(void *unused) {
  atomic_store_explicit(&y, 1, memory_order_relaxed);
  atomic_thread_fence(memory_order_seq_cst);
  int b = atomic_load_explicit(&x, memory_order_relaxed);
  return NULL;
}

int main() {
  pthread_t t1, t2;
  if (pthread_create(&t1, NULL, thread_1, NULL)) abort();
  if (pthread_create(&t2, NULL, thread_2, NULL)) abort();
  return 0;
}
