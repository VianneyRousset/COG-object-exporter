#pragma once

#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <array>

#define SUCCESS true
#define FAILURE false

using namespace std;

class Mesh
{
private:
	
	string name;

	vector<float> vertices;
	vector<float> uvVertices;
	vector<float> normals;
	vector<unsigned int>   faces;

	float* fvertices, fuvVertices, ffaces, fnormals;

	template<typename T>
	static void writeBlock(std::ofstream& file, std::vector<T>& vector);
public:

	Mesh();
	Mesh(string&& path);

	bool loadObjFile(string path);
	
	void printName();
	void printVertices();
	void printUvVertices();
	void printNormal();
	void printFaces();

	void serialize(string&& path);
};
