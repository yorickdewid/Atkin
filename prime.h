#ifndef PRIMEGEN_H
#define PRIMEGEN_H

#include <stdint.h>

#define PRIMEGEN_WORDS 2048
#define B32 PRIMEGEN_WORDS
#define B (PRIMEGEN_WORDS * 32)

typedef struct {
  uint32_t buf[16][PRIMEGEN_WORDS];
  uint64_t p[512]; /* p[num-1] ... p[0], in that order */
  int num;
  int pos; /* next entry to use in buf; WORDS to restart */
  uint64_t base;
  uint64_t L;
} primegen;

extern void primegen_sieve(primegen *);
extern void primegen_fill(primegen *);

extern void primegen_init(primegen *);
extern uint64_t primegen_next(primegen *);
extern uint64_t primegen_peek(primegen *);
extern uint64_t primegen_count(primegen *, uint64_t to);
extern void primegen_skipto(primegen *, uint64_t to);

#endif
