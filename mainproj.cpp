/* Main function of the project */
/* Group: The Trojans */
/* Mambers: Alexa Dorsey, Ibrahim Sorkhoh, Lingyu Wei, Xin-Zeng Wu */

#include <cstdlib>
#include "gz.h"
#include "disp.h"
#include "rend.h"
#define OUTFILE "./output.ppm"

//Vec2 iMouse(0,0);
Vec2 iResolution(512,512);
Vec2 camRot(0.2,0.01);//+Vec2(-.35,4.5)*(iMouse.yx()/iResolution.yx());
float iGlobalTime = 0;

int main(int argc, char *argv[]) {
  int width = iResolution.x, height = iResolution.y;
  int xRes, yRes, dispClass;
  Vec3 fragColor;
  Vec2 fragCoord;
  GzDisplay* display;

  int status = 0;
  status |= GzNewDisplay(&display, GZ_RGBAZ_DISPLAY, width, height);

  status |= GzGetDisplayParams(display, &xRes, &yRes, &dispClass);

  status |= GzInitDisplay(display);

  if (status) exit(GZ_FAILURE);
  
  initWorld();
  for (int i = 0; i < 100; i++) {
    iGlobalTime = i * 1.0/15.0;

    FILE *outfile;
    char outfilename[100];
    sprintf(outfilename,"./frame/%03d.ppm",i);
    if((outfile = fopen(outfilename, "wb")) == NULL) {
      printf("Could not open output file for writing %s \n", outfilename);
      return GZ_FAILURE;
    }


    for (int i = 0; i < width; i++) {
      fragCoord.x = i;
      for (int j = 0; j < height; j++) {
        fragCoord.y = 256-j;
        mainImage(fragColor, fragCoord);
        fragColor *= 4095;
        GzPutDisplay(display, i, j, fragColor[RED], fragColor[GREEN], fragColor[BLUE], 1, 0);
      }
    }

    GzFlushDisplay2File(outfile, display);

    if(fclose(outfile)) printf("The output file was not closed\n");
    
  }
  status |= GzFreeDisplay(display);
  if (status) return GZ_FAILURE;
  else return GZ_SUCCESS;
}