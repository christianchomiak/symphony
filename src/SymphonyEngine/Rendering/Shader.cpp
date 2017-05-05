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
    
    Shader* Shader::GetShader(const char* shaderName)
    {
        if (ShaderExists(shaderName))
        {
            return shaderPool[shaderName];
        }
        return nullptr;
    }

    Shader::Shader()
    {
        shaders[VERTEX_SHADER] = 0;
        shaders[FRAGMENT_SHADER] = 0;
        shaders[GEOMETRY_SHADER] = 0;
    }

    Shader::~Shader()
    {
        glDeleteProgram(programID);
    }

    bool Shader::CreateAndLink()
    {
        programID = glCreateProgram();
        if (shaders[VERTEX_SHADER] != 0) {
            glAttachShader(programID, shaders[VERTEX_SHADER]);
        }
        if (shaders[FRAGMENT_SHADER] != 0) {
            glAttachShader(programID, shaders[FRAGMENT_SHADER]);
        }
        if (shaders[GEOMETRY_SHADER] != 0) {
            glAttachShader(programID, shaders[GEOMETRY_SHADER]);
        }
        
        //TO-DO: We don't need to set the default attributes here because
        //       we'll be using layouts instead
        //SetDefaultAttributes();

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
            Debug::LogError("Linking: ERROR\n\n");
            std::cerr << "Link log: " << infoLog << std::endl << std::endl;
            delete[] infoLog;
            return false;
        }

        Debug::Log("Linking: OK\n\n");
        
        glDeleteShader(shaders[VERTEX_SHADER]);
        glDeleteShader(shaders[FRAGMENT_SHADER]);
        glDeleteShader(shaders[GEOMETRY_SHADER]);

        shaders[VERTEX_SHADER]   = 0;
        shaders[FRAGMENT_SHADER] = 0;
        shaders[GEOMETRY_SHADER] = 0;

        return true;
    }

    bool Shader::LoadFromString(ShaderType typeOfShader, const char* source)
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
            Debug::LogError("\tCompilation: ERROR");
            std::cerr << "Compile log: " << infoLog << std::endl << std::endl;
            delete[] infoLog;
            return false;
        }
                
        Debug::Log("\tCompilation: OK");
        
        shaders[typeOfShader] = shader;

        return true;
    }

    bool Shader::LoadFromFile(ShaderType typeOfShader, const char* filename)
    {
        char* shaderName;
        
        if (typeOfShader == ShaderType::VERTEX_SHADER)        shaderName = "Vertex";
        else if (typeOfShader == ShaderType::GEOMETRY_SHADER) shaderName = "Geometry";
        else                                                  shaderName = "Fragment"; //if (whichShader == GL_FRAGMENT_SHADER)

        Debug::LogF("> %s shader (%s)", shaderName, filename);
        
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
            Debug::Log("\tLoading: OK");
            //copy to source
            return LoadFromString(typeOfShader, buffer.c_str());
        }

        Debug::Log("\tLoading: ERROR\n\n");

        return false;
    }
    
    void Shader::AddAttribute(const char* attribute)
    {
        attributeList[attribute] = glGetAttribLocation(programID, attribute);
    }
    
    void Shader::AddUniform(const char* uniform)
    {
        uniformLocationList[uniform] = glGetUniformLocation(programID, uniform);
    }

    Shader* Shader::CreateNewShader(const char* shaderName,
                                    const vector<const char*>& attributes, const vector<const char*>& uniforms,
                                    const char* vertexShaderFilename, const char* fragmentShaderFilename,
                                    const char* geometryShaderFilename)
    {

        //There's no point in creating the same shader over and over again
        if (ShaderExists(shaderName))
        {
            Debug::LogF("Using previously loaded shader: %s", shaderName);
            return shaderPool[shaderName];
        }

        Debug::LogF("Creating new shader: \"%s\"", shaderName);

        Shader* newShader = new Shader();

        //Load all programs for this shader
        if (!newShader->LoadFromFile(ShaderType::VERTEX_SHADER, vertexShaderFilename))
            return nullptr;

        if (!newShader->LoadFromFile(ShaderType::FRAGMENT_SHADER, fragmentShaderFilename))
            return nullptr;
        
        if (geometryShaderFilename != nullptr && geometryShaderFilename[0] != '\0' 
            && !newShader->LoadFromFile(ShaderType::GEOMETRY_SHADER, geometryShaderFilename))
            return nullptr;
        
        //compile and link shader
        if (!newShader->CreateAndLink())
            return nullptr;

        newShader->Use();

        //Add attributes
        for (unsigned int i = 0; i < attributes.size(); ++i)
        {
            newShader->AddAttribute(attributes[i]);
        }

        //Add uniforms
        for (unsigned int i = 0; i < uniforms.size(); ++i)
        {
            newShader->AddUniform(uniforms[i]);
        }
        
        newShader->Release();

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
