#include "thinning.hpp"
#include "../utils/exception.hpp"

void AdjustmentThinning::apply(Image* target) {
  BWImage* bwImage = dynamic_cast<BWImage*>(target);
  if (bwImage == NULL) {
    throw new Exception("Image is not black and white");
  }
  int dk[] = {-1, -1, -1, 0, 1, 1, 1, 0, -1};
  int dl[] = {-1, 0, 1, 1, 1, 0, -1, -1, -1};
  bool done = true;

  int cnt = 0;
  do {
    done = true;
    cnt++;
    for (int i = 1; i < target->height - 1; i++) {
      for (int j = 1; j < target->width - 1; j++) {
        if (target->get_pixel(i, j).in[0] > 128) {
          int countWhite = 0;
          for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
              if (target->get_pixel(i + k, j + l).in[0] > 128) {
                countWhite++;
              }
            }
          }

          if (2 < countWhite && countWhite < 8) {
            int trans = 0;
            for (int k = 0; k < 8; k++) {
              if (target->get_pixel(i + dk[k    ], j + dl[k    ]).in[0] <  128 &&
                  target->get_pixel(i + dk[k + 1], j + dl[k + 1]).in[0] >= 128) {
                trans++;
              }
            }
            if (trans == 1) {
              done = false;
              target->set_black(i, j);
            }
          }
        }
      }
    }
  } while (!done);
}
