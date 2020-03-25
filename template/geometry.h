#include "defines.h"

// ManHattanDis returns the Manhattan distance of these two points.
int ManHattanDis(PII p1, PII p2) {
    return abs(p1.first-p2.first) + abs(p1.second-p2.second);
}