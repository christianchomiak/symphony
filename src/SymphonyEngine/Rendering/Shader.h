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
        unsigned int operator[](const char* attribute);
        unsigned int operator()(const char* uniform);
        unsigned int ID() const;

        static Shader* GetShader(const char* shaderName);

    protected:
        std::string name;
        unsigned int programID;
        unsigned int shaders[3];

        //TO-DO: Figure out if caching locations improves perfomance.
        //       If so, determine whether a vector might be more suitable than a map for 
        //       small sets of values like locations in a shader
        std::map<const char*, unsigned int> attributeList;
        std::map<const char*, unsigned int> uniformLocationList;
        
    private:
        
        Shader();
        ~Shader();
        bool CreateAndLink();
        void AddAttribute(const char* attribute);
        void AddUniform(const char* uniform);
        bool LoadFromString(ShaderType typeOfShader, const char* source);
        bool LoadFromFile(ShaderType typeOfShader, const char* filename);
        
    protected:
        static Shader* CreateNewShader(const char* shaderName, const std::vector<const char*>& attributes, const std::vector<const char*>& uniforms,
                                       const char* vertexShaderFilename, const char* fragmentShaderFilename, const char* geometryShaderFilename = nullptr);
        static bool ShaderExists(const char* shaderName);
        static void DeleteShader(const char* shaderName);
        static void DeleteAllShaders();

        //When using Char* as keys of a map, the comparisson is made over the pointer itself and not the actual string
		//As such, we need to specify a custom function to compare them properly
        struct CharArrayCmp
        {
            bool operator()(char const* a, char const* b) const
            {
                return std::strcmp(a, b) < 0;
            }
        };
        //TO-DO: Use hashes instead of char*
        static std::map<const char*, Shader*, CharArrayCmp> shaderPool;
    };
    

    inline unsigned int Shader::operator[](const char* attribute)
    {
        return attributeList[attribute];
    }

    inline unsigned int Shader::operator()(const char* uniform)
    {
        return uniformLocationList[uniform];
    }

    inline unsigned int Shader::ID() const
    {
        return programID;
    }
}
