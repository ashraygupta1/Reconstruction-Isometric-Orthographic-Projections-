#include "edge.h"
#include "vertex.h"

edge::edge(){
	this->a = NULL;
	this->b = NULL;
	this->eno = -1;
	this->hidden = false;
	this->istrue = true;
	/**
	* Default Constructor
	**/
}
edge::edge(vertex *a, vertex *b, int n){
	this->a = a;
	this->b = b;
	this->eno = n;
	this->hidden = false;
	this->istrue = true;
	if ((a->x == b->x) && (a->y == b->y) && (a->z == b->z)){
		// cout<<"Same vertices "<<a->vno<<" and "<<b->vno<<". No edge added!!"<<endl;
		this->istrue = false;
	}
	/**
	* Set Edge with pointers to vertices
	**/
}
// void edge::add_surface(surface *a){
// 	edge::adjsurface.push_back(a);
// 	/**
// 	* Add a surface to list of adjacent surfaces
// 	*/
// }
vertex* edge::get_neighbour(vertex *d){
	if(a->vno == d->vno)
		return b;
	else return a;
	/**
	* Get the neighboring vertex of a vertex with corresponding edge
	*/
}
vertex* edge::midpoint(){
	vertex *v = new vertex((this->a->x+this->b->x)/2,(this->a->y+this->b->y)/2,(this->a->z+this->b->z)/2,-1);
	return v;
	/**
	* Return the vertex corresponding to mid point of the edge
	*/
}
edge* edge::get_edge()
{
	return this;
	/**
	* Return the edge object
	*/
}
bool edge::overlap(edge *e2)
{
	float res = ((this->a->x - this->b->x)*(e2->a->x - e2->b->x)) + ((this->a->y - this->b->y)*(e2->a->y - e2->b->y)) + ((this->a->z - this->b->z)*(e2->a->z - e2->b->z));
	float a1 = sqrt(pow((this->a->x - this->b->x),2)+pow((this->a->y - this->b->y),2)+pow((this->a->z - this->b->z),2));
	float a2 = sqrt(pow((e2->a->x - e2->b->x),2)+pow((e2->a->y - e2->b->y),2)+pow((e2->a->z - e2->b->z),2));
	res= abs(res/(a1*a2));
	bool y=false;
	if(!(res<0.99 || res>1.01) && (e2->a->same(this->a)||e2->a->same(this->b)||e2->b->same(this->a)||e2->b->same(this->b)))
		y=true;
	// cout<<"edge i : "<<e2->eno<<" res= "<<res<<" y="<<y<<" ";
	return y;
}