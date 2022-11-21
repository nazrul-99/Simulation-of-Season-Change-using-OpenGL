//Season change in nature- Computer Graphics Lab Project
#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include "imageloader.h"
#include "vec3f.h"
#include "Birdseye.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


//new import
#define PI 3.1416

double Txval=0,Tyval=0,Tzval=0;
GLfloat alpha = 0.0, theta = 0.0, beta =0.0, 
axis_x=0.0, axis_y=0.0;


float rot_ang=0, rot_ang2=0,  
scale_x=1, scale_y=1, scale_z=1, 
frust=10, frustx = 0.0, frusty= 0.0;

GLfloat eye[3]= {0,0,10};
GLfloat look[3]= {0,0,0};
GLfloat up[3]= {0,1,0};

bool birds = false;

//new
GLfloat i =0.0f;
float lit = 1,lit2=0;
float amb = 1, diff = 1, spec = 1;
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
unsigned int ID;

int housepolygon = 1;
bool fan_state = 0;
GLfloat fan_angle = 0;
bool inside_house;


#define MAX_PARTICLES 1000
#define WCX		640
#define WCY		480
#define SUMMER	0
#define RAIN	1
#define	AUTUMN	2
#define SNOW	3
#define SPRING  4

using namespace std;

float slowdown = 2.0;
float velocity = 0.0;
float zoom = -40.0;
float pan = 0.0;
float tilt = 0.0;
float hailsize = 0.1;
int stopSnow = 0;
int loop;
int fall;
int earthQ =0;

//floor colors
float r = 1.0;
float g = 1.0;
float b = 1.0;
float ground_points[21][21][3];
float ground_colors[21][21][4];
int fog=0;


typedef GLfloat point[3];
point v[] = { { -0.5, 0.3, -0.5 }, { -0.5, -0.5, -0.5 }, { 0.5, -0.5, -0.5 }, { 0.5, 0.3, -0.5 }, { -0.5, 0.3, 0.5 }, { -0.5, -0.5, 0.5 }, { 0.5, -0.5, 0.5 }, { 0.5, 0.3, 0.5 } };
point z[] = { { -0.5, -0.3, 0.3 }, { -0.5, -0.5, 0.3 }, { -0.3, -0.5, 0.3 }, { -0.3, -0.3, 0.3 }, { -0.5, -0.3, -0.3 }, { -0.5, -0.5, -0.3 }, { -0.3, -0.5, -0.3 }, { -0.3, -0.3, -0.3 } };
point h[] = { { 0, 0.6, 0.0 }, { -0.5, 0.3, -0.5 }, { 0.5, 0.3, -0.5 }, { -0.5, 0.3, 0.5 }, { 0.5, 0.3, 0.5 } };
point f[] = { { 0.0, 0.35, 0.0 }, { 0.0, 0.25, 0.0 }, { 0.025, 0.25, -0.025 }, { -0.025, 0.25, -0.025 }, { -0.025, 0.25, 0.025 }, { 0.025, 0.25, 0.025 } };
point fb[] = { { 0.025, 0.25, -0.025 }, { 0.025, 0.25, 0.025 }, { 0.2, 0.25, 0.05 }, { 0.2, 0.25, -0.05 }, { -0.025, 0.25, -0.025 }, { -0.025, 0.25, 0.025 }, { -0.2, 0.25, 0.05 }, { -0.2, 0.25, -0.05 }, { 0.025, 0.25, -0.025 }, { -0.025, 0.25, -0.025 }, { -0.05, 0.25, -0.2 }, { 0.05, 0.25, -0.2 }, { -0.025, 0.25, 0.025 }, { 0.025, 0.25, 0.025 }, { 0.05, 0.25, 0.2 }, { -0.05, 0.25, 0.2 } };
point sft[] = { { -0.5, -0.3, 0.3 }, { -0.3, -0.3, 0.3 }, { -0.3, -0.3, 0.25 }, { -0.5, -0.3, 0.25 }, { -0.5, -0.25, 0.3 }, { -0.3, -0.25, 0.3 }, { -0.3, -0.25, 0.25 }, { -0.5, -0.25, 0.25 } };
point srt[] = { { -0.5, -0.3, -0.3 }, { -0.3, -0.3, -0.3 }, { -0.3, -0.3, -0.25 }, { -0.5, -0.3, -0.25 }, { -0.5, -0.25, -0.3 }, { -0.3, -0.25, -0.3 }, { -0.3, -0.25, -0.25 }, { -0.5, -0.25, -0.25 } };
point sbk[] = { { -0.5, -0.3, 0.3 }, { -0.5, -0.2, 0.3 }, { -0.45, -0.2, 0.3 }, { -0.45, -0.3, 0.3 }, { -0.5, -0.3, -0.3 }, { -0.5, -0.2, -0.3 }, { -0.45, -0.2, -0.3 }, { -0.45, -0.3, -0.3 } };
point t[] = { { 0.4, -0.1, -0.2 }, { 0.4, 0.1, -0.2 }, { 0.4, 0.1, 0.2 }, { 0.4, -0.1, 0.2 } };
point ts[] = { { 0.4, 0.05, -0.05 }, { 0.4, 0.0, -0.05 }, { 0.4, 0.0, 0.05 }, { 0.4, 0.05, 0.05 }, { 0.5, 0.0, -0.05 }, { 0.5, -0.05, -0.05 }, { 0.5, -0.05, 0.05 }, { 0.5, 0.0, 0.05 } };;
point hfrt[] = { { -0.5, 0.3, 0.5 }, { 0.5, 0.3, 0.5 }, { 0.5, 0.25, 0.65 }, { -0.5, 0.25, 0.65 } };



static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}


typedef struct {
    // Life
    bool alive;	// is the particle alive?
    float life;	// particle lifespan
    float fade; // decay
    // color
    float red;
    float green;
    float blue;
    // Position/direction
    float xpos;
    float ypos;
    float zpos;
    // Velocity/Direction, only goes down in y dir
    float vel;
    // Gravity
    float gravity;
}particles;

// Paticle System
particles par_sys[MAX_PARTICLES];


int flag =0;
float rHill= 0.3,gHill= 0.9,bHill=1.0;
float rSky=0.2 , gSky=0.0 , bSky= 0.8;

//Represents a terrain, by storing a set of heights and normals at 2D locations
class Terrain {
private:
    //no of grid points in the x and z directions
    int w; //Width
    int l; //Length
    //2d array which stores the height of the terrain at each of the grid point
    float** hs; //Heights
    //2d array which stores the normals of the terrain at each of the grid point
    
    Vec3f** normals;
    bool computedNormals; //Whether normals is up-to-date
public: //make the two 2d arrays.
    Terrain(int w2, int l2) { //constructor
        w = w2;
        l = l2;
        
        hs = new float*[l];
        for(int i = 0; i < l; i++) {
            hs[i] = new float[w];
        }
        
        normals = new Vec3f*[l];
        for(int i = 0; i < l; i++) {
            normals[i] = new Vec3f[w];
        }
        
        computedNormals = false;
    }
    
    ~Terrain() { //constructor for deleing
        for(int i = 0; i < l; i++) {
            delete[] hs[i];
        }
        delete[] hs;
        
        for(int i = 0; i < l; i++) {
            delete[] normals[i];
        }
        delete[] normals;
    }
    
    int width() {
        return w;
    }
    
    int length() {
        return l;
    }
    
    //Sets the height at (x, z) to y
    void setHeight(int x, int z, float y) {
        hs[z][x] = y;
        computedNormals = false;
    }
    
    //Returns the height at (x, z)
    float getHeight(int x, int z) {
        return hs[z][x];
    }
    
    //Computes the normals, if they haven't been computed yet
    void computeNormals() {
        if (computedNormals) {
            return;
        }
        
        //Compute the rough version of the normals
        Vec3f** normals2 = new Vec3f*[l];
        for(int i = 0; i < l; i++) {
            normals2[i] = new Vec3f[w];
        }
        
        for(int z = 0; z < l; z++) {
            for(int x = 0; x < w; x++) {
                Vec3f sum(0.0f, 0.0f, 0.0f);
                
                Vec3f out;
                if (z > 0) {
                    out = Vec3f(0.0f, hs[z - 1][x] - hs[z][x], -1.0f);
                }
                Vec3f in;
                if (z < l - 1) {
                    in = Vec3f(0.0f, hs[z + 1][x] - hs[z][x], 1.0f);
                }
                Vec3f left;
                if (x > 0) {
                    left = Vec3f(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
                }
                Vec3f right;
                if (x < w - 1) {
                    right = Vec3f(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
                }
                
                if (x > 0 && z > 0) {
                    sum += out.cross(left).normalize();
                }
                if (x > 0 && z < l - 1) {
                    sum += left.cross(in).normalize();
                }
                if (x < w - 1 && z < l - 1) {
                    sum += in.cross(right).normalize();
                }
                if (x < w - 1 && z > 0) {
                    sum += right.cross(out).normalize();
                }
                
                normals2[z][x] = sum;
            }
        }
        
        //Smooth out the normals
        const float FALLOUT_RATIO = 0.5f;
        for(int z = 0; z < l; z++) {
            for(int x = 0; x < w; x++) {
                Vec3f sum = normals2[z][x];
                
                if (x > 0) {
                    sum += normals2[z][x - 1] * FALLOUT_RATIO;
                }
                if (x < w - 1) {
                    sum += normals2[z][x + 1] * FALLOUT_RATIO;
                }
                if (z > 0) {
                    sum += normals2[z - 1][x] * FALLOUT_RATIO;
                }
                if (z < l - 1) {
                    sum += normals2[z + 1][x] * FALLOUT_RATIO;
                }
                
                if (sum.magnitude() == 0) {
                    sum = Vec3f(0.0f, 1.0f, 0.0f);
                }
                normals[z][x] = sum;
            }
        }
        
        for(int i = 0; i < l; i++) {
            delete[] normals2[i];
        }
        delete[] normals2;
        
        computedNormals = true;
    }
    
    //Returns the normal at (x, z)
    Vec3f getNormal(int x, int z) {
        if (!computedNormals) {
            computeNormals();
        }
        return normals[z][x];
    }
};

//Loads a terrain from a heightmap.  The heights of the terrain range from
//-height / 2 to height / 2.
Terrain* loadTerrain(const char* filename, float height) {
    Image* image = loadBMP(filename);
    Terrain* t = new Terrain(image->width, image->height); //construct a new terrain using the image height and width
    for(int y = 0; y < image->height; y++) { //takes each pixel and sets the cheight accordingly
        for(int x = 0; x < image->width; x++) {
            unsigned char color =
            (unsigned char)image->pixels[3 * (y * image->width + x)]; //takes the red component and calculate the hright
            float h = height * ((color / 255.0f) - 0.5f);
            t->setHeight(x, y, h);
        }
    }
    
    delete image;
    t->computeNormals();
    return t;
}
#define reflect glColor3f


GLuint loadTexture(Image* image) {
    GLuint textureId;
    //GLuint _textureId2;
    
    //The first argument is the number of textures we need, and the second is an array where OpenGL will store the id's of the textures.
    glGenTextures(1, &textureId); //Make room for our texture
    // to assign the texture id to our image data.
    //	We call glBindTexture(GL_TEXTURE_2D, textureId) to let OpenGL know
    // that we want to work with the texture we just created. Then, we call glTexImage2D to load the image into OpenGL.
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}


GLuint _textureId;
GLuint _textureSpring;
GLuint _textureSkySummer;
GLuint _textureSkyRain;
GLuint _textureSkyAutumn;
GLuint _textureSkyWinter;
GLuint _textureSkySpring;
GLuint _textureLeaf1;

float _angle = 60.0f;
Terrain* _terrain;

void cleanup() {
    delete _terrain;
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}
void initParticles(int i) {
    par_sys[i].alive = true;
    par_sys[i].life = 1.0;
    par_sys[i].fade = float(rand()%100)/1000.0f+0.003f;
    
    par_sys[i].xpos = (float) (rand() % 501) - 10;
    par_sys[i].ypos = 100.0;
    par_sys[i].zpos = (float) (rand() % 501) - 10;
    
    par_sys[i].red = 0.5;
    par_sys[i].green = 0.5;
    par_sys[i].blue = 1.0;
    
    par_sys[i].vel = velocity;
    par_sys[i].gravity = -0.8;//-0.8;
    
}
void init( ) {
    //int x, z;
    
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_FOG);
    glEnable(GL_NORMALIZE);
    
    
    
    Image* image = loadBMP("s1.bmp");
    _textureSpring = loadTexture(image);
    delete image;
    
    image = loadBMP("grass.bmp");
    _textureId = loadTexture(image);
    delete image;
    
    image = loadBMP("skySummer.bmp");
    _textureSkySummer = loadTexture(image);
    delete image;
    
    image = loadBMP("skyRain.bmp");
    _textureSkyRain = loadTexture(image);
    delete image;
    image = loadBMP("skyAutumn.bmp");
    _textureSkyAutumn = loadTexture(image);
    delete image;
    
    image = loadBMP("skySpring.bmp");
    _textureSkySpring= loadTexture(image);
    delete image;
    
    image = loadBMP("skyWinter.bmp");
    _textureSkyWinter = loadTexture(image);
    delete image;
    
    
    
    // Initialize particles
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        initParticles(loop);
    }
}

void reflectf(float r, float g, float b, float shiny = 0)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r,g,b, 1.0 };
    GLfloat mat_specular[] = { r,g,b, 1.0 };
    GLfloat mat_shininess[] = {shiny};
    
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
}

void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
    // GLfloat light_specular[] = { .4, .4, .4, 1.0 };
    GLfloat light_position[] = { -0.5f, 0.8f, 0.1f, 0.0f };
    
    if(lit==1)
        glEnable( GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
    
    if (amb == 1)   glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);   else    glLightfv( GL_LIGHT0, GL_AMBIENT, no_mat);
    if (diff == 1)  glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);   else    glLightfv( GL_LIGHT0, GL_DIFFUSE, no_mat);
    // if (spec == 1)  glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular); else    glLightfv( GL_LIGHT0, GL_SPECULAR, no_mat);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
}

void light2()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0, 0.5, 0., 1.0};
    GLfloat light_diffuse[]  = { 0, 0.5, 0.5, 1.0 };
    GLfloat light_specular[] = { 1.0, 1, 1, 1.0 };
    GLfloat light_position[] = { -2, 8, 8, 1.0 };
    
    if(lit2==1)
        glEnable( GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    if (amb == 1)   glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);   else    glLightfv( GL_LIGHT1, GL_AMBIENT, no_mat);
    if (diff == 1)  glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);   else    glLightfv( GL_LIGHT1, GL_DIFFUSE, no_mat);
    if (spec == 1)  glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular); else    glLightfv( GL_LIGHT1, GL_SPECULAR, no_mat);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    
    GLfloat spot_direction[] = { 0.0, -2, -2 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
}

void house(point a, point b, point c, point d, point e, point f, point g, point h)
{
	if (housepolygon)
	{
        glColor3f(0.545, 0.271, 0.075);
		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(e);
		glVertex3fv(f);			//left
		glVertex3fv(b);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3fv(d);
		glVertex3fv(h);			//right
		glVertex3fv(g);
		glVertex3fv(c);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);			//back
		glVertex3fv(c);
		glVertex3fv(d);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3fv(e);
		glVertex3fv(h);
		glVertex3fv(g);
		glVertex3fv(f);
		glEnd();
		glColor3f(1, 0.5, 0.31);
		glBegin(GL_POLYGON);
		glVertex3f(-0.15, -0.1, 0.51);
		glVertex3f(-0.15, -0.5, 0.51);
		glVertex3f(0.15, -0.5, 0.51);
		glVertex3f(0.15, -0.1, 0.51);
		glEnd();
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		glVertex3fv(b);
		glVertex3fv(f);
		glVertex3fv(g);
		glVertex3fv(c);
		glEnd();
		glBegin(GL_LINES);
		glVertex3fv(e);
		glVertex3fv(f);
		glVertex3fv(h);
		glVertex3fv(g);
		glVertex3fv(d);
		glVertex3fv(c);
		glVertex3fv(a);
		glVertex3fv(b);
		glEnd();
		glColor3f(1, 0.5, 0.31);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.15, -0.1, 0.5);
		glVertex3f(-0.15, -0.5, 0.5);
		glVertex3f(0.15, -0.5, 0.5);
		glVertex3f(0.15, -0.1, 0.5);
		glEnd();
	}
	glColor3f(0.96, 0.87, 0.70);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.49, -0.5);
	glVertex3f(-0.5, -0.49, 0.5);
	glVertex3f(0.5, -0.49, 0.5);				//bottom
	glVertex3f(0.5, -0.49, -0.5);
	glEnd();
}

void htop(point a, point b, point c, point d, point e)
{
	if (housepolygon)
	{
        if(fall==SNOW)
        {
            
            glColor3f(0.871, 0.722, 0.529);
        }
        else
        {
            glColor3f(0.855, 0.647, 0.125);
        }		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);			//back
		glVertex3fv(c);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);			//left
		glVertex3fv(d);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(d);			//front
		glVertex3fv(e);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(c);			//right
		glVertex3fv(e);
		glEnd();
	}
	else
	{
		glColor3f(0.70, 0.13, 0.13);
		glBegin(GL_LINES);
		glVertex3fv(a);
		glVertex3fv(b);
		glEnd();
		glBegin(GL_LINES);
		glVertex3fv(a);
		glVertex3fv(c);
		glEnd();
		glBegin(GL_LINES);
		glVertex3fv(a);
		glVertex3fv(d);
		glEnd();
		glBegin(GL_LINES);
		glVertex3fv(a);
		glVertex3fv(e);
		glEnd();
	}
}

void window()
{
	if (housepolygon)
	{
		glColor3f(0.5, 0.55, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(0.25, -0.1, 0.505);
		glVertex3f(0.4, -0.1, 0.505);
		glVertex3f(0.4, 0.05, 0.505);
		glVertex3f(0.25, 0.05, 0.505);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-0.25, -0.1, 0.505);
		glVertex3f(-0.4, -0.1, 0.505);
		glVertex3f(-0.4, 0.05, 0.505);
		glVertex3f(-0.25, 0.05, 0.505);
		glEnd();
	}
	else
	{
		glColor3f(0.5, 0.55, 0.5);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.25, -0.1, 0.505);
		glVertex3f(0.4, -0.1, 0.505);
		glVertex3f(0.4, 0.05, 0.505);
		glVertex3f(0.25, 0.05, 0.505);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.25, -0.1, 0.505);
		glVertex3f(-0.4, -0.1, 0.505);
		glVertex3f(-0.4, 0.05, 0.505);
		glVertex3f(-0.25, 0.05, 0.505);
		glEnd();
	}
}

void housefront(point a, point b, point c, point d)
{
	glColor3f(0.5,0,0);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(0.5, 0.25, 0.65);
	glVertex3f(0.5, -0.5, 0.65);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-0.5, 0.25, 0.65);
	glVertex3f(-0.5, -0.5, 0.65);
	glEnd();
}
void bed()
{
	glPushMatrix();
	glScalef(.1, .1, .1);
	glTranslatef(-3.5, -4.8, -7);
    //bed headboard
    glColor3f(0.5,0.2,0.2);
    glPushMatrix();
    glScalef(0.1, 0.5, 0.9);
    glTranslatef(-2,-0.5,6);
    drawCube();
    glPopMatrix();
    
    //bed body
    glColor3f(0.824, 0.706, 0.549);
    glPushMatrix();
    glScalef(1, 0.2, 0.9); //1, 0.2, 0.9
    glTranslatef(0,-0.5,6.2);
    drawCube();
    glPopMatrix();
    
    //pillow right far
    glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(0.5,0.5,6);
    glRotatef(20, 0,0,1);
    glScalef(0.1, 0.15, 0.28);
    drawCube();
    glPopMatrix();
    
    //pillow left near
    glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(0.5,0.5,7.2);
    glRotatef(22, 0,0,1);
    glScalef(0.1, 0.15, 0.28);
    drawCube();
    glPopMatrix();
    
    //blanket
    glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(1.4,0.45,5.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 0.05, 0.95);
    drawCube();
    glPopMatrix();
    
    //blanket side left part
    glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(1.4,-0.3,8.15);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 0.25, 0.05);
    drawCube();
    glPopMatrix();

	glPopMatrix();
    
}

void wardrobe()
{
    //Wardrobe *******************************************
       glPushMatrix();
	glScalef(.2, .2, .2);
	glTranslatef(-1.75, -2.4, -3);
       //wardrobe
       glColor3f(0.3,0.1,0);
       glPushMatrix();
       glTranslatef(0,0,4);
       glScalef(0.12, 0.6, 0.4);
       drawCube();
       glPopMatrix();
       
       //wardrobe's 1st drawer
       glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,1.4,4.05);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube();
       glPopMatrix();
       
       //wardrobe's 2nd drawer
       glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,1,4.05);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube();
       glPopMatrix();
       
       //wardrobe's 3rd drawer
       glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,0.6,4.05);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube();
       glPopMatrix();

       //wardrobe's 4th drawer
       glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,0.2,4.05);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube();
       glPopMatrix();
       
       //wardrobe's 1st drawer handle
       glColor3f(0.3,0.1,0);
       glPushMatrix();
       glTranslatef(0.37,1.5,4.3);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.03, 0.2);
       drawCube();
       glPopMatrix();
       
       //wardrobe's 2nd drawer handle
       glColor3f(0.3,0.1,0);
       glPushMatrix();
       glTranslatef(0.37,1.1,4.3);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.03, 0.2);
       drawCube();
       glPopMatrix();
       
       //wardrobe's 3rd drawer handle
       glColor3f(0.3,0.1,0);
       glPushMatrix();
       glTranslatef(0.37,0.7,4.3);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.03, 0.2);
       drawCube();
       glPopMatrix();
       
       //wardrobe's 4th drawer handle
       glColor3f(0.3,0.1,0);
       glPushMatrix();
       glTranslatef(0.37,0.3,4.3);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.03, 0.2);
       drawCube();
       glPopMatrix();
       
       //wardrobe left stripline
       glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.35,0,5.3);
       //glRotatef(22, 0,0,1);
       glScalef(0.01, 0.6, 0.0001);
       drawCube();
       glPopMatrix();
	   glPopMatrix();
}

void table()
{
	glColor3f(0.80, 0.72, 0.62);
	glPushMatrix();
	glTranslated(0.375, -0.325, -0.375);
	glScaled(2.5, 0.5, 2.5);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.475, -0.425, -0.475);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.475, -0.425, -0.275);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.275, -0.425, -0.275);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.275, -0.425, -0.475);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();
}

void tv(point a, point b, point c, point d)
{
	glColor3f(0.19, 0.31, 0.31);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();

}

void tvs(point a, point b, point c, point d, point a1, point b1, point c1, point d1)
{
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_LINES);
	glVertex3fv(a);
	glVertex3fv(a1);
	glEnd();
	glBegin(GL_LINES);
	glVertex3fv(b);
	glVertex3fv(b1);
	glEnd();
	glBegin(GL_LINES);
	glVertex3fv(c);
	glVertex3fv(c1);
	glEnd();
	glBegin(GL_LINES);
	glVertex3fv(d);
	glVertex3fv(d1);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(a1);
	glVertex3fv(b1);
	glVertex3fv(b);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(a1);
	glVertex3fv(d1);
	glVertex3fv(d);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(b);
	glVertex3fv(b1);
	glVertex3fv(c1);
	glVertex3fv(c);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(c);
	glVertex3fv(c1);
	glVertex3fv(d1);
	glVertex3fv(d);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(a1);
	glVertex3fv(b1);
	glVertex3fv(c1);
	glVertex3fv(d1);
	glEnd();
}


void teapot()
{
	glColor3f(0.55, 0.27, 0.07);
	glPushMatrix();
	glTranslated(0.35, -0.275, -0.35);
	glScaled(0.5, 0.5, 0.5);
	glutSolidTeapot(0.1);
	glPopMatrix();
}

void fan(point a, point b, point c, point d, point e, point f)
{
	glColor3f(0.72, 0.53, 0.04);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3fv(a);
	glVertex3fv(b);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(c);
	glVertex3fv(d);
	glVertex3fv(e);
	glVertex3fv(f);
	glEnd();
}

void fblade(point a, point b, point c, point d, point a1, point b1, point c1, point d1, point a2, point b2, point c2, point d2, point a3, point b3, point c3, point d3)
{
	glColor3f(0.72, 0.53, 0.04);
	if (fan_state)
	glRotatef(fan_angle, 0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(a1);
	glVertex3fv(b1);
	glVertex3fv(c1);
	glVertex3fv(d1);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(a2);
	glVertex3fv(b2);
	glVertex3fv(c2);
	glVertex3fv(d2);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3fv(a3);
	glVertex3fv(b3);
	glVertex3fv(c3);
	glVertex3fv(d3);
	glEnd();
}


void tree()
{
	glColor3f(0.9, 0.8, 0.0);
	glPushMatrix();
	glTranslated(-0.75, -0.35, 0.8);
	glScaled(0.5, 4.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

    
	if(fall == SNOW)
    {
        glColor3f(1.0,1.0,1.0);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.0,1.0,0.0);
    }
    
    else
    {
        glColor3f(0.0, 0.804, 0.0);
    }

	glPushMatrix();
	glTranslated(-0.75, -0.3, 0.8);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.1, 0.3, 500, 500);
	glPopMatrix();

	if(fall == SNOW)
    {
        glColor3f(1.0,1.0,1.0);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.0,1.0,0.0);
    }
    
    else
    {
        glColor3f(0.0, 0.804, 0.1);
    }
	glPushMatrix();
	glTranslated(-0.75, -0.25, 0.8);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.1, 0.3, 500, 500);
	glPopMatrix();

	if(fall == SNOW)
    {
        glColor3f(1.0,1.0,1.0);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.0,1.0,0.0);
    }
    
    else
    {
        glColor3f(0.196, 0.804, 0.196);
    }
	glPushMatrix();
	glTranslated(-0.75, -0.2, 0.8);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.1, 0.3, 500, 500);
	glPopMatrix();
}

void makecylinder(float height,float Base)
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	glColor3f(0.722, 0.525, 0.043);
	glPushMatrix();
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	gluCylinder(qobj, Base, Base - (0.2 * Base), height, 20, 20);
	glPopMatrix();
}
void maketree(float height,float Base)
{

	glPushMatrix();
	float angle;
	makecylinder(height, Base);
	glTranslatef(0.0f, height,0.0f);
	height -= height * 0.2f;
	Base -= Base * 0.3f;

	if (height > 1)
	{
		angle = 22.5f;
		glPushMatrix();
		glRotatef(angle, -1.0f, 0.0f, 0.0f);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5f, 0.0f, 0.866f);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5f, 0.0f, -0.866f);
		maketree(height, Base);
		glPopMatrix();
	}
	glPopMatrix();
}

void tree_2(){
    if(fall == SNOW)
    {
        glColor3f(0.561, 0.737, 0.561);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.000, 0.843, 0.000);
    }
    
    else
    {
        glColor3f(0.7, 0.7, 0.0);
    }
    

    glPushMatrix();
    glTranslatef(0,2,4.0);
    glTexCoord3f(5.0f, 5.0f,5.0f);
    glutSolidSphere(0.8, 16, 16);
    glPopMatrix();
    
    glColor3f(0.1, 0.2, 0.0); 
    
    glPushMatrix();
    glTranslatef(0,0,-2.0);
    glPushMatrix();
    glTranslatef(-0.5,0.0,6.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCone(0.1,2.0,100,100);
    glPopMatrix();
    glPopMatrix();
}

void tree_3()
{
	glColor3f(0.9, 0.8, 0.0);
	glPushMatrix();
	glTranslated(-0.75, -0.35, 0.8);
	glScaled(0.5, 4.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

    
	if(fall == SNOW)
    {
        glColor3f(1.0,1.0,1.0);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.0,1.0,0.0);
    }
    
    else
    {
        glColor3f(0.0, 0.804, 0.0);
    }

	glPushMatrix();
	glTranslated(-0.75, -0.3, 0.8);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.1, 0.4, 500, 500);
	glPopMatrix();

	if(fall == SNOW)
    {
        glColor3f(1.0,1.0,1.0);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.0,1.0,0.0);
    }
    
    else
    {
        glColor3f(0.0, 0.804, 0.1);
    }
	glPushMatrix();
	glTranslated(-0.75, -0.25, 0.8);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.1, 0.4, 500, 500);
	glPopMatrix();

}

void grass()
{
	glColor3f(0.13, 0.55, 0.13);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, -0.5, -1.0);
	glVertex3f(-1.0, -0.5, 1.0);
	glVertex3f(1.0, -0.5, 1.0);
	glVertex3f(1.0, -0.5, -1.0);
	glEnd();
}


void display_inside(){
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5+0,5+0,-5+0,5+0, 15, 40+10);
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    

    gluLookAt(0,0,20,0,0,0,0,1,0);

    glPushMatrix ();
    glScalef(4,4,4);
    
    glPushMatrix();
    glScalef(scale_x,scale_y,scale_z);
    glRotatef(rot_ang,0,1,0);
    glRotatef(rot_ang2,1,0,0);

    glPushMatrix();
    glTranslatef(0,0,-2);
    glScalef(2, 2, 2);
    house(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
	htop(h[0], h[1], h[2], h[3], h[4]);
	tv(t[0], t[1], t[2], t[3]);
	tvs(ts[0], ts[1], ts[2], ts[3], ts[4], ts[5], ts[6], ts[7]);
	grass();

	table();
	teapot();

	window();
	bed();
	wardrobe();

	housefront(hfrt[0], hfrt[1], hfrt[2], hfrt[3]);
	fan(f[0], f[1], f[2], f[3], f[4], f[5]);
	fblade(fb[0], fb[1], fb[2], fb[3], fb[4], fb[5], fb[6], fb[7], fb[8], fb[9], fb[10], fb[11], fb[12], fb[13], fb[14], fb[15]);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
	glEnable(GL_DEPTH_TEST);
    glFlush();
    glutSwapBuffers();
}

// For Rain
void drawRain() {
    float x, y, z;
    //glClearColor(rSky, gSky, bSky, 1.0f);
    for (loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
        if (par_sys[loop].alive == true) {
            x = par_sys[loop].xpos;
            y = par_sys[loop].ypos;
            z = par_sys[loop].zpos + zoom;
            
            // Draw particles
            glDisable(GL_TEXTURE_2D);
            glColor3f(0.5, 0.5, 1.0);
            glBegin(GL_LINES);
            glVertex3f(x, y, z);
            glVertex3f(x, y+3, z);
            glEnd();
            
            // Update values
            //Move
            // Adjust slowdown for speed!
            par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
            par_sys[loop].vel += par_sys[loop].gravity;
            // Decay
            par_sys[loop].life -= par_sys[loop].fade;
            
            if (par_sys[loop].ypos <= -2) {
                par_sys[loop].life = -1.0;
            }
            //Revive
            if (par_sys[loop].life < 0.0) {
                initParticles(loop);
            }
        }
    }
}

// For Snow
void drawSnow() {
    if(stopSnow==0)
    {
        float x, y, z;
        //glClearColor(rSky, gSky, bSky, 1.0f);
        for (loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
            if (par_sys[loop].alive == true) {
                x = par_sys[loop].xpos;
                y = par_sys[loop].ypos;
                z = par_sys[loop].zpos + zoom;
                
                // Draw particles
                glDisable(GL_TEXTURE_2D);
                glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                glTranslatef(x, y, z);
                glutSolidSphere(.8, 16, 16);
                glPopMatrix();
                
                // Update values
                //Move
                par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
                par_sys[loop].vel += par_sys[loop].gravity;
                // Decay
                par_sys[loop].life -= par_sys[loop].fade;
                
                if (par_sys[loop].ypos <= -5) {
                    int zi = z - zoom + 10;
                    int xi = x + 10;
                    ground_colors[zi][xi][0] = 1.0;
                    ground_colors[zi][xi][2] = 1.0;
                    ground_colors[zi][xi][3] += 1.0;
                    if (ground_colors[zi][xi][3] > 1.0) {
                        ground_points[xi][zi][1] += 0.1;
                    }
                    par_sys[loop].life = -1.0;
                }
                
                //Revive
                if (par_sys[loop].life < 0.0) {
                    initParticles(loop);
                }
            }
        }
    }
}



void Scale(bool clock = true)
{
    if(clock){
        
        scale_x+=1;
        scale_y+=1;
        scale_z+=1;
        
    }
    else {
        if(scale_x<0.01) {}
        else{
            scale_x-=1;
            scale_y-=1;
            scale_z-=1;
        }
    }
}



void display() {
    if (inside_house) {
        display_inside();
    } else {
        GLUquadric *quadric;
    quadric = gluNewQuadric();
    int i, j;
    //float x, y, z;
    glClearColor(rSky, gSky, bSky, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-3+frustx,3+frustx,-2+frusty,5+frusty, frust, 100+frust);

    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();    
    gluLookAt(eye[0],eye[1],eye[2],look[0],look[1],look[2],up[0],up[1],up[2]);
    
    
    
    glPushMatrix();
    glScalef(scale_x,scale_y,scale_z);
    glRotatef(rot_ang,0,1,0);
    glRotatef(rot_ang2,1,0,0);
    
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-_angle, 0.0f, 1.0f, 0.0f);
    
    // GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    // GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    // GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    light();
    light2();
    if(fog ==1)
    {
        GLfloat fogcolour[4]= {1.0,1.0,1.0,1.0};
        
        glFogfv(GL_FOG_COLOR,fogcolour);              /* Define the fog colour */
        /* How dense */
        glFogi(GL_FOG_MODE,GL_EXP);
        glFogf(GL_FOG_DENSITY,0.08);                   /* exponential decay */
        glFogf(GL_FOG_START,3.0);                   /* Where we start fogging */
        glFogf(GL_FOG_END,100.0);                       /* end */
        glHint(GL_FOG_HINT, GL_FASTEST);              /* compute per vertex */
        glEnable(GL_FOG);/* ENABLE */
        
    }
    else if(fog==0)
    {
        
        glDisable(GL_FOG);
    }
    

    
    glPushMatrix();
    
    glColor3f(4.0, 4.0, 4.0);          // green
    
    glEnable(GL_TEXTURE_2D);
    if (fall == RAIN)
    {
        glBindTexture(GL_TEXTURE_2D, _textureSkyRain);
    }
    else if (fall == SUMMER)
    {
        glBindTexture(GL_TEXTURE_2D, _textureSkySummer);
    }
    else if (fall == SNOW)
    {
        glBindTexture(GL_TEXTURE_2D, _textureSkyWinter);
    }
    else if (fall == AUTUMN)
    {
        glBindTexture(GL_TEXTURE_2D, _textureSkyAutumn);
    }
    else if (fall == SPRING)
    {
        glBindTexture(GL_TEXTURE_2D, _textureSkySpring);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluQuadricTexture(quadric, 20);
    gluSphere(quadric,75,40,40);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    
    
    glEnable(GL_TEXTURE_2D);
    if(fall == SPRING|| fall==AUTUMN)
    {
        glBindTexture(GL_TEXTURE_2D, _textureSpring);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, _textureId);
    }
    
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    
    glDisable(GL_TEXTURE_2D);

    //1st tree
    glPushMatrix();

    glTranslatef(7,3,-3.0);
    glScalef(4,4,4);
    tree();
    glPopMatrix();



    // 2nd tree
    if(fall == SNOW)
    {
        glColor3f(1.0,1.0,1.0);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.000, 0.498, 0.314);
    }
    
    else
    {
        glColor3f(0.0, 0.9, 0.0);
    }
    
    
    glPushMatrix();
    glTranslatef(-1.7,1.5,-4.5);
    glTexCoord3f(5.0f, 5.0f,5.0f);
    glutSolidSphere(0.6, 16, 16);
    
    glPopMatrix();

    glColor3f(0.722, 0.525, 0.043);
    glPushMatrix();
    glTranslatef(-4,0,1);
    glPushMatrix();
    glTranslatef(3.0,0.0,-5.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCone(0.1,2.0,100,100);
    glPopMatrix();
    glPopMatrix();


    
    
    if(fall == SNOW)
    {
        glColor3f(1.0,1.0,1.0);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(1.000, 0.498, 0.314);
    }
    
    else
    {
        glColor3f(0.0, 0.9, 0.0);
    }
    
    
    glPushMatrix();
    glTranslatef(-3.9,1.6,0);
    glTexCoord3f(5.0f, 5.0f,5.0f);
    glutSolidSphere(0.6, 16, 16);
    
    glPopMatrix();
    
    glColor3f(0.722, 0.525, 0.043);
    glPushMatrix();
    glTranslatef(-7,0,5);
    glPushMatrix();
    glTranslatef(3.0,0.0,-5.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCone(0.1,2.0,100,100);
    glPopMatrix();
    glPopMatrix();

    // tree 4
    glPushMatrix();
    glTranslatef(-.7,0, -.2);
    tree_2();
    glPopMatrix();


    // tree 5
    if(fall == SNOW)
    {
        glColor3f(1.0, 0.737, 0.561);
    }
    else if(fall == AUTUMN)
    {
        glColor3f(0.502, 0.502, 0.000);
    }
    
    else
    {
        glColor3f(0.722, 0.525, 0.043);
    }
    
    glPushMatrix();
    glTranslatef(3.8,2,-1.6);
    glTexCoord3f(5.0f, 5.0f,5.0f);
    glutSolidSphere(0.6, 16, 16);
    
    glPopMatrix();
    
    
    glColor3f(0.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(3.5,0.0,-2.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCone(0.1,2.0,100,100);
    
    glPopMatrix();
    


    // tree 6
    glPushMatrix();
    glScalef(.6,.6,.6);
    glTranslatef(7,-1, -4.5);
    maketree(2.0f,0.1f);
    glPopMatrix();


    // tree 7
    glPushMatrix();
    glScalef(.4,.4,.4);
    glTranslatef(9,-1, 9);
    maketree(3.0f,0.1f);
    glPopMatrix();

    // tree 8 
    glPushMatrix();
    glTranslatef(5,2,1.0);
    glScalef(4,4,4);
    tree_3();

    glPopMatrix();
    // tree 9
    glPushMatrix();
    glTranslatef(5,3,2.0);
    glScalef(4,4,4);
    tree();
    glPopMatrix();

    // lamp
    glColor3f(0, 0, 0);
    
    glPushMatrix();
    glTranslatef(-4,0.0,-5.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, .05, .05, 2, 100, 100);
    glPopMatrix();

    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-4,2,-5);
    glTexCoord3f(5.0f, 5.0f,5.0f);
    glutSolidSphere(0.15, 16, 16);
    
    glPopMatrix();


    // house
    glPushMatrix();
    glScalef(1.5,1.5,1.5);
    glPushMatrix();
    glTranslatef(1,1,0);
    house(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
	htop(h[0], h[1], h[2], h[3], h[4]);
	tv(t[0], t[1], t[2], t[3]);
	tvs(ts[0], ts[1], ts[2], ts[3], ts[4], ts[5], ts[6], ts[7]);
	table();
	teapot();
	window();
	bed();
	wardrobe();

	housefront(hfrt[0], hfrt[1], hfrt[2], hfrt[3]);
	fan(f[0], f[1], f[2], f[3], f[4], f[5]);
	fblade(fb[0], fb[1], fb[2], fb[3], fb[4], fb[5], fb[6], fb[7], fb[8], fb[9], fb[10], fb[11], fb[12], fb[13], fb[14], fb[15]);
    glPopMatrix();
    glPopMatrix();
    

    //house top
    glPushMatrix();
    glTranslatef(0,1,0);
    if(fall==SNOW)
    {
        
        glColor3f(0.871, 0.722, 0.529);
    }
    else
    {
        glColor3f(0.855, 0.647, 0.125);
    }

    
    glPushMatrix();
    glTranslatef(-3.0,0.5,-1.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCone(0.8,1.0,100,100);
    
    glPopMatrix();


    //house bottom
    glColor3f(0.545, 0.271, 0.075);
    
    glPushMatrix();
    glTranslatef(-3.0,0.0,-1.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCube(1.0);
    
    glPopMatrix();
    glPopMatrix();


    // house top2
    glPushMatrix();
    glTranslatef(0,1,0);
    if(fall==SNOW)
    {
        
        glColor3f(0.871, 0.722, 0.529);
    }
    else
    {
        glColor3f(0.722, 0.525, 0.043);
    }
    
    glPushMatrix();
    glTranslatef(-3, 0, 4);
    glPushMatrix();
    glTranslatef(-1.0,0.5,-2.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCone(0.8,1.0,100,100);
    
    glPopMatrix();
    glPopMatrix();

    //house bottom2
    glColor3f(0.4, 0.0, 0.0040);
    glPushMatrix();
    glTranslatef(-3, 0, 4);

    glPushMatrix();
    glTranslatef(-1.0,0.0,-2.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCube(1.0);
    
    glPopMatrix();
    
    glColor3f(0.8, 0.68, 0.0040);
    
    glPushMatrix();
    glTranslatef(-0.7,0.0,-2.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCube(0.5);
    
    glPopMatrix();
    glColor3f(0.8, 0.68, 0.0040);
    
    glPushMatrix();
    glTranslatef(-1.0,0.0,-1.7);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCube(0.5);

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    //house top3
    glPushMatrix();
    glTranslatef(0,1,0);
    if(fall==SNOW)
    {
        
        glColor3f(0.871, 0.722, 0.529);
    }
    else
    {
        glColor3f(0.824, 0.412, 0.118);
    }
    
    
    glPushMatrix();
    glTranslatef(-1.0,0.5,2.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCone(0.8,1.0,100,100);
    
    glPopMatrix();

    
    //house bottom3
    glColor3f(0.545, 0.271, 0.075);
    
    glPushMatrix();
    glTranslatef(-1.0,0.0,2.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCube(1.0);
    
    glPopMatrix();
    
    glColor3f(1.0, 1.0, 0.0);
    
    glPushMatrix();
    glTranslatef(-0.7,0.0,2.0);
    glRotatef(240.0,1.5,2.0,1.3);
    glTexCoord3f(5.0f, 5.0f,0.0f);
    glutSolidCube(0.5);
    
    glPopMatrix();
    glPopMatrix();
    
    
    
    glEnable(GL_TEXTURE_2D);
    if (fall== SNOW)
    {
        glDisable(GL_TEXTURE_2D);
    }
    
    
    
    float scale = 15.0f / max(_terrain->width() - 1, _terrain->length() - 1);
    glScalef(scale, scale, scale);
    glTranslatef(-(float)(_terrain->width() - 1) / 2,
                 0.0f,
                 -(float)(_terrain->length() - 1) / 2);
    
    glColor3f(r, g, b);
    for(int z = 0; z < _terrain->length() - 1; z++) {
        //Makes OpenGL draw a triangle at every three consecutive vertices
        glBegin(GL_TRIANGLE_STRIP);
        for(int x = 0; x < _terrain->width(); x++) {
            Vec3f normal = _terrain->getNormal(x, z);
            glNormal3f(normal[0], normal[1], normal[2]);
            glTexCoord3f(0.0f, 0.0f,0.0f);
            
            glVertex3f(x, _terrain->getHeight(x, z), z);
            normal = _terrain->getNormal(x, z + 1);
            glNormal3f(normal[0], normal[1], normal[2]);
            glTexCoord3f(100.0f, 5.0f,0.0f);
            glVertex3f(x, _terrain->getHeight(x, z + 1), z + 1);
        }
        glEnd();
    }
    
    
    
    glRotatef(pan, 0.0, 1.0, 0.0);
    glRotatef(tilt, 1.0, 0.0, 0.0);
    
    // GROUND?!
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    // along z - y const
    for (i = -10; i+1 < 11; i++) {
        // along x - y const
        for (j = -10; j+1 < 11; j++) {
            glColor3fv(ground_colors[i+10][j+10]);
            glVertex3f(ground_points[j+10][i+10][0],
                       ground_points[j+10][i+10][1],
                       ground_points[j+10][i+10][2] + zoom);
            glColor3fv(ground_colors[i+10][j+1+10]);
            glVertex3f(ground_points[j+1+10][i+10][0],
                       ground_points[j+1+10][i+10][1],
                       ground_points[j+1+10][i+10][2] + zoom);
            glColor3fv(ground_colors[i+1+10][j+1+10]);
            glVertex3f(ground_points[j+1+10][i+1+10][0],
                       ground_points[j+1+10][i+1+10][1],
                       ground_points[j+1+10][i+1+10][2] + zoom);
            glColor3fv(ground_colors[i+1+10][j+10]);
            glVertex3f(ground_points[j+10][i+1+10][0],
                       ground_points[j+10][i+1+10][1],
                       ground_points[j+10][i+1+10][2] + zoom);
        }
        
    }
    glEnd();
    // Which Particles
    if (fall == RAIN) {
        drawRain();
    }
    else if (fall == SNOW) {
        drawSnow();
    }
    
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    }
    
}



void my_keyboard(unsigned char key, int x, int y)
{
    
    switch (key) {
        
        case 'q': 
            eye[0]=0;eye[1]=0; eye[2]=10;
            look[0]=0;look[1]=0;look[2]=0; 
            up[0]=0.0; up[1]=1.0; up[2]=0.0;
            break;

        case 'a':
            rot_ang += 5;
            break;
        case 'd':
            rot_ang -= 5;
            break;
        case 'w':
            rot_ang2 += 5;
            break;
        case 's':
            rot_ang2 -= 5;
            break;
            
        
        case 'r':
            Roll(eye,look,up,alpha);
            break;
            
        case 'R':
            Roll(eye,look,up,alpha,false);
            break;

        case 'p':
            Pitch(eye,look,up,theta);
            break;
        case 'P':
            Pitch(eye,look,up,theta,false);
            break;

        case 'y':
            Yaw(eye,look,up,beta);
            break;
        case 'Y':
            Yaw(eye,look,up,beta,false);
            break;

        case 'z': //zoom out
            eye[2]++;
            look[2]++;
            break;

            
        case 'Z':  //zoom in
            eye[2]--;
            look[2]--;
            break;

        case 'x':
            Scale(true);
            break;
            
        case 'X':
            Scale(false);
            break;
        
        case 'i':
            moveForward(look,eye);
            break;

        case 'k':
            moveBackward(look,eye);
            break;
            
        case 'b':
        birds = !birds;
        if(birds){
            eye[0] = 0;
            eye[1] = 10;
            eye[2] = 0;
            look[0] = 0;
            look[1] = 0;
            look[2] = 0;
            up[0] = 0;
            up[1] = 0;
            up[2] = -1;
        }
        else{
            eye[0] = 0;
            eye[1] = 0;
            eye[2] = 10;
            look[0] = 0;
            look[1] = 0;
            look[2] = 0;
            up[0] = 0;
            up[1] = 1;
            up[2] = 0;
        }
        break;
          
            
          
        // Summer  
        case '6':
            r = 0.678;
            g = 1.0;
            b = 0.184;
            fog =0;
            // earthQ=0;
            
            
            rSky = 0.118;
            gSky = 0.565;
            bSky =   1.0;
            fall = SUMMER;
            break;

        // Rain 
        case '7':
            r = 0.3;
            g = 0.9;
            b  = 1.0;
            fog =0;
            //earthQ=0;
            
            rSky = 0.663;
            gSky = 0.663;
            bSky = 0.663;
            fall = RAIN;
            drawRain();
            break;

        //Autumn
        case '8':
            r = 1.0;
            g = 0.588;
            b  = 0.0;
            fog =0;
            //earthQ=0;
            
            rSky = 0.690;
            gSky =  0.844;
            bSky =   1.0;
            fall = AUTUMN;
            break;

        // Winter with Snow
        case '9':
            
            glDisable(GL_TEXTURE_2D);
            
            r = 1.0;
            g = 1.0;
            b = 1.0;
            // earthQ=0;
            
            rSky = 0.690;
            gSky = 0.769;
            bSky =  0.871;
            
            fall = SNOW;
            
            drawSnow();
            
            break;

        // Spring 
        case '0':
            r = 1.0;
            g = 1.0;
            b  = 1.0;
            fog =0;
            //earthQ=0;
            
            
            rSky = 0.000;
            gSky = 0.0;
            bSky =  1.0;
            fall = SPRING;
            break;

        // Cycle of season
        case 'c':
            earthQ = 1;
            break;
            
        // Pause   
        case 'v':
            earthQ = 0;
            break;

        case 'l':
            if(lit == 1) { lit2 = 1; lit = 0;}
            else if(lit2 ==1 ) { lit = 0; lit2 = 0;}
            else lit = 1;
            break;
            
        case '1':
            if(amb == 1)    amb = 0;
            else    amb = 1;
            break;
            
        case '2':
            if(diff == 1)    diff = 0;
            else    diff = 1;
            break;
            
        case '3':
            if(spec == 1)    spec = 0;
            else    spec = 1;
            break;

        // Foggy  Winter Snow
        case '4':
            
            
            if(fall==SNOW)
            {
                stopSnow=1;
                fog =1;
            }
            
            
            break;
        // Snow Winter
        case '5':
            
            if(fall==SNOW)
            {
                fog =0;
                stopSnow=0;
            }
            
            break;

        case 'm':
            fan_state = !fan_state;
            break;
        
        case 'f':
            if(housepolygon) {
                housepolygon = 0;
            } else {
                housepolygon = 1;
            }
            break;

        case 'g' :
            inside_house = !inside_house;
            break;
            
        case 27:    // Escape key
            exit(1);
            break;
             
        default:
            break;
    }
}


void update(int value) {
    if(earthQ==1)
    {
        fall += 1;
        if (fall > 4) {
            fall -= 5.0;
        }
    }
    else{
        fall += 0;
        
        
    }
    
    
    glutPostRedisplay();
    glutTimerFunc(2500, update, 0);
    
    
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45, (float) w / (float) h, .1, 200);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void animate()
{
    if (fan_state == true)
    {
        fan_angle += 10;
        if(fan_angle > 360.0)
            fan_angle -= 360.0*floor(fan_angle/360.0);
    }
    
    glutPostRedisplay();
    
}

void idle ( ) {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 400);
    
    glutCreateWindow("1707086_Season_Change");
    
    init();
    
    _terrain = loadTerrain("map5.bmp", 20);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(my_keyboard);
    glutReshapeFunc(handleResize);
    glutTimerFunc(2500, update, 0);
    
    glutReshapeFunc(reshape);
    glutIdleFunc(animate);
    
    glutMainLoop();
    return 0;
}

