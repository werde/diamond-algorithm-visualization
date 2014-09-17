#include "skybox.h"

GLfloat skybox_vertex_buffer_data[] = {
    -100.0f,-100.0f,-100.0f, // triangle 1 : begin
    -100.0f,-100.0f, 100.0f,
    -100.0f, 100.0f, 100.0f, // triangle 1 : end
    100.0f, 100.0f,-100.0f, // triangle 2 : begin
    -100.0f,-100.0f,-100.0f,
    -100.0f, 100.0f,-100.0f, // triangle 2 : end
    100.0f,-100.0f, 100.0f,
    -100.0f,-100.0f,-100.0f,
    100.0f,-100.0f,-100.0f,
    100.0f, 100.0f,-100.0f,
    100.0f,-100.0f,-100.0f,
    -100.0f,-100.0f,-100.0f,
    -100.0f,-100.0f,-100.0f,
    -100.0f, 100.0f, 100.0f,
    -100.0f, 100.0f,-100.0f,
    100.0f,-100.0f, 100.0f,
    -100.0f,-100.0f, 100.0f,
    -100.0f,-100.0f,-100.0f,
    -100.0f, 100.0f, 100.0f,
    -100.0f,-100.0f, 100.0f,
    100.0f,-100.0f, 100.0f,
    100.0f, 100.0f, 100.0f,
    100.0f,-100.0f,-100.0f,
    100.0f, 100.0f,-100.0f,
    100.0f,-100.0f,-100.0f,
    100.0f, 100.0f, 100.0f,
    100.0f,-100.0f, 100.0f,
    100.0f, 100.0f, 100.0f,
    100.0f, 100.0f,-100.0f,
    -100.0f, 100.0f,-100.0f,
    100.0f, 100.0f, 100.0f,
    -100.0f, 100.0f,-100.0f,
    -100.0f, 100.0f, 100.0f,
    100.0f, 100.0f, 100.0f,
    -100.0f, 100.0f, 100.0f,
    100.0f,-100.0f, 100.0f
};

GLfloat skybox_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};
GLvoid skyboxLoad(GLvoid){


    loadTexture("./img/skybox_tex.bmp", &Skybox.top);
    Skybox.vertices = skybox_vertex_buffer_data;
    Skybox.texCoords = skybox_uv_buffer_data;

    glGenBuffers(1, &Skybox.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Skybox.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertex_buffer_data), Skybox.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &Skybox.UVbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Skybox.UVbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_uv_buffer_data), Skybox.texCoords, GL_STATIC_DRAW);
}


GLvoid skyboxDraw(GLvoid) {

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, Skybox.top);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    //glUniform1i(TextureID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, Skybox.vertexBuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, Skybox.UVbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size : U+V => 2
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3*sizeof(skybox_vertex_buffer_data)); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
