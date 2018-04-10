#include "vertex.h"
vertex::vertex(){
	this->x=0.0;
	this->y=0.0;
	this->z=0.0;
	this->vno = -1;
	this->istrue = false;
	//vertex::count++;
	// neighbours = NULL;
	/**
	*Default constructor
	*/
}
vertex::vertex(float x, float y, float z,int n = -1){
	this->x=x;
	this->y=y;
	this->z=z;
	this->istrue = true;
	this->vno = n;
	// neighbours = NULL;
	/**
	* Set the coordinates of the vertex
	*/
}
vertex::vertex(vertex* v){
	this->x = v->x;
	this->y = v->y;
	this->z = v->z;
	this->vno = -1;
	/**
	* Copy constructor
	*/
}
vertex vertex::getxy(){
	vertex a;
	a.x=this->x;
	a.y=this->y;
	a.z=0;
	return a;
	/**
	* Get the XY coordinates for top view projection
	*/
}
vertex vertex::getyz(){
	vertex a;
	a.x=0;
	a.y=this->y;
	a.z=this->z;
	return a;
	/**
	* Get the YZ coordinates for side view projection
	*/
}
vertex vertex::getxz(){
	vertex a;
	a.x=this->x;
	a.y=0;
	a.z=this->z;
	return a;
	/**
	* Get the XZ coordinates for Right side projection
	*/
}
bool vertex::same(vertex *a){
	if((this->x==a->x)&&(this->y==a->y)&&(this->z==a->z))
		return true;
	else
		return false;
}