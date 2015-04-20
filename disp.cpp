/*
*  disp.cpp -- definition file for Display
*  USC csci 580
*/

#include "gz.h"
#include "disp.h"
#include <climits>

int GzNewFrameBuffer(char** framebuffer, int width, int height)
{
  /* create a framebuffer:
   -- allocate memory for framebuffer : (sizeof)GzPixel x width x height
   -- pass back pointer
  */
  *framebuffer = new char[sizeof(GzPixel) * width * height];
  return GZ_SUCCESS;
}

int GzNewDisplay(GzDisplay **display, GzDisplayClass dispClass, int xRes, int yRes)
{
  /* create a display:
   -- allocate memory for indicated class and resolution
   -- pass back pointer to GzDisplay object in display
   */
  if (dispClass == GZ_RGBAZ_DISPLAY) {
    (*display) = new GzDisplay();
    (*display)->dispClass = dispClass;
    (*display)->xres = xRes;
    (*display)->yres = yRes;
  }
  return GZ_SUCCESS;
}


int GzFreeDisplay(GzDisplay *display)
{
  /* clean up, free memory */
  delete display->fbuf; // free the framebuffer before free the display to prevent memory leackage
  delete display;
  return GZ_SUCCESS;
}


int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes, GzDisplayClass	*dispClass)
{
  /* pass back values for an open display */
  if (xRes) (*xRes) = display->xres;
  if (yRes) (*yRes) = display->yres;
  if (dispClass) (*dispClass) = display->dispClass;
  return GZ_SUCCESS;
}


int GzInitDisplay(GzDisplay *display)
{
  /* set everything to some default values - start a new frame */
  display->open = 0;
  display->fbuf = new GzPixel[display->xres * display->yres];

  for (int i = 0; i < (display->xres * display->yres); ++i)
  {
    display->fbuf[i].red = 2047;
    display->fbuf[i].green = 1791;
    display->fbuf[i].blue = 1535;
    display->fbuf[i].alpha = 1;
    display->fbuf[i].z = INT_MAX;
  }
  return GZ_SUCCESS;
}

int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
  /* write pixel values into the display */
  if (i > display->xres || j > display->yres || i < 0 || j < 0) return GZ_FAILURE;
  if (r > 4095) r = 4095;
  if (g > 4095) g = 4095;
  if (b > 4095) b = 4095;
  display->fbuf[ARRAY(i,j)].red = r;
  display->fbuf[ARRAY(i,j)].green = g;
  display->fbuf[ARRAY(i,j)].blue = b;
  display->fbuf[ARRAY(i,j)].alpha = a;
  display->fbuf[ARRAY(i,j)].z = z;
  return GZ_SUCCESS;
}


int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
  /* pass back pixel value in the display */
  /* check display class to see what vars are valid */
  if (i > display->xres || j > display->yres || i < 0 || j < 0) return GZ_FAILURE;
  if(r) *r = display->fbuf[ARRAY(i,j)].red;
  if(g) *g = display->fbuf[ARRAY(i,j)].green;
  if(b) *b = display->fbuf[ARRAY(i,j)].blue;
  if(a) *a = display->fbuf[ARRAY(i,j)].alpha;
  if(z) *z = display->fbuf[ARRAY(i,j)].z;
  return GZ_SUCCESS;
}

int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{
  /* write pixels to ppm file based on display class -- "P6 %d %d 255\r" */
  int xres, yres;
  GzGetDisplayParams(display, &xres, &yres, NULL);
  //fprintf(outfile, "P6 %d %d 4095\r", xres, yres);
  fprintf(outfile, "P3 %d %d 4095\n", xres, yres);

  for (int j = 0; j < yres; j++)
  {
    for (int i = 0; i < xres; i++)
    {
      GzIntensity rgb[3];
      GzGetDisplay(display, i, j, &rgb[0], &rgb[1], &rgb[2], NULL, NULL);
      //fwrite(rgb, sizeof(GzIntensity), 3, outfile);
      fprintf(outfile,"%d %d %d ", rgb[0],rgb[1],rgb[2]);
    }
  }
  return GZ_SUCCESS;
}

int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{
  /* write pixels to framebuffer:
   - Put the pixels into the frame buffer
   - Caution: store the pixel to the frame buffer as the order of blue, green, and red
   - Not red, green, and blue !!!
  */
  int xres, yres;
  GzPixel *fb = (GzPixel*) framebuffer;
  GzGetDisplayParams(display, &xres, &yres, NULL);
  for (int i = 0; i < xres; i++)
  {
    for (int j = 0; j < yres; j++) *fb = display->fbuf[ARRAY(i,j)];
  }
  return GZ_SUCCESS;
}
