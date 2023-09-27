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

void loadMaterial(const aiScene* pScene, std::vector<Material>& material, ResourceManager* rm){
    material.resize(pScene->mNumMaterials);

    //Just beacuse I found a bug with a object that doesn't have a material but says it has
    bool actually_has_material = false;

    for(unsigned int i = 0; i < pScene->mNumMaterials; i++){
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load diffuse Texture
                actually_has_material = true;
                material[i].Albedo = rm->getTexture(path.C_Str());
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::Albedo);
            }
        }
        else{
             material[i].Albedo = rm->getTexture("def");
        }
        if(pMaterial->GetTextureCount(aiTextureType_LIGHTMAP) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_LIGHTMAP, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load AO Texture
                actually_has_material = true;
                material[i].AmbientOcclusion = rm->getTexture(path.C_Str());
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::AmbientOcclusion);
            }
        }
        // unsure if this should be aiTextureType_DISPLACEMENT
        if(pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_HEIGHT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load Heightmap Texture
                actually_has_material = true;
                material[i].HeightMap = rm->getTexture(path.C_Str());
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::HeightMap);
            }
        }
        if(pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load normal Texture
                actually_has_material = true;
                material[i].NormalMap = rm->getTexture(path.C_Str());
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::NormalMap);
            }
        }
        float ns;
        aiColor3D kd,ka,ks,ke;
		float ni, d;
        ni = 0;
		pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ka);
		pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, ks);
		pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, kd);
		pMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, ke);
		pMaterial->Get(AI_MATKEY_SHININESS, ns);
		pMaterial->Get(AI_MATKEY_OPACITY, d);
        
        if(actually_has_material)
        {
            material[i].Ka.x = ka.r;
            material[i].Ka.y = ka.g;
            material[i].Ka.z = ka.b;
            
            material[i].Kd.x = kd.r;
            material[i].Kd.y = kd.g;
            material[i].Kd.z = kd.b;
            
            material[i].Ks.x = ks.r;
            material[i].Ks.y = ks.g;
            material[i].Ks.z = ks.b;
            
            material[i].Ke.x = ke.r;
            material[i].Ke.y = ke.g;
            material[i].Ke.z = ke.b;
            
            material[i].d = d;
            material[i].Ni = ni;
            material[i].Ns = ns;
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
        glm::vec3 pos, norm, tangent, bitangent;
        pos.x = pMesh->mVertices[i].x;
        pos.y = pMesh->mVertices[i].y;
        pos.z = pMesh->mVertices[i].z;

        norm.x = pMesh->mNormals[i].x;
        norm.y = pMesh->mNormals[i].y;
        norm.z = pMesh->mNormals[i].z;

        tangent.x = pMesh->mTangents[i].x;
        tangent.y = pMesh->mTangents[i].y;
        tangent.z = pMesh->mTangents[i].z;

        bitangent.x = pMesh->mBitangents[i].x;
        bitangent.y = pMesh->mBitangents[i].y;
        bitangent.z = pMesh->mBitangents[i].z;

        if(pMesh->HasTextureCoords(0)){
            TexCoord = pMesh->mTextureCoords[0][i];
        }

        vertex.push_back(
            Vertex(
                pos,
                glm::vec2(TexCoord.x, TexCoord.y),
                norm, 
                tangent,
                bitangent
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
    Mesh theMesh = Mesh(
        0, 
        pMesh->mNumVertices, 
        vertexBuffer, 
        (unsigned int)indecies.size(), 
        indeciesBuffer,
        vertexArray
    );

    return theMesh;
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

    //come on
    std::vector<Material> materials;
    loadMaterial(pScene, materials, rm);

    std::vector<materialConstBuffer> mcb;
    mcb.resize(materials.size());

    for(int i = 0; i < mcb.size(); i++){
        mcb[i] = materials[i];//special operator
    }
    
    for(unsigned int i = 0; i < pScene->mNumMeshes; i++){
        theReturnModel->getMeshes().push_back(loadMesh(pScene->mMeshes[i]));
        theReturnModel->getMeshes()[theReturnModel->getMeshes().size() - 1].material = materials[pScene->mMeshes[i]->mMaterialIndex];
        theReturnModel->getMeshes()[theReturnModel->getMeshes().size() - 1].mcb = CreateUniformBuffer(mcb[pScene->mMeshes[i]->mMaterialIndex]);
    }
    
    
    return theReturnModel;
}
