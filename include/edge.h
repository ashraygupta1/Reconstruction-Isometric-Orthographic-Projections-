#ifndef EDGE_H
#define EDGE_H

#include<bits/stdc++.h>
#include "vertex.h"
using namespace std;

class edge{
public:
	vertex *a;
	vertex *b;
	// static int count=0;
	bool hidden;
	bool istrue;
	// vector<surface*> adjsurface;
	int eno;
	edge();
	edge(vertex *a, vertex *b, int c);
	// void add_surface(surface *a);
	vertex* get_neighbour(vertex *d);
	vertex* midpoint();
	edge* get_edge();
	bool overlap(edge *e2);
};

#endif