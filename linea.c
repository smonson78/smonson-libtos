#include "linea.h"

// LINE-A initialisation (get parameter blocks)
void linea_init(LINEA **parameter_block, FONT_HDR ***sysfont_pointers) {
  __asm__ __volatile__
  (
    ".short 0xa000\n\t"      // Call Line-A initialisation
    "move.l %%a0,%0\n\t"     // Get address of parameter block from a0
    "move.l %%a1,%1\n\t"     // Get address of system font pointer array from a1
  : "=r"(*parameter_block), "=r"(*sysfont_pointers) /* outputs */
  : /* inputs */
  : "d0", "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );  
}

void linea_textblock_transfer() {
  __asm__ __volatile__
  (
    ".short 0xa008\n\t"      // Call Line-A text block transfer
  : /* outputs */
  : /* inputs */
  : "d0", "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );  
}

void linea_showmouse() {
  __asm__ __volatile__
  (
    ".short 0xa009\n\t"      // Call Line-A text block transfer
  : /* outputs */
  : /* inputs */
  : "d0", "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );  
}

void linea_hidemouse() {
  __asm__ __volatile__
  (
    ".short 0xa00a\n\t"      // Call Line-A text block transfer
  : /* outputs */
  : /* inputs */
  : "d0", "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );  
}
