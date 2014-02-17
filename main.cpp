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
    return EXIT_SUCCESS;
}