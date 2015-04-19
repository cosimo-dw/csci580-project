/* Main function of the project */
/* Group: The Trojans */
/* Mambers: Alexa Dorsey, Ibrahim Sorkhoh, Lingyu Wei, Xin-Zeng Wu */
#include <stdio.h>
#include <stdlib.h>
#include "gz.h"
#include "disp.h"
#include "mat.h"
#include "rend.cpp"

#define OUTFILE "./output.ppm"

int main(int argc, char *argv[]) {
  int width = 512, height = 512;
  int xRes, yRes, dispClass;
  float fragColor[3];
  float fragCoord[2];
  GzDisplay* display;

  int status = 0;

  status |= GzNewDisplay(&display, GZ_RGBAZ_DISPLAY, width, height);

  status |= GzGetDisplayParams(display, &xRes, &yRes, &dispClass);

  status |= GzInitDisplay(display);

  if (status) exit(GZ_FAILURE);

  FILE *outfile;
  if((outfile = fopen(OUTFILE, "wb")) == NULL) {
    printf("Could not open output file for writing %s \n", OUTFILE);
    return GZ_FAILURE;
  }

  for (int i = 0; i < width; i++) {
    fragCoord[X] = i;
    for (int j = 0; j < height; j++) {
      fragCoord[Y] = j;
      mainImage(fragColor, fragCoord);
      GzPutDisplay(display, i, j, fragColor[RED], fragColor[GREEN], fragColor[BLUE], 1, 0);
    }
  }

  GzFlushDisplay2File(outfile, display);

  if(fclose(outfile)) printf("The output file was not closed\n");
  
  status |= GzFreeDisplay(display);
  
  if (status) return GZ_FAILURE;
  else return GZ_SUCCESS;
}