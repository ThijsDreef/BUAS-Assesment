#include "System/Graphics/Geometry/geometry.h"

Geometry::Geometry()
{
  name = "error";
}

Geometry::Geometry(const std::string& fileName, const std::string& name, MaterialLib& materialLib)
{
	std::string extension = fileName.substr(fileName.size() - 4, fileName.size());
	if (extension == ".obj")
  	parseObj(fileName, materialLib);
	else if (extension == ".dae")
		parseDae(fileName, materialLib);
	this->name = name;
}

void Geometry::setIndiceOffset(int offset)
{
  this->offset = offset;
  for (unsigned int i = 0; i < allIndices.size(); i++)
    for (unsigned int j = 0; j < allIndices[i].size(); j++)
      offsetIndices[i][j] = allIndices[i][j] + offset;
}

void Geometry::parseDaeGeometry(rapidxml::xml_node<> * geometryNode)
{
	// for all geomtries in library_geometries
	for (rapidxml::xml_node<>* mesh = geometryNode->first_node("mesh"); mesh; mesh = mesh->next_sibling("mesh"))
	{
		std::string verticesAlias;
		// for all meshes in geomtries
		for (rapidxml::xml_node<>* source = mesh->first_node("source"); source; source = source->next_sibling("source"))
		{
			// for all sources in mesh
			std::string temp = source->name();
			std::string id = source->first_attribute()->value();
			std::string tokens = source->first_node()->value();
			char* token = strtok(&tokens[0], " ");
			while (token != 0) 
			{
				float_arrays[id].push_back((float)atof(token));
				token = std::strtok(0, " ");
			}
		}
		for (rapidxml::xml_node<>* vertices = mesh->first_node("vertices"); vertices; vertices = vertices->next_sibling("vertices"))
		{
			verticesAlias = vertices->first_node()->first_attribute("source")->value();
		}
		for (rapidxml::xml_node<>* triangles = mesh->first_node("polylist"); triangles; triangles = triangles->next_sibling("polylist"))
		{
			std::string vSource;
			std::string nSource;
			std::string uvSource;

			unsigned int vOffset = 0;
			unsigned int nOffset = 0;
			unsigned int uvOffset = 0;
			// read all input tags
			for (rapidxml::xml_node<>* input = triangles->first_node("input"); input; input = input->next_sibling("input")) 
			{
				std::string semantic = input->first_attribute("semantic")->value();
				// set the offset for this polyList
				if (semantic == "VERTEX") {
					vSource = input->first_attribute("source")->value();
					vOffset = atoi(input->first_attribute("offset")->value());
				} else if (semantic == "NORMAL") {
					nSource = input->first_attribute("source")->value();
					nOffset = atoi(input->first_attribute("offset")->value());
				} else if (semantic == "TEXCOORD") {
					uvSource = input->first_attribute("source")->value();
					uvOffset = atoi(input->first_attribute("offset")->value());
				}
			}

			vSource = (verticesAlias.size() != 0) ? verticesAlias.substr(1, verticesAlias.length()) : vSource.substr(1, vSource.length());
			nSource = nSource.substr(1, nSource.length());
			uvSource = uvSource.substr(1, uvSource.length());

			//build polyList now
			//push back the material for the polylist
			materials.push_back(triangles->first_attribute("material")->value());
			std::map<std::string, int> uniqueIndices;
			allIndices.push_back(std::vector<unsigned int>());
			offsetIndices.push_back(std::vector<unsigned int>());
			// always expect a polylist in triangles so vcount = 3 everywhere
			std::string indices = triangles->first_node("p")->value();
			char* token  = strtok(&indices[0], " ");

			Vec3<float> currentVertex;
			Vec3<float> currentNormal;
			Vec2<float> currentUv;
			Vec3<int> boneIdices;
			Vec3<float> boneWeights;

			std::string unique;

			unsigned int count = 0;
			//how hacky can my parsers get D:
			unsigned int largestOffset = (vOffset > nOffset) ? ((vOffset > uvOffset) ? vOffset : uvOffset) : (nOffset > uvOffset) ? nOffset : uvOffset;

			while (token != 0) 
			{
				int indiceToken = atoi(token);
				if (count == vOffset) {
						std::vector<float> array = float_arrays[vSource];
						currentVertex = Vec3<float>(array[indiceToken * 3], array[indiceToken * 3 + 1], array[indiceToken * 3 + 2]);
						unique += token;
						unique += "/";
				} 
				if (count == nOffset) {
						std::vector<float> array = float_arrays[nSource];
						currentNormal = Vec3<float>(array[indiceToken * 3], array[indiceToken * 3 + 1], array[indiceToken * 3 + 2]);
						unique += token;
						unique += "/";
				}
				if (count == uvOffset) {
						std::vector<float> array = float_arrays[uvSource];
						currentUv = Vec2<float>(array[indiceToken * 2], array[indiceToken * 2 + 1]);
						unique += token;
						unique += "/";
				}
				if (count == largestOffset + 1) {
						auto it = uniqueIndices.find(unique);
						if (it == uniqueIndices.end()) {
							storedVertices.push_back(VertexFormat(currentVertex, currentNormal, currentUv));
							uniqueIndices[unique] = storedVertices.size() - 1;
						}
						int indicePos = uniqueIndices[unique];
						allIndices[allIndices.size() - 1].push_back(indicePos);
						offsetIndices[offsetIndices.size() - 1].push_back(indicePos);
						unique.clear();
				}
				//make unique string for all indices
				count++;
				count %= (largestOffset + 2);
				if (count != largestOffset + 1)
					token = strtok(0, " ");
			}
		}
	}
}

void Geometry::parseDaeMaterials(rapidxml::xml_node<> * materialNode) 
{

}

void Geometry::parseDaeImages(rapidxml::xml_node<> * imageNode)
{

}

void Geometry::parseDae(const std::string& fileName, MaterialLib& matLib)
{
	std::vector<char> text;
	UtilLoader::loadFile(text, fileName);
	text.push_back('\0');
	rapidxml::xml_document<> doc;
	doc.parse<0>(&text[0]);


	rapidxml::xml_node<> *rootNode = doc.first_node("COLLADA");
	// rapidxml::xml_node<> *library_images = rootNode->first_node("library_images");
	// rapidxml::xml_node<> *library_effects = rootNode->first_node("library_effects");
	// rapidxml::xml_node<> *library_materials = rootNode->first_node("library_materials");
	rapidxml::xml_node<> *library_geometry = rootNode->first_node("library_geometries");
	// rapidxml::xml_node<> *library_geometry = rootNode->first_node("library_controllers");


	for (rapidxml::xml_node<>* geometry = library_geometry->first_node("geometry"); geometry; geometry = geometry->next_sibling("geometry"))
	{	
		parseDaeGeometry(geometry);
	}
	std::cout << this->storedVertices.size() << "\n";
}

void Geometry::parseObj(const std::string& name, MaterialLib& matlib)
{
  std::map<std::string, int> unique;
  int currentMaterialGroup = -1;
	Material currentMaterial;
	std::vector<VertexFormat> finalVertices;
	std::vector<Vec3<float>> vertices;
	std::vector<Vec2<float>> texture;
	std::vector<Vec3<float>> normals;
	std::ifstream objFile(name);

	std::string line;
	if (objFile.is_open())
	{
		while (std::getline(objFile, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				Vec3<float> vertex;
				sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
				vertices.push_back(vertex);
			}
			else if (line.substr(0, 2) == "vn")
			{
				Vec3<float> vertex;
				sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
				normals.push_back(vertex);
			}
			else if (line.substr(0, 2) == "vt")
			{
				Vec2<float> vertex;
				sscanf(line.c_str(), "%*s %f %f", &vertex[0], &vertex[1]);
				//flip y coord for textures
				vertex[1] = 1 - vertex[1];
				texture.push_back(vertex);
			}
			else if (line.substr(0, 7) == "usemtl ")
			{
        materials.push_back(line.substr(7, line.size()));
        allIndices.push_back(std::vector<unsigned int>());
        offsetIndices.push_back(std::vector<unsigned int>());

				currentMaterialGroup ++;
			}
			else if (line.substr(0, 2) == "f ")
			{
        // make face using indices if indices match reuse the indice
				int vertexIndice[3];
				int uvIndice[3];
				int normalIndice[3];
        std::string indices[3];
				sscanf(line.c_str(), "%*s %i/%i/%i %i/%i/%i %i/%i/%i",
                                     &vertexIndice[0], &uvIndice[0], &normalIndice[0],
																	   &vertexIndice[1], &uvIndice[1], &normalIndice[1],
																	   &vertexIndice[2], &uvIndice[2], &normalIndice[2]);
        for (int i = 0; i < 3; i++)
        {
          indices[i] += std::to_string(vertexIndice[i]) + "/" + std::to_string(uvIndice[i]) + "/" + std::to_string(normalIndice[i]);
          auto it = unique.find(indices[i]);
          if (it == unique.end())
          {
            int indicePos = unique.size();
            unique[indices[i]] = indicePos;
            storedVertices.push_back(VertexFormat(vertices[vertexIndice[i] - 1], normals[normalIndice[i] - 1], texture[uvIndice[i] - 1]));
            allIndices[currentMaterialGroup].push_back(indicePos);
            offsetIndices[currentMaterialGroup].push_back(indicePos);
          }
          else
          {
            allIndices[currentMaterialGroup].push_back(unique[indices[i]]);
            offsetIndices[currentMaterialGroup].push_back(unique[indices[i]]);
          }
        }
			}
			else if (line.substr(0, 7) == "mtllib ")
			{
				std::ifstream mtlFile(name.substr(0, name.rfind("/") + 1) + line.substr(7, line.size()));
				std::string mtlLine;
				std::string currentMaterialName;
				while (std::getline(mtlFile, mtlLine))
				{
					if (mtlLine.substr(0, 7) == "map_Kd ")
					{
						//add texture here
						std::string textureName = name.substr(0, name.rfind("/") + 1) + mtlLine.substr(7, mtlLine.size());
						size_t pos = textureName.find("\\");
						while (pos < textureName.size()) {
							textureName.replace(pos, 1, "/");
							pos = textureName.find("\\", pos);
						}
						Texture * texture = new Texture(textureName);
						texture->makeResident();
						matlib.addTexture(textureName, texture);
						currentMaterial.color = Vec4<float>(0.2, 0.2, 0.2, 1);
						currentMaterial.texture = texture->getResidentHandle();
						std::cout << textureName << " id" << currentMaterial.texture << "\n";
						
					}
          // wil work as long as material only supports color
					if (mtlLine.substr(0, 3) == "Kd ")
					{
						Vec4<float> matColor;
						matColor[3] = 1;
						sscanf(mtlLine.c_str(), "%*s %f %f %f", &matColor[0], &matColor[1], &matColor[2]);
						currentMaterial.color = matColor;
					}
					else if (mtlLine.substr(0, 7) == "newmtl ")
					{
						if (currentMaterialName.size() > 0)
							matlib.addMaterial(currentMaterialName, currentMaterial);
						currentMaterialName = mtlLine.substr(7, mtlLine.size());
						currentMaterial = Material();
					}
				}
				mtlFile.close();
				if (currentMaterialName.size() > 0) matlib.addMaterial(currentMaterialName, currentMaterial);
			}
		}
	}
  objFile.close();
}

const std::vector<unsigned int>& Geometry::getIndice(int group)
{
  return offsetIndices[group];
}


const std::vector<std::string>&Geometry::getMaterials()
{
  return materials;
}

Geometry::~Geometry()
{

}
