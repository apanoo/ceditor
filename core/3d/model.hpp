#pragma once

#include <sstream>
#include <vector>
#include "vertex.hpp"
#include "file.hpp"
#include "util.h"

// index struct helper
struct VertexIndex {
    int pIndex;
    int tIndex;
    int nIndex;
};

class OBJModel {
public:
    OBJModel(const char *filepath) : _filepath(std::string(filepath)) {
        // load file
        if (!load(filepath)) {
            SDL_Log("Load obj model fail [%s]", filepath);
        }
        SDL_Log("Load obj model success [%s]", filepath);
    }

    virtual ~OBJModel() {}

private:
    bool load(const char *filepath) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texcoords;
        std::vector<glm::vec3> normals;
        std::vector<VertexIndex> indices;

        unsigned char* strptr = FileUtils::read_raw(filepath);
        std::string str = std::string((const char*)strptr);
        if (str.empty()) {
            SDL_Log("Read model file [%s] returl null string", filepath);
            return false;
        }
        
        std::stringstream stream(str.c_str());
        char szLine[256];
        while (!stream.eof()) {
            memset(szLine, 0, 256);
            stream.getline(szLine, 256);
            if (strlen(szLine) > 0) {
                if (szLine[0] == 'v') {
                    if (szLine[1] == 't') { // texcoord
                        float s, t;
                        if (sscanf(szLine, "%*s %f %f", &s, &t) == 0) {
                            continue;
                        }
                        texcoords.push_back(glm::vec2(s, t));
                    }
                    else if (szLine[1] == 'n') { // normal
                        float x, y, z;
                        if (sscanf(szLine, "%*s %f %f %f", &x, &y, &z) == 0) {
                            continue;
                        }
                        normals.push_back(glm::vec3(x, y, z));
                    } else { // position
                        float x, y, z;
                        if (sscanf(szLine, "%*s %f %f %f", &x, &y, &z) == 0) {
                            continue;
                        }
                        positions.push_back(glm::vec3(x, y, z));
                    }
                } else if (szLine[0] == 'f') {
                    VertexIndex vi[3];
                    std::string strLine(szLine);
                    if (auto sl = strLine.find_first_of('/')) {
                        if (strLine[sl+1] == '/') {
                            // no texcoord index
                            // f index/texcoord/normal
                            if (sscanf(szLine, "%*s %d//%d %d//%d %d//%d",
                                &vi[0].pIndex, &vi[0].nIndex,
                                &vi[1].pIndex, &vi[1].nIndex,
                                &vi[2].pIndex, &vi[2].nIndex) == 0 ) {
                                // continue if err
                                continue;
                            }
                            // default index
                            vi[0].tIndex = 1;
                            vi[1].tIndex = 1;
                            vi[2].tIndex = 1;
                            texcoords.push_back(glm::vec2(0, 0));
                        } else {
                            // f index/texcoord/normal
                            if (sscanf(szLine, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
                                &vi[0].pIndex, &vi[0].tIndex, &vi[0].nIndex,
                                &vi[1].pIndex, &vi[1].tIndex, &vi[1].nIndex,
                                &vi[2].pIndex, &vi[2].tIndex, &vi[2].nIndex) == 0 ) {
                                // continue if err
                                continue;
                            } 
                        }
                    }

                    for (size_t i = 0; i < 3; i++) {
                        // index start at 0
                        // index should be 0 when no texcoord data
                        vi[i].pIndex --;
                        vi[i].tIndex --;
                        vi[i].nIndex --;

                        auto cul = _vertices.size();
                        unsigned int cuidx = -1;
                        for (size_t j=0; j < cul; ++j) {
                            if (_vertices[j].position == positions[vi[i].pIndex] &&
                                _vertices[j].texcoord == texcoords[vi[i].tIndex] &&
                                _vertices[j].normal == normals[vi[i].nIndex]) {
                                // find same point
                                cuidx = j;
                            }
                        }
                        if (cuidx == -1) {
                            cuidx = _vertices.size();
                            // push vertex data
                            _vertices.push_back(Vertex(
                                positions[vi[i].pIndex],
                                texcoords[vi[i].tIndex],
                                normals[vi[i].nIndex]
                            ));
                        }
                        // push index
                        _indices.push_back(cuidx);
                    }
                }
            }
        }

        // free
        FileUtils::free_raw(strptr);

        return true;
    }

  public:
    std::string _filepath;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
};
