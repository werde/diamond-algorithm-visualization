#include "terrain.h"

struct _TTerrain* tterrain_init(GLfloat* vertex_buffer_data, GLfloat* uv_buffer_data, GLuint* tex){
    int i;
    struct _TTerrain *tterrain;
    tterrain = malloc(sizeof(struct _TTerrain));
    tterrain->vertex_buffer_data = vertex_buffer_data;
    tterrain->uv_buffer_data = malloc(2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*6*sizeof(GLfloat));
    tterrain->normal_buffer_data = malloc(2*(SQUARE_SIZE)*(SQUARE_SIZE-1)*9*sizeof(GLfloat));
    //uv data
    for (i = 0; i < (2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)); i++) {
        tterrain->uv_buffer_data[i*6] = uv_buffer_data[0];
        tterrain->uv_buffer_data[i*6 + 1] = uv_buffer_data[1];
        tterrain->uv_buffer_data[i*6 + 2] = uv_buffer_data[2];
        tterrain->uv_buffer_data[i*6 + 3] = uv_buffer_data[3];
        tterrain->uv_buffer_data[i*6 + 4] = uv_buffer_data[4];
        tterrain->uv_buffer_data[i*6 + 5] = uv_buffer_data[5];
    }
    printf(" filled terraing UV data\n");
    //normals
    vec4 v1, v2, v3, edge1, edge2, normal;
    float normals[3*2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)];
    for (i = 0; i < (2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)); i++) {
        v1.x = vertex_buffer_data[i*9+0];
        v1.y = vertex_buffer_data[i*9+1];;
        v1.z = vertex_buffer_data[i*9+2];;
        v1.w = 0;

        v2.x = vertex_buffer_data[i*9+3];
        v2.y = vertex_buffer_data[i*9+4];;
        v2.z = vertex_buffer_data[i*9+5];;
        v2.w = 0;

        v3.x = vertex_buffer_data[i*9+6];
        v3.y = vertex_buffer_data[i*9+7];;
        v3.z = vertex_buffer_data[i*9+8];;
        v3.w = 0;

        edge1 = substractvec4(v2, v1);
        edge2 = substractvec4(v3, v1);
        normal = crossvec4(edge1, edge2);
        normalizevec4(&normal);
        normals[3*i+0] = normal.m[0];
        normals[3*i+1] = normal.m[1];
        normals[3*i+2] = normal.m[2];
    }
    int tr_index, tr_index2;
    float vertex_normals[3*SQUARE_SIZE*SQUARE_SIZE];
    for (i = 0; i < (SQUARE_SIZE)*(SQUARE_SIZE); i++) {
        tr_index = 2*(i-SQUARE_SIZE) - 2*(i/SQUARE_SIZE) + 1;
        tr_index2 = 2*i - 2*(i/SQUARE_SIZE) - 2;
        normals[3*tr_index+0] + normals[3*tr_index+3] + normals[3*tr_index+6];
        normals[3*tr_index+1] + normals[3*tr_index+4] + normals[3*tr_index+7];
        normals[3*tr_index+2] + normals[3*tr_index+5] + normals[3*tr_index+8];
        normals[3*tr_index2+0] + normals[3*tr_index2+3] + normals[3*tr_index2+6];
        normals[3*tr_index2+1] + normals[3*tr_index2+4] + normals[3*tr_index2+7];
        normals[3*tr_index2+2] + normals[3*tr_index2+5] + normals[3*tr_index2+8];

        vertex_normals[3*i + 0] = 0;
        vertex_normals[3*i + 1] = 0;
        vertex_normals[3*i + 2] = 0;

        if ((i>SQUARE_SIZE)&&((i%SQUARE_SIZE) != 0)) {
            vertex_normals[3*i + 0] += normals[3*tr_index+0];
            vertex_normals[3*i + 1] += normals[3*tr_index+1];
            vertex_normals[3*i + 2] += normals[3*tr_index+2];
        }
        if ((i>SQUARE_SIZE)&&(((i+1)%SQUARE_SIZE)!=0)){
            vertex_normals[3*i + 0] += normals[3*tr_index+3] + normals[3*tr_index+6];
            vertex_normals[3*i + 1] += normals[3*tr_index+4] + normals[3*tr_index+7];
            vertex_normals[3*i + 2] += normals[3*tr_index+5] + normals[3*tr_index+8];
        }
        if ((i > (SQUARE_SIZE*SQUARE_SIZE - SQUARE_SIZE))&&(((i+1)%SQUARE_SIZE)!=0)){
            vertex_normals[3*i + 0] += normals[3*tr_index2+6];
            vertex_normals[3*i + 1] += normals[3*tr_index2+7];
            vertex_normals[3*i + 2] += normals[3*tr_index2+8];
        }
        if (((i%SQUARE_SIZE) != 0)&&(i > (SQUARE_SIZE*SQUARE_SIZE - SQUARE_SIZE))){
           vertex_normals[3*i + 0] += normals[3*tr_index2+0] + normals[3*tr_index2+3];
           vertex_normals[3*i + 1] += normals[3*tr_index2+1] + normals[3*tr_index2+4];
           vertex_normals[3*i + 2] += normals[3*tr_index2+2] + normals[3*tr_index2+5];
        }
    }

    int x, y, bigN, k00, k01, k10, k11;
    for (i = 0; i < 2*((SQUARE_SIZE-1)*(SQUARE_SIZE-1));i++) {

        bigN = (i/2);
        x = bigN % (SQUARE_SIZE-1);
        y = bigN /(SQUARE_SIZE-1);
        k00 = 3*(x + (SQUARE_SIZE-1)*y);
        k01 = 3*(x + (SQUARE_SIZE-1)*(y+1));
        k10 = 3*(x + 1 + (SQUARE_SIZE-1)*y);
        k11 = 3*(x + 1 + (SQUARE_SIZE-1)*(y+1));
        if ((i%2) == 0) {
            tterrain->normal_buffer_data[i*9+0] = -vertex_normals[k01+0];
            tterrain->normal_buffer_data[i*9+1] = -vertex_normals[k01+1];
            tterrain->normal_buffer_data[i*9+2] = -vertex_normals[k01+2];
            tterrain->normal_buffer_data[i*9+3] = -vertex_normals[k00+0];
            tterrain->normal_buffer_data[i*9+4] = -vertex_normals[k00+1];
            tterrain->normal_buffer_data[i*9+5] = -vertex_normals[k00+2];
            tterrain->normal_buffer_data[i*9+6] = -vertex_normals[k10+0];
            tterrain->normal_buffer_data[i*9+7] = -vertex_normals[k10+1];
            tterrain->normal_buffer_data[i*9+8] = -vertex_normals[k10+2];
        } else {
            tterrain->normal_buffer_data[i*9+0] = -vertex_normals[k01+0];
            tterrain->normal_buffer_data[i*9+1] = -vertex_normals[k01+1];
            tterrain->normal_buffer_data[i*9+2] = -vertex_normals[k01+2];
            tterrain->normal_buffer_data[i*9+3] = -vertex_normals[k11+0];
            tterrain->normal_buffer_data[i*9+4] = -vertex_normals[k11+1];
            tterrain->normal_buffer_data[i*9+5] = -vertex_normals[k11+2];
            tterrain->normal_buffer_data[i*9+6] = -vertex_normals[k10+0];
            tterrain->normal_buffer_data[i*9+7] = -vertex_normals[k10+1];
            tterrain->normal_buffer_data[i*9+8] = -vertex_normals[k10+2];
        }
    }
    printf("tterrain->normal_buffer_data    %f \n", tterrain->normal_buffer_data[2*((SQUARE_SIZE-1)*(SQUARE_SIZE-1)-1)*9+6]        );
    printf("tterrain->normal_buffer_data    %f \n", tterrain->normal_buffer_data[2*((SQUARE_SIZE-1)*(SQUARE_SIZE-1)-1)*9+7]        );
    printf("tterrain->normal_buffer_data    %f \n", tterrain->normal_buffer_data[2*((SQUARE_SIZE-1)*(SQUARE_SIZE-1)-1)*9+8]        );



    printf(" filled terrain normals data\n");
    //texture
    tterrain->texture = tex;
    //buffers
    glGenBuffers(1, &(tterrain->vertexbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, tterrain->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, 2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*9*sizeof(GLfloat), tterrain->vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(tterrain->uvbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, tterrain->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, 2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*6*sizeof(GLfloat), tterrain->uv_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(tterrain->normalbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, tterrain->normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, 2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*9*sizeof(GLfloat), tterrain->normal_buffer_data, GL_STATIC_DRAW);

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
        GL_FALSE,           // normalized?
        0,                  // stride
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
    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, tterrain->normalbuffer);
    glVertexAttribPointer(
        2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size of normals
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 2*(SQUARE_SIZE-1)*(SQUARE_SIZE-1)*3); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
};
