#ifndef RAYTRACER_WAVEFRONTPARSER_H
#define RAYTRACER_WAVEFRONTPARSER_H

#include <fstream>
#include <sstream>
#include "Mesh.h"
#include "point2.h"

class WavefrontParser {
public:
    static void importWavefrontMesh(const std::string filename, const std::shared_ptr<Mesh> mesh) {
        std::ifstream objfile (filename);
        std::cout << filename;
        if (objfile.is_open()) {
            parseFile(objfile, mesh);
            objfile.close();
        }
        else std::cerr << "Unable to open OBJ File " << filename;
    }
private:
    static void parseFile(std::ifstream& file, const std::shared_ptr<Mesh> mesh){
        std::vector<point3> vertices{};
        std::vector<point2> texels{};
        std::vector<vec3> normals{};
        std::vector<shared_ptr<Face>> faces;

        for (std::string line; std::getline(file,line);)
        {
            std::vector<std::string> parts = splitIntoParts(line, ' ');

            if(parts.at(0) == "v") {
                point3 vertex = point3(parts.at(1), parts.at(2), parts.at(3));
                vertices.push_back(vertex);
            }else if(parts.at(0) == "vt") {
                point2 texel = point2(parts.at(1), parts.at(2));
                texels.push_back(texel);
            }else if(parts.at(0) == "vn") {
                vec3 normal = vec3(parts.at(1), parts.at(2), parts.at(3));
                normals.push_back(normal);
            }else if(parts.at(0) == "f") {
                int v1 = std::stoi(splitIntoParts(parts.at(1), '/').at(0));
                int v2 = std::stoi(splitIntoParts(parts.at(2), '/').at(0));
                int v3 = std::stoi(splitIntoParts(parts.at(3), '/').at(0));

                int vt1 = std::stoi(splitIntoParts(parts.at(1), '/').at(1));
                int vt2 = std::stoi(splitIntoParts(parts.at(2), '/').at(1));
                int vt3 = std::stoi(splitIntoParts(parts.at(3), '/').at(1));

                int vn1 = std::stoi(splitIntoParts(parts.at(1), '/').at(2));
                int vn2 = std::stoi(splitIntoParts(parts.at(2), '/').at(2));
                int vn3 = std::stoi(splitIntoParts(parts.at(3), '/').at(2));

                auto face = std::make_shared<Face>(
                        vertices.at(v1-1),
                        vertices.at(v2-1),
                        vertices.at(v3-1),
                        texels.at(vt1-1),
                        texels.at(vt2-1),
                        texels.at(vt3-1),
                        normals.at(vn1-1),
                        normals.at(vn2-1),
                        normals.at(vn3-1)
                        );
                faces.push_back(face);
            }
        }

        mesh->setFaces(faces);
    }

    static std::vector<std::string> splitIntoParts(std::string line, char dlm) {
        std::stringstream linestram(line);
        std::vector<std::string> parts;
        std::string segment;

        while(std::getline(linestram, segment, dlm))
        {
            parts.push_back(segment);
        }

        return parts;
    }
};

#endif //RAYTRACER_WAVEFRONTPARSER_H
