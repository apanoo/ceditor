#pragma once

#include <sstream>
#include <vector>
#include "vertex.hpp"
#include "file.hpp"
#include "util.h"

class OBJModel
{
  public:
    OBJModel(const char *filename) : _filename(std::string(filename))
    {
        // load file
        load(filename);
    }

    virtual ~OBJModel()
    {
        delete _vertexs;
        delete _indexs;
    }

  private:
    void load(const char *filename)
    {
        // vertex data
        struct VertexInfo
        {
            float v[3];
        };
        struct VertexDefine
        {
            int positionIndex;
            int texcoordIndex;
            int normalIndex;
        };

        std::vector<VertexInfo> positions;
        std::vector<VertexInfo> texcoords;
        std::vector<VertexInfo> normals;

        std::vector<unsigned int> indexes;
        std::vector<VertexDefine> vertexs;

        const char *fc = FileUtils::read(filename).c_str();
        if (fc != nullptr)
        {
            std::stringstream stream(fc);
            char szLine[256];
            while (!stream.eof())
            {
                memset(szLine, 0, 256);
                stream.getline(szLine, 256);
                if (strlen(szLine) > 0)
                {
                    if (szLine[0] == 'v')
                    {
                        if (szLine[1] == 't')
                        {
                            // texcoord
                            VertexInfo vi;
                            int result = sscanf(szLine, "%*s %f %f", &vi.v[0], &vi.v[1]);
                            if (result == 0)
                                continue;
                            texcoords.push_back(vi);
                        }
                        else if (szLine[1] == 'n')
                        {
                            // normal
                            VertexInfo vi;
                            int result = sscanf(szLine, "%*s %f %f %f", &vi.v[0], &vi.v[1], &vi.v[2]);
                            if (result == 0)
                                continue;
                            normals.push_back(vi);
                        }
                        else
                        {
                            // position
                            VertexInfo vi;
                            int result = sscanf(szLine, "%*s %f %f %f", &vi.v[0], &vi.v[1], &vi.v[2]);
                            if (result == 0)
                                continue;
                            positions.push_back(vi);
                        }
                    }
                    else if (szLine[0] == 'f')
                    {
                        // f index/texcoord/normal
                        VertexDefine vd[3];
                        int result = sscanf(szLine, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
                            &vd[0].positionIndex, &vd[0].texcoordIndex, &vd[0].normalIndex,
                            &vd[1].positionIndex, &vd[1].texcoordIndex, &vd[1].normalIndex,
                            &vd[2].positionIndex, &vd[2].texcoordIndex, &vd[2].normalIndex);
                        if (result == 0)
                        {
                            SDL_Log("face data unsupport");
                            continue;
                        }

                        for (size_t i = 0; i < 3; i++)
                        {
                            // index start at 0
                            vd[i].positionIndex -= 1;
                            vd[i].texcoordIndex -= 1;
                            vd[i].normalIndex -= 1;

                            // filter same position
                            int currentidx = -1;
                            size_t curcount = vertexs.size();
                            for (size_t j = 0; j < curcount; j++)
                            {
                                if (vertexs[j].positionIndex == vd[i].positionIndex &&
                                    vertexs[j].texcoordIndex == vd[i].texcoordIndex &&
                                    vertexs[j].normalIndex == vd[i].normalIndex)
                                {
                                    currentidx = j;
                                    break;
                                }
                            }
                            if (currentidx == -1)
                            {
                                currentidx = vertexs.size();
                                vertexs.push_back(vd[i]);
                            }
                            indexes.push_back(currentidx);
                        }
                    }
                }
            }
            _indexCount = (int)indexes.size();
            _indexs = new unsigned int[_indexCount];
            for (int i = 0; i < _indexCount; i++)
            {
                _indexs[i] = indexes[i];
            }
            _vertexCount = (int)vertexs.size();

            _vertexs = new Vertex[_vertexCount];
            for (int i = 0; i < _vertexCount; i++)
            {
                memcpy(_vertexs[i].position, positions[vertexs[i].positionIndex].v, sizeof(float) * 3);
                memcpy(_vertexs[i].texcoord, texcoords[vertexs[i].texcoordIndex].v, sizeof(float) * 2);
                memcpy(_vertexs[i].position, normals[vertexs[i].normalIndex].v, sizeof(float) * 3);
            }
        }
    }

  public:
    std::string _filename;
    Vertex *_vertexs;
    int _vertexCount;
    int _indexCount;
    unsigned int *_indexs;
};