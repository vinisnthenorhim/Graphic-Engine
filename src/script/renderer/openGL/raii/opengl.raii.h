#ifndef OPENGL_RAII_H
#define OPENGL_RAII_H
#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stb/stb_image.h>
#include <iostream>

class VBO
{
    public:
        VBO () {    glGenBuffers   (1, &VBOid  );    }
        ~VBO() {    glDeleteBuffers(1, &VBOid  );    }
        void bind() const {glBindBuffer(GL_ARRAY_BUFFER, VBOid);}
        template <typename T> 
        void data(const std::vector<T>& vertices) 
        {
            bind();
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(T)), vertices.data(), GL_STATIC_DRAW);
        }
        GLuint id() const { return VBOid; }
        VBO(const VBO&) = delete;
        VBO& operator=(const VBO&) = delete;
    private:
        GLuint VBOid;
};
class EBO
{
    public:
        EBO () {    glGenBuffers   (1, &EBOid  );    }
        ~EBO() {    glDeleteBuffers(1, &EBOid  );    }
        void bind() const {glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid);}
        template <typename T> 
        void data(const std::vector<T>& vertices) 
        {
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(T)), vertices.data(), GL_STATIC_DRAW);
        }
        GLuint id() const { return EBOid; }
        EBO(const EBO&) = delete;
        EBO& operator=(const EBO&) = delete;
    private:
        GLuint EBOid;
};
class VAO
{
    public:
        VAO () {    glGenVertexArrays   (1, &VAOid  );    }
        ~VAO() {    glDeleteVertexArrays(1, &VAOid  );    }
        void bind() const {glBindVertexArray(VAOid);}
        void unbind() const { glBindVertexArray(0); }
        void linkAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, const void* offset)
        {
            bind();
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
            glEnableVertexAttribArray(index);
        }
        GLuint id() const { return VAOid;}
        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;
    private:
        GLuint VAOid;
};
class SSBO
{
    public:
        SSBO () {    glGenBuffers   (1, &SSBOid  );    }
        ~SSBO() {    glDeleteBuffers(1, &SSBOid  );    }
        void bind() const {glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOid);}
        template <typename T> 
        void data(const std::vector<T>& vertices, GLuint binding) 
        {
            bind();
            glBufferData(GL_SHADER_STORAGE_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(T)), vertices.data(), GL_STATIC_DRAW);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, &SSBOid);
        }
        template <typename T> 
        void updateData(const std::vector<T>& vertices)
        {
          bind();
          glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, static_cast<GLsizeiptr>(vertices.size() * sizeof(T)), vertices.data())
        }
        GLuint id() const { return SSBOid; }
        SSBO(const SSBO&) = delete;
        SSBO& operator=(const SSBO&) = delete;
    private:
        GLuint SSBOid;
        GLuint binding;
};
class Framebuffer
{
    public:
        GLuint id;

        Framebuffer() { glGenFramebuffers(1, &id); }
        ~Framebuffer() { glDeleteFramebuffers(1, &id); }
        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;
        void bind() { glBindFramebuffer(GL_FRAMEBUFFER, id); }
        void unbind(){ glBindFramebuffer(GL_FRAMEBUFFER, 0); }
};
class Shader
{
    public:
        GLuint shader;

        Shader(GLenum type, const char* path)
        {
            shader = glCreateShader(type);
            std::string source = loadShader(path);
            const char* sourcePtr = source.c_str();
            glShaderSource( shader, 1, &sourcePtr, nullptr);
            glCompileShader( shader );            
        }
        ~Shader()  {  glDeleteShader( shader );  }
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
    private:
        std::string loadShader(const char* path)
        {
            std::ifstream file(path);

            if (!file)
                throw std::runtime_error("Failed to open shader");

            std::stringstream buffer;
            buffer << file.rdbuf();

            return buffer.str();
        }
};
class ShaderProgram
{
    public:
        GLuint program;
        ShaderProgram(GLenum type, const char* path)
        {
          Shader shader(type, path);
          link(&shader, nullptr);
        }
        ShaderProgram(const char* vertPath, const char* fragPath)
        {
          Shader vertShader(GL_VERTEX_SHADER, vertPath);
          Shader fragShader(GL_FRAGMENT_SHADER, fragPath);
          link(&vertShader, &fragShader);
        }
        ~ShaderProgram() {  glDeleteProgram(program);  }
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        void bind()  {  glUseProgram(program); }
    private:
        void link( const Shader* vertex, const Shader* fragment)
        {
            program = glCreateProgram();
            glAttachShader(program, vertex->shader);
            if ( fragment ) glAttachShader(program, fragment->shader);
            glLinkProgram(program);
            GLint success;
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "[SHADER LINK ERROR] " << infoLog << "\n";
            }
        }
};

class ComputeProgram
{
    public:
        GLuint program;
        ComputeProgram(GLenum type, const char* path)
        {
          Shader shader(type, path);
          link(&shader, nullptr);
        }
        ComputeProgram(const char* vertPath, const char* fragPath)
        {
          Shader vertShader(GL_VERTEX_SHADER, vertPath);
          Shader fragShader(GL_FRAGMENT_SHADER, fragPath);
          link(&vertShader, &fragShader);
        }
        ~ComputeProgram() {  glDeleteProgram(program);  }
        ComputeProgram(const ComputeProgram&) = delete;
        ComputeProgram& operator=(const ComputeProgram&) = delete;
        void bind()  {  glUseProgram(program); }
    private:
        void link( const Shader* vertex, const Shader* fragment)
        {
            program = glCreateProgram();
            glAttachShader(program, vertex->shader);
            if ( fragment ) glAttachShader(program, fragment->shader);
            glLinkProgram(program);
            GLint success;
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "[SHADER LINK ERROR] " << infoLog << "\n";
            }
        }
};

class Texture
{
public:
    GLuint id;
    Texture(const char* path)
    {
        glGenTextures(1, &id);

        glBindTexture(GL_TEXTURE_2D, id);
        int width, height, channels;

        unsigned char* pixels = stbi_load( path, &width, &height, &channels, 4 );
        if (!pixels)   {std::cout << "Failed to load " << path << '\n'; return;}
        glTexImage2D(  GL_TEXTURE_2D, 0, GL_RGBA,  width,  height,  0,  GL_RGBA,  GL_UNSIGNED_BYTE,  pixels  );
        stbi_image_free(pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    void setFilter(GLint min, GLint mag)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
    }
    void setWrap(GLint s, GLint t)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );
    }
    ~Texture() { glDeleteTextures(1, &id); }
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    void bind(){ glBindTexture(GL_TEXTURE_2D, id); }
};


#endif