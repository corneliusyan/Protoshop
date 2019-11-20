#include <iostream>
#include <vector>
#include "../image/b_w.hpp"
#include "./number_recognition.hpp"
#include "../filter/filter.hpp"

namespace nr {
  struct t_point {
    int r, c;
    t_point() { r = 0; c = 0; }
    t_point(int _r, int _c) { r = _r; c = _c; }
  };

  struct t_bound {
    int minR, maxR, minC, maxC;
  };

  bool isBlack(pixel px) {
    return px.in[0] < 10;
  }

  bool isWhite(pixel px) {
    return !isBlack(px);
  }

  void floodfill(BWImage* img, int** mark, int r, int c) {
    int dr[] = {0, 1, -1, 0, 1, 1, -1, -1};
    int dc[] = {1, 0, 0, -1, 1, -1, 1, -1};
    for (int i = 0; i < 8; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];
      if (0 <= nr && nr < img->height && 0 <= nc && nc < img->width) {
        if (mark[nr][nc] == -1 && nr::isWhite(img->get_pixel(nr, nc))) {
          mark[nr][nc] = mark[r][c];
          floodfill(img, mark, nr, nc);
        }
      }
    }
  }

  int** createMatrixBlobLabel(BWImage* img, int* counter) {
    int** mark = new int*[img->height];
    for (int i = 0; i < img->height; i++) {
      mark[i] = new int[img->width];
      for (int j = 0; j < img->width; j++) {
        mark[i][j] = -1;
      }
    }

    for (int i = 0; i < img->height; i++) {
      for (int j = 0; j < img->width; j++) {
        if (mark[i][j] == -1 && isWhite(img->get_pixel(i, j))) {
          mark[i][j] = *counter;
          floodfill(img, mark, i, j);
          (*counter)++;
        }
      }
    }
    return mark;
  }

  void findBound(int r, int c, int** mark, int numBlob, t_bound* bounds) {
    for (int i = 0; i < numBlob; i++) {
      bounds[i].minR = r - 1; bounds[i].maxR = 0;
      bounds[i].minC = c - 1; bounds[i].maxC = 0;
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        int _mark = mark[i][j];
        if (mark[i][j] != -1) {
          bounds[_mark].minR = std::min(bounds[_mark].minR, i);
          bounds[_mark].maxR = std::max(bounds[_mark].maxR, i);
          bounds[_mark].minC = std::min(bounds[_mark].minC, j);
          bounds[_mark].maxC = std::max(bounds[_mark].maxC, j);
        }
      }
    }
  }

  void determineBlob(int numBlob, t_bound* bounds, bool* isNoise, int minWidth, int maxWidth, int minHeight, int maxHeight) {
    for (int i = 0; i < numBlob; i++) {
      int t_boundHeight = bounds[i].maxR - bounds[i].minR + 1;
      int t_boundWidth = bounds[i].maxC - bounds[i].minC + 1;
      isNoise[i] = !(minWidth <= t_boundWidth && t_boundWidth <= maxWidth &&
                    minHeight <= t_boundHeight && t_boundHeight <= maxHeight);
    }
  }

  void removeUnwantedBlob(BWImage* img, int** mark, bool* isNoise) {
    for (int i = 0; i < img->height; i++) {
      for (int j = 0; j < img->width; j++) {
        if (mark[i][j] != -1 && isNoise[mark[i][j]]) {
          img->set_pixel(i, j, pixel(0));
        }
      }
    }
  }

  struct t_countour {
    std::vector<int> directions;
    t_point centroid;
  };

  bool validPoint(BWImage* img, int r, int c) {
    return (
      0 <= r && r < img->height &&
      0 <= c && c < img->width
    );
  }

  struct character {
    char cc;
    int r;
    int c;
    int count;

    character() {
      cc = ' ';
      r = 0;
      c = 0;
      count = 0;
    }
  };

  std::string tmpltChar = "0128345WB679AHCDEFGIJKLMNOPQRSTUVXYZ";
  std::string tmpltMap[36][9] = {
    { // 0
      " +++ ",
      "     ",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "     ",
      " +++ "
    },
    { // 1
      " +++ ",
      " +++ ",
      " +++ ",
      "  ++ ",
      "  ++ ",
      "  ++ ",
      "   + ",
      "   + ",
      "   + "
    },
    { // 2
      "  +  ",
      "     ",
      "--  +",
      "-    ",
      "     ",
      "   --",
      "  ---",
      "     ",
      " ++++"
    },
    { // 8
      "- + -",
      "     ",
      "+ - +",
      "     ",
      "- + -",
      "     ",
      "+ - +",
      "     ",
      "- + -"
    },
    { // 3
      "  +  ",
      "     ",
      "- - +",
      "-    ",
      "- ++ ",
      "-    ",
      "- - +",
      "     ",
      "  +  "
    },
    { // 4
      "--   ",
      "-    ",
      "    -",
      "   --",
      "     ",
      "     ",
      "     ",
      " - + ",
      " - + "
    },
    { // 5
      "  +  ",
      "     ",
      "+ ---",
      "     ",
      "  +  ",
      "     ",
      "---  ",
      "     ",
      "  +  "
    },
    { // W
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+   +",
      "+ + +",
      "+ + +",
      " +++ ",
      "  +  "
    },
    { // B
      "+++  ",
      "+    ",
      "+ - +",
      "+    ",
      "+++  ",
      "+    ",
      "+ - +",
      "+    ",
      "+++  "
    },
    { // 6
      " ++  ",
      "     ",
      "+ ---",
      "     ",
      "  +  ",
      "     ",
      "+ - +",
      "     ",
      "  +  "
    },
    { // 7
      " ++++",
      "    +",
      "---  ",
      "--   ",
      "-    ",
      "-    ",
      "-   -",
      "- + -",
      "- + -"
    },
    { // 9
      "  +  ",
      "     ",
      "+ - +",
      "     ",
      "  +  ",
      "     ",
      "--- +",
      "     ",
      "  +  "
    },
    { // A
      "- + -",
      "-   -",
      " +-+ ",
      "     ",
      " +++ ",
      "     ",
      "+ - +",
      "+ - +",
      "+ - +"
    },
    { // H
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+++++",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +"
    },
    { // C
      "- + -",
      "     ",
      "  -  ",
      "  -  ",
      "+ ---",
      "  -  ",
      "  -  ",
      "     ",
      "- + -"
    },
    { // D
      "+++ -",
      "+    ",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+    ",
      "+++ -"
    },
    { // E
      "+++++",
      "+    ",
      "+ ---",
      "+    ",
      "+++  ",
      "+    ",
      "+ ---",
      "+    ",
      "+++++"
    },
    { // F
      "+++++",
      "+    ",
      "+ ---",
      "+    ",
      "+    ",
      "+ ---",
      "+ ---",
      "+ ---",
      "+ ---"
    },
    { // G
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // I
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // J
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // K
      "+   +",
      "+    ",
      "+  + ",
      "+   +",
      "+++ -",
      "+   -",
      "+  + ",
      "+    ",
      "+   +"
    },
    { // L
      "  ---",
      "+ ---",
      "+ ---",
      "+ ---",
      "+ ---",
      "+ ---",
      "+ ---",
      "+    ",
      "++++ "
    },
    { // M
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // N
      "+ - +",
      "+ - +",
      "++- +",
      "+   +",
      "+ + +",
      "+   +",
      "+ -++",
      "+ - +",
      "+ - +"
    },
    { // O
      "- + -",
      "     ",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "     ",
      "- + -"
    },
    { // P
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // Q
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // R
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // S
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // T
      "+++++",
      "  +  ",
      "- + -",
      "- + -",
      "- + -",
      "- + -",
      "- + -",
      "- + -",
      "- + -"
    },
    { // U
      "  -  ",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "+ - +",
      "     ",
      "- + -"
    },
    { // V
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    },
    { // X
      "+ - +",
      "     ",
      " + + ",
      "     ",
      "- + -",
      "     ",
      " + + ",
      "     ",
      "+ - +"
    },
    { // Y
      "+ - +",
      "+ - +",
      " + + ",
      " + + ",
      "- + -",
      "- + -",
      "- + -",
      "- + -",
      "- + -"
    },
    { // Z
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----",
      "-----"
    }
  };

  char characterRecognition(int r, int c, int** pixel) {
    if (r != 9 && c != 5) throw "not implemented";
    char candidate = '0';
    int minWrongs = 50;
    for (int n = 0; n < tmpltChar.length(); n++) {
      bool valid = true;
      int wrongs = 0;
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
          if (tmpltMap[n][i][j] == '+' && pixel[i][j] == 0) { valid = false; wrongs++; }
          if (tmpltMap[n][i][j] == '-' && pixel[i][j] == 1) { valid = false; wrongs++; }
        }
      }
      if (valid) return tmpltChar[n];
      else if (wrongs < minWrongs) {
        minWrongs = wrongs;
        candidate = tmpltChar[n];
      }
    }
    return candidate;
  }

  std::vector<character> makeSuperPixel(int numBlob, int** mark, t_bound* bounds, bool* isNoise) {
    int height = 9;
    int width = 5;

    std::vector<character> res;
    for (int blob = 0; blob < numBlob; blob++) {
      if (isNoise[blob]) continue;

      t_bound bound = bounds[blob];
      character newchar;

      int** superPixel = new int*[height];
      int** superPixelCount = new int*[height];
      for (int i = 0; i < height; i++) {
        superPixel[i] = new int[width];
        superPixelCount[i] = new int[width];
        for (int j = 0; j < width; j++) {
          superPixel[i][j] = 0;
          superPixelCount[i][j] = 0;
        }
      }

      for (int i = bound.minR; i < bound.maxR; i++) {
        for (int j = bound.minC; j < bound.maxC; j++) {
          if (mark[i][j] == blob) {
            newchar.r += i;
            newchar.c += j;
            newchar.count += 1;
            superPixel[(i - bound.minR) * height / (bound.maxR - bound.minR)][(j - bound.minC) * width / (bound.maxC - bound.minC)] += 1;
          }
          superPixelCount[(i - bound.minR) * height / (bound.maxR - bound.minR)][(j - bound.minC) * width / (bound.maxC - bound.minC)] += 1;
        }
      }

      for (int i= 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          superPixel[i][j] = (superPixel[i][j] * 2 >= superPixelCount[i][j]);
          std::cout << (superPixel[i][j] ? '#' : ' ');
        }
        std::cout << std::endl;
      }

      newchar.r /= newchar.count;
      newchar.c /= newchar.count;

      newchar.cc = characterRecognition(height, width, superPixel);
      res.push_back(newchar);

      for (int i = 0; i < height; i++) {
        delete superPixel[i];
        delete superPixelCount[i];
      }
      delete superPixel;
      delete superPixelCount;
    }
    sort(res.begin(), res.end(), [](const character& a, const character& b) {
      return a.c < b.c;
    });
    return res;
  }
}

std::string numberRecognition(BWImage* img) {
  BWImage imgCopy = *img;

  int numBlob = 0;
  int** mark = nr::createMatrixBlobLabel(&imgCopy, &numBlob);
  nr::t_bound* bounds = new nr::t_bound[numBlob];
  bool* isNoise = new bool[numBlob];

  nr::findBound(imgCopy.height, imgCopy.width, mark, numBlob, bounds);
  // !!!WARNING!!! We assume the size of each letter is this size
  // this is heuristic and fragile assumption
  nr::determineBlob(numBlob, bounds, isNoise, std::min(5, imgCopy.width / 20), imgCopy.width / 6, imgCopy.height / 3, 5 * imgCopy.height / 6 );
  nr::removeUnwantedBlob(&imgCopy, mark, isNoise);
  std::vector<nr::character> characters = nr::makeSuperPixel(numBlob, mark, bounds, isNoise);
  std::string res = "";
  for (int i = 0; i < characters.size(); i++) {
    res += characters[i].cc;
  }

  imgCopy.show();

  for (int i = 0; i < imgCopy.height; i++) delete mark[i];
  delete mark;
  delete bounds;
  delete isNoise;
  return res;
}
