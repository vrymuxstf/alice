#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

namespace alice {
    struct MeshReader {
        std::vector<MeshVertex> vertices;
        std::vector<uint32_t> indices;

        void Read(const char *filename) {
            vertices.clear();
            indices.clear();

            Assimp::Importer importer;
            const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs |
                                                               aiProcess_MakeLeftHanded);

            aiMesh *mesh = scene->mMeshes[0];

            for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
                MeshVertex vertex{
                        {mesh->mVertices[i].x,         mesh->mVertices[i].y, mesh->mVertices[i].z},
                        {mesh->mNormals[i].x,          mesh->mNormals[i].y,  mesh->mNormals[i].z},
                        {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y}
                };

                vertices.push_back(vertex);
            }

            for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                aiFace face = mesh->mFaces[i];
                for (unsigned int j = 0; j < face.mNumIndices; j++) {
                    indices.push_back(face.mIndices[j]);
                }
            }
        }
    };
}