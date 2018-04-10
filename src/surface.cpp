#include "surface.h"
#include "edge.h"
#include "vertex.h"
#include <bits/stdc++.h>
surface::surface(){
	// surface::boundary = NULL;
	this->truesurface = false;
	this->coeff[0] = 0;
	this->coeff[1] = 0;
	this->coeff[2] = 0;
	this->coeff[3] = 0;
	this->sno=-1;
	/**
	*Default constructor
	*/
}
surface::surface(vector<edge*> a, int n){
	if(a.size()<3){
		cout<<"Number of edges can't be less than 3. Wrong input!";
		return;
	}
	this->boundary = a;
	this->calc_coeff();
	this->truesurface = true;
	//surface::count++;
	this->sno = n;
	/**
	* Add a new surface
	*/
}
void surface::calc_coeff()
{
	vertex *m, *n, *o;
	m = boundary[0]->a;
	n = boundary[0]->b;
	o = boundary[1]->a;
	if(((o->x==m->x) && (o->y == m->y) && (o->z == m->z)) || ((o->x==n->x) && (o->y == n->y) && (o->z == n->z)))
		o = boundary[1]->b;
	// cout<<m->x<<" "<<m->y<<" "<<m->z<<" "<<n->x<<" "<<n->y<<" "<<n->z<<" "<<o->x<<" "<<o->y<<" "<<o->z<<" "<<endl;
	float x1 = m->x - n->x;
	float y1 = m->y - n->y;
	float z1 = m->z - n->z;
	
	float x2 = o->x - n->x;
	float y2 = o->y - n->y;
	float z2 = o->z - n->z;

	this->coeff[0] = y1*z2 - y2*z1;
	this->coeff[1] = x2*z1 - x1*z2;
	this->coeff[2] = x1*y2 - x2*y1;
	this->coeff[3] = -1*((y1*z2 - y2*z1)*n->x + (x2*z1 - x1*z2)*n->y + (x1*y2 - x2*y1)*n->z);
	int mag = sqrt(coeff[0]*coeff[0] + coeff[1]*coeff[1] + coeff[2]*coeff[2]);

	coeff[0]/=mag;
	coeff[1]/=mag;
	coeff[2]/=mag;
	coeff[3]/=mag;
	/**
	* Calculate the normal coefficients of the surface
	*/
}
float surface::calc_proj(vertex* v_test)
{
	float res = coeff[0]*v_test->x + coeff[1]*v_test->y + coeff[2]*v_test->z + coeff[3];
	return res;
	/**
	* Calculate the result of putting vertex coordinaes in the equation of surface. used in findling hidden edges.
	*/
}
float surface::dotpdt(edge *e_t)
{
	float res = coeff[0]*(e_t->a->x - e_t->b->x) + coeff[1]*(e_t->a->y - e_t->b->y) + coeff[2]*(e_t->a->z - e_t->b->z);
	return res;
	/**
	* Calculate the dot product of edge and the normal to the surface
	*/
}
