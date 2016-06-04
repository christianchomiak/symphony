#include "Shader.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace Symphony
{
    map<string, Shader*> Shader::shaderPool;
    
    void Shader::Use()       const { glUseProgram(programID); };
    void Shader::Release()   const { glUseProgram(0); };

    Shader* Shader::GetShader(const std::string & shaderName)
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
            std::cerr << "Link log: " << infoLog << std::endl;
            delete[] infoLog;
            return false;
        }

        std::cout << std::endl << "> Linking of the shaders was successful" << std::endl;
        
        glDeleteShader(shaders[VERTEX_SHADER]);
        glDeleteShader(shaders[FRAGMENT_SHADER]);
        glDeleteShader(shaders[GEOMETRY_SHADER]);

        shaders[VERTEX_SHADER]   = 0;
        shaders[FRAGMENT_SHADER] = 0;
        shaders[GEOMETRY_SHADER] = 0;

        return true;
    }

    bool Shader::LoadFromString(ShaderType typeOfShader, const string& source)
    {
        GLenum whichShader;

        if (typeOfShader == ShaderType::VERTEX_SHADER)        whichShader = GL_VERTEX_SHADER;
        else if (typeOfShader == ShaderType::GEOMETRY_SHADER) whichShader = GL_GEOMETRY_SHADER;
        else                                                  whichShader = GL_FRAGMENT_SHADER;
        
        GLuint shader = glCreateShader(whichShader);

        const char * ptmp = source.c_str();
        glShaderSource(shader, 1, &ptmp, NULL);

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
            std::cerr << "Compile log: " << infoLog << std::endl;
            delete[] infoLog;
            return false;
        }

        char* shaderName;
        if (typeOfShader == ShaderType::VERTEX_SHADER)        shaderName = "vertex";
        else if (typeOfShader == ShaderType::GEOMETRY_SHADER) shaderName = "geometry";
        else                                                  shaderName = "fragment"; //if (whichShader == GL_FRAGMENT_SHADER)

        
        cout << "> " << shaderName << " shader compiled" << endl;
        
        shaders[typeOfShader] = shader;

        return true;
    }

    bool Shader::LoadFromFile(ShaderType typeOfShader, const string& filename)
    {
        char* shaderName;
        
        if (typeOfShader == ShaderType::VERTEX_SHADER)        shaderName = "vertex";
        else if (typeOfShader == ShaderType::GEOMETRY_SHADER) shaderName = "geometry";
        else                                                  shaderName = "fragment"; //if (whichShader == GL_FRAGMENT_SHADER)
        
        cout << endl << "> Loading " << shaderName << " shader (" << filename << ")" << endl;
        
        ifstream fp;
        fp.open(filename.c_str(), ios_base::in);

        if (fp)
        {
            string line, buffer; //TO-DO: Maybe a sstream could be better?
            while (getline(fp, line))
            {
                buffer.append(line);
                buffer.append("\r\n");
            }
            //copy to source
            return LoadFromString(typeOfShader, buffer);
        }

        cerr << "Error loading " << shaderName << " shader: " << filename << endl;

        return false;
    }
    
    void Shader::AddAttribute(const std::string& attribute)
    {
        attributeList[attribute] = glGetAttribLocation(programID, attribute.c_str());
    }
    
    void Shader::AddUniform(const std::string& uniform)
    {
        uniformLocationList[uniform] = glGetUniformLocation(programID, uniform.c_str());
    }

    Shader* Shader::CreateNewShader(const string& shaderName,
                                    const vector<string>& attributes, const vector<string>& uniforms,
                                    const string& vertexShaderFilename, const string& fragmentShaderFilename, 
                                    const string& geometryShaderFilename)
    {
        //There's no point in creating the same shader over and over again
        if (ShaderExists(shaderName))
        {
            return shaderPool[shaderName];
        }

        Shader* newShader = new Shader();

        //Load all programs for this shader
        if (!newShader->LoadFromFile(ShaderType::VERTEX_SHADER, vertexShaderFilename))
            return nullptr;

        if (!newShader->LoadFromFile(ShaderType::FRAGMENT_SHADER, fragmentShaderFilename))
            return nullptr;
        
        if (!geometryShaderFilename.empty() && !newShader->LoadFromFile(ShaderType::GEOMETRY_SHADER, geometryShaderFilename))
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

        shaderPool[shaderName] = newShader;

        return newShader;
    }
    
    bool Shader::ShaderExists(const std::string & shaderName)
    {
        return shaderPool.find(shaderName) != shaderPool.end();
    }
    
    void Shader::DeleteShader(const std::string & shaderName)
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
            //string key = it->first;
            delete it->second;
        }
        shaderPool.clear();
    }
}
