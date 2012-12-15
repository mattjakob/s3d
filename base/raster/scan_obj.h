#include "geom.h"
#include "poly.h"

typedef struct Edge {
  int n;
  Vector3 p, i;
  double t, d;
} Edge;

static int first_vertex(Vector3 v[], int n);
static Edge *edge(Vector3 p0, Vector3 p1, char c, Edge *e);
static Edge *increment(Edge *e);
