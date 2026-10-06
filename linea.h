#ifndef __LINEA_H
#define __LINEA_H

#include <stdint.h>

#include "aes.h"

// The Line-A Parameter Block
typedef struct
{
   int16_t  v_planes,               /*   0: # Bit planes (1, 2 or 4)     */
            v_lin_wr,               /*   2: # bytes/scanline             */
            *contrl,
            *intin,
            *ptsin,                 /*  12: Coordinates input            */
            *intout,
            *ptsout,                /*  20: Coordinates output           */
            fg_bp_1,                /*  24: Plane 0                      */
            fg_bp_2,                /*  26: Plane 1                      */
            fg_bp_3,                /*  28: Plane 2                      */
            fg_bp_4,                /*  30: Plane 3                      */
            lstlin;                 /*  32: Draw last pixel of a line    */
                                    /*      (1) or don't draw it (0)     */
   uint16_t ln_mask;                /*  34: Line pattern                 */
   int16_t  wrt_mode,               /*  36: Writing modes                */
            x1, y1, x2, y2;         /*  38: Coordinate                   */
   void     *patptr;                /*  46: Fill pattern                 */
   uint16_t patmsk;                 /*  50: Fill pattern "mask"          */
   int16_t  multifill,              /*  52: Fill pattern for planes      */
            clip,                   /*  54: Flag for clipping            */
            xmn_clip, ymn_clip,
            xmx_clip, ymx_clip,     /*  60: Clipping rectangle           */
                                    /*      Rest for text_blt:           */
            xacc_dda,               /*  64: Set to 0x8000 before text    */
                                    /*      output                       */
            dda_inc,                /*  66: Scaling increment            */
            t_sclsts,               /*  68: Scaling direction            */
            mono_status,            /*  70: Proportional font            */
            sourcex, sourcey,       /*  72: Coordinates in font          */
            destx, desty,           /*  76: Screen coordinates           */
            delx, dely;             /*  80: Width and height of character*/
   uint16_t *fbase;                 /*  84: Pointer to font data         */
   int16_t  fwidth,                 /*  88: Width of font form           */
            style;                  /*  90: Font style effect            */
   uint16_t litemask,               /*  92: Mask for light               */
            skewmask;               /*  94: Mask for italic              */
   int16_t  weight,                 /*  96: Width for bold               */
            r_off,                  /*  98: Italic offset right          */
            l_off,                  /* 100: Italic offset left           */
            scale,                  /* 102: Scaling flag yes/no          */
            chup,                   /* 104: Character rotation angle *10 */
            text_fg;                /* 106: Text foreground colour       */
   void     *scrtchp;               /* 108: Pointer to 2 contiguous      */
                                    /*      scratch buffers              */
   int16_t  scrpt2,                 /* 112: Index in buffer              */
            text_bg,                /* 114: Unused                       */
            copy_tran,              /* 116: --                           */
            (*fill_abort)();        /* 118: Tests seedfill               */
} LINEA;

void linea_init(LINEA **parameter_block, FONT_HDR ***sysfont_pointers);
void linea_textblock_transfer();
void linea_showmouse();
void linea_hidemouse();

#endif