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
	vector<int>   faces;

	float* fvertices, fuvVertices, ffaces, fnormals;

public:

	Mesh();
	Mesh(string&& path);

	bool loadObjFile(string path);
	
	void printName();
	void printVertices();
	void printUvVertices();
	void printNormal();
	void printFaces();
};