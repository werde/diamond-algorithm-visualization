#include "polygon.h"

struct _TPolygon* tpolygon_init(GLfloat vertex_buffer_data[9], GLfloat uv_buffer_data[6], GLuint* tex){
    struct _TPolygon *tpolygon;
    tpolygon = malloc(sizeof(struct _TPolygon));
    tpolygon->vertex_buffer_data = vertex_buffer_data;
    tpolygon->uv_buffer_data = uv_buffer_data;
    tpolygon->texture = tex;

    glGenBuffers(1, &(tpolygon->vertexbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, tpolygon->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), tpolygon->vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(tpolygon->uvbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, tpolygon->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, 6*sizeof(GLfloat), tpolygon->uv_buffer_data, GL_STATIC_DRAW);
	return tpolygon;
};

GLvoid tpolygon_draw(struct _TPolygon* tpolygon){

    GLuint TextureID;
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *tpolygon->texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, tpolygon->vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, tpolygon->uvbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size : U+V => 2
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
};
