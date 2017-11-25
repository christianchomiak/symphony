#pragma once

#include <vector>
#include <map>
#include "../Utilities/HashString.h"

namespace Symphony
{
    class Shader
    {
        friend class SymphonyEngine;
        
    public:
        enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
        
        void Use()       const;
        void Release()   const;
        
        unsigned int ID() const;

        static Shader* GetShader(HashString shaderName);

    protected:
        HashString name;
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
        static Shader* CreateNewShader(HashString shaderName, const char* vertexShaderFilename,
                                       const char* fragmentShaderFilename, const char* geometryShaderFilename = nullptr);
        static bool ShaderExists(HashString name);
        static void DeleteShader(HashString name);
        static void DeleteAllShaders();
        
        //TO-DO: Use hashes instead of char*
        static std::map<HashString, Shader*> shaderPool;
    };

    inline unsigned int Shader::ID() const
    {
        return programID;
    }
}
