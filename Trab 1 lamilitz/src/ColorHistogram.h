#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <vector>

#include "image.h"

class ColorHistogram {
   public:
      ColorHistogram(int x, int y, int length, int height);

      void draw();
      void clearHistogram();

      void setColorValues(std::vector<int> &values, char color);
      void setActiveChannels(bool r, bool g, bool b, bool l);
      void setSizeYScale(int highestValue);

   private:
      int x, y, length, height;
      float sizeYScale, sizeXScale;
      bool plotRed, plotGreen, plotBlue, plotLuminance;
      std::vector<int> redValues, greenValues, blueValues, luminanceValues;
};

#endif // COLORHISTOGRAM_H
