#include <iostream>

#include "Material.h"

using namespace std;

Material::Material(const std::string& mtlPath)
{
	// open file
	ifstream file(mtlPath);
	if (!file.good())
	{
		cout << "Unable to open mtl file " << mtlPath;
		return;
	}
	
	// parsing
	string word;
	while (file >> word)
	{
		if (word == "Ka") {
			file >> this->parameters[Material::Ka+0];
			file >> this->parameters[Material::Ka+1];
			file >> this->parameters[Material::Ka+2];
			file.ignore(std::numeric_limits<std::streamsize>::max(),
				    '\n');
		} else if (word == "Kd") {
			file >> this->parameters[Material::Kd+0];
			file >> this->parameters[Material::Kd+1];
			file >> this->parameters[Material::Kd+2];
			file.ignore(std::numeric_limits<std::streamsize>::max(),
				    '\n');
		} else if (word == "Ks") {
			file >> this->parameters[Material::Ks+0];
			file >> this->parameters[Material::Ks+1];
			file >> this->parameters[Material::Ks+2];
			file.ignore(std::numeric_limits<std::streamsize>::max(),
				    '\n');
		} else if (word == "Ns") {
			file >> this->parameters[Material::Ns];
			file.ignore(std::numeric_limits<std::streamsize>::max(),
				    '\n');
		} else if (word == "d" || word == "Tr") {
			file >> this->parameters[Material::Ns];
			file.ignore(std::numeric_limits<std::streamsize>::max(),
				    '\n');
		}
	}
}

void Material::print() const
{
	printf("\tKa = (%.3f %.3f %.3f)\n" \
	       "\tKd = (%.3f %.3f %.3f)\n" \
	       "\tKs = (%.3f %.3f %.3f)\n" \
	       "\tNs = %.3f\n" \
	       "\t d = %.3f\n",
	       this->parameters[Material::Ka+0],
	       this->parameters[Material::Ka+1],
	       this->parameters[Material::Ka+2],
	       this->parameters[Material::Kd+0],
	       this->parameters[Material::Kd+1],
	       this->parameters[Material::Kd+2],
	       this->parameters[Material::Ks+0],
	       this->parameters[Material::Ks+1],
	       this->parameters[Material::Ks+2],
	       this->parameters[Material::Ns],
	       this->parameters[Material::d]);
}


void Material::write(const std::string& mbfPath) const
{
	// open/create file
	ofstream file;
	file.open(mbfPath, std::ifstream::binary);
	if (!file.good())
	{
		cout << "Unable to create material binary file " << mbfPath
		    << endl;
		return;
	}
	
	// write		
	file.write(reinterpret_cast<const char *>(this->parameters.data()),
		   sizeof(float) * 11);
	file.close();
	
	// end
	cout << "Material binary file writen." << endl;
}
