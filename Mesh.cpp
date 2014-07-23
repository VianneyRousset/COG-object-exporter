#include "Mesh.h"

#include <map>
#include <array>

using namespace std;

Mesh::Mesh()
{}

Mesh::Mesh(string&& path)
{
	loadObjFile(path);
}

bool Mesh::loadObjFile(string path)
{
	ifstream file(path);

	if (!file)
	{
		cout << "Unable to open " + path << endl;
		return FAILURE;
	}
	
	std::string word = "#";
	float coordinate;
	int face;
	char c;

	do {

		file >> word;
		
		if (word == "o")
		{
			getline(file, this->name, '\n');
		} else if (word == "v") {
			for (unsigned char i=0; i<3; i++) {
				file >> coordinate;
				this->vertices.push_back(coordinate);
			}
		} else if (word == "vt") {
			for (unsigned char i=0; i<2; i++) {
				file >> coordinate;
				this->uvVertices.push_back(coordinate);
			}
		} else if (word == "vn") {
			for (unsigned char i=0; i<3; i++) {
				file >> coordinate;
				this->normals.push_back(coordinate);
			}
		} else if (word == "s") {
			cout << "WARNING: smooth shading ignored." << endl;
		} else if (word == "mtlib") {
			cout << "WARNING: material file ignored." << endl;
		} else if (word == "usemtl") {
			cout << "WARNING: usemtl ignored." << endl;
		} else if (word == "f") {
			for (unsigned char i=0; i<3; i++) {
				file >> face;
				file >> c;
				this->faces.push_back(face);
				
				file >> face;
				file >> c;
				this->faces.push_back(face);
				
				file >> face;
				this->faces.push_back(face);
			}
		}
	} while(file);


	if (this->vertices.size() == 0)
		cout << "WARNING: No vertices found." << endl;
	if (this->uvVertices.size() == 0)
		cout << "WARNING: No uvVertices found." << endl;
	if (this->normals.size() == 0)
		cout << "WARNING: No normals found." << endl;

	return SUCCESS;
}

void Mesh::printName()
{
	cout << "== " << this->name << " ==" << endl;
}

void Mesh::printVertices()
{
	cout << "- Vertices -" << endl;
	for(unsigned int i=0; i < this->vertices.size(); i+=3)
		cout << "\t" << i / 3 << ". ("
		<< this->vertices[i]   << ';'
		<< this->vertices[i+1] << ';'
		<< this->vertices[i+2] << ')' << endl;
}

void Mesh::printUvVertices()
{
	cout << "- UV vertices -" << endl;
	for(unsigned int i=0; i < this->uvVertices.size(); i+=2)
		cout << "\t" << i / 2 << ". ("
		<< this->uvVertices[i]   << ';'
		<< this->uvVertices[i+1] << ')' << endl;
}

void Mesh::printNormal()
{
	cout << "- Normals -" << endl;
	for(unsigned int i=0; i < this->normals.size(); i+=3)
		cout << "\t" << i / 3 << ". ("
		<< this->normals[i]   << ';'
		<< this->normals[i+1] << ';'
		<< this->normals[i+2] << ')' << endl;
}

void Mesh::printFaces()
{
	cout << "- Faces -" << endl;
	for(unsigned int i=0; i < this->faces.size(); i+=9)
		cout << "\t" << i / 9 
		<< ". ["
		<< this->faces[i]   << '-'
		<< this->faces[i+1] << '-'
		<< this->faces[i+2] << "] "
		<< "\t["
		<< this->faces[i+3]   << '-'
		<< this->faces[i+4] << '-'
		<< this->faces[i+5] << "] "
		<< "\t["
		<< this->faces[i+6]   << '-'
		<< this->faces[i+7] << '-'
		<< this->faces[i+8] << "] " << endl;
}

void Mesh::index()
{
	// verticle,vertice texture, normal => index
	std::map<std::array<float,8>,size_t> map;
	std::vector<unsigned int> indexedFaces;

	for(auto i = this->faces.begin(); i != this->faces.end(); i+=3) {

#ifdef __APPLE__
		std::array<float,8> point =
#else
		std::array<float,8> point {
#endif
			{this->vertices[(*(i + 0) - 1) * 3 + 0],
			 this->vertices[(*(i + 0) - 1) * 3 + 1],
			 this->vertices[(*(i + 0) - 1) * 3 + 2],
			 this->uvVertices[(*(i + 1) - 1) * 2 + 0],
			 this->uvVertices[(*(i + 1) - 1) * 2 + 1],
			 this->normals[(*(i + 2) - 1) * 3 + 0],
			 this->normals[(*(i + 2) - 1) * 3 + 1],
			 this->normals[(*(i + 2) - 1) * 3 + 2]}
#ifdef __APPLE__
			;
#else
			};
#endif
		if(!map.count(point))
			map[point] = map.size();

		indexedFaces.push_back(map[point]);
	}

	this->vertices.clear();
	this->uvVertices.clear();
	this->normals.clear();
	this->vertices.resize(map.size() * 3);
	this->uvVertices.resize(map.size() * 2);
	this->normals.resize(map.size() * 3);

	for(auto i = map.begin(); i != map.end(); i++) {
		vertices[i->second * 3 + 0] = i->first[0];
		vertices[i->second * 3 + 1] = i->first[1];
		vertices[i->second * 3 + 2] = i->first[2];
		uvVertices[i->second * 2 + 0] = i->first[3];
		uvVertices[i->second * 2 + 1] = i->first[4];
		normals[i->second * 3 + 0] = i->first[5];
		normals[i->second * 3 + 1] = i->first[6];
		normals[i->second * 3 + 2] = i->first[7];
	}

	this->faces.clear();
	this->faces = indexedFaces;
}

template<typename T>
void Mesh::writeBlock(std::ofstream& file, std::vector<T>& vector)
{
	unsigned int size = vector.size();
		
	file.write(reinterpret_cast<char*>(&size), sizeof(unsigned int));

	file.write(reinterpret_cast<char*>(vector.data()),
			sizeof(T) * vector.size());
}

void Mesh::serialize(string&& path)
{
	std::ofstream file;
	file.open(path);

	writeBlock(file, this->vertices);
	writeBlock(file, this->uvVertices);
	writeBlock(file, this->normals);
	writeBlock(file, this->faces);

	file.close();
}
