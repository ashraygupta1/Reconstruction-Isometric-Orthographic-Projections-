#include "model_3d.h" 

model_2d* model_3d::basic_proj(int direction){
	model_2d *t_view = new model_2d();
	t_view->direction = direction;
	vertex *v_temp;
	for(int i=0 ; i<model_3d::v.size() && v[i]->istrue; i++){
		switch(direction)
		{
			case 0: t_view->v.push_back(new vertex(model_3d::v[i]->x, model_3d::v[i]->y, 0, model_3d::v[i]->vno));
					break;
			case 1: t_view->v.push_back(new vertex(model_3d::v[i]->x, 0, model_3d::v[i]->z, model_3d::v[i]->vno));
					break;
			case 2: t_view->v.push_back(new vertex(0, model_3d::v[i]->y, model_3d::v[i]->z, model_3d::v[i]->vno));
					break;
			default: ;
		}
	}

	for(int i=0 ; i<model_3d::e.size() ; i++){
		edge *e_temp = new edge(t_view->v[model_3d::e[i]->a->vno-1] , t_view->v[model_3d::e[i]->b->vno-1] ,model_3d::e[i]->eno);
		t_view->e.push_back(e_temp);
	}

	for(int i=0 ; i<model_3d::s.size() ; i++){
		surface *s_temp = new surface();				
		for(int j=0; j<model_3d::s[i]->boundary.size(); j++){
			s_temp->boundary.push_back(t_view->e[model_3d::s[i]->boundary[j]->eno-1]);
		}
		s_temp->sno = model_3d::s[i]->sno;
		t_view->s.push_back(s_temp);
	}
	return t_view;
	/**
	* Develop a basic 2D projection of the given 3D solid without ay hidden lines. Just the 2D projections
	*/
}

void model_3d::calc_2d(int direction){
	model_2d *view;
	switch(direction)
	{
		case 0: view = this->topview;
				break;
		case 1: view = this->frontview;
				break;
		case 2: view = this->sideview;
				break;
		default: cout<<"Wrong direction input!!";
				break;
	}
	// cout<<e.size()<<endl;
	for(int i=0;i<e.size();i++)
	{
		if(e[i]->istrue){
			for(int j=i+1;j<e.size();j++)
			{
				if(e[j]->istrue){
					vertex* v_intersect_2D = view->model_2d::is_intersect(i,j);
					if(v_intersect_2D!=NULL){
						// cout<<"Hello!"<<e[i]->eno<<" "<<e[j]->eno<<endl;
						vertex *v_int1 = new vertex(v_intersect_2D);
						vertex *v_int2 = new vertex(v_intersect_2D);
						// cout<<"Intersection!! "<<v_intersect_2D->vno<<" "<<v_intersect_2D->x<<" "<<v_intersect_2D->y<<" "<<v_intersect_2D->z<<endl;
						switch(direction)
						{
							case 0: if(e[i]->a->y == e[i]->b->y)
										v_int1->z = (e[i]->a->z - e[i]->b->z)/(e[i]->a->x - e[i]->b->x) * (v_int1->x - e[i]->a->x) + e[i]->a->z;
									else
										v_int1->z = (e[i]->a->z - e[i]->b->z)/(e[i]->a->y - e[i]->b->y) * (v_int1->y - e[i]->a->y) + e[i]->a->z;

									if(e[j]->a->y == e[j]->b->y)
										v_int2->z = (e[j]->a->z - e[j]->b->z)/(e[j]->a->x - e[j]->b->x) * (v_int2->x - e[j]->a->x) + e[j]->a->z;
									else
										v_int2->z = (e[j]->a->z - e[j]->b->z)/(e[j]->a->y - e[j]->b->y) * (v_int2->y - e[j]->a->y) + e[j]->a->z;
									
									v_int1->vno = v.size()+1;
									v_int1->istrue = false;
									v.push_back(v_int1);
									v_int2->vno = v.size()+1;
									v_int2->istrue = false;
									v.push_back(v_int2);
									// cout<<"123 "<<v_int1->vno<<" "<<v_int1->x<<" "<<v_int1->y<<" "<<v_int1->z<<endl;
									// cout<<"123 "<<v_int2->vno<<" "<<v_int2->x<<" "<<v_int2->y<<" "<<v_int2->z<<endl;
									view->v[v_int1->vno-1]->z = v_int1->z;
									view->v[v_int2->vno-1]->z = v_int2->z;
									break;

							case 1: if(e[i]->a->z == e[i]->b->z)
										v_int1->y = (e[i]->a->y - e[i]->b->y)/(e[i]->a->x - e[i]->b->x) * (v_int1->x - e[i]->a->x) + e[i]->a->y;
									else
										v_int1->y = (e[i]->a->y - e[i]->b->y)/(e[i]->a->z - e[i]->b->z) * (v_int1->z - e[i]->a->z) + e[i]->a->y;

									if(e[j]->a->z == e[j]->b->z)
										v_int2->y = (e[j]->a->y - e[j]->b->y)/(e[j]->a->x - e[j]->b->x) * (v_int2->x - e[j]->a->x) + e[j]->a->y;
									else
										v_int2->y = (e[j]->a->y - e[j]->b->y)/(e[j]->a->z - e[j]->b->z) * (v_int2->z - e[j]->a->z) + e[j]->a->y;

									v_int1->vno = v.size()+1;
									v_int1->istrue = false;
									v.push_back(v_int1);
									v_int2->vno = v.size()+1;
									v_int2->istrue = false;
									v.push_back(v_int2);
									// cout<<"123 "<<v_int1->vno<<" "<<v_int1->x<<" "<<v_int1->y<<" "<<v_int1->z<<endl;
									// cout<<"123 "<<v_int2->vno<<" "<<v_int2->x<<" "<<v_int2->y<<" "<<v_int2->z<<endl;
									view->v[v_int1->vno-1]->y = v_int1->y;
									view->v[v_int2->vno-1]->y = v_int2->y;
									break;

							// case 2: v_int1->x = (e[i]->a->x - e[i]->b->x)/(e[i]->a->y - e[i]->b->y) * (v_int1->y - e[i]->a->y) + e[i]->a->x;
							// 		v_int2->x = (e[j]->a->x - e[j]->b->x)/(e[j]->a->y - e[j]->b->y) * (v_int2->y - e[j]->a->y) + e[j]->a->x;

							case 2: if(e[i]->a->z == e[i]->b->z)
										v_int1->x = (e[i]->a->x - e[i]->b->x)/(e[i]->a->y - e[i]->b->y) * (v_int1->y - e[i]->a->y) + e[i]->a->x;
									else
										v_int1->x = (e[i]->a->x - e[i]->b->x)/(e[i]->a->z - e[i]->b->z) * (v_int1->z - e[i]->a->z) + e[i]->a->x;

									if(e[j]->a->z == e[j]->b->z)
										v_int2->x = (e[j]->a->x - e[j]->b->x)/(e[j]->a->y - e[j]->b->y) * (v_int2->y - e[j]->a->y) + e[j]->a->x;
									else
										v_int2->x = (e[j]->a->x - e[j]->b->x)/(e[j]->a->z - e[j]->b->z) * (v_int2->z - e[j]->a->z) + e[j]->a->x;


									v_int1->vno = v.size()+1;
									v_int1->istrue = false;
									v.push_back(v_int1);
									v_int2->vno = v.size()+1;
									v_int2->istrue = false;
									v.push_back(v_int2);
									// cout<<"123 "<<v_int1->vno<<" "<<v_int1->x<<" "<<v_int1->y<<" "<<v_int1->z<<endl;
									// cout<<"123 "<<v_int2->vno<<" "<<v_int2->x<<" "<<v_int2->y<<" "<<v_int2->z<<endl;
									view->v[v_int1->vno-1]->x = v_int1->x;
									view->v[v_int2->vno-1]->x = v_int2->x;
									break;
						}
						// cout<<"Intersection!! "<<v_int1->vno<<" "<<v_int1->x<<" "<<v_int1->y<<" "<<v_int1->z<<endl;
						// cout<<"Intersection!! "<<v_int2->vno<<" "<<v_int2->x<<" "<<v_int2->y<<" "<<v_int2->z<<endl;

						edge *pe1 = new edge();
						pe1->a = e[i]->a;
						pe1->b = v_int1;
						pe1->eno = e.size()+1;
						pe1->istrue = false;
						e.push_back(pe1);

						edge *pe2 = new edge();
						pe2->a = v_int1;
						pe2->b = e[i]->b;
						pe2->eno = e.size()+1;
						pe2->istrue = false;
						e.push_back(pe2);

						edge *qe1 = new edge();
						qe1->a = e[j]->a;
						qe1->b = v_int2;
						qe1->eno = e.size()+1;
						qe1->istrue = false;
						e.push_back(qe1);

						edge *qe2 = new edge();
						qe2->a = v_int2;
						qe2->b = e[j]->b;
						qe2->eno = e.size()+1;
						qe2->istrue = false;
						e.push_back(qe2);
					}
				}
			}
		}
	}
	model_3d::calc_2d_1(direction);
	/**
	*Performs segmentation of edges in 2D views i.e. if two edges of a 3D model intersect in 2D view, then the 2D edges are segmented so that the 
	* segmented part can be individually tested for hidden nature.
	*/
}
void model_3d::calc_2d_1(int direction)
{
	model_2d *view;
	switch(direction)
	{
		case 0: view = this->topview;
				break;
		case 1: view = this->frontview;
				break;
		case 2: view = this->sideview;
				break;
		default:
				break;
	}
	for(int i=0;i<view->e.size();i++)
	{
		if(!view->e[i]->istrue)
			continue;
		for(int j=0;j<s.size();j++)
		{
			float coefficient;
			switch(direction)
			{
				case 0: coefficient = s[j]->coeff[2];break;
				case 1: coefficient = s[j]->coeff[1];break;
				case 2: coefficient = s[j]->coeff[0];
			}
			// cout<<i<<' '<<j<<' '<<coefficient<<endl;
			if(coefficient!=0)
			{
				vertex *v_mid = e[i]->midpoint();
				// cout<<"\t"<<i<<" "<<j<<" "<<e[i]->a->vno<<" "<<e[i]->b->vno<<" "<<v_mid->x<<" "<<v_mid->y<<" "<<v_mid->z<<endl;
				vertex *R = new vertex(s[j]->boundary[0]->a);
				switch(direction)
				{
					case 0: R->z = R->z + 10;break;
					case 1: R->y = R->y + 10;break;
					case 2: R->x = R->x + 10;break;
				}
				float result = s[j]->calc_proj(v_mid) * s[j]->calc_proj(R);
				// cout<<i<<" "<<j<<' '	<<s[j]->calc_proj(v_mid)<<" "<<s[j]->calc_proj(R)<<" "<<result<<endl;
				if(result < 0)
				{
					//do point in polygon, if inside, return 1, else 0.
					//if hidden, change edge variable and break surfaces loop, else do nothing
					bool res_inside;
					// cout<<"\t"<<s[j]->sno<<endl;
					res_inside = view->isinside(v_mid, s[j]->sno-1);
					if(res_inside)
					{
						// cout<<"Hidden hai!!"<<endl<<endl;
						view->e[i]->hidden = 1;
						break;
					}
				}
			}
		}
	}
	/**
	* Performs the point in a polygon algorithm in all the segmented edges over the surfaces of the 3D solid.
	*/
}
void model_3d::form_wireframe(){
	/**
	* 2D to 3D modelling:
	*Perform calculations to generate the wireframe model of the 3D solid by generating correspondence between edges in various views
	*/
	#undef v
	#undef e
	#undef s
	for(int i=0;i<this->topview->v.size() ; i++){
		float x=this->topview->v[i]->x;
		float y=this->topview->v[i]->y;
		float z=this->frontview->v[i]->z;
		int vno=this->topview->v[i]->vno;
		vertex *v_3d = new vertex(x,y,z,vno);
		model_3d::v.push_back(v_3d);
	}
	for(int i=0;i<this->topview->e.size() ; i++){
		vertex *a = model_3d::v[this->topview->e[i]->a->vno-1];
		vertex *b = model_3d::v[this->topview->e[i]->b->vno-1];
		int eno=this->topview->e[i]->eno;
		edge *e_3d = new edge(a,b,eno);
		e_3d->hidden= false;
		model_3d::e.push_back(e_3d);
	}
	//display_wireframe();
	form_3dfaces();	
}
void model_3d::form_3dfaces(){
	/**
	*Form 3d faces on the wireframe model using Minimum Surface Angle approach
	*/
	int nos=0;
	int matrix[e.size()+2][e.size()+2];
	static int ibc=0;
	for(int i=0;i<v.size();i++)
	{
		vector<int> neighbours = get_neighbours(v[i]);
		for(int j=0;j<neighbours.size();j++)
		{
			edge *e1 = is_edge(v[i]->vno,neighbours[j]);
			int checkno = neighbours[j];
			for(int k=j+1;k<neighbours.size();k++)
			{
				edge *e2 = is_edge(v[i]->vno,neighbours[k]);
				if(matrix[e1->eno][e2->eno]==1)
					continue;
				surface *s_temp = new surface();
				s_temp->boundary.push_back(e1);
				s_temp->boundary.push_back(e2);
				s_temp->calc_coeff();
				if((s_temp->coeff[0]!=s_temp->coeff[0])||(s_temp->coeff[1]!=s_temp->coeff[1])||(s_temp->coeff[2]!=s_temp->coeff[2])||(s_temp->coeff[3]!=s_temp->coeff[3]))
					continue;
				// cout<<"edge1 : "<<e1->eno<<" edge2: "<<e2->eno<<" coeff: "<<s_temp->coeff[0]<<" "<<s_temp->coeff[1]<<" "<<s_temp->coeff[2]<<" "<<s_temp->coeff[3]<<endl;
				int vno2 = neighbours[k];
				int prev_vno = v[i]->vno;
				flag2:
				vector<int> n1 = get_neighbours(v[vno2-1]);
				int dummy=0;
				for (int l = 0; l < n1.size(); l++)
				{
					if(n1[l]==prev_vno)
						continue;
					edge *e3 = is_edge(vno2,n1[l]);
					//  mimnimum internal angle nr
					// float d1= abs(e3->dotproduct(e1));
					// float d2= abs(e3->dotproduct(e2));
					// cout<<"Edge3 : "<<e3->eno<<" ";
					bool var=true;
					for(int l1=0;l1<s_temp->boundary.size();l1++)
						if(e3->overlap(s_temp->boundary[l1]))
							var=false;
					if(s_temp->dotpdt(e3)==0 && var)
					{
						// cout<<"ghi"<<endl;
						ibc++;
						if(ibc==1000)
							exit(0);
						s_temp->boundary.push_back(e3);

						prev_vno = vno2;
						vno2= n1[l];
						dummy=1;
						if(s_temp->boundary.size()>=8)
							goto flag3;
						if(checkno == n1[l])
						{
							for(int m=0;m<s_temp->boundary.size();m++)
							{
								for(int m1=0;m1<s_temp->boundary.size();m1++)
								{
									matrix[s_temp->boundary[m]->eno][s_temp->boundary[m1]->eno]=1;
									matrix[s_temp->boundary[m1]->eno][s_temp->boundary[m]->eno]=1;
								}		
							}
							s_temp->sno = ++nos;
							s.push_back(s_temp);
							goto flag1;
						}
						goto flag2;
					}
					// cout<<endl;
				}
				if(dummy==0)
				{
					flag3:;
					delete s_temp;
				}
				flag1:;
			}
		}
	}
	// display_3d_model();
}
vector<int> model_3d::get_neighbours(vertex *vn){
	/**
	*Returns vertex numbers of all the neighbours of a given vertex
	*/
	vector<int> arr;
	for(int i=0;i<e.size();i++)
	{
		if(e[i]->a->vno == vn->vno)
		{
			arr.push_back(e[i]->b->vno);
		}
		else if(e[i]->b->vno == vn->vno)
		{
			arr.push_back(e[i]->a->vno);
		}
	}
	return arr;

}
edge* model_3d::is_edge(int a, int b)
{
	for(int i=0;i<e.size();i++)
	{
		if((e[i]->a->vno == a && e[i]->b->vno == b)||(e[i]->a->vno == b && e[i]->b->vno == a))
			return e[i];
	}
	/**
	* Return the edge corresponding to vertices whose vertex numbers are given as integers
	*/
} 

void model_3d::model_3d_verification(){/**
	*Verify vertices,edges and surfaces using a set of decision rules and remove false ones
	*/
}
void model_3d::display_wireframe(){
	/**
	* Display the 3d wireframe model formed by the form_wireframe function as a list of vertices and edges.
	*/
	cout<<"3\n"<<v.size()<<endl;
	for(int i=0;i<topview->v.size() ; i++){
		cout<<v[i]->vno<<" "<<v[i]->x<<" "<<v[i]->y<<" "<<v[i]->z<<endl;
	}
	cout<<e.size()<<endl;
	for(int i=0;i<topview->e.size() ; i++){
		cout<<e[i]->eno<<" "<<e[i]->a->vno<<" "<<e[i]->b->vno<<endl;
	}	
}
void model_3d::display_3d_model(){
	/**
	* Display the 3d solid model formed in the end as a list of vertices, edges and surfaces.
	*/
	this->dispvertex();
	this->dispedge();
	this->dispsurface();
}
void model_3d::dispvertex(){
	int i, n = v.size();
	cout<<"3D Vertices"<<endl;
	for(i=0;i<n;i++){
		cout<<v[i]->vno<<" "<<v[i]->x<<" "<<v[i]->y<<" "<<v[i]->z<<endl;
	}
	/**
	* Display the list of true vertices in the 3D solid
	*/
}

void model_3d::dispedge(){
	int i, n = v.size();
	cout<<"3D Edges"<<endl;
	n = e.size();
	for(i=0;i<n;i++){
		cout<<e[i]->eno<<" "<<e[i]->a->vno<<" "<<e[i]->b->vno<<" Hidden:"<<e[i]->hidden<<" istrue:"<<e[i]->istrue<<endl;
	}
	/**
	* Display the ist of edges of the 3D solid
	*/
}

void model_3d::dispsurface(){
	int i, j, n = v.size();
	cout<<"3D Surfaces"<<endl;
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
	* Display the list of surfaces in the 3D solid each as a list of edges forming the surface boundary
	*/
}
void model_3d::save2Dmodels(fstream &out){
	out<<"2"<<endl;
	out<<"0"<<endl;
	out<<topview->v.size()<<endl;
	for(int i=0;i<topview->v.size();i++)
		out<<topview->v[i]->vno<<" "<<topview->v[i]->x<<" "<<topview->v[i]->y<<endl;
	out<<topview->e.size()<<endl;
	for (int i=0;i<topview->e.size();i++)
		out<<topview->e[i]->eno<<" "<<topview->e[i]->a->vno<<" "<<topview->e[i]->b->vno<<" "<<(topview->e[i]->hidden?1:0)<<endl;

	out<<"1"<<endl;
	out<<frontview->v.size()<<endl;
	for(int i=0;i<frontview->v.size();i++)
		out<<frontview->v[i]->vno<<" "<<frontview->v[i]->x<<" "<<frontview->v[i]->z<<endl;
	out<<frontview->e.size()<<endl;
	for (int i=0;i<frontview->e.size();i++)
		out<<frontview->e[i]->eno<<" "<<frontview->e[i]->a->vno<<" "<<frontview->e[i]->b->vno<<" "<<(frontview->e[i]->hidden?1:0)<<endl;

	out<<"2"<<endl;
	out<<sideview->v.size()<<endl;
	for(int i=0;i<sideview->v.size();i++)
		out<<sideview->v[i]->vno<<" "<<sideview->v[i]->y<<" "<<sideview->v[i]->z<<endl;
	out<<sideview->e.size()<<endl;
	for (int i=0;i<sideview->e.size();i++)
		out<<sideview->e[i]->eno<<" "<<sideview->e[i]->a->vno<<" "<<sideview->e[i]->b->vno<<" "<<(sideview->e[i]->hidden?1:0)<<endl;
	/**
	* Save the 2D views of the solid in a .txt file. This file can be further usable as an input to 2D to 3D reconstruction of the solid!
	*/
}

void model_3d::save3Dmodel(fstream &out){
	out<<"3"<<endl;
	out<<topview->v.size()<<endl;
	for(int i=0;i<topview->v.size();i++){
		if(this->v[i]->istrue)
			out<<this->v[i]->vno<<" "<<this->v[i]->x<<" "<<this->v[i]->y<<" "<<this->v[i]->z<<endl;
	}
	out<<topview->e.size()<<endl;
	for (int i=0;i<topview->e.size();i++){
		if(this->e[i]->istrue)
			out<<this->e[i]->eno<<" "<<this->e[i]->a->vno<<" "<<topview->e[i]->b->vno<<endl;
	}
	out<<topview->s.size()<<endl;
	for (int i=0; i<this->s.size();i++){
		out<<s[i]->sno<<" "<<s[i]->boundary.size()<<" ";
		for (int j = 0;j<s[i]->boundary.size();j++	){
			out<<s[i]->boundary[j]->eno<<" ";
		}
		out<<endl;
	}
	/**
	* Save the 3D view of the solid in a .txt file. This file can be further usable as an input to 3D to 2D reconstruction of the solid!
	*/
}