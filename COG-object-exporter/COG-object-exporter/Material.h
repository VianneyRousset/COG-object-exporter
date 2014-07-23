#pragma once

#include <array>
#include <fstream>

class Material {
enum
{
	Ka = 0,
	Kd = 3,
	Ks = 6,
	Ns = 9,
	d  = 10, 
};

private:
	// material parameters
	// Ka[3] (ambient color), Kd[3] (diffuse color), Ks[3] specular color,
	// Ns (specular coeficient), d (transparency)
	std::array<float, 11> parameters;
	
	/*
	// textures
	std::shared_ptr<Texture> map_Ka,   // ambient color texture
							 map_Kd,   // diffuse color texture
							 map_Ks,   // specular color texture
							 map_Ns,   // specular intensity texture
							 map_d,	   // transparency texture
							 map_bump; // normal map texture
	*/


public:
	/**
	 * Constructor, load the given .mtl file
	 * \param mtlPath path to the .mtl file
	 */
        Material(const std::string& mtlPath);
	
	/**
	 * print the informations of the material
	 */
        void print() const;
	
	/**
	 * Write the material in a material binary file
	 * \param mbfPath path to the material binary file
	 */
	 void write(const std::string& mbfPath) const;
};
