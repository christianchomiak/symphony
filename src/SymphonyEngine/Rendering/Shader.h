#pragma once

#include <vector>
#include <map>

namespace Symphony
{
    class Shader
    {
        friend class SymphonyEngine;
        
    public:
        enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
        
        void Use()       const;
        void Release()   const;
        
        //An indexer that returns the location of the attribute/uniform
        unsigned int operator[](const std::string& attribute);
        unsigned int operator()(const std::string& uniform);
        unsigned int ID() const;

        static Shader* GetShader(const std::string& shaderName);

    protected:
        std::string name;
        unsigned int programID;
        unsigned int shaders[3];

        //TO-DO: Figure out if caching locations improves perfomance.
        //       If so, determine whether a vector might be more suitable than a map for 
        //       small sets of values like locations in a shader
        std::map<std::string, unsigned int> attributeList;
        std::map<std::string, unsigned int> uniformLocationList;
        
    private:
        
        Shader();
        ~Shader();
        bool CreateAndLink();
        void AddAttribute(const std::string& attribute);
        void AddUniform(const std::string& uniform);
        bool LoadFromString(ShaderType typeOfShader, const std::string& source);
        bool LoadFromFile(ShaderType typeOfShader, const std::string& filename);
        
    protected:
        static Shader* CreateNewShader(const std::string& shaderName, const std::vector<std::string>& attributes, const std::vector<std::string>& uniforms,
                                       const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename, const std::string& geometryShaderFilename = nullptr);
        static bool ShaderExists(const std::string& shaderName);
        static void DeleteShader(const std::string& shaderName);
        static void DeleteAllShaders();
        static std::map<std::string, Shader*> shaderPool;
    };
    

    inline unsigned int Shader::operator[](const std::string& attribute)
    {
        return attributeList[attribute];
    }

    inline unsigned int Shader::operator()(const std::string& uniform)
    {
        return uniformLocationList[uniform];
    }

    inline unsigned int Shader::ID() const
    {
        return programID;
    }
}
