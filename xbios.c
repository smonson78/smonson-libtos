#include "xbios.h"

int32_t xbios_supexec(int32_t (*func)())
{
  register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
      "pea       (%1)\n\t"
      "move.w    #38,-(%%sp)\n\t"
      "trap      #14\n\t"
      "addq.l    #6,%%sp\n\t"
    : "=r"(val) /* outputs */
    : "p"(func) /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}

// Get screen logical base address
void *Logbase() {
  register void * val __asm__("d0");
  __asm__ __volatile__
  (
    "move.w    #3,-(%%sp)\n\t"
    "trap      #14\n\t"
    "addq.l    #2,%%sp\n\t"
  : /* outputs */
  : /* inputs */
  : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );
  return val;
}

// Get screen physical base address
void *Physbase() {
  register void * val __asm__("d0");
  __asm__ __volatile__
  (
    "move.w    #2,-(%%sp)\n\t"
    "trap      #14\n\t"
    "addq.l    #2,%%sp\n\t"
  : /* outputs */
  : /* inputs */
  : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );
  return val;
}
