#ifndef VERTEX_H
#define VERTEX_H

#include<bits/stdc++.h>

using namespace std;

class vertex{
public:
	float x,y,z; 	///Vertex coordinates
	// vector<edge*> neighbours;	///Vertex neighbours
	bool istrue;
	int vno;
	vertex();
	vertex(float x, float y, float z, int n);
	vertex(vertex* v);
	vertex getxy();
	vertex getyz();
	vertex getxz();
	bool same(vertex *a);
	// void addedge(edge *a);
};

#endif
