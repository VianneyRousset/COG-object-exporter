#include "Mesh.h"

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
}
