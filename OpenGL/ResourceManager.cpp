#include "ResourceManager.h"
#include "modelReader.h"

ResourceManager::ResourceManager()
{
    loadDef();
}

ResourceManager::~ResourceManager()
{
    for (auto const& [key, val] : ShaderProgram)
    {
        glDeleteProgram(val);
    }
    for (auto const& [key, val] : Models)
    {
        delete val;
    }
}

Model* ResourceManager::getModel(const std::string& FileName)
{
    if(Models.find(FileName) == Models.end()){
        Model* temp = loadModel(FileName, this);
        Models.insert(std::pair<std::string, Model*>(FileName, temp));
    }
    return Models.find(FileName)->second;
}

unsigned int ResourceManager::getShader(const std::string& ShaderFile)
{
    return 0;
}

unsigned int ResourceManager::getShaderProgram(const std::string& ShaderProgram)
{
    if(this->ShaderProgram.find(ShaderProgram) == this->ShaderProgram.end()){
        std::cout << "couldn't find shaderProgram " << ShaderProgram << std::endl;
        return this->ShaderProgram.find("defShaderProgram")->second;
    }
    return this->ShaderProgram.find(ShaderProgram)->second;
}

unsigned int ResourceManager::getTexture(const std::string& FileName)
{
    if (Textures.find(FileName) == Textures.end()) {
        unsigned int textureID;
        if(ReadImage(FileName, textureID)){
            Textures.insert(std::make_pair(FileName, textureID));
        }
        else{
            //return def
            return Textures.find("def")->second;
        }
        
    }
    return Textures.find(FileName)->second;
}

unsigned int ResourceManager::createShaderProgram(const std::string& ShaderProgramName, unsigned int vertex, unsigned int pixel)
{
    unsigned int shaderProgram = attachShaders(vertex, pixel);
    ShaderProgram.insert(std::make_pair(ShaderProgramName, shaderProgram));
    return shaderProgram;
}


void ResourceManager::loadDef()
{
	std::vector<Vertex> DefaultVertecies;
    DefaultVertecies.push_back(Vertex(glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0,0,1), glm::vec2(0,0)));
    DefaultVertecies.push_back(Vertex(glm::vec3(0.f,1.f,0.f), glm::vec3(0,0,1), glm::vec2(0,0)));
    DefaultVertecies.push_back(Vertex(glm::vec3(-1.f,0.f,0.f), glm::vec3(0,0,1), glm::vec2(0,0)));
    std::vector<unsigned int> DefaultIndecies = {
        0,1,2,
    };
    unsigned int defVertexArray = CreateVertexArray();
    Model *temp = new Model();
    temp->getMeshes().push_back(
        Mesh(
            0, 
            DefaultVertecies.size(), 
            CreateVertexBuffer(DefaultVertecies), 
            DefaultIndecies.size(), 
            CreateIndeciesBuffer(DefaultIndecies),
            defVertexArray
        ));
    Models.insert(std::pair<std::string, Model*>("def", temp));

    unsigned int def_vShader, def_pShader;
    GLTest(loadVShader("BasicVertexShader.vert", def_vShader));
    Shaders.insert(std::make_pair("defVertex", def_vShader));

    GLTest(loadPShader("BasicPixelShader.frag", def_pShader));
    Shaders.insert(std::make_pair("defPixel", def_pShader));

    unsigned int def_shaderProgram = attachShaders(def_vShader, def_pShader);
    ShaderProgram.insert(std::make_pair("defShaderProgram", def_shaderProgram));
    glUseProgram(def_shaderProgram);

    unsigned int defTexture;
    if(ReadImage("../Textures/Def/defTexture.png", defTexture)){
        Textures.insert(std::make_pair("def", defTexture));
    }
    else{ 
        std::cout << "error couldn't load defTexture" << std::endl;
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Textures["def"]);
}



