#include "modelReader.h"
#include "ResourceManager.h"

static glm::vec3 AssimpToOpenGL(const aiVector3D aVec3)
{
	return glm::vec3(aVec3.x,aVec3.y,aVec3.z);
}

static glm::vec2 AssimpToOpenGL(const aiVector2D& aVec2)
{
	return glm::vec2(aVec2.x,aVec2.y);
}

void loadMaterial(const aiScene* pScene){
    for(unsigned int i = 0; i < pScene->mNumMaterials; i++){
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load diffuse Texture
            }
        }
        if(pMaterial->GetTextureCount(aiTextureType_LIGHTMAP) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_LIGHTMAP, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load AO Texture
            }
        }
        // unsure if this should be aiTextureType_DISPLACEMENT
        if(pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_HEIGHT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load Heightmap Texture
            }
        }
        if(pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load normal Texture
            }
        }
    }
}

Mesh loadMesh(const aiMesh* pMesh)
{
    std::vector<Vertex> vertex;
    std::vector<unsigned int> indecies;

    vertex.reserve(pMesh->mNumVertices);
    indecies.reserve(pMesh->mNumFaces * 3);

    aiVector3D TexCoord(0,0,0);
    for(unsigned int i = 0; i < pMesh->mNumVertices; i++){
        glm::vec3 pos, norm;
        pos.x = pMesh->mVertices[i].x;
        pos.y = pMesh->mVertices[i].y;
        pos.z = pMesh->mVertices[i].z;

        norm.x = pMesh->mNormals[i].x;
        norm.y = pMesh->mNormals[i].y;
        norm.z = pMesh->mNormals[i].z;

        if(pMesh->HasTextureCoords(0)){
            TexCoord = pMesh->mTextureCoords[0][i];
        }

        vertex.push_back(
            Vertex(
                pos,
                norm, 
                glm::vec2(TexCoord.x, TexCoord.y)
            )
        );
    }

    for(unsigned int i = 0; i < pMesh->mNumFaces; i++){
        indecies.push_back(pMesh->mFaces[i].mIndices[0]);
        indecies.push_back(pMesh->mFaces[i].mIndices[1]);
        indecies.push_back(pMesh->mFaces[i].mIndices[2]);
    }


    unsigned int vertexArray = CreateVertexArray();
    unsigned int vertexBuffer = CreateVertexBuffer(vertex);
    unsigned int indeciesBuffer = CreateIndeciesBuffer(indecies);

    return Mesh(
        0, 
        pMesh->mNumVertices, 
        vertexBuffer, 
        (unsigned int)indecies.size(), 
        indeciesBuffer,
        vertexArray
    );
}

Model* loadModel(const std::string& modelFile, ResourceManager* rm)
{
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(modelFile.c_str(),
        aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs
    );
    if(!pScene){
        return nullptr;
    }
    Model* theReturnModel = new Model();

    theReturnModel->getMeshes().reserve(pScene->mNumMeshes);

    for(unsigned int i = 0; i < pScene->mNumMeshes; i++){
        theReturnModel->getMeshes().push_back(loadMesh(pScene->mMeshes[i]));
    }
    
    
    return theReturnModel;
}
