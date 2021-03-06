#ifndef _FB_DRAW_H_
#define _FB_DRAW_H_

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <linux/fb.h>


// struct fb_st {
//      struct fb_fix_screeninfo fix;
//      struct fb_var_screeninfo var;
//      unsigned long bpp;
//      int fd;
//      char *fbp;
// };


int fb_open(void);
void fb_close(void);
void fb_draw_point(int x, int y, int color);

int xres(void);
int yres(void);

#endif
