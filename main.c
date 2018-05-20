#include <stdio.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* choice is to choose which screen to be displayed.
 The car_no gives which car to be shown next. */
int choice=0,car_no=1;

/* This window is created to destroy the window when exited from display. */
GLint window;

/* r,g,b gives the car body color, r1,g1,b1 gives the outer edges of the car sides. */
GLfloat r=0,g=0,b=0.9;
GLfloat r1=0,g1=0,b1=1.0;
GLfloat r2=0.97,g2=0.97,b2=0.97;
GLfloat pr,pg,pb;
GLfloat pr1,pg1,pb1;

/* xangle, yangle and zangle is used for rotational view of the car.
 tx,ty,tz used for translation of the car. */
GLfloat xangle=0,yangle=0,zangle=0,angle=0;
GLfloat tx=0.0,ty=0.0,tz=0.0;

/* the following is used to get text of key entered and car chosen for renting or buying. */
char text;
char chosen_car='b';
int picked_car = 0;

/* The following is used for drawing wheels and ignition system for cars. */
float theta = 0, theta2;
GLUquadricObj *t;

/* The following is used for giving each car names and the title of the project. */
char carName[][50] = {"Alto K10","PickUp Truck","KUV S10"};
char name3[]="PROJECT: CAR RENT";

/* Key function for exiting the screen or go back to previous screen. */
#define ESCAPE 27
#define BACK 127

/* This function uses glutStrokeCharacter to display strings for bigger font sizes. */
void displayStrings(char name[], float tx, float ty, float tz, float sx, float sy, float sz, float r, float g, float b) {
    glPushMatrix();
    glColor3f(r,g,b);
    glTranslatef(tx,ty,tz);
    glScalef(sx,sy,sz);
    for(int i=0;name[i]!='\0';i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,name[i]);
    }
    glPopMatrix();
}

/* This function is used for displaying strings using glutBitmapCharater. */
void display_string(int x, int y, int z,GLfloat red,GLfloat green,GLfloat blue, char *string, int font)
{
    int len,i;
    glColor3f(red,green,blue);
    glRasterPos3f(x,y,z);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        if(font==1)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
        if(font==2)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
        if(font==3)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
        if(font==4)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,string[i]);
    }
    
}

/* To display the first title screen of the mini project. */
void displayTitleScreen() {
    glClearColor(0.0,1.0,1.0,1.0);
    display_string(-500,800,700,1.0,0.20,0.0,"Institute name",1); //correct cordinate according to name
    display_string(-270,700,700,1.0,0.20,0.0,name3,2);
    display_string(-900,470,700,1.0,0.20,0.0,"HELP :-",2);
    display_string(-900,400,700,1.0,0.20,0.0,"MOUSE",2);
    display_string(-880,320,700,1.0,0.20,0.0,"1. PRESS RIGHT BUTTON FOR MENU",3);
    display_string(-900,250,700,1.0,0.20,0.0,"KEYBOARD",2);
    display_string(-880,190,700,1.0,0.20,0.0,"1.) Z-X-V KEYS FOR CORRESPONDING ROTATION",3);
    display_string(-880,120,0,1.0,0.20,0.0,"2.) USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO GO TO NEXT CAR",3);
    display_string(-880,60,0,1.0,0.20,0.0,"3.) ESCAPE TO EXIT",3);
    display_string(-270,-350,0,1.0,0.20,0.0,"PRESS SPACE BAR TO ENTER",2);
    display_string(-900,-450,0,1.0,0.20,0.0,"TEAM MEMBERS :-",2);
    display_string(-850,-520,0,1.0,0.20,0.0,"NAMES",2);
    display_string(-400,-520,0,1.0,0.20,0.0,"USN",2);
    display_string(-850,-580,0,1.0,0.20,0.0,"Name1",3);
    display_string(-850,-630,0,1.0,0.20,0.0,"Name2",3);
    display_string(-400,-580,0,1.0,0.20,0.0,"USN1",4);
    display_string(-400,-630,0,1.0,0.20,0.0,"USN2",4);
    glutPostRedisplay();
    glutSwapBuffers();
}

/* This function is used for showing the color options available for each car. */
void displayColor() {
    display_string(-950,900,0,1.0,0.1,0.1,"press below keys",1);
    display_string(-950,850,0,1.0,0.1,0.1,"to change color of car",1);
    display_string(-950,750,0,1.0,0.1,0.1,"r = ",1);
    glColor3f(1.0,0.0,0);
    glPushMatrix();
    glTranslatef(-850,750,0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(80);
    glPopMatrix();
    
    display_string(-950,650,0,1.0,0.1,0.1,"g = ",1);
    glColor3f(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(-850,650,0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(80);
    glPopMatrix();
    
    display_string(-950,550,0,1.0,0.1,0.1,"b = ",1);
    glColor3f(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(-850,550,0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(80);
    glPopMatrix();
    
    display_string(-950,450,0,1.0,0.1,0.1,"c = ",1);
    glColor3f(0.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(-850,450,0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(80);
    glPopMatrix();
    
    display_string(-950,350,0,1.0,0.1,0.1,"o = ",1);
    glColor3f(1.0,0.63,0);
    glPushMatrix();
    glTranslatef(-850,350,0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(80);
    glPopMatrix();
    
    display_string(-950,250,0,1.0,0.1,0.1,"y = ",1);
    glColor3f(1.0,1.0,0);
    glPushMatrix();
    glTranslatef(-850,250,0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(80);
    glPopMatrix();
    
    display_string(-950,150,0,1.0,0.1,0.1,"h = ",1);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(-850,150,0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(80);
    glPopMatrix();
}

/* The following functions top1, boottom1, left1, right1, back1, front1 is for
 drawing first car(alto K10 type). */
void top1(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Top part of the car before the front window. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(-10,-240,0);
    glScalef(0.23,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(-10,-240,0);
    glScalef(0.23,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
    
    /* top part of the car after the front window. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(418,-30,0);
    glScalef(0.75,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(418,-30,0);
    glScalef(0.75,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
}

void bottom1(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-475,0);
    glScalef(1.3,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(300,-475,0);
    glScalef(1.3,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
}

void front1(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Front window wipers for the car. */
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(110,-155,-150);
    glRotated(-30,0,0,1);
    glRotated(-50,1,0,0);
    glScalef(0.02,1.8,0.04);
    glutSolidCube(120);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(110,-155,120);
    glRotated(-30,0,0,1);
    glRotated(-50,1,0,0);
    glScalef(0.02,1.8,0.04);
    glutSolidCube(120);
    glPopMatrix();
    
    
    /* Front two lights for the car. */
    glColor3f(0.8,0.8,0.0);
    glPushMatrix();
    glTranslatef(-80,-380,-210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glColor3f(0.8,0.8,0.0);
    glPushMatrix();
    glTranslatef(-80,-380,210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    
    /* bottom part of the front body */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(-85,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(-85,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* front part of the body where glass is placed */
    glColor3f(r1,g1,b1);
    glLineWidth(12.0);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-55,0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* The glass which placed on the top part of the front body */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-50,-0);
    glScalef(0.01,0.35,0.81);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-50,-0);
    glScalef(0.01,0.35,0.81);
    glutWireCube(602);
    glPopMatrix();
}

void back1(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    
    /* Back two stop lights for the car. */
    glColor3f(1.0,0.5,0.0);
    glPushMatrix();
    glTranslatef(680,-380,-210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glColor3f(1.0,0.5,0.0);
    glPushMatrix();
    glTranslatef(680,-380,210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    /* The behind lower part of the car1. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(690,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(690,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* Behind upper part of the body of the car.*/
    glColor3f(r1,g1,b1);
    glLineWidth(12.0);
    glPushMatrix();
    glRotated(15,0,0,1);
    glTranslatef(610,-305,0);
    glScalef(0.01,0.33,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* The glass which placed on the back part of the body */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glRotated(15,0,0,1);
    glTranslatef(610,-300,0);
    glScalef(0.01,0.3,0.8);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r2+0.01,g2+0.01,b2+0.01);
    glPushMatrix();
    glRotated(15,0,0,1);
    glTranslatef(610,-300,0);
    glScalef(0.01,0.3,0.8);
    glutWireCube(602);
    glPopMatrix();
}

void left1(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Left mirror. */
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,260);
    glScalef(0.01,0.05,0.2);
    glutWireCube(62);
    glPopMatrix();
    
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(98,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(62);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(100,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutWireCube(62);
    glPopMatrix();
    
    /* Left bottom side of the car.*/
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-350,250);
    glScalef(1.3,0.4,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(300,-350,250);
    glScalef(1.3,0.4,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show door handles. */
    /* First Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(350,-275,255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* Second Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(600,-275,255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(590,-275,255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(590,-275,255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* To show 1st window the left side of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(90.6,-217.5,250.0);
    glVertex3f(190.6,-217.5,250.0);
    glVertex3f(190.6,-35.0,250.0);
    glEnd();
    glPopMatrix();
    
    /* To show 2nd window of the left side of the car. */
    glColor3f(0.95,0.95,0.95);
    glPushMatrix();
    glTranslatef(290,-130,245);
    glScalef(0.32,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(290,-130,245);
    glScalef(0.32,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 3rd window of the side of the car */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(510,-130,245);
    glScalef(0.40,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(510,-130,245);
    glScalef(0.40,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 4th window triangle form of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(630.6,-217.5,250.0);
    glVertex3f(680.6,-217.5,250.0);
    glVertex3f(630.6,-35.0,250.0);
    glEnd();
    glPopMatrix();
    
}

void right1(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Right mirror. */
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,-260);
    glScalef(0.01,0.05,0.2);
    glutWireCube(62);
    glPopMatrix();
    
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(98,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(62);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(100,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutWireCube(62);
    glPopMatrix();
    
    /* right bottom side of the car. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-350,-250);
    glScalef(1.3,0.4,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(300,-350,-250);
    glScalef(1.3,0.4,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show door handles. */
    /* First Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(350,-275,-255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,-255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,-255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* Second Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(600,-275,-255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(590,-275,-255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(590,-275,-255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* To show 1st window the left side of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(90.6,-215.5,-250.0);
    glVertex3f(190.6,-215.5,-250.0);
    glVertex3f(190.6,-35.0,-250.0);
    glEnd();
    glPopMatrix();
    
    /* To show 2nd window of the left side of the car. */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(290,-130,-245);
    glScalef(0.32,0.33,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(290,-130,-245);
    glScalef(0.32,0.33,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 3rd window of the side of the car */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(510,-130,-245);
    glScalef(0.40,0.33,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(510,-130,-245);
    glScalef(0.40,0.33,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 4th window triangle form of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(630.6,-217.5,-250.0);
    glVertex3f(680.6,-217.5,-250.0);
    glVertex3f(630.6,-35.0,-250.0);
    glEnd();
    glPopMatrix();
    
}

void wheel1() {
    t=gluNewQuadric();
    gluQuadricDrawStyle(t,GLU_FILL);
    glColor3f(0.7,0.7,0.7);
    glPushMatrix();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(530,-480,270);
        glVertex3f(530+(35*(cos(((theta2)*3.14)/180))),-480+(35*(sin(((theta2)*3.14)/180))),270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(530,-480,-270);
        glVertex3f(530+(35*(cos(((theta2+angle)*3.14)/180))),-480+(35*(sin(((theta2+angle)*3.14)/180))),-270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(80,-480,270);
        glVertex3f(80+(35*(cos(((theta2)*3.14)/180))),-480+(35*(sin(((theta2)*3.14)/180))),270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(80,-480,-270);
        glVertex3f(80+(35*(cos(((theta2)*3.14)/180))),-480+(35*(sin(((theta2)*3.14)/180))),-270);
    }
    glEnd();
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(530,-485,-255);
    glutSolidTorus(20,45,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(530,-485,255);
    glutSolidTorus(20,45,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(80,-485,-255);
    glutSolidTorus(20,45,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(80,-485,255);
    glutSolidTorus(20,45,10,25);
    glPopMatrix();
}

void ignition1() {
    glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(460,-475,-200);
    glRotatef(90.0,0,1,0);
    gluCylinder(t,10,20,250,150,150);
    glPopMatrix();
}

/* The following 6 faces of second car is drawn which is a pick up truck type. */
void top2(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1){
    /* Top part of the car before the front window. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(-10,-240,0);
    glScalef(0.23,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(-10,-240,0);
    glScalef(0.23,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
    
    /* top part of the car after the front window. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(290,-30,0);
    glScalef(0.3,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(290,-30,0);
    glScalef(0.3,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
    
    /* Top part of the car after the back window. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(530,-340,0);
    glScalef(0.5,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(530,-340,0);
    glScalef(0.5,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
}

void bottom2(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-475,0);
    glScalef(1.3,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(300,-475,0);
    glScalef(1.3,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
}

void front2(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Front window wipers for the car. */
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(110,-155,-150);
    glRotated(-30,0,0,1);
    glRotated(-50,1,0,0);
    glScalef(0.02,1.8,0.04);
    glutSolidCube(120);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(110,-155,120);
    glRotated(-30,0,0,1);
    glRotated(-50,1,0,0);
    glScalef(0.02,1.8,0.04);
    glutSolidCube(120);
    glPopMatrix();
    
    
    /* Front two lights for the car. */
    glColor3f(0.8,0.8,0.0);
    glPushMatrix();
    glTranslatef(-80,-380,-210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glColor3f(0.8,0.8,0.0);
    glPushMatrix();
    glTranslatef(-80,-380,210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    
    /* bottom part of the front body */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(-85,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(-85,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* front part of the body where glass is placed */
    glColor3f(r1,g1,b1);
    glLineWidth(12.0);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-55,0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* The glass which placed on the top part of the front body */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-50,-0);
    glScalef(0.01,0.35,0.81);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-50,-0);
    glScalef(0.01,0.35,0.81);
    glutWireCube(602);
    glPopMatrix();
}

void back2(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    
    /* Back two stop lights for the car. */
    glColor3f(1.0,0.5,0.0);
    glPushMatrix();
    glTranslatef(680,-380,-210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glColor3f(1.0,0.5,0.0);
    glPushMatrix();
    glTranslatef(680,-380,210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    /* The behind lower part of the car1. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(690,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(690,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* Behind upper part of the body of the car.*/
    glColor3f(r1,g1,b1);
    glLineWidth(12.0);
    glPushMatrix();
    glTranslatef(380,-205,0);
    glScalef(0.01,0.53,0.82);
    glutWireCube(602);
    glPopMatrix();

    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(380,-205,0);
    glScalef(0.01,0.53,0.8);
    glutSolidCube(600);
    glPopMatrix();
}

void left2(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Left mirror. */
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,260);
    glScalef(0.01,0.05,0.2);
    glutWireCube(62);
    glPopMatrix();
    
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(98,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(62);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(100,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutWireCube(62);
    glPopMatrix();
    
    /* Left bottom side of the car.*/
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-350,250);
    glScalef(1.3,0.4,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(300,-350,250);
    glScalef(1.3,0.4,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show door handles. */
    /* First Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(350,-275,255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* To show 1st window the left side of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(90.6,-217.5,250.0);
    glVertex3f(190.6,-217.5,250.0);
    glVertex3f(190.6,-35.0,250.0);
    glEnd();
    glPopMatrix();
    
    /* To show 2nd window of the left side of the car. */
    glColor3f(0.95,0.95,0.95);
    glPushMatrix();
    glTranslatef(290,-130,245);
    glScalef(0.32,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(290,-130,245);
    glScalef(0.32,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
}

void right2(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    
    /* Right mirror. */
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,-260);
    glScalef(0.01,0.05,0.2);
    glutWireCube(62);
    glPopMatrix();
    
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(98,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(62);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(100,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutWireCube(62);
    glPopMatrix();
    
    /* right bottom side of the car. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-350,-250);
    glScalef(1.3,0.4,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(300,-350,-250);
    glScalef(1.3,0.4,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show door handles. */
    /* First Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(350,-275,-255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,-255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,-255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* To show 1st window the left side of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(90.6,-215.5,-250.0);
    glVertex3f(190.6,-215.5,-250.0);
    glVertex3f(190.6,-35.0,-250.0);
    glEnd();
    glPopMatrix();
    
    /* To show 2nd window of the left side of the car. */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(290,-130,-245);
    glScalef(0.32,0.33,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(290,-130,-245);
    glScalef(0.32,0.33,0.01);
    glutWireCube(602);
    glPopMatrix();
}

void wheel2() {
    t=gluNewQuadric();
    gluQuadricDrawStyle(t,GLU_FILL);
    glColor3f(0.7,0.7,0.7);
    glPushMatrix();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(530,-480,270);
        glVertex3f(530+(45*(cos(((theta2)*3.14)/180))),-480+(45*(sin(((theta2)*3.14)/180))),270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(530,-480,-270);
        glVertex3f(530+(45*(cos(((theta2+angle)*3.14)/180))),-480+(45*(sin(((theta2+angle)*3.14)/180))),-270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(80,-480,270);
        glVertex3f(80+(45*(cos(((theta2)*3.14)/180))),-480+(45*(sin(((theta2)*3.14)/180))),270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(80,-480,-270);
        glVertex3f(80+(45*(cos(((theta2)*3.14)/180))),-480+(45*(sin(((theta2)*3.14)/180))),-270);
    }
    glEnd();
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(530,-485,-255);
    glutSolidTorus(25,50,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(530,-485,255);
    glutSolidTorus(25,50,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(80,-485,-255);
    glutSolidTorus(25,50,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(80,-485,255);
    glutSolidTorus(25,50,10,25);
    glPopMatrix();
}

void ignition2() {
    glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(460,-475,-200);
    glRotatef(90.0,0,1,0);
    gluCylinder(t,15,22.5,265,350,500);
    glPopMatrix();
}


/* The following functions top3, bottom3, left3, right3, back3, front3 is for
 drawing third car(SUV type). */
void top3(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1){
    /* Top part of the car before the front window. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(-10,-240,0);
    glScalef(0.23,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(-10,-240,0);
    glScalef(0.23,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
    
    /* top part of the car after the front window. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(440,-30,0);
    glScalef(0.83,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(440,-30,0);
    glScalef(0.83,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
}

void bottom3(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-475,0);
    glScalef(1.3,0.01,0.83);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(300,-475,0);
    glScalef(1.3,0.01,0.83);
    glutWireCube(602);
    glPopMatrix();
}

void front3(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Front window wipers for the car. */
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(110,-155,-150);
    glRotated(-30,0,0,1);
    glRotated(-50,1,0,0);
    glScalef(0.02,1.8,0.04);
    glutSolidCube(120);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(110,-155,120);
    glRotated(-30,0,0,1);
    glRotated(-50,1,0,0);
    glScalef(0.02,1.8,0.04);
    glutSolidCube(120);
    glPopMatrix();
    
    
    /* Front two lights for the car. */
    glColor3f(0.8,0.8,0.0);
    glPushMatrix();
    glTranslatef(-80,-380,-210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glColor3f(0.8,0.8,0.0);
    glPushMatrix();
    glTranslatef(-80,-380,210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    
    /* bottom part of the front body */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(-85,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(-85,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* front part of the body where glass is placed */
    glColor3f(r1,g1,b1);
    glLineWidth(12.0);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-55,0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* The glass which placed on the top part of the front body */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-50,-0);
    glScalef(0.01,0.35,0.81);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glRotated(-30,0,0,1);
    glTranslatef(180,-50,-0);
    glScalef(0.01,0.35,0.81);
    glutWireCube(602);
    glPopMatrix();
}

void back3(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    
    /* Back two stop lights for the car. */
    glColor3f(1.0,0.5,0.0);
    glPushMatrix();
    glTranslatef(680,-380,-210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glColor3f(1.0,0.5,0.0);
    glPushMatrix();
    glTranslatef(680,-380,210);
    glScalef(0.8,1.4,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    /* The behind lower part of the car1. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(690,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(690,-350,-0);
    glScalef(0.01,0.4,0.82);
    glutWireCube(602);
    glPopMatrix();
    
    /* Door Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(700,-275,150);
    glScalef(0.01,0.9,1.0);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(710,-275,150);
    glScalef(0.3,0.3,0.8);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(710,-275,150);
    glScalef(0.3,0.3,0.8);
    glutSolidCube(40);
    glPopMatrix();
    
    /* The left side glass which placed on the back part of the body */
    glLineWidth(8.0);
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(690,-130,120);
    glScalef(0.01,0.33,0.42);
    glutWireCube(602);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(690,-130,120);
    glScalef(0.01,0.3,0.37);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r2+0.01,g2+0.01,b2+0.01);
    glPushMatrix();
    glTranslatef(690,-130,120);
    glScalef(0.01,0.3,0.37);
    glutWireCube(602);
    glPopMatrix();
    
    /* The right side glass which placed on the back part of the body */
    glLineWidth(8.0);
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(690,-130,-125);
    glScalef(0.01,0.33,0.42);
    glutWireCube(602);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(690,-130,-125);
    glScalef(0.01,0.3,0.37);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r2+0.01,g2+0.01,b2+0.01);
    glPushMatrix();
    glTranslatef(690,-130,-125);
    glScalef(0.01,0.3,0.37);
    glutWireCube(602);
    glPopMatrix();
}

void left3(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Left mirror. */
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,260);
    glScalef(0.01,0.05,0.2);
    glutWireCube(62);
    glPopMatrix();
    
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(98,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(62);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(100,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,280);
    glRotated(25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutWireCube(62);
    glPopMatrix();
    
    /* Left bottom side of the car.*/
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-350,250);
    glScalef(1.3,0.4,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(300,-350,250);
    glScalef(1.3,0.4,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show door handles. */
    /* First Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(350,-275,255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* Second Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(540,-275,255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(530,-275,255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(530,-275,255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* To show 1st window the left side of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(90.6,-217.5,250.0);
    glVertex3f(190.6,-217.5,250.0);
    glVertex3f(190.6,-35.0,250.0);
    glEnd();
    glPopMatrix();
    
    /* To show 2nd window of the left side of the car. */
    glColor3f(0.95,0.95,0.95);
    glPushMatrix();
    glTranslatef(290,-130,245);
    glScalef(0.32,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(290,-130,245);
    glScalef(0.32,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 3rd window of the side of the car */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(480,-130,245);
    glScalef(0.32,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(480,-130,245);
    glScalef(0.32,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 4th window triangle form of the car. */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(635,-130,245);
    glScalef(0.18,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(635,-130,245);
    glScalef(0.18,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
    
}

void right3(GLfloat r,GLfloat g,GLfloat b,GLfloat r1,GLfloat g1,GLfloat b1) {
    /* Right mirror. */
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,-260);
    glScalef(0.01,0.05,0.2);
    glutWireCube(62);
    glPopMatrix();
    
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(98,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(62);
    glPopMatrix();
    
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(100,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutSolidCube(60);
    glPopMatrix();
    
    glLineWidth(2.0);
    glColor3f(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(100,-210,-280);
    glRotated(-25, 0, 1, 0);
    glScalef(0.01,0.7,0.7);
    glutWireCube(62);
    glPopMatrix();
    
    /* right bottom side of the car. */
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(300,-350,-250);
    glScalef(1.3,0.4,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glColor3f(r1,g1,b1);
    glPushMatrix();
    glTranslatef(300,-350,-250);
    glScalef(1.3,0.4,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show door handles. */
    /* First Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(350,-275,-255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,-255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(335,-275,-255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* Second Handle. */
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(600,-275,-255);
    glScalef(1.0,0.9,0.01);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(590,-275,-255);
    glScalef(0.3,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    glLineWidth(2.0);
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(590,-275,-255);
    glScalef(0.8,0.3,0.3);
    glutSolidCube(40);
    glPopMatrix();
    
    /* To show 1st window the left side of the car. */
    glPushMatrix();
    glLineWidth(12.0);
    glColor3f(r2,g2,b2);
    glBegin(GL_TRIANGLES);
    glVertex3f(90.6,-215.5,-250.0);
    glVertex3f(190.6,-215.5,-250.0);
    glVertex3f(190.6,-35.0,-250.0);
    glEnd();
    glPopMatrix();
    
    /* To show 2nd window of the left side of the car. */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(290,-130,-245);
    glScalef(0.32,0.33,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(290,-130,-245);
    glScalef(0.32,0.33,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 3rd window of the side of the car */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(480,-130,-245);
    glScalef(0.32,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(480,-130,-245);
    glScalef(0.32,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
    
    /* To show the 4th window triangle form of the car. */
    glColor3f(r2,g2,b2);
    glPushMatrix();
    glTranslatef(635,-130,-245);
    glScalef(0.18,0.32,0.01);
    glutSolidCube(600);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(r1,g1,b1);
    glTranslatef(635,-130,-245);
    glScalef(0.18,0.32,0.01);
    glutWireCube(602);
    glPopMatrix();
    
}

void wheel3() {
    t=gluNewQuadric();
    gluQuadricDrawStyle(t,GLU_FILL);
    glColor3f(0.7,0.7,0.7);
    glPushMatrix();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(530,-480,270);
        glVertex3f(530+(45*(cos(((theta2)*3.14)/180))),-480+(45*(sin(((theta2)*3.14)/180))),270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(530,-480,-270);
        glVertex3f(530+(45*(cos(((theta2+angle)*3.14)/180))),-480+(45*(sin(((theta2+angle)*3.14)/180))),-270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(80,-480,270);
        glVertex3f(80+(45*(cos(((theta2)*3.14)/180))),-480+(45*(sin(((theta2)*3.14)/180))),270);
    }
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for(theta2=0;theta2<360;theta2=theta2+20)
    {
        glVertex3f(80,-480,-270);
        glVertex3f(80+(45*(cos(((theta2)*3.14)/180))),-480+(45*(sin(((theta2)*3.14)/180))),-270);
    }
    glEnd();
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(530,-485,-255);
    glutSolidTorus(25,55,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(530,-485,255);
    glutSolidTorus(25,55,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(80,-485,-255);
    glutSolidTorus(25,55,10,25);
    glPopMatrix();
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(80,-485,255);
    glutSolidTorus(25,55,10,25);
    glPopMatrix();
}

void ignition3() {
    glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(440,-475,-200);
    glRotatef(90.0,0,1,0);
    gluCylinder(t,10,20,280,150,150);
    glPopMatrix();
}

/* This function is used for displaying the end of list of cars screen. */
void displayEndOfScreen() {
    glClearColor(0,0,0,0);
    char end[]= "End of list of cars!";
    char end2[] = "Press (<-) key to show the cars";
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-700,600,0);
    glScalef(0.5,0.6,0.01);
    for(int i=0;end[i]!='\0';i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,end[i]);
    }
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-700,300,0);
    glScalef(0.5,0.6,0.01);
    for(int i=0;end2[i]!='\0';i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,end2[i]);
    }
    glPopMatrix();
}

/* This display function is used to display the car models available in showroom currently. */
void display_car() {
    if(car_no==1) {
        glClearColor(0.94,0.94,0.94,1.0);
        glPushMatrix();
        glRotatef(xangle,1,0,0);
        glRotatef(yangle,0,1,0);
        glRotatef(zangle,0,0,1);
        top1(r,g,b,r1,g1,b1);
        right1(r,g,b,r1,g1,b1);
        left1(r,g,b,r1,g1,b1);
        bottom1(r,g,b,r1,g1,b1);
        front1(r,g,b,r1,g1,b1);
        back1(r,g,b,r1,g1,b1);
        wheel1();
        ignition1();
        glPopMatrix();
    }else if(car_no==2) {
        glClearColor(0.94,0.94,0.94,1.0);
        glPushMatrix();
        glRotatef(xangle,1,0,0);
        glRotatef(yangle,0,1,0);
        glRotatef(zangle,0,0,1);
        glScalef(1.1, 1.05, 1.0);
        top2(r,g,b,r1,g1,b1);
        right2(r,g,b,r1,g1,b1);
        left2(r,g,b,r1,g1,b1);
        bottom2(r,g,b,r1,g1,b1);
        front2(r,g,b,r1,g1,b1);
        back2(r,g,b,r1,g1,b1);
        wheel2();
        ignition2();
        glPopMatrix();
    }else if(car_no==3) {
        glClearColor(0.94,0.94,0.94,1.0);
        glPushMatrix();
        glRotatef(xangle,1,0,0);
        glRotatef(yangle,0,1,0);
        glRotatef(zangle,0,0,1);
        glScalef(1.3, 1.45, 1.1);
        top3(r,g,b,r1,g1,b1);
        right3(r,g,b,r1,g1,b1);
        left3(r,g,b,r1,g1,b1);
        bottom3(r,g,b,r1,g1,b1);
        front3(r,g,b,r1,g1,b1);
        back3(r,g,b,r1,g1,b1);
        wheel3();
        ignition3();
        glPopMatrix();
    }
    
}

/* This function tells which car is picked by the customer and views them in a new screen. */
void display_picked_car() {
    if(picked_car == 1) {
        glClearColor(0.8,0.8,1.0,1.0);
        glPushMatrix();
        glRotatef(xangle,1,0,0);
        glRotatef(yangle,0,1,0);
        glRotatef(zangle,0,0,1);
        top1(pr,pg,pb,pr1,pg1,pb1);
        right1(pr,pg,pb,pr1,pg1,pb1);
        left1(pr,pg,pb,pr1,pg1,pb1);
        bottom1(pr,pg,pb,pr1,pg1,pb1);
        front1(pr,pg,pb,pr1,pg1,pb1);
        back1(pr,pg,pb,pr1,pg1,pb1);
        wheel1();
        ignition1();
        glPopMatrix();
    }else if(picked_car == 2) {
        glClearColor(0.8,0.8,1.0,1.0);
        glPushMatrix();
        glRotatef(xangle,1,0,0);
        glRotatef(yangle,0,1,0);
        glRotatef(zangle,0,0,1);
        glScalef(1.1, 1.05, 1.0);
        top2(pr,pg,pb,pr1,pg1,pb1);
        right2(pr,pg,pb,pr1,pg1,pb1);
        left2(pr,pg,pb,pr1,pg1,pb1);
        bottom2(pr,pg,pb,pr1,pg1,pb1);
        front2(pr,pg,pb,pr1,pg1,pb1);
        back2(pr,pg,pb,pr1,pg1,pb1);
        wheel2();
        ignition2();
        glPopMatrix();
    }else if(picked_car == 3) {
        glClearColor(0.8,0.8,1.0,1.0);
        glPushMatrix();
        glRotatef(xangle,1,0,0);
        glRotatef(yangle,0,1,0);
        glRotatef(zangle,0,0,1);
        glScalef(1.3, 1.45, 1.1);
        top3(pr,pg,pb,pr1,pg1,pb1);
        right3(pr,pg,pb,pr1,pg1,pb1);
        left3(pr,pg,pb,pr1,pg1,pb1);
        bottom3(pr,pg,pb,pr1,pg1,pb1);
        front3(pr,pg,pb,pr1,pg1,pb1);
        back3(pr,pg,pb,pr1,pg1,pb1);
        wheel3();
        ignition3();
        glPopMatrix();
    }
}

/* This function helps in guiding the customer about the keyboard functionalities added for the cars. */
void displayRotateFunctions() {
    display_string(-540, 890,0,1.0,0,0,"1.Right click the mouse button for more options",1);
    display_string(-540, 830,0,1.0,0,0, "2.Press z,x for rotating along x,y axis respectively",1);
    display_string(250, 890,0,1.0,0,0, "3.Press left(<-) or right(->) to view next car",1);
    display_string(250, 830,0,1.0,0,0, "4.Press a or d to move the car front or back",1);
}

void displayRates(void);

/* This function is used for dusplaying the car names when shown in a screen. */
void display_car_name() {
    if(car_no == 1 || picked_car == 1){
        displayStrings(carName[0],-100,-850,400,0.6,0.3,0.01,0,0,0);
    } else if(car_no == 2 || picked_car == 2){
        displayStrings(carName[1],-100,-850,400,0.6,0.3,0.01,0,0,0);
    } else if(car_no == 3 || picked_car == 3){
        displayStrings(carName[2],-100,-850,400,0.6,0.3,0.01,0,0,0);
    }
}

/* This function guides which key to press for buying the car chosen. */
void displayBuyButton() {
    display_string(-900,-600,700,1.0,0.0,0.0,"please press m ",1);
    display_string(-900,-670,700,1.0,0.0,0.0,"for buying/renting!",1);
}

/* This is the main display function based on the choices from customer different screens are displayed. */
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(choice==0) {
        displayTitleScreen();
        glutPostRedisplay();
    } else if(choice==1) {
        glLoadIdentity();
        glPushMatrix();
        glRotated(15,0,1,0);
        glRotated(15,1,0,0);
        glTranslatef(tx, ty, tz);
        display_car_name();
        display_car();
        glPopMatrix();
        displayRates();
        displayBuyButton();
        displayColor();
        displayRotateFunctions();
        glutPostRedisplay();
        glutSwapBuffers();
    } else if( choice == 2) {
        glLoadIdentity();
        displayEndOfScreen();
        glutPostRedisplay();
        glutSwapBuffers();
    } else if( choice == 3) {
        glLoadIdentity();
        glPushMatrix();
        glRotated(15,0,1,0);
        glRotated(15,1,0,0);
        display_car_name();
        display_picked_car();
        glPopMatrix();
        displayRates();
        displayStrings("press n for confirmation on buying this car!",-900,600,200,0.6,0.5,0.01,1.0,0.0,0.0);
        displayStrings("press back button to view cars!",-900,800,200,0.6,0.5,0.01,1.0,0.0,0.0);
        glutPostRedisplay();
        glutSwapBuffers();
    } else if( choice == 4) {
        glLoadIdentity();
        glPushMatrix();
        glRotated(15,0,1,0);
        glRotated(15,1,0,0);
        display_car_name();
        display_picked_car();
        glPopMatrix();
        displayStrings("Thank you for buying a car from us!!",-900,800,200,0.6,0.5,0.01,1.0,0.0,0.0);
        displayStrings("Please come back next time to our showroom!!",-900,700,200,0.6,0.5,0.01,1.0,0.0,0.0);
        glutPostRedisplay();
        glutSwapBuffers();
    }
}

/* This function helps in adding input functionalities from keyboard. */
void NormalKey(GLubyte key, GLint x, GLint y)
{
    text = key;
    int count = 0;
    switch ( key )    {
        case ESCAPE :
             glutDestroyWindow(window);    // Kill our window
             exit(0);
             break;
        case ' ':
            printf("%d\n",choice);
            choice=1;
            printf("%d\n",choice);
            break;
            case BACK :
            if( choice != 4){
            choice=1;
            picked_car = 0;
            }
             break;
        case 'r' :
            if(!picked_car) {
            r=0.99;b=0;g=0;
            r1=1.0;g1=0;b1=0;
            }
            chosen_car = 'r';
            break;
        case 'g' :
            if(!picked_car) {
            r=0;b=0;g=0.99;
            r1=0;b1=0;g1=1.0;
            }
            chosen_car = 'g';
            break;
        case 'b' :
            if(!picked_car) {
            r=0,g=0,b=0.9;
            r1=0;b1=1.0;g1=0;
            }
            chosen_car = 'b';
            break;
        case 'h' :
            if(!picked_car) {
            r=0.1;b=0.1;g=0.1;
            r1=0.15;b1=0.15;g1=0.15;
            }
            chosen_car = 'h';
            break;
        case 'y' :
            if(!picked_car) {
            r=0.99;g=0.99;b=0;
            r1=01.0;g1=1.0;b1=0;
            }
            chosen_car = 'y';
            break;
        case 'c' :
            if(!picked_car) {
            r=0;g=0.9;b=0.9;
            r1=0;g1=1.0;b1=1.0;
            }
            chosen_car = 'c';
            break;
        case 'o' :
            if(!picked_car) {
            r=0.99;g=0.66;b=0.0;
            r1=1.0;g1=0.69;b1=0.0;
            }
            chosen_car = 'o';
            break;
        case 'a' : tx-=50.0;
            break;
        case 'd' : tx+=50.0;
            break;
        case 'z' : xangle+=15.0;
            tx = 0;
            break;
        case 'Z' : xangle-=15.0;
            tx = 0;
            break;
        case 'x' : yangle+=15.0;
            tx = 0;
            break;
        case 'X' : yangle-=15.0;
            tx = 0;
            break;
        case 'v' : zangle+=15.0;
            tx = 0;
            break;
        case 'V' : zangle-=15.0;
            tx = 0;
            break;
        case 'm' :
            if(choice != 0 && choice != 4) {
            choice = 3;
            picked_car = car_no;
            pr = r; pg = g; pb = b;
            pr1 = r1; pg1 = g1; pb1 = b1;
            }
            break;
        case 'n' : choice = 4;
            break;
        default:
            break;
    }
    
}

/* This function displays the rate based on the car and the color chosen by the customer. */
void displayRates() {
    int k = 0;
    if(chosen_car=='r' && (picked_car == 1|| car_no == 1)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 4.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹450/hr", 1);
    }
    if(chosen_car=='r' && (picked_car == 2 || car_no == 2)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 3.1 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹310/hr", 1);
    }
    if(chosen_car=='r' && (picked_car == 3|| car_no == 3)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 10.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹1050/hr", 1);
    }
    if(chosen_car=='g' && (picked_car == 1|| car_no == 1)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 4.1 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹410/hr", 1);
    }
    if(chosen_car=='g' &&(picked_car == 2 || car_no == 2)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 8.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹850/hr", 1);
    }
    if(chosen_car=='g' && (picked_car == 3|| car_no == 3)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 11.0 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹1100/hr", 1);
    }
    if(chosen_car=='b' && (picked_car == 1|| car_no == 1)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 2.6 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹260/hr", 1);
    }
    if(chosen_car=='b' && (picked_car == 2 || car_no == 2)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 4.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹450/hr", 1);
    }
    if(chosen_car=='b' && (picked_car == 3|| car_no == 3)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 10.0 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹1000/hr", 1);
    }
    if(chosen_car=='y' && (picked_car == 1|| car_no == 1)) {
        display_string(-900, -830,k,r-0.1,g-0.6,b,"Buy At: 4.5 lakhs", 1);
        display_string(-900, -900,k,r-0.1,g-0.6,b,"OR Rent Rate: ₹450/hr", 1);
    }
    if(chosen_car=='y' &&(picked_car == 2 || car_no == 2)) {
        display_string(-900, -830,k,r-0.6,g-0.6,b,"Buy At: 2.5 lakhs", 1);
        display_string(-900, -900,k,r-0.6,g-0.6,b,"OR Rent Rate: ₹250/hr", 1);
    }
    if(chosen_car=='y' && (picked_car == 3|| car_no == 3)) {
        display_string(-900, -830,k,r-0.6,g-0.6,b,"Buy At: 11.5 lakhs", 1);
        display_string(-900, -900,k,r-0.6,g-0.6,b,"OR Rent Rate: ₹1150/hr", 1);
    }
    if(chosen_car=='c' && (picked_car == 1|| car_no == 1)) {
        display_string(-900, -830,k,0,0.8,1.0,"Buy At: 4.3 lakhs", 1);
        display_string(-900, -900,k,0,0.8,1.0,"OR Rent Rate: ₹430/hr", 1);
    }
    if(chosen_car=='c' && (picked_car == 2 || car_no == 2)) {
        display_string(-900, -830,k,0,0.8,1.0,"Buy At: 4.4 lakhs", 1);
        display_string(-900, -900,k,0,0.8,1.0,"OR Rent Rate: ₹440/hr", 1);
    }
    if(chosen_car=='c' && (picked_car == 3|| car_no == 3)) {
        display_string(-900, -830,k,0,0.8,1.0,"Buy At: 12.0 lakhs", 1);
        display_string(-900, -900,k,0,0.8,1.0,"OR Rent Rate: ₹1200/hr", 1);
    }
    if(chosen_car=='h' && (picked_car == 1|| car_no == 1)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 4.9 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹490/hr", 1);
    }
    if(chosen_car=='h' && (picked_car == 2 || car_no == 2)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 7.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹750/hr", 1);
    }
    if(chosen_car=='h' && (picked_car == 3|| car_no == 3)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 12.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹1250/hr", 1);
    }
    if(chosen_car=='o' && (picked_car == 1|| car_no == 1)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 1.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹150/hr", 1);
    }
    if(chosen_car=='o' && (picked_car == 2 || car_no == 2)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 4.9 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹490/hr", 1);
    }
    if(chosen_car=='o' && (picked_car == 3|| car_no == 3)) {
        display_string(-900, -830,k,r,g,b,"Buy At: 9.5 lakhs", 1);
        display_string(-900, -900,k,r,g,b,"OR Rent Rate: ₹950/hr", 1);
    }
}

/* These are the special key functions input from the keyboard. */
static void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key ) {
        case GLUT_KEY_RIGHT:
            if(car_no < 4 && picked_car == 0 && choice != 0) {
                xangle=yangle=zangle=0;
                r=g=0;b=0.9;
                r1=g1=0;b1=1.0;
                tx=0.0;
                car_no++;
            }
            if( car_no == 4 && choice != 0) {
                choice = 2;
            }
            break;
            
        case GLUT_KEY_LEFT:
            if(car_no == 4 && picked_car == 0 && choice != 0) {
                choice = 1;
            }
            if(car_no>1 && picked_car == 0 && choice != 0) {
                xangle=yangle=zangle=0;
                r=g=0;b=0.9;
                r1=g1=0;b1=1.0;
                tx=0.0;
                car_no--;
            }
            break;
    }
}

/* This function gives the mouse function added to this project. */
void myMenu(int id)
{
    if (id==1)
    {
        choice=0;
    }
    if(id ==2)
    {
        glutDestroyWindow(window);    /* Kill our window */
        exit(0);
    }
}

/* This function helps in initiallizing the screen setup. */
void init() {
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0,1000.0,-1000.0,1000.0,-1000.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
}

/* This is the main function of the program to create window and display modes.
 The display function, keyboard function and init function are called here. */
int main(int argc,char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(2560,1600);
    glutCreateWindow("CAR BUY OR RENT");
    init();
    glutKeyboardFunc(NormalKey);
    glutSpecialFunc(SpecialKeyFunc);
    glutFullScreen();
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutCreateMenu(myMenu);
    glutAddMenuEntry("Title Screen", 1);
    glutAddMenuEntry("EXIT", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
