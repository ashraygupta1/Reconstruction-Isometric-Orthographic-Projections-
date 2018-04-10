#include<bits/stdc++.h>
#include<fstream>
#include<GL/glut.h>	
#include<gtk/gtk.h>
#include "vertex.h"
#include "edge.h"
#include "surface.h"
#include "model_2d.h"
#include "model_3d.h"

// Global variables:

// Main file
static model_3d Model;
static model_2d Top;
static model_2d Front;
static model_2d Side;

// OpenGL
int n = 0;
static float max1 = 1.0;
static float alp = 0, bet = 0, gam = 0;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool fullscreen = false;
bool mouseDown = false;

// GTK:
string file_path;
string file_name;
string save_file_path;
int argc1;
char **argv1;


// Open GL functions:
void initGL1() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}
void initGL2() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
void calcmax(){

	// Model.display_3d_model();
	// cout<<endl;
	// Model.topview->display_model();
	// cout<<endl;
	// Model.frontview->display_model();
	// cout<<endl;
	// Model.sideview->display_model();
	
	int i, n = Model.v.size();
	// cout<<n<<endl;
	for(i=0;i<n;i++){
   		if (!Model.v[i]->istrue)
   			continue;
		if(Model.v[i]->x > max1)
			max1 = Model.v[i]->x;

		if(Model.v[i]->y > max1)
			max1 = Model.v[i]->y;
		if(Model.v[i]->z > max1)
			max1 = Model.v[i]->z;
	}
   max1*=2;
   // cout<<"Max = "<<max1<<endl;
}
void display1(){
   // if(toggle){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
	//Print 2D figures
	// glRotatef(60.0f, 0.0f, 0.0f, 1.0f); // Rotate 180 degree
	glPushAttrib(GL_ENABLE_BIT);	
	// cout<<"Hidden Top View edges:\n";
	int i, n;
	n = Model.topview->e.size();
	for(int i=0;i<n;i++){
		if(!Model.topview->e[i]->istrue)
			continue;
		glLineStipple(5, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		if(Model.topview->e[i]->hidden){
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(-1.25f+Model.topview->e[i]->a->x/max1, -1.25f+Model.topview->e[i]->a->y/max1);
			glVertex2f(-1.25f + Model.topview->e[i]->b->x /max1, -1.25f+Model.topview->e[i]->b->y/max1);
			// cout<<-3.0+Model.topview->e[i]->a->x/max1<<endl;
			// cout<<i<<" ("<<Model.topview->e[i]->a->x/max1<<", "<<Model.topview->e[i]->a->y/max1<<") , ("
			// 		<<Model.topview->e[i]->b->x /max1<<", "<<Model.topview->e[i]->b->y/max1<<")\n";
		}
		glEnd();
	}
	glPopAttrib();	
	// cout<<"Solid Top View edges:\n";
	for(int i=0;i<n;i++){
		if(!Model.topview->e[i]->istrue)
			continue;
		glBegin(GL_LINES);
		if(!Model.topview->e[i]->hidden){
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(-1.25f+Model.topview->e[i]->a->x/max1, -1.25f+Model.topview->e[i]->a->y/max1);
			glVertex2f(-1.25f + Model.topview->e[i]->b->x /max1, -1.25f+Model.topview->e[i]->b->y/max1);
			// cout<<i<<" ("<<Model.topview->e[i]->a->x/max1<<", "<<Model.topview->e[i]->a->x/max1<<") , ("
			// 		<<Model.topview->e[i]->b->x /max1<<", "<<Model.topview->e[i]->b->y/max1<<")\n";
		}
		glEnd();
	}
	//Hidden Front View edges:
	// cout<<"Hidden front View edges:\n";
	glPushAttrib(GL_ENABLE_BIT);	
	n = Model.frontview->e.size();
	for(int i=0;i<n;i++){
		if(!Model.frontview->e[i]->istrue)
			continue;
		glLineStipple(5, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		if(Model.frontview->e[i]->hidden){
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(-1.25f+Model.frontview->e[i]->a->x/max1, Model.frontview->e[i]->a->z/max1);
			glVertex2f(-1.25f + Model.frontview->e[i]->b->x /max1,Model.frontview->e[i]->b->z/max1);
			// cout<<i<<" ("<<Model.frontview->e[i]->a->x/max1<<", "<<Model.frontview->e[i]->a->z/max1<<") , ("
			// 		<<Model.frontview->e[i]->b->x /max1<<", "<<Model.frontview->e[i]->b->z/max1<<")\n";
		}
		glEnd();
	}
	glPopAttrib();	
	//Solid Front View edges:
	// cout<<"Solid Front View edges:\n";
	for(int i=0;i<n;i++){
		if(!Model.frontview->e[i]->istrue)
			continue;
		glBegin(GL_LINES);
		if(!Model.frontview->e[i]->hidden){
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(-1.25f+Model.frontview->e[i]->a->x/max1, Model.frontview->e[i]->a->z/max1);
			glVertex2f(-1.25f + Model.frontview->e[i]->b->x /max1, Model.frontview->e[i]->b->z/max1);
			// cout<<i<<" ("<<Model.frontview->e[i]->a->x/max1<<", "<<Model.frontview->e[i]->a->z/max1<<") , ("
			// 		<<Model.frontview->e[i]->b->x /max1<<", "<<Model.frontview->e[i]->b->z/max1<<")\n";
		}
		glEnd();
	}

	//Hidden Side View edges:
	// cout<<"Hidden side View edges:\n";
	glPushAttrib(GL_ENABLE_BIT);	
	n = Model.sideview->e.size();
	for(int i=0;i<n;i++){
		if(!Model.sideview->e[i]->istrue)
			continue;
		glLineStipple(5, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		if(Model.sideview->e[i]->hidden){
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(Model.sideview->e[i]->a->y/max1, -1.25f+Model.sideview->e[i]->a->z/max1);
			glVertex2f(Model.sideview->e[i]->b->y /max1, -1.25f+Model.sideview->e[i]->b->z/max1);
			// cout<<i<<" ("<<Model.sideview->e[i]->a->y/max1<<", "<<Model.sideview->e[i]->a->z/max1<<") , ("
			// 		<<Model.sideview->e[i]->b->y /max1<<", "<<Model.sideview->e[i]->b->z/max1<<")\n";
		}
		glEnd();
	}
	glPopAttrib();	
	//Solid Side View edges:
	// cout<<"solid side View edges:\n";
	for(int i=0;i<n;i++){
		if(!Model.sideview->e[i]->istrue)
			continue;
		glBegin(GL_LINES);
		if(!Model.sideview->e[i]->hidden){
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(Model.sideview->e[i]->a->y/max1, -1.25f+Model.sideview->e[i]->a->z/max1);
			glVertex2f(Model.sideview->e[i]->b->y /max1, -1.25f+Model.sideview->e[i]->b->z/max1);
			// cout<<i<<" ("<<Model.sideview->e[i]->a->y/max1<<", "<<Model.sideview->e[i]->a->z/max1<<") , ("
			// 		<<Model.sideview->e[i]->b->y /max1<<", "<<Model.sideview->e[i]->b->z/max1<<")\n";
		}
		glEnd();
	}

	glFlush();
	// cout<<"2D view done!!"<<endl;
   // glutSwapBuffers();
}

void display2(){
   // glMatrixMode(GL_MODELVIEW);
   glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   int i, j, n = Model.s.size();
   // cout<<n;
   glRotatef(0.01*alp,1.0f,0.0f,0.0f);
   glRotatef(0.01*bet,0.0f,1.0f,0.0f);
   glRotatef(0.01*gam,0.0f,0.0f,1-.0f);
   for(i=0; i<n; i++){

      glColor3f(0.0, (float)((i+1)%n)/n,1.0f);
      // glColor4f((float)i/n, (float)((i+1)%n)/n, (float)((i+4)%n)/n, 0.0f);
      // cout<<i <<" ";
      // glColor4f(1.0, 0,0,1.0);
      glBegin(GL_POLYGON);
      
         glVertex3f(Model.s[i]->boundary[0]->a->x/max1, Model.s[i]->boundary[0]->a->y/max1, Model.s[i]->boundary[0]->a->z/max1);
         glVertex3f(Model.s[i]->boundary[0]->b->x/max1, Model.s[i]->boundary[0]->b->y/max1, Model.s[i]->boundary[0]->b->z/max1);
         // cout<<"("<<Model.s[i]->boundary[0]->a->x/max1<<" "<<Model.s[i]->boundary[0]->a->y/max1<<" "<<Model.s[i]->boundary[0]->a->z/max1<<") ";
         // cout<<"("<<Model.s[i]->boundary[0]->b->x/max1<<" "<<Model.s[i]->boundary[0]->b->y/max1<<" "<<Model.s[i]->boundary[0]->b->z/max1<<") ";

         for(j=1;j<Model.s[i]->boundary.size(); j++){
            if((Model.s[i]->boundary[j]->a->vno == Model.s[i]->boundary[j-1]->a->vno) || (Model.s[i]->boundary[j]->a->vno == Model.s[i]->boundary[j-1]->b->vno)){
               glVertex3f(Model.s[i]->boundary[j]->b->x/max1, Model.s[i]->boundary[j]->b->y/max1, Model.s[i]->boundary[j]->b->z/max1);
               // cout<<"("<<Model.s[i]->boundary[j]->b->x/max1<<" "<<Model.s[i]->boundary[j]->b->y/max1<<" "<<Model.s[i]->boundary[j]->b->z/max1<<") ";
            }
            else if((Model.s[i]->boundary[j]->b->vno == Model.s[i]->boundary[j-1]->a->vno) || (Model.s[i]->boundary[j]->b->vno == Model.s[i]->boundary[j-1]->b->vno)){
               glVertex3f(Model.s[i]->boundary[j]->a->x/max1, Model.s[i]->boundary[j]->a->y/max1, Model.s[i]->boundary[j]->a->z/max1);
               // cout<<"("<<Model.s[i]->boundary[j]->a->x/max1<<" "<<Model.s[i]->boundary[j]->a->y/max1<<" "<<Model.s[i]->boundary[j]->a->z/max1<<") ";
            }
         }
         // cout<<endl;
      
      glEnd();
      
   }
   glutSwapBuffers();
}

void idle(){
	if (!mouseDown){
		alp += 0.3f;
		bet += 0.4f;
	}
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		mouseDown = true;
		 
		xdiff = x - bet;
		ydiff = -y + alp;
	}
	else
		mouseDown = false;
}
 
void mouseMotion(int x, int y){
	if (mouseDown){
		bet = x - 0.1*xdiff;
		alp = y + 0.1*ydiff;
		 
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y){
   switch(key){
      case '9': alp =200;
      			bet = 0; gam = 0;
               break;
      case '8':   alp = -200; 
      			bet = 0; gam = 0;
               break;
      case '6':   bet = 200;
      			alp = 0; gam = 0;
               break;
      case '5': bet = -200;
      			alp = 0; gam = 0;
               break;
      case '3': gam =200;
      			bet = 0; alp = 0;
               break;
      case '2': gam = -200;
      			bet = 0; alp = 0;
               break;
      default: alp =0; bet =0; gam=0; break;
   }
   glutPostRedisplay();
}

// void reshape(int w, int h){
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
	 
// 	glViewport(0, 0, w, h);
	 
// 	gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
	 
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// }


static void open_dialog(GtkWidget* button, gpointer window)
{
        GtkWidget *dialog;
        dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_widget_show_all(dialog);
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_current_dir());
        gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if(resp == GTK_RESPONSE_OK)
        {
                file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
                int loc=0;
                loc=file_path.rfind('/')+1;
                file_name = file_path.substr(loc);
                cout<<file_name<<endl;
                string file_folder = file_path.substr(0,loc-1);
                cout<<file_path<<endl;                
        }        
        else
                g_print("You pressed Cancel\n");
        gtk_widget_destroy(dialog);
        
}
static void generate_dialog(GtkWidget *widget, gpointer window)
{
int i=0, j=0, k=0, dir=0, nv, ne, ns, a, b, c, d;
	fstream inFile;
	string inname;
inname = file_path;
	inFile.open(inname.c_str(), ios::in);

	// Add exception handling
	
	if(inFile.is_open()){
		inFile>>n;
		// model_2d *temp;
		if(n == 2){
			cout<<"\nFile is 2D\n";

			// Top view details
			inFile>>dir;
			if(dir != 0){
				cout<< "Wrong input!\n";
				// Raise exception
			}
			// Read Top view details
			Top.direction = dir;
			inFile >> nv; // No. of vertices
			for (i=0;i<nv;i++){
				inFile >> a >> b >> c;
				vertex *t = new vertex(b,c,0,a);
				// else if(dir == 2) vertex t(b,c,0,a);
				// else if(dir == 3) vertex t(0,y,z,a);
				Top.v.push_back(t);
			}
			inFile >> ne; //No. of edges
			for (i=0;i<ne;i++){
				inFile >> a >> b >> c >> d;
				edge *t = new edge(Top.v[b-1], Top.v[c-1], a);
				t->hidden = (d == 1)?true:false;
				// Top.v[b-1]->neighbours.push_back(t);
				// Top.v[c-1]->neighbours.push_back(t);
				Top.e.push_back(t);
			}
			// Read Front view details
			inFile>>dir;
			if(dir != 1){
				cout<< "Wrong input!\n";
				// Raise exception
			}
			Front.direction = dir;
			inFile >> nv; // No. of vertices
			for (i=0;i<nv;i++){
				inFile >> a >> b >> c;
				vertex *t = new vertex(b,0,c,a);
				Front.v.push_back(t);
			}
			inFile >> ne; //No. of edges
			for (i=0;i<ne;i++){
				inFile>>a>>b>>c>>d;
				edge *t = new edge(Front.v[b-1], Front.v[c-1], a);
				t->hidden = (d == 1)?true:false;
				// Front.v[b-1]->neighbours.push_back(t);		// Add edge to neighbours of the vertex
				// Front.v[c-1]->neighbours.push_back(t);
				Front.e.push_back(t);
			}
			// Side view details
			inFile>>dir;
			if(dir != 2){
				cout<< "Wrong input!\n";
				// Raise exception
			}
			// Read Side view details
			Side.direction = dir;
			inFile >> nv; // No. of vertices
			for (i=0;i<nv;i++){
				inFile >> a >> b >> c;
				vertex *t = new vertex(0,b,c,a);
				Side.v.push_back(t);
			}
			inFile >> ne; //No. of edges
			for (i=0;i<ne;i++){
				inFile>>a>>b>>c>>d;
				edge *t = new edge(Side.v[b-1], Side.v[c-1], a);
				t->hidden = (d == 1)?true:false;
				// Side.v[b-1]->neighbours.push_back(t);
				// Side.v[c-1]->neighbours.push_back(t);
				Side.e.push_back(t);
			}
			Model.frontview = &Front;
			Model.topview = &Top;
			Model.sideview = &Side;
			Model.form_wireframe();

		}
		else if(n == 3){
			cout<<"\nFile is 3D\n";
			inFile >> nv; // No. of vertices
			for (i=0;i<nv;i++){
				inFile >> a >> b >> c >> d;
				vertex *t = new vertex(b,c,d,a);
				Model.v.push_back(t);
			}
			// Model.dispvertex();
			inFile >> ne; //No. of edges
			for (i=0;i<ne;i++){
				inFile >> a >> b >> c;
				edge *t = new edge(Model.v[b-1], Model.v[c-1], a);
				// Model.v[b-1]->neighbours.push_back(t);
				// Model.v[c-1]->neighbours.push_back(t);
				Model.e.push_back(t);
			}
			// Model.dispedge();
			inFile >> ns; // No. of surfaces
			for (i=0;i<ns;i++){
				inFile>> c;
				inFile>> a;
				vector<edge*> t;
				for(j=0;j<a;j++){
					inFile>>b;
					t.push_back(Model.e[b-1]);
				}
				surface *t1 = new surface(t,c);
				// for (j=0;j<t.size();j++){
				// 	t1->boundary[j]->adjsurface.push_back(t1);
				// }
				// t1->calc_coeff();
				Model.s.push_back(t1); //Add surface list to model_3d class.
			}
			Model.topview = Model.basic_proj(0);
			Model.frontview = Model.basic_proj(1);
			Model.sideview = Model.basic_proj(2);
			// Model.display_3d_model();

			Model.calc_2d(0);
			Model.calc_2d(1);
			Model.calc_2d(2);
			//Write model in a file:
			
			// Model.dispsurface();	
		}
		else{
			cout<<"Invalid file format!\n";
		}
		//Display Model:
		Model.display_3d_model();
		cout<<endl;
		Model.topview->display_model();
		cout<<endl;
		Model.frontview->display_model();
		cout<<endl;
		Model.sideview->display_model();
	}
	else cout<<"File did not open!";
	// Display in GLCD: 
	calcmax();
//Save
	fstream outFile;
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;
    dialog = gtk_file_chooser_dialog_new ("Save File",
                                  GTK_WINDOW(window),
                                  action,GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    chooser = GTK_FILE_CHOOSER (dialog);

    gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
    string file_name_1 ="out_";
    file_name_1 = file_name_1 + file_name;
    const char *file_name_2 =file_name_1.c_str();
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(dialog),file_name_2);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_OK)
      {
        save_file_path = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
        cout<<save_file_path<<endl;
        outFile.open(save_file_path.c_str(), ios::out);
		if(outFile.is_open()){
			if(n==3)
				Model.save2Dmodels(outFile);
			else if(n==2)
				Model.save3Dmodel(outFile);
		}
		else cout<<"Out file not open";
    }

    gtk_widget_destroy (dialog);
//OpenGL
	glutInit(&argc1, argv1);          // Initialize GLUT
	// glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutCreateWindow("2D views");  // Create window with the given title
	glutInitWindowSize(300, 300);   // Set the window's initial width & height
	glutInitWindowPosition(355, 434); // Position the window's initial top-left corner
	// glMatrixMode(GL_MODELVIEW);      // Select the Projection matrix for operation
	// glLoadIdentity();                 // Reset Projection matrix
	gluOrtho2D(-2,1,-2,1);
   // glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutDisplayFunc(display1);       // Register callback handler for window re-paint event
	initGL1();                       // Our own OpenGL initialization

	glutCreateWindow("3D view");  // Create window with the given title
	glutInitWindowSize(300, 300);   // Set the window's initial width & height
	//glutInitWindowPosition(140, 140); // Position the window's initial top-left corner
	glMatrixMode(GL_MODELVIEW);      // Select the Projection matrix for operation
	glLoadIdentity();                 // Reset Projection matrix
	gluOrtho2D(-1,1,-1,1);
   // glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutDisplayFunc(display2);       // Register callback handler for window re-paint event
	initGL2();

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	// glutIdleFunc(idle);

	glutMainLoop();                 // Enter the event-processing loop
	//gtk_label_set_text(GTK_LABEL(data),"You clicked the button.");
}
// static void save_dialog(GtkWidget* button, gpointer window)
// {

// }
void gtk_interface()
{
	gtk_init(&argc1, &argv1);
	GtkWidget *window, *label, *open, *generate, *table;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//button = gtk_button_new_with_label("Exit");
	g_signal_connect(window,"delete event",G_CALLBACK(gtk_main_quit),NULL);
	
	//gtk_widget_set_size_request(window, 550, 330);
	
	/*g_signal_connect(button,"clicked",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_add(GTK_CONTAINER(window),button);
	gtk_widget_set_size_request(window,1000,1000);
	gtk_window_set_title(GTK_WINDOW(window),"Implementing Button");
	*/
	table = gtk_table_new(3,3,FALSE);
	open = gtk_button_new_with_mnemonic("Open");
	generate = gtk_button_new_with_mnemonic("Save & Generate");
	//save = gtk_button_new_with_mnemonic("Save");
	//label = gtk_label_new ("Hello World");
	g_signal_connect(open, "clicked", G_CALLBACK(open_dialog), window);
    g_signal_connect(generate, "clicked", G_CALLBACK(generate_dialog), window);
    //g_signal_connect(save, "clicked", G_CALLBACK(save_dialog), window);
        
	gtk_table_attach(GTK_TABLE(table),open,0,1,2,3,GTK_FILL,GTK_FILL,0,0);
	gtk_table_attach(GTK_TABLE(table),generate,1,2,2,3,GTK_FILL,GTK_FILL,0,0);
	// gtk_table_attach(GTK_TABLE(table),save,2,3,2,3,GTK_FILL,GTK_FILL,0,0);
	
	//gtk_table_set_col_spacing (GTK_TABLE(table),0, 200);
	//gtk_table_set_col_spacing (GTK_TABLE(table),1, 200);
	
	//button = gtk_button_new_with_mnemonic("Button_2");
	/*label = gtk_label_new ("Hello World_2");
	gtk_table_attach(GTK_TABLE(table),label,0,1,1,2,GTK_FILL,GTK_FILL,0,0);
	gtk_table_attach(GTK_TABLE(table),button,1,2,1,2,GTK_FILL,GTK_FILL,0,0);
	*/
	gtk_container_add(GTK_CONTAINER(window),table);


	gtk_widget_show_all(window);
	gtk_main();
}
// Main Function:

int main(int argc, char **argv){
	// int i=0, j=0, k=0, n=0, dir=0, nv, ne, ns, a, b, c, d;
	// fstream inFile, outFile;
	// string inname, outname;
	argc1=argc;
	argv1=argv;
	gtk_interface();
	// cout<<" Enter file name: (Please keep the file in sample folder to be accesible. Give the name without extension but the extension must be .txt)"<<endl;
	// cin>> s;
	//inname = "../sample/" + s + ".txt";
	//outname = "../sample/" + s + "_out.txt";
	
	// cout<<"shello";
	return 0;
}
