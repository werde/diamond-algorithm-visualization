#include "terrain.h"

struct _TTerrain* tterrain_init(GLfloat* vertex_buffer_data, GLfloat* uv_buffer_data, GLuint* tex){
    int i;
    struct _TTerrain *tterrain;
    tterrain = malloc(sizeof(struct _TTerrain));
    tterrain->vertex_buffer_data = vertex_buffer_data;
    tterrain->uv_buffer_data = malloc(2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*6*sizeof(GLfloat));

    for (i = 0; i < (2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)); i++) {
        tterrain->uv_buffer_data[i*6] = uv_buffer_data[0];
        tterrain->uv_buffer_data[i*6 + 1] = uv_buffer_data[1];
        tterrain->uv_buffer_data[i*6 + 2] = uv_buffer_data[2];
        tterrain->uv_buffer_data[i*6 + 3] = uv_buffer_data[3];
        tterrain->uv_buffer_data[i*6 + 4] = uv_buffer_data[4];
        tterrain->uv_buffer_data[i*6 + 5] = uv_buffer_data[5];
    }




    tterrain->texture = tex;

    glGenBuffers(1, &(tterrain->vertexbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, tterrain->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, 2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*9*sizeof(GLfloat), tterrain->vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(tterrain->uvbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, tterrain->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, 2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*6*sizeof(GLfloat), tterrain->uv_buffer_data, GL_STATIC_DRAW);
	return tterrain;
};

GLvoid tterrain_draw(struct _TTerrain* tterrain){

    GLuint TextureID;
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *tterrain->texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, tterrain->vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_TRUE,           // normalized?
        3*sizeof(GLfloat),                  // stride
        (void*)0            // array buffer offset
    );
    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, tterrain->uvbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size : U+V => 2
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*3); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
};
