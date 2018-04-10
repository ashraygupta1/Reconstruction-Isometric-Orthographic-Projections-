# 3D projection and Solid Reconstruction
A software for effectively making projections of 3D solids to three 2D views, namely top, front and side view. Further, we provide the ability to reconstruct a 3D solid from it's three 2D views.

### Features and Functionalities

  - An easy to use interface to upload the input .txt file and save the output .txt file. 
  - An Open GL canvus to display the 2D views as well as the 3D solid with the functionality to rotate the solid as well.
  - The hidden lines for hidden edges and surfaces in the 2D views have been taken care of and been displayed in either case.

### Installation

3D solid projections and reconstruction requires [GTK](https://www.gtk.org/) library and [OpenGL](https://www.opengl.org/) to be installed.
For installing OpenGL, you can go through this [tutorial](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/). 
For installing GTK on Linux,
- First you need gtk2 and the command for that is:
```sh
$ sudo apt-get install gtk2.0
```
- Then you need the development package libgtk2.0-dev and this can be installed by the command:
```sh
$ sudo apt-get install build-essential libgtk2.0-dev
```
Windows users might refer to [this](https://www.gtk.org/download/windows.php) to install GTK on their devices. Alternatively, here is the [link](https://www.gtk.org/download/macos.php) for MAC users.
Now, we are good to go.

### How to build and run the app?
Clone or download this repository. For clone, use ``` $ git clone (repository link)```. If download, unzip the folder and switch to src folder.
```sh
$ cd src
```
Then, type ``` $ make```. And you are ready to go.  Then type this to run your application.
```sh
$ ./app
```
For any future runs, you can just double click the 'app' created.

### Input file specifications
For a 3D file: 
```sh
3                   //3 for 3D, 2 for 2D
8                   //No. of vertices
1 0 0 0             //vertex no., vertex coordinate x,y,z
2 0 0 5             //vertex no., vertex coordinate x,y,z     
...
12                  //No. of edges
1 1 2               //edge no., edge between vertex no. 1 and 2. 
2 2 3               //edge no., edge between the two vertex nos.
...
6                   //No. of surfaces
1 4 1 2 3 4         //Surface no., list of edge nos.(in order) comprising the surface. 
2 4 1 6 9 5         //Surface no., list of edge nos.(in order) comprising the surface. 
...
```
For a 2D file,
```sh
2					//2 for 2D, 3 for 3D
0					//0 for top view, 1 for front and 2 for side
8                   //No. of vertices in this view
1 0 0               //vertex no., vertex coordinate x,y
2 0 0               //vertex no., vertex coordinate x,y
...
12					//No. of edges in this view
1 1 2 0             //edge no. ; edge between vertex no. 1 and 2. ; 0 for hidden, 1 for not hidden
...
1					//0 for top view, 1 for front and 2 for side
8					//No. of vertices in this view
1 0 0				//vertex no., vertex coordinate x,y
12					//No. of edges in this view
2 2 3 0				//edge no. ; edge between vertex no. 1 and 2. ; 0 for hidden, 1 for not hidden
...
2					//0 for top view, 1 for front and 2 for side
8					//No. of vertices in this view
1 0 0				//vertex no., vertex coordinate x,y
12					//No. of edges in this view
3 3 4 0				//edge no. ; edge between vertex no. 1 and 2. ; 0 for hidden, 1 for not hidden
...
```

### Specifications / Assumptions

- Currently, we deal with rectilinear figures only.
- As in engineering graphics as well, the correspondences of vertices in 3 corresponding 2D views are known.
 
### Credits
We, Ashray Gupta (https://github.com/ashraygupta1) and Sarthak Tyagi (https://github.com/Sarthak-Tyagi) thank our professor [Subhashis Banerjee](http://www.cse.iitd.ernet.in/~suban/) and all the teacher assistants for the course Design Practices (COP290) for guiding us throughout this wonderful project.# Reconstruction-Isometric-Orthographic-Projections-
# Reconstruction-Isometric-Orthographic-Projections-
