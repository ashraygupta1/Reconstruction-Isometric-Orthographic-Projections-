#include<bits/stdc++.h>
#include "model_2d.h"
using namespace std;

#ifndef MODEL_3D_H
#define MODEL_3D_H
#endif

class model_3d
{
public:
	vector<vertex*> v;
	vector<edge*> e;
	vector<surface*> s;
	model_2d *topview;
	model_2d *frontview;
	model_2d *sideview;
	// model_2d calc_2d(vector<vertex*> v, vector<edge*> e);
	void calc_2d(int direction);
	model_2d* basic_proj(int);
	void calc_2d_1(int);
	// vertex midpoint(edge);
	void form_wireframe();
	void form_3dfaces();
	vector<int> get_neighbours(vertex *vn);
	edge* is_edge(int a, int b);
	void model_3d_verification();
	void add_vertex(float x, float y, float z);
	void add_edge(vertex *a, vertex *b);
	void add_surface(vector<edge*> edges);
	model_2d get_2dview(int direction);
	// void input_2dview(vector<vertex*> v, vector<edge*> e, int direction);
	void input_2dview(vector <vertex*> v1, vector<edge*> e1, int direction);
	void display_wireframe();
	void display_3d_model();
	void generate_3d();
	void dispvertex();
	void dispedge();
	void dispsurface();
	void save2Dmodels(fstream &out);
	void save3Dmodel(fstream &out);
};

