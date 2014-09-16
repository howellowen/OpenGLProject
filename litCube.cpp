////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



#define REFRESH_RATE 0.0167f  //60th of a sec


/// Initialise OpenGL stuff ///
void init()
{

	
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,800.0/600.0,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);


	glEnable(GL_LIGHTING);	//we enable lighting, to make the 3D object to 3D
	glEnable(GL_LIGHT0);
	float diffuse[]={1.0f,1.0f,1.0f,1.0f};	//light color is white
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	float ambient[]={0.2f,0.2f,0.2f,1.0f};	//light color is white
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);

}

/// Define an OpenGL cube ///
int cube(float angle)
{
	int id;	//the id for the list
	id=glGenLists(1);	//generate a unique OpenGL list
	glNewList(id,GL_COMPILE);	//and create it

		glBegin(GL_QUADS);
			//Front
			glNormal3f(0.0,0.0,1.0);glVertex3f(0.5,0.5,0.5);
			glNormal3f(0.0,0.0,1.0);glVertex3f(-0.5,0.5,0.5);
			glNormal3f(0.0,0.0,1.0);glVertex3f(-0.5,-0.5,0.5);
			glNormal3f(0.0,0.0,1.0);glVertex3f(0.5,-0.5,0.5);

			//Left
			glNormal3f(-1.0,0.0,0.0);glVertex3f(-0.5,0.5,-0.5);
			glNormal3f(-1.0,0.0,0.0);glVertex3f(-0.5,0.5,-0.5);
			glNormal3f(-1.0,0.0,0.0);glVertex3f(-0.5,-0.5,-0.5);
			glNormal3f(-1.0,0.0,0.0);glVertex3f(-0.5,-0.5,-0.5);

			//Back
			glNormal3f(0.0,0.0,-1.0);glVertex3f(0.5,0.5,-0.5);
			glNormal3f(0.0,0.0,-1.0);glVertex3f(-0.5,0.5,-0.5);
			glNormal3f(0.0,0.0,-1.0);glVertex3f(-0.5,-0.5,-0.5);
			glNormal3f(0.0,0.0,-1.0);glVertex3f(0.5,-0.5,-0.5);

			//Right
			glNormal3f(1.0,0.0,0.0);glVertex3f(0.5,0.5,-0.5);
			glNormal3f(1.0,0.0,0.0);glVertex3f(0.5,0.5,0.5);
			glNormal3f(1.0,0.0,0.0);glVertex3f(0.5,-0.5,0.5);
			glNormal3f(1.0,0.0,0.0);glVertex3f(0.5,-0.5,-0.5);

			//Top
			glNormal3f(0.0,1.0,0.0);glVertex3f(0.5,0.5,0.5);
			glNormal3f(0.0,1.0,0.0);glVertex3f(-0.5,0.5,0.5);
			glNormal3f(0.0,1.0,0.0);glVertex3f(-0.5,0.5,-0.5);
			glNormal3f(0.0,1.0,0.0);glVertex3f(0.5,0.5,-0.5);

			//Bottom
			glNormal3f(0.0,-1.0,0.0);glVertex3f(0.5,-0.5,0.5);
			glNormal3f(0.0,-1.0,0.0);glVertex3f(-0.5,-0.5,0.5);
			glNormal3f(0.0,-1.0,0.0);glVertex3f(-0.5,-0.5,-0.5);
			glNormal3f(0.0,-1.0,0.0);glVertex3f(0.5,-0.5,-0.5);

		glEnd();

	glEndList();

	return id;
}



/// Display the Object ///
void display(float angle)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

			float pos[]={-2.0,4.0,4.0,1.0};	//set the position
	glLightfv(GL_LIGHT0,GL_POSITION,pos);

	glTranslatef(0.0,0.0,-5.0);
	glRotatef(angle,1.0,1.0,1.0);

	int id;

	id=cube(angle);

	glCallList(id);

}



////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Create the main window
    
	sf::WindowSettings Settings;
	Settings.DepthBits         = 24; // Request a 24 bits depth buffer
	Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 2;  // Request 2 levels of antialiasing
sf::Window App(sf::VideoMode(800, 600, 32), "Cube Model Viewer", 
sf::Style::Close, Settings);

	// Create a clock for measuring time elapsed
    	sf::Clock Clock;
	
// declare a struct to get the system time 
	SYSTEMTIME st;

	float angle=0.0;
	
	init();
	  
			
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
            		if ((Event.Type == sf::Event::KeyPressed) 
&& (Event.Key.Code == sf::Key::Escape))
                		App.Close();

            		// Resize event : adjust viewport
            		if (Event.Type == sf::Event::Resized)
                		glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        	}

        	// Set the active window before using OpenGL commands
        	App.SetActive();

		float elapsedTime=Clock.GetElapsedTime();
		
if(elapsedTime>REFRESH_RATE){
			// get current system time
			GetSystemTime(&st);
		
			Clock.Reset();

			// Increment the angle and re-display object
			angle+=0.5;

			if (angle>360)
				angle-=360;
			display(angle);
		}
       
        	// Finally, display rendered frame on screen
        	App.Display();
}

    	return EXIT_SUCCESS;
}
