#ifndef SURFACE_H
#define SURFACE_H

#include<bits/stdc++.h>
#include "edge.h"
using namespace std;

class surface{
public:
	vector<edge*> boundary;
	float coeff[4];
	bool truesurface;
	int sno;
	surface();
	surface(vector<edge*> a, int n);
	vector<edge*> get_edges();
	void calc_coeff();
	float calc_proj(vertex* v_test);
	float dotpdt(edge *et);
};
#endif