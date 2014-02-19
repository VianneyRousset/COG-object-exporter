#include <iostream>

#include "Mesh.h"
#include <array>

int main (int argc, const char * argv[])
{
	Mesh mesh = Mesh("ressources/cube.obj");
	mesh.printName();
	mesh.printVertices();
	mesh.printUvVertices();
	mesh.printNormal();
	mesh.printFaces();
	mesh.index();
	mesh.serialize("ressources/cube.mesh");
    return EXIT_SUCCESS;
}
