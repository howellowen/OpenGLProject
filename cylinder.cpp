///////////////////////////////////////////////////////////
//  cylinder.cpp
//  Main program to draw a cylinder in OpenGL
//  Created on:      07-Nov-2012
//  Original author: histan00
///////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>

#define SC_WIDTH 800
#define SC_HEIGHT 800
#define REFRESH_RATE 0.03f
using namespace std;

void drawCylinder(float radius, int numberSides, float height)
{
	// assume the cylinder is formed around the y-axis
	// this function draws in immediate mode, and generates the vertices on every refresh 
	float angle = 360.f/(float)numberSides;
	float x=0.f, y=0.f, z = 0.f;
	float theta = 0.f;
	const float PI = 3.14159f;
	bool redFace = true;
	//draw top end
	x = 0.f, y = height/2, z = 0.f;
	glBegin(GL_TRIANGLE_FAN);
		//set centre of the fan
		glVertex3f(x, y, z);
		//red face
		glColor3f(1.0,0.0,0.0);
		for (int n= 0; n< numberSides + 1; n++)
		{ 
			
			x = radius* cos((theta/180.f)*PI);
			z = radius* sin((theta/180.f)*PI);
			glVertex3f(x, y, z);
			theta += angle;
		}
		
	glEnd();

	//draw sides end
	y = height/2;
	glBegin(GL_QUAD_STRIP);

		glColor3f(1.0,1.0,1.0);

		for (int n= 0; n< numberSides + 1; n++)
		{
			
			x = radius* cos((theta/180.f)*PI);
			z = radius* sin((theta/180.f)*PI);
			glVertex3f(x, y, z);
			glVertex3f(x,-y, z);
			theta += angle;
		}
		
	glEnd();

	//draw bottom end
	x = 0.f, y = -height/2, z = 0.f;
	glBegin(GL_TRIANGLE_FAN);
		// red face
		glColor3f(1.0,0.0,0.0);
		// set centre of the fan
		glVertex3f(x, y, z);
		for (int n= 0; n< numberSides + 1; n++)
		{ 
			
			x = radius* cos((theta/180.f)*PI);
			z = radius* sin((theta/180.f)*PI);
			glVertex3f(x, y, z);
			theta += angle;
		}
		
	glEnd();

}

void drawBox(){
	 glBegin(GL_QUADS);
			//red
			glColor3f(1.0,0.0,0.0);
			//back face
            glVertex3f(-10.f, 10.f, -10.f);
            glVertex3f(-10.f, -10.f, -10.f);
            glVertex3f( 10.f,  -10.f, -10.f);
            glVertex3f( 10.f, 10.f, -10.f);

			//yellow
			glColor3f(1.0,1.0,0.0);
			//front face
            glVertex3f(-10.f, 10.f, 10.f);
            glVertex3f(-10.f, -10.f, 10.f);
            glVertex3f( 10.f,  -10.f, 10.f);
            glVertex3f( 10.f, 10.f, 10.f);

			//cyan
			glColor3f(0.0,1.0,1.0);
			//left end
			glVertex3f(-10.f, 10.f, -10.f);
            glVertex3f(-10.f, -10.f, -10.f);
			glVertex3f(-10.f, -10.f, 10.f);
			glVertex3f(-10.f, 10.f, 10.f);

			//blue
			glColor3f(0.0,0.0,1.0);
			//right end
			glVertex3f( 10.f,  10.f, -10.f);
            glVertex3f( 10.f, -10.f, -10.f);
			glVertex3f( 10.f,  -10.f, 10.f);
			glVertex3f( 10.f,  10.f, 10.f);

			//white 
			glColor3f(1.0,1.0,1.0);
			//top
			 glVertex3f(-10.f, 10.f, -10.f);
			 glVertex3f( 10.f, 10.f, -10.f);
			 glVertex3f( 10.f, 10.f, 10.f);
			 glVertex3f(-10.f, 10.f, 10.f);

			 //green 
			glColor3f(0.0,1.0,0.0);
			//bottom
			 glVertex3f(-10.f, -10.f, -10.f);
			 glVertex3f( 10.f, -10.f, -10.f);
			 glVertex3f( 10.f, -10.f, 10.f);
			 glVertex3f(-10.f, -10.f, 10.f);
        glEnd();
}

int main()
{
    // Create the main window
	 sf::Window App(sf::VideoMode(SC_WIDTH, SC_HEIGHT, 32), "SFML OpenGL");
	 

    // Create a clock for measuring time elapsed
    sf::Clock Clock;
	// Create a clock to tell the time from
	sf::Clock Timer;
	double seconds = 0.0;
	const float rotateIncrement = 0.5f;
	float xRotate = 30.f, yRotate = 10.f, zRotate = 20.f;
	//output version of OpenGL to the console
	 cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<endl;


    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();

            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                App.Close();

            // Resize event : adjust viewport
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        }

        // Set the active window before using OpenGL commands
        // It's useless here because active window is always the same,
        // but don't forget it if you use multiple windows or controls
        App.SetActive();

    
		if((float)Clock.GetElapsedTime()>REFRESH_RATE){
			// Clear colour and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Apply some transformations
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			xRotate += rotateIncrement;
			yRotate += rotateIncrement;
			zRotate += rotateIncrement;

			glTranslatef(0.f, 0.f, -50.f);
			glRotatef(xRotate,1.0,0.0,0.0);
			glRotatef(yRotate,0.0,1.0,0.0);
			glRotatef(zRotate,0.0,0.0,1.0);

			//drawBox();
			drawCylinder(10.f,10,5.f);
			Clock.Reset();
		}

       
        // Finally, display rendered frame on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}
