#ifndef __AES_H
#define __AES_H

#include <stdint.h>
#include <aes_object.h>
#include <aes_window.h>

/* Event types */
typedef enum {
    MN_SELECTED = 10,
    WM_REDRAW = 20,
    WM_TOPPED,
    WM_CLOSED,
    WM_FULLED,
    WM_SIZED = 27,
    WM_MOVED,
    WM_NEWTOP
} WM_Event;

extern int16_t global[];
extern int16_t control[];
extern int16_t int_in[];
extern int16_t int_out[];
extern void *addr_in[];
extern void *addr_out[];

typedef struct
{
  int16_t *cb_pcontrol;  /* Pointer to control array */
  int16_t *cb_pglobal;   /* Pointer to global array  */
  int16_t *cb_pintin;    /* Pointer to int_in array  */
  int16_t *cb_pintout;   /* Pointer to int_out array */
  void **cb_padrin;    /* Pointer to adr_in array  */
  void **cb_padrout;   /* Pointer to adr_out array */
} AESPB;

typedef struct
{
	int16_t *contrl;    /* Pointer to control array */
	int16_t *intin;     /* Pointer to int_in array  */
	int16_t *ptsin;     /* Pointer to points in array  */
	int16_t *intout;    /* Pointer to int_out array */
	int16_t *ptsout;    /* Pointer to points out array */
} VDIPB;

// Mouse pointer form
typedef struct
{
  int16_t  mf_xhot;       /* X-position hot-spot */
  int16_t  mf_yhot;       /* Y-position hot-spot */
  int16_t  mf_nplanes;    /* Number of planes    */
  int16_t  mf_fg;         /* Mask colour         */
  int16_t  mf_bg;         /* Pointer colour      */
  int16_t  mf_mask[16];   /* Mask form           */
  int16_t  mf_data[16];   /* Pointer form        */
} MFORM;

// Memory Form Definition Block - for raster operations
typedef struct
{
  void *fd_addr;               /* Pointer to the start of the
                                  memory block, e.g. the
                                  screen memory base address  */
  int16_t fd_w;                /* Width in pixels             */
  int16_t fd_h;                /* Height in pixels            */
  int16_t fd_wdwidth;          /* Width of a line in words    */
  int16_t fd_stand;            /* 0 = Device-specific format  */
                               /* 1 = Standard format         */
  int16_t fd_nplanes;          /* Number of planes            */
  int16_t fd_r1, fd_r2, fd_r3; /* Reserved, must be 0         */
} MFDB;

typedef struct
{
  int16_t     font_id;        /* Font number                        0 */
  int16_t     point;          /* Size in points                     2 */
  int8_t      name[32];       /* Name of the font                   4 */
  uint16_t    first_ade;      /* First character in font            36 */
  uint16_t    last_ade;       /* Last character in font             38 */
  uint16_t    top;            /* Distance: Top line    <-> Baseline 40 */
  uint16_t    ascent;         /* Distance: Ascent line <-> Baseline 42 */
  uint16_t    half;           /* Distance: Half line   <-> Baseline 44 */
  uint16_t    descent;        /* Distance: Descent line<-> Baseline 46 */
  uint16_t    bottom;         /* Distance: Bottom line <-> Baseline 48 */
  uint16_t    max_char_width; /* Largest character width            50 */
  uint16_t    max_cell_width; /* Largest character cell width       52 */
  uint16_t    left_offset;    /* Left offset for italic (skewed)    54 */
  uint16_t    right_offset;   /* Right offset for italic (skewed)   56 */
  uint16_t    thicken;        /* Thickening factor for bold         58 */
  uint16_t    ul_size;        /* Width of underline                 60 */
  uint16_t    lighten;        /* Mask for light (0x5555)            62 */
  uint16_t    skew;           /* Mask for italic (0x5555)           64 */
  uint16_t    flags;          /* Various flags:
                                Set for system font
                                  Bit 1: Set if horizontal offset
                                        table is in use
                                  Bit 2: Set if Motorola format
                                  Bit 3: Set if non-proportional    66 */
  uint8_t     *hor_table;     /* Pointer to horizontal offset table 68 */
  uint16_t    *off_table;     /* Pointer to character offset table  72 */
  uint16_t    *dat_table;     /* Pointer to font image              76 */
  uint16_t    form_width;     /* Width of the font image            80 */
  uint16_t    form_height;    /* Height of the font image           82 */
  struct font_hdr *next_font;     /* Pointer to next font header    84 */
} FONT_HDR;

typedef enum {
    M_OFF = 256,
    M_ON = 257
} M_Mouse;

void aes();
void vdi();
int16_t crys_if(int16_t opcode);

int16_t appl_init();
int16_t appl_exit();
int16_t appl_write(int16_t ap_wid, int16_t ap_wlength, void *ap_wpbuff);

void v_opnvwk(int16_t *work_in, int16_t *handle, int16_t *work_out);
void vq_extnd(int16_t handle, int16_t owflag, int16_t *work_out);
void vq_mouse(int16_t handle, int16_t *pstatus, int16_t *x, int16_t *y);

int16_t graf_mouse(int16_t gr_monumber, MFORM *gr_mofaddr);
int16_t graf_handle(int16_t *gr_hwchar, int16_t *gr_hhchar,
  int16_t *gr_hwbox, int16_t *gr_hhbox);

// Form library
int16_t form_alert (int16_t fo_adefbttn, const char *fo_astring);
int16_t form_dial(int16_t fo_diflag, int16_t fo_dilittlx, int16_t fo_dilittly, int16_t fo_dilittlw,
   int16_t fo_dilittlh, int16_t fo_dibigx, int16_t fo_dibigy, int16_t fo_dibigw, int16_t fo_dibigh);

void v_clswk(int16_t handle);
void v_clsvwk(int16_t handle);
void v_eeos(int16_t handle);
void v_eeol(int16_t handle);

// Reverse video on/off
void v_rvon(int16_t handle);
void v_rvoff(int16_t handle);

void v_contourfill(int16_t handle, int16_t x, int16_t y, int16_t index);

void vro_cpyfm(int16_t handle, int16_t vr_mode, int16_t *pxyarray, MFDB *psrcMFDB, MFDB *pdesMFDB);

#define v_curaddress vs_curaddress
// Move cursor to specified position
void vs_curaddress(int16_t handle, int16_t row, int16_t column);

void set_screen_attr();

// event
int16_t evnt_mesag(int16_t *msg);
int16_t evnt_multi(int16_t ev_mflags,  int16_t ev_mbclicks,
    int16_t ev_mbmask,  int16_t ev_mbstate,
    int16_t ev_mm1flags, int16_t ev_mm1x,
    int16_t ev_mm1y, int16_t ev_mm1width,
    int16_t ev_mm1height, int16_t ev_mm2flags,
    int16_t ev_mm2x, int16_t ev_mm2y,
    int16_t ev_mm2width, int16_t ev_mm2height,
    int16_t *ev_mmgpbuff, int16_t ev_mtlocount,
    int16_t ev_mthicount, int16_t *ev_mmox,
    int16_t *ev_mmoy, int16_t *ev_mmbutton,
    int16_t *ev_mmokstate, int16_t *ev_mkreturn,
    int16_t *ev_mbreturn);

// VDI
int16_t vs_color(int16_t handle, int16_t color_index, int16_t *rgb_in);
int16_t vsf_color(int16_t handle, int16_t color_index);
int16_t vst_color(int16_t handle, int16_t color_index);

void vr_recfl(int16_t handle, int16_t *pxyarray);
void v_bar(int16_t handle, int16_t *pxyarray);
int16_t vswr_mode(int16_t handle, int16_t mode);
int16_t vsf_interior(int16_t handle, int16_t style);
void v_ellipse (int16_t handle, int16_t x, int16_t y, int16_t xradius, int16_t yradius);
void v_gtext(int16_t handle, int16_t x, int16_t y, const char *string);
void vqf_attributes(int16_t handle, int16_t *attrib);
int16_t vsf_style(int16_t handle, int16_t style_index);
int16_t vsf_perimeter(int16_t handle, int16_t per_vis);
void vsf_udpat(int16_t handle, int16_t *pfill_pat, int16_t planes);
void v_circle(int16_t handle, int16_t x, int16_t y, int16_t radius);
void v_justified(int16_t handle, int16_t x, int16_t y, int8_t *string, int16_t length, 
   int16_t word_space, int16_t char_space);
void vs_clip(int16_t handle, int16_t clip_flag, int16_t *pxyarray);
void v_pline(int16_t handle, int16_t count, int16_t *pxyarray);

// resource files
int16_t rsrc_free();
int16_t rsrc_gaddr(int16_t re_gtype, int16_t re_gindex, OBJECT **gaddr);
int16_t rsrc_load (const char *re_lpfname);

// menu
int16_t menu_bar(OBJECT *me_btree, Menu_Operation me_bshow);
int16_t menu_tnormal(OBJECT *me_ntree, int16_t me_ntitle, int16_t me_nnormal);

// file
int16_t fsel_input(char *fs_iinpath, char *fs_iinsel, int16_t *fs_iexbutton);

#endif
