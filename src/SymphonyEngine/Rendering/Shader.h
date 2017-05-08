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
        
        unsigned int ID() const;

        static Shader* GetShader(const char* shaderName);

    protected:
        std::string name;
        unsigned int programID;

        //TO-DO: Figure out if caching locations improves perfomance.
        //       If so, determine whether a vector might be more suitable than a map for 
        //       small sets of values like locations in a shader
        /*std::map<const char*, unsigned int> attributeList;
        std::map<const char*, unsigned int> uniformLocationList;*/
        
    private:
        
        Shader();
        ~Shader();
        
        bool CreateAndLink(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader = 0);
        unsigned int LoadFromString(ShaderType typeOfShader, const char* source);
        unsigned int LoadFromFile(ShaderType typeOfShader, const char* filename);
        
    protected:
        static Shader* CreateNewShader(const char* shaderName, const char* vertexShaderFilename,
                                       const char* fragmentShaderFilename, const char* geometryShaderFilename = nullptr);
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

    inline unsigned int Shader::ID() const
    {
        return programID;
    }
}
