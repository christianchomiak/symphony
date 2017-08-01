#include "Shader.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h>

#include <fstream>
#include <iostream>
#include <string>

#include "../Debugging/Debugging.h"

using namespace std;

namespace Symphony
{
    map<const char*, Shader*, Shader::CharArrayCmp> Shader::shaderPool;
    
    void Shader::Use()       const { glUseProgram(programID); };
    void Shader::Release()   const { glUseProgram(0);         };
    
    Shader::Shader()
        : programID(0)
    {
    }

    Shader::~Shader()
    {
        glDeleteProgram(programID);
    }

    /*static*/ Shader* Shader::GetShader(const char* shaderName)
    {
        if (ShaderExists(shaderName))
        {
            return shaderPool[shaderName];
        }
        return nullptr;
    }

    bool Shader::CreateAndLink(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader)
    {
        programID = glCreateProgram();

        if (vertexShader != 0)
        {
            glAttachShader(programID, vertexShader);
        }

        if (fragmentShader != 0)
        {
            glAttachShader(programID, fragmentShader);
        }

        if (geometryShader != 0)
        {
            glAttachShader(programID, geometryShader);
        }
        
        //link and check whether the program links fine
        GLint status;
        glLinkProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &status);
        
        if (status == GL_FALSE)
        {
            GLint infoLogLength;
            
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar *infoLog = new GLchar[infoLogLength];
            glGetProgramInfoLog(programID, infoLogLength, NULL, infoLog);
            LogError("Linking: ERROR\n\n");
            std::cerr << "Link log: " << infoLog << std::endl << std::endl;
            delete[] infoLog;
            return false;
        }

        Log("Linking: OK\n\n");
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteShader(geometryShader);
        
        return true;
    }

    unsigned int Shader::LoadFromString(ShaderType typeOfShader, const char* source)
    {
        GLenum whichShader;

        if (typeOfShader == ShaderType::VERTEX_SHADER)        whichShader = GL_VERTEX_SHADER;
        else if (typeOfShader == ShaderType::GEOMETRY_SHADER) whichShader = GL_GEOMETRY_SHADER;
        else                                                  whichShader = GL_FRAGMENT_SHADER;
        
        GLuint shader = glCreateShader(whichShader);

        glShaderSource(shader, 1, &source, NULL);

        //check whether the shader loads fine
        GLint status;
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint infoLogLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar *infoLog = new GLchar[infoLogLength];
            glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
            LogError("\tCompilation: ERROR");
            std::cerr << "Compile log: " << infoLog << std::endl << std::endl;
            delete[] infoLog;
            
            return 0;
        }

        Log("\tCompilation: OK");
        
        return shader;
    }

    unsigned int Shader::LoadFromFile(ShaderType typeOfShader, const char* filename)
    {
        char* shaderName;
        
        if (typeOfShader == ShaderType::VERTEX_SHADER)        shaderName = "Vertex";
        else if (typeOfShader == ShaderType::GEOMETRY_SHADER) shaderName = "Geometry";
        else                                                  shaderName = "Fragment"; //if (whichShader == GL_FRAGMENT_SHADER)

        LogF("> %s shader (%s)", shaderName, filename);
        
        ifstream fp;
        fp.open(filename, ios_base::in);

        if (fp)
        {
            string line, buffer; //TO-DO: Maybe a sstream could be better?
            while (getline(fp, line))
            {
                buffer.append(line);
                buffer.append("\r\n");
            }
            Log("\tLoading: OK");
            //copy to source
            return LoadFromString(typeOfShader, buffer.c_str());
        }

        Log("\tLoading: ERROR\n\n");

        return 0;
    }

    Shader* Shader::CreateNewShader(const char* shaderName, const char* vertexShaderFilename,
                                    const char* fragmentShaderFilename, const char* geometryShaderFilename)
    {

        //There's no point in creating the same shader over and over again
        if (ShaderExists(shaderName))
        {
            LogF("Using previously loaded shader: %s", shaderName);
            return shaderPool[shaderName];
        }

        LogF("Creating new shader: \"%s\"", shaderName);

        Shader* newShader = new Shader();

        //Load all programs for this shader
        
        unsigned int vertexShader = newShader->LoadFromFile(ShaderType::VERTEX_SHADER, vertexShaderFilename);

        if (vertexShader == 0)
        {
            delete newShader;
            return nullptr;
        }

        unsigned int fragmentShader = newShader->LoadFromFile(ShaderType::FRAGMENT_SHADER, fragmentShaderFilename);

        if (fragmentShader == 0)
        {
            delete newShader;
            return nullptr;
        }
        
        unsigned int geometryShader(0);
        if (geometryShaderFilename != nullptr && geometryShaderFilename[0] != '\0')
        {
            geometryShader = newShader->LoadFromFile(ShaderType::GEOMETRY_SHADER, geometryShaderFilename);

            if (geometryShader == 0)
            {
                delete newShader;
                return nullptr;
            }
        }
        
        //compile and link shader
        if (!newShader->CreateAndLink(vertexShader, fragmentShader, geometryShader))
        {
            delete newShader;
            return nullptr;
        }

        newShader->name = shaderName;

        shaderPool[newShader->name.c_str()] = newShader;

        return newShader;
    }
    
    bool Shader::ShaderExists(const char* shaderName)
    {
        return shaderPool.find(shaderName) != shaderPool.end();
    }
    
    void Shader::DeleteShader(const char* shaderName)
    {
        if (ShaderExists(shaderName))
        {
            delete shaderPool[shaderName];
            shaderPool.erase(shaderName);
        }
    }
    
    void Shader::DeleteAllShaders()
    {
        for (auto it = shaderPool.begin(); it != shaderPool.end(); ++it)
        {
            //const char* key = it->first;
            delete it->second;
        }
        shaderPool.clear();
    }
}
