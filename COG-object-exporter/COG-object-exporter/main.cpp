#include <iostream>
#include <array>

#include "Mesh.h"
#include "Material.h"

int main (int argc, const char * argv[])
{
	// create mesh file
	Mesh mesh = Mesh("/Users/Vianney/Xcode/COG-object-exporter/test.obj");
	mesh.printName();
	mesh.printVertices();
	mesh.printUvVertices();
	mesh.printNormal();
	mesh.printFaces();
	mesh.index();
	mesh.serialize("ressources/test.mesh");
	
	// create mbf
	Material material("/Users/Vianney/Xcode/COG-object-exporter/test.mtl");
	material.print();
	material.write("ressources/test.mbf");
	return EXIT_SUCCESS;
}
