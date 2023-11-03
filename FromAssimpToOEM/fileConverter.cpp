#include "fileConverter.h"

bool loadMaterials(const aiScene* pScene, std::vector<MaterialSave>& materialSave)
{
    materialSave.resize(pScene->mNumMaterials);

    for(int i = 0; i < pScene->mNumMaterials; i++){
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                materialSave[i].fileNames.push_back(path.C_Str());
                materialSave[i].TextureType.push_back(MaterialFlags::Albedo);
                materialSave[i].materialFlags = (MaterialFlags)(materialSave[i].materialFlags | MaterialFlags::Albedo);
            }
        }
        else{
            materialSave[i].fileNames.push_back("def");
            materialSave[i].materialFlags = (MaterialFlags)(materialSave[i].materialFlags | MaterialFlags::Albedo);
            materialSave[i].TextureType.push_back(MaterialFlags::Albedo);
        }
        if(pMaterial->GetTextureCount(aiTextureType_LIGHTMAP) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_LIGHTMAP, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                materialSave[i].fileNames.push_back(path.C_Str());
                materialSave[i].TextureType.push_back(MaterialFlags::AmbientOcclusion);
                materialSave[i].materialFlags = (MaterialFlags)(materialSave[i].materialFlags | MaterialFlags::AmbientOcclusion);
            }
        }
        if(pMaterial->GetTextureCount(aiTextureType_DISPLACEMENT) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_DISPLACEMENT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                materialSave[i].fileNames.push_back(path.C_Str());
                materialSave[i].TextureType.push_back(MaterialFlags::HeightMap);
                materialSave[i].materialFlags = (MaterialFlags)(materialSave[i].materialFlags | MaterialFlags::HeightMap);
            }
        }
        if(pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                materialSave[i].fileNames.push_back(path.C_Str());
                materialSave[i].TextureType.push_back(MaterialFlags::NormalMap);
                materialSave[i].materialFlags = (MaterialFlags)(materialSave[i].materialFlags | MaterialFlags::NormalMap);
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

        materialSave[i].Ns = ns;
        materialSave[i].Ka = glm::vec3(ka.r, ka.g, ka.b);
        materialSave[i].Kd = glm::vec3(kd.r, kd.g, kd.b);
        materialSave[i].Ks = glm::vec3(ks.r, ks.g, ks.b);
        materialSave[i].Ke = glm::vec3(ke.r, ke.g, ke.b);
        materialSave[i].Ni = ni;
        materialSave[i].d = d;
        materialSave[i].tessellationLevel = 0;
    }

    return true;
}

bool loadMesh(const aiMesh* pMesh, std::vector<Vertex>& vertecies, std::vector<uint32_t>& indecies)
{
    vertecies.reserve(pMesh->mNumVertices);
    indecies.reserve(pMesh->mNumFaces * 3);

    aiVector3D TexCoord(0,0,0);
    for(uint32_t i = 0; i < pMesh->mNumVertices; i++){
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

        vertecies.push_back(
            Vertex(
                pos,
                glm::vec2(TexCoord.x, TexCoord.y),
                norm, 
                tangent,
                bitangent
            )
        );
    }

    for(uint32_t i = 0; i < pMesh->mNumFaces; i++){
        indecies.push_back(pMesh->mFaces[i].mIndices[0]);
        indecies.push_back(pMesh->mFaces[i].mIndices[1]);
        indecies.push_back(pMesh->mFaces[i].mIndices[2]);
    }

    return true;
}

bool createFile(
    std::string fileName,
    std::vector<std::vector<Vertex>> n_vertecies,
    std::vector<std::vector<uint32_t>> indecies,
    std::vector<MaterialSave> materialSave,
    std::vector<int> materialIndex
)
{
    if(fileName.substr(fileName.find_last_of(".") + 1) != "OEM"){
        fileName += ".OEM";
    }
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    VerteciesType w = VerteciesType::normalVertecies;
    uint32_t uw;
    uw = (uint32_t)materialSave.size();
    file.write((char*)&uw, sizeof(uint32_t));//nr of Materials

    for(int t = 0; t < materialSave.size(); t++){
        file.write((char*)&materialSave[t].materialFlags, sizeof(MaterialFlags));

        //write all texture names
        uw = (uint32_t)materialSave[t].fileNames.size();
        file.write((char*)&uw, sizeof(uint32_t));//size of vector

        writeVectorFromFile(file, materialSave[t].TextureType);
        //write 
        for(int i = 0; i < materialSave[t].fileNames.size(); i++){
            uw = materialSave[t].fileNames[i].size();
            file.write((char*)&uw, sizeof(uint32_t));//size of filename

            std::string fileName = materialSave[t].fileNames[i];//something wrong here
            file.write(fileName.c_str(), uw);
        }
        
        file.write((char*)&materialSave[t].Ns, sizeof(float));

        file.write((char*)&materialSave[t].Ka, sizeof(glm::fvec3));
        file.write((char*)&materialSave[t].Kd, sizeof(glm::fvec3));
        file.write((char*)&materialSave[t].Ks, sizeof(glm::fvec3));
        file.write((char*)&materialSave[t].Ke, sizeof(glm::fvec3));

        file.write((char*)&materialSave[t].Ni, sizeof(float));
        file.write((char*)&materialSave[t].d, sizeof(float));

        file.write((char*)&materialSave[t].tessellate, sizeof(bool));
        file.write((char*)&materialSave[t].tessellationLevel, sizeof(float));
    }

    file.write((char*)&w, sizeof(VerteciesType));

    uw = (uint32_t)n_vertecies.size();
    file.write((char*)&uw, sizeof(uint32_t));//nr of Meshes

    //for each mesh
    for(int i = 0; i < n_vertecies.size(); i++){
        writeVectorFromFile(file, n_vertecies[i]);
        writeVectorFromFile(file, indecies[i]);
        file.write((char*)&materialIndex[i], sizeof(int));//material index
    }
    
    file.close();
    if(!file.good()){
        std::cerr << "Error: something went wrong while writing" << std::endl;
        return false;
    }
    return true;
}

bool convert(const std::string& fileName, std::string newName)
{
    std::vector<std::vector<Vertex>> n_vertecies;
    std::vector<std::vector<uint32_t>> indecies;
    std::vector<MaterialSave> materialSave;
    std::vector<int> materialIndex;

    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(fileName.c_str(),
        aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs
    );
    if(!pScene){
        std::cout << "Error: cannot find file or open scene" << std::endl;
        return false;
    }

    n_vertecies.resize(pScene->mNumMeshes);
    indecies.resize(pScene->mNumMeshes);

    if(pScene->HasAnimations()){
        std::cout << "Warning: This object has animation and is not supported yet" << std::endl;
    }

    if(!loadMaterials(pScene, materialSave)){
        std::cout << "Error: cannot load materials" << std::endl;
        return false;
    };
    for(int i = 0; i < pScene->mNumMeshes; i++){
        materialIndex.push_back(pScene->mMeshes[i]->mMaterialIndex);
        if(!loadMesh(pScene->mMeshes[i], n_vertecies[i], indecies[i]))
        {
            std::cout << "Error: cannot create mesh" << std::endl;
            return false;
        }
    }

    if(newName == ""){
        newName = fileName;
    }
    return createFile(
        newName,
        n_vertecies,
        indecies,
        materialSave,
        materialIndex
    );

}
