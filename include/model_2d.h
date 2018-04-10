#ifndef MODEL_2D_H
#define MODEL_2D_H

#include<bits/stdc++.h>
#include "vertex.h"
#include "edge.h"
#include "surface.h"

#define INF 10000
using namespace std;

class model_2d
{
public:
	int direction;
	vector<vertex*> v;
	vector<edge*> e;
	vector<surface*> s;
	model_2d();
	vertex* is_intersect(int a, int b);
	void do_intersect(edge *a, edge *b);
	void add_vertices(vector<vertex*> vt);
	void add_edges(vector<edge*> et);
	void add_vertex(vertex *vt);
	vector<vertex*> ret_vertices();
	vector<edge*> ret_edges();
	model_2d* return_model();
	void display_model();
	bool onSegment(pair<float, float> p, pair<float, float> q, pair<float, float> r);
	int orientation(pair<float, float> p, pair<float, float> q,pair<float, float> r);
	bool doIntersect(pair<float, float> p1, pair<float, float> q1, pair<float, float> p2, pair<float, float> q2);
	bool isinside(vertex* t, int q);
	void dispvertex();
	void dispedge();
	void dispsurface();
};

#endif