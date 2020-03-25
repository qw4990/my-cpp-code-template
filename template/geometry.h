#include "defines.h"

// manhattan_dis returns the Manhattan distance of these two points.
int manhattan_dis(PII p1, PII p2) {
    return abs(p1.first-p2.first) + abs(p1.second-p2.second);
}