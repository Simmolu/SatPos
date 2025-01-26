#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>	
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Requests.h"
#include "Manager.h"


//what this teaches me is EITHER i need to have shaders for every primary color (likely) or have dynamic shaders that can be modified on the fly
//TODO: create "Renderer" class which contains all code neccesary to draw text to screen (just to start)

int main() {


	Requests squire;
	string zip;
	cout << "Please enter your zip code: \n";
	cin >> zip;


	Manager mrKrabs(zip);

	mrKrabs.geoInfo(squire.GeoAboveMe(mrKrabs.latitude, mrKrabs.longitude));
	mrKrabs.tleInfo(squire.SatTLE("25544"));

	
	return 0;
}





/*So if I wanted to compartmentialize all of this rendering and get my own triangle, line, circle shapes etc I'd just need a function that takes in the size and shape you want, and then have dedicated functions for translating entities.*/