#include <stdio.h>
#include <stdlib.h>
#include "Edge.h"

Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

