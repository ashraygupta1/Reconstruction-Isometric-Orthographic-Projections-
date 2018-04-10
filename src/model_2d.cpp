/*  direction=0 :: top view		x,y
	direction=1 :: front view	x,z
	direction=2 :: side view	y,z
*/
#include <iostream>
#include "model_2d.h"
#define EPS 0.0001
//add constructor
model_2d::model_2d(){
	this->direction = -1;
}
void model_2d::add_vertices(vector<vertex*> vt){
	for(int i=0;i<vt.size();i++)
		model_2d::v.push_back(vt[i]);
/**
*Adding vertices to this 2d model
*/
}
void model_2d::add_edges(vector<edge*> et){
	for(int i=0;i<et.size();i++)
		model_2d::e.push_back(et[i]);
/**
*Adding edges to this 2d model
*/
}
void model_2d::add_vertex(vertex *vt){
	model_2d::v.push_back(vt);//add vno
/**
*Add a single vertex to this 2d model
*/
}
vector<vertex*> model_2d::ret_vertices(){
	return model_2d::v;
	/**
	* Returns the list of vertices
	*/
}	
vector<edge*> model_2d::ret_edges(){
	return model_2d::e;
	/**
	cout<<"1 "<<p<<" "<<q<<endl;
	* Returns the list of edges
	*/
}
vertex* model_2d::is_intersect(int p, int q){
	float px1,py1,px2,py2;
	float qx1,qy1,qx2,qy2;
	// cout<<"1 "<<p<<" "<<q<<endl;
	switch(this->direction)
	{
		case 0: px1=this->e[p]->a->x; py1 = this->e[p]->a->y;
				px2=this->e[p]->b->x; py2=this->e[p]->b->y;
				qx1=this->e[q]->a->x; qy1=this->e[q]->a->y;
				qx2=this->e[q]->b->x; qy2=this->e[q]->b->y;
				this->e[p]->a->z=0; this->e[p]->b->z=0;
				this->e[q]->a->z=0; this->e[q]->b->z=0;
				break;
		case 1: px1=this->e[p]->a->x; py1=this->e[p]->a->z;
				px2=this->e[p]->b->x; py2=this->e[p]->b->z;
				qx1=this->e[q]->a->x; qy1=this->e[q]->a->z;
				qx2=this->e[q]->b->x; qy2=this->e[q]->b->z;
				this->e[p]->a->y=0; this->e[p]->b->y=0;
				this->e[q]->a->y=0; this->e[q]->b->y=0;
				break;
		case 2: px1=this->e[p]->a->z; py1=this->e[p]->a->y;
				px2=this->e[p]->b->z; py2=this->e[p]->b->y;
				qx1=this->e[q]->a->z; qy1=this->e[q]->a->y;
				qx2=this->e[q]->b->z; qy2=this->e[q]->b->y;
				this->e[p]->a->x=0; this->e[p]->b->x=0;
				this->e[q]->a->x=0; this->e[q]->b->x=0;
				break;
		default: ;
	}
	float num_s,den_s,num_t,den_t;
	num_s=(qx2-qx1)*(qy1-py1)-(qy2-qy1)*(qx1-px1);
	den_s=(qx2-qx1)*(py2-py1)-(qy2-qy1)*(px2-px1);
	num_t=(px2-px1)*(qy1-py1)-(py2-py1)*(qx1-px1);
	den_t=(qx2-qx1)*(py2-py1)-(qy2-qy1)*(px2-px1);
	float s_j=num_s / den_s;
	float t_j=num_t / den_t;
	if(den_s!=0 && den_t!=0 && s_j>0 && s_j<1 && t_j>0 && t_j<1 && s_j==s_j && t_j == t_j)// do stuff for s and t =0 and =1. bad edges also produced.
	{
		// cout<<p<<' '<<q<<" "<<s_j<<" "<<t_j<<endl;
		// cout<<"Points of first line:"<<px1<<" "<<py1<<" "<<px2<<" "<<py2<<endl;
		// cout<<"Points of second line:"<<qx1<<" "<<qy1<<" "<<qx2<<" "<<qy2<<endl;
		float x_intersection = px1 + (px2-px1)*s_j;			// Check if correct
		float y_intersection = py1 + (py2-py1)*s_j;			// Check if correct
		// cout<<"Points of intersection:"<<x_intersection<<" "<<y_intersection<<endl;
		vertex *v_intersect = new vertex();
		// cout<<direction<<endl;
		switch(direction)
		{
			case 0: v_intersect->x=x_intersection; v_intersect->y=y_intersection; v_intersect->z=0;break;
			case 1: v_intersect->x=x_intersection; v_intersect->y=0; v_intersect->z=y_intersection;break;
			case 2: v_intersect->x=0; v_intersect->y=y_intersection; v_intersect->z=x_intersection;break;
			default: break;
		}

		// Add first vertex
		v_intersect->vno = v.size()+1;
		v_intersect->istrue = true;
		// cout<<"New vertex added:"<<v_intersect->vno<<" "<<v_intersect->x<<" "<<v_intersect->y<<" "<<v_intersect->z<<" "<<endl;
		vertex *v_intersect2 = new vertex(v_intersect);
		add_vertex(v_intersect);
		//split edges
		edge *pe1 = new edge();
		edge *pe2 = new edge();
		edge *qe1 = new edge();
		edge *qe2 = new edge();
		// cout<<"New edges added:"<<endl;
		pe1->a = this->e[p]->a;
		pe1->b = v_intersect;//wrong
		pe1->eno = e.size()+1;
		e.push_back(pe1);

		// cout<<pe1->eno<<" "<<pe1->a->vno<<" Values:("<<pe1->a->x<<", "<<pe1->a->y<<", "<<pe1->a->z<<
		// ") "<<pe1->b->vno<<" Values:("<<pe1->b->x<<", "<<pe1->b->y<<", "<<pe1->b->z<<") Hidden:"<<pe1->hidden<<" istrue:"<<pe1->istrue<<endl;

		pe2->a = v_intersect;
		pe2->b = this->e[p]->b;
		pe2->eno = e.size()+1;
		e.push_back(pe2);

		// cout<<pe2->eno<<" "<<pe2->a->vno<<" Values:("<<pe2->a->x<<", "<<pe2->a->y<<", "<<pe2->a->z<<
		// ") "<<pe2->b->vno<<" Values:("<<pe2->b->x<<", "<<pe2->b->y<<", "<<pe2->b->z<<") Hidden:"<<pe2->hidden<<" istrue:"<<pe2->istrue<<endl;

		// Add second vertex
		v_intersect2->vno = v.size()+1;
		add_vertex(v_intersect2);

		qe1->a = this->e[q]->a;
		qe1->b = v_intersect2;
		qe1->eno = e.size()+1;
		e.push_back(qe1);

		// cout<<qe1->eno<<" "<<qe1->a->vno<<" Values:("<<qe1->a->x<<", "<<qe1->a->y<<", "<<qe1->a->z<<
		// ") "<<qe1->b->vno<<" Values:("<<qe1->b->x<<", "<<qe1->b->y<<", "<<qe1->b->z<<") Hidden:"<<qe1->hidden<<" istrue:"<<qe1->istrue<<endl;
		
		qe2->a = v_intersect2;
		qe2->b = this->e[q]->b;
		qe2->eno = e.size()+1;
		e.push_back(qe2);

		// cout<<qe2->eno<<" "<<qe2->a->vno<<" Values:("<<qe2->a->x<<", "<<qe2->a->y<<", "<<qe2->a->z<<
		// ") "<<qe2->b->vno<<" Values:("<<qe2->b->x<<", "<<qe2->b->y<<", "<<qe2->b->z<<") Hidden:"<<qe2->hidden<<" istrue:"<<qe2->istrue<<endl;

		e[p]->istrue = false;
		e[q]->istrue = false;
		// this->display_model();
		return v_intersect;
	}
	else return NULL;
	/**
	* Checks whether the two edges intersect or not and if they do, adds the intersection vertex to list of vertices and 
	*updates the list of edges with new edges replacing the old ones too.
	*/
}

bool model_2d::onSegment(pair<float, float> p, pair<float, float> q, pair<float, float> r){
    if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
            q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))
        return true;
    return false;
    /**
    * Returns whether Q lies on line segment PR or not, given P, Q and R are collinear.
    */
}

int model_2d::orientation(pair<float, float> p, pair<float, float> q,pair<float, float> r){
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
    /**
    * Returns the orientation of point Q with respect to line segment PR
	* Returns 0 if they are collinear, 1 if clockwise, and 3 if anti clockwise.
	*/
}

bool model_2d::doIntersect(pair<float, float> p1, pair<float, float> q1, pair<float, float> p2, pair<float, float> q2){
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
    /**
    * Returns true if two line segments P1Q1 and P2Q2 intersect.
    */
}

bool model_2d::isinside(vertex* t, int q){
	pair<float, float> p;
	int i,n = this->s[q]->boundary.size();
	if (n<3){
		cout<<"Wrong surface!!";
		return false;
	}
	vector< pair <float, float > > poly(n);
	switch(this->direction){
		case 1: p.first = t->x;
				p.second = t->z;
				poly[0].first = this->s[q]->boundary[0]->a->x;
				poly[0].second = this->s[q]->boundary[0]->a->z;
				poly[1].first = this->s[q]->boundary[0]->b->x;
				poly[1].second = this->s[q]->boundary[0]->b->z;
				for(i=1;i<n-1;i++){
					if((poly[i].first == this->s[q]->boundary[i]->a->x && poly[i].second == this->s[q]->boundary[i]->a->z)
						|| poly[i-1].first == this->s[q]->boundary[i]->a->x && poly[i-1].second == this->s[q]->boundary[i]->a->z){
						poly[i+1].first = this->s[q]->boundary[i]->b->x;
						poly[i+1].second = this->s[q]->boundary[i]->b->z;
					}
					if((poly[i].first == this->s[q]->boundary[i]->b->x && poly[i].second == this->s[q]->boundary[i]->b->z)
						|| poly[i-1].first == this->s[q]->boundary[i]->b->x && poly[i-1].second == this->s[q]->boundary[i]->b->z){
						poly[i+1].first = this->s[q]->boundary[i]->a->x;
						poly[i+1].second = this->s[q]->boundary[i]->a->z;
					}
				}
				break;

		case 0: p.first = t->x;
				p.second = t->y;
				poly[0].first = this->s[q]->boundary[0]->a->x;
				poly[0].second = this->s[q]->boundary[0]->a->y;
				poly[1].first = this->s[q]->boundary[0]->b->x;
				poly[1].second = this->s[q]->boundary[0]->b->y;
				for(i=1;i<n-1;i++){
					if((poly[i].first == this->s[q]->boundary[i]->a->x && poly[i].second == this->s[q]->boundary[i]->a->y)
						|| poly[i-1].first == this->s[q]->boundary[i]->a->x && poly[i-1].second == this->s[q]->boundary[i]->a->y){
						poly[i+1].first = this->s[q]->boundary[i]->b->x;
						poly[i+1].second = this->s[q]->boundary[i]->b->y;
					}
					if((poly[i].first == this->s[q]->boundary[i]->b->x && poly[i].second == this->s[q]->boundary[i]->b->y)
						|| poly[i-1].first == this->s[q]->boundary[i]->b->x && poly[i-1].second == this->s[q]->boundary[i]->b->y){
						poly[i+1].first = this->s[q]->boundary[i]->a->x;
						poly[i+1].second = this->s[q]->boundary[i]->a->y;
					}
				}
				break;

		case 2: p.first = t->y;
				p.second = t->z;
				poly[0].first = this->s[q]->boundary[0]->a->y;
				poly[0].second = this->s[q]->boundary[0]->a->z;
				poly[1].first = this->s[q]->boundary[0]->b->y;
				poly[1].second = this->s[q]->boundary[0]->b->z;
				for(i=1;i<n-1;i++){
					if((poly[i].first == this->s[q]->boundary[i]->a->y && poly[i].second == this->s[q]->boundary[i]->a->z)
						|| poly[i-1].first == this->s[q]->boundary[i]->a->y && poly[i-1].second == this->s[q]->boundary[i]->a->z){
						poly[i+1].first = this->s[q]->boundary[i]->b->y;
						poly[i+1].second = this->s[q]->boundary[i]->b->z;
					}
					if((poly[i].first == this->s[q]->boundary[i]->b->y && poly[i].second == this->s[q]->boundary[i]->b->z)
						|| poly[i-1].first == this->s[q]->boundary[i]->b->y && poly[i-1].second == this->s[q]->boundary[i]->b->z){
						poly[i+1].first = this->s[q]->boundary[i]->a->y;
						poly[i+1].second = this->s[q]->boundary[i]->a->z;
					}
				}
				break;
		default: ;
	}
	// for (i=0;i<n;i++){
	// 	cout<<poly[i].first<<","<<poly[i].second<<"  ";
	// }	
	i=0;
	// cout<<endl;
	pair<float,float> extreme1(INF, p.second);
	int count = 0;
    do{
        int next = (i+1)%n;
 
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(poly[i], poly[next], p, extreme1)){
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(poly[i], p, poly[next]) == 0)
               return onSegment(poly[i], p, poly[next]);
            count++;
        }
        i = next;
    } while (i != 0);
 
    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
    /** Point in a polygon algorithm!
    * Checks whether a given point is inside or outside the surface
    */
}

void model_2d::display_model(){/**
	* -Display the 3d solid model formed in the end.\n
	* -Uses the graphic library to display the 3d solid model.\n
	*/
	this->dispvertex();
	this->dispedge();
	// this->dispsurface();
	/**
	* Display the complete 2D model in the form of vertices, edges and surfaces
	*/
}
void model_2d::dispvertex(){
	int i, n = v.size();
	cout<<"Vertices: View "<<direction<<endl;
	for(i=0;i<n;i++){
		cout<<v[i]->vno<<" "<<v[i]->x<<" "<<v[i]->y<<" "<<v[i]->z<<endl;
	}
	/**
	* Display the list of vertices
	*/
}

void model_2d::dispedge(){
	int i, n = v.size();
	cout<<"Edges: View "<<direction<<endl;
	n = e.size();
	for(i=0; i<n ;i++){
		// cout<<e[i]->eno<<" "<<e[i]->a->vno<<" "<<e[i]->b->vno<<" Hidden:"<<e[i]->hidden<<" istrue:"<<e[i]->istrue<<endl;
		cout<<e[i]->eno<<" "<<e[i]->a->vno<<" Values:("<<e[i]->a->x<<", "<<e[i]->a->y<<", "<<e[i]->a->z<<
		") "<<e[i]->b->vno<<" Values:("<<e[i]->b->x<<", "<<e[i]->b->y<<", "<<e[i]->b->z<<") Hidden:"<<e[i]->hidden<<" istrue:"<<e[i]->istrue<<endl;
	}
	/**
	* Display the lsit of edges of the polygon
	*/
}

void model_2d::dispsurface(){
	int i, j, n = v.size();
	cout<<"Surfaces: View "<<direction<<endl;
	n = s.size();
	for (i = 0;i<n;i++){
		// s[i]->calc_coeff();
		cout<<s[i]->sno<<" ";
		for (j=0;j<s[i]->boundary.size();j++){
			// cout<<s[i]->boundary[j]->eno<<" ";
		cout<<"\t\t"<<s[i]->boundary[j]->eno<<" "<<s[i]->boundary[j]->a->vno<<" Values:("<<s[i]->boundary[j]->a->x<<", "<<s[i]->boundary[j]->a->y<<", "<<
		s[i]->boundary[j]->a->z<<") "<<s[i]->boundary[j]->b->vno<<" Values:("<<s[i]->boundary[j]->b->x<<", "<<s[i]->boundary[j]->b->y<<", "
		<<s[i]->boundary[j]->b->z<<") Hidden:"<<s[i]->boundary[j]->hidden<<" istrue:"<<s[i]->boundary[j]->istrue<<endl;
		}
		cout<<" Coeff:("<<s[i]->coeff[0]<<", "<<s[i]->coeff[1]<<", "<<s[i]->coeff[2]<<", "<<s[i]->coeff[3]<<")";
		cout<<endl;
	}
	/**
	* Display the list of surfaces giving all the necessary details of the edges
	*/
}
