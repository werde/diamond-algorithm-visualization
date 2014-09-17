#include "shaders.h"
GLuint LoadShaders(char * vertex_file_path, char * fragment_file_path){
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    char *vertex_shader_string;
    char *fragment_shader_string;
    // Read the Vertex Shader code from the file
    vertex_shader_string = getShaderString(vertex_file_path, 0);
    //printf("vertex_shader_string%s\n", vertex_shader_string);
    // Read the Fragment Shader code from the file
    fragment_shader_string = getShaderString(fragment_file_path, 1);
    //printf("fragment_shader_string %d \n%s", strlen(fragment_shader_string), fragment_shader_string);
    // Compile Vertex Shader
    printf("\nCompiling shader : %s\n", vertex_file_path);
    glShaderSource(VertexShaderID, 1, &vertex_shader_string , NULL);
    glCompileShader(VertexShaderID);

    {
        GLint success;
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE) {
            char log[1024];
            glGetShaderInfoLog(VertexShaderID, sizeof(log), 0, log);
            printf("vert shader compile info: \n %s \n", log);
            glDeleteShader(VertexShaderID);
            //glDeleteProgram(shader);
            //shader = 0;
            return 1;
        }
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = fragment_shader_string;
    glShaderSource(FragmentShaderID, 1, &fragment_shader_string , NULL);
    glCompileShader(FragmentShaderID);

    {
        GLint success;
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE) {
            char log[1024];
            glGetShaderInfoLog(FragmentShaderID, sizeof(log), 0, log);
            printf("fragment shader compile info: \n %s \n", log);
            glDeleteShader(FragmentShaderID);
            //glDeleteProgram(shader);
            //shader = 0;
            return 1;
        }
    }

    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

char* getShaderString(char *path, int frag_flag) {

    // Read the Vertex Shader code from the file
    long file_size;
    char *string;
    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    printf("file size %d \n", file_size);
    rewind(file);
    string = malloc((file_size+1) * sizeof(char));

    fread(string, sizeof(char),file_size, file);

    string[file_size] = '\0';
    fclose(file);

    return string;
}
