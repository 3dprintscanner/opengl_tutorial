#include <cstdlib>
#include <iostream>
#include "GL\glew.h"
#include "SDL.h"
#include "shader_utils.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "SDL_image.h"
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2.lib")
using namespace std;


GLuint program;
GLint attribute_coord2d, attribute_v_colour, uniform_fade, attribute_coord3d, uniform_m_transform, uniform_mvp, attribute_texcoord;
GLuint vbo_triangle, vbo_triangle_colours;
GLuint vbo_cube_vertices, vbo_cube_colors, ibo_cube_elements;
GLuint texture_id, program_id,vbo_tex_coords;
GLint uniform_mytexture;
int screen_width= 800, screen_height = 600;

//struct attributes {
//
//	GLfloat coord3d[3];
//	GLfloat v_color[3];
//};


//const char* version;
//int *profile;
//int SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
//if (profile == SDL_GL_CONTEXT_PROFILE_ES){
//	version = "#version 100\n";
//}
//else {
//	version = "#version 120\n";
//}
//
//const GLchar* sources[] = {version,source};
//
//glShaderSource(res, 2, sources, NULL);

bool init_resources(void){
	/*
	GLfloat triangle_vertices[] = {
	0.0, 0.8,
	-0.8, -0.8,
	0.8, -0.8,
	};

	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	GLfloat triangle_colors[] = {
	1.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 0.0, 0.0,
	};

	glGenBuffers(1, &vbo_triangle_colours);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);

	GLfloat triangle_attributes[] = {

	0.0, 0.8, 1.0, 1.0, 1.0,
	-0.8, -0.8, 0.0, 0.0, 1.0,
	0.8, -0.8, 1.0, 0.0, 0.0,
	};

	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);*/

	//struct attributes new_triangle_attributes[] = {
	//	{ { 0.0, 0.8, 0.0 }, { 1.0, 1.0, 0.0 } },
	//	{ { -0.8, -0.8, 0.0 }, { 0.0, 0.0, 1.0 } },
	//	{ { 0.8, -0.8, 0.0 }, { 1.0, 0.0, 0.0 } },
	//};

	//glGenBuffers(1, &vbo_triangle);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(new_triangle_attributes), new_triangle_attributes, GL_STATIC_DRAW);
	SDL_Surface* res_texture = IMG_Load("res_texture.png");

	if (res_texture == NULL){
		cerr << "Could not load image" << res_texture << endl;
		return false;
	}

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res_texture->w, res_texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, res_texture->pixels);
	SDL_FreeSurface(res_texture);

	//GLfloat cube_vertices[] = {
	//	//front
	//	-1.0, -1.0, 1.0,
	//	1.0, -1.0, 1.0,
	//	1.0, 1.0, 1.0,
	//	-1.0, 1.0, 1.0,
	//	//back
	//	-1.0, -1.0, -1.0,
	//	1.0, -1.0, -1.0,
	//	1.0, 1.0, -1.0,
	//	-1.0, 1.0, -1.0,
	//};

	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// top
		-1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
		// back
		1.0, -1.0, -1.0,
		-1.0, -1.0, -1.0,
		-1.0, 1.0, -1.0,
		1.0, 1.0, -1.0,
		// bottom
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0, 1.0,
		-1.0, -1.0, 1.0,
		// left
		-1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,
		-1.0, 1.0, 1.0,
		-1.0, 1.0, -1.0,
		// right
		1.0, -1.0, 1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		1.0, 1.0, 1.0,
	};

	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_cube_vertices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	GLfloat cube_colors[] = {
		//front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		//back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,

	};

	glGenBuffers(1, &vbo_cube_colors);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_cube_colors);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

	//GLushort cube_elements[] = {
	//	//front
	//	0, 1, 2,
	//	2, 3, 0,
	//	//top
	//	1, 5, 6,
	//	6, 2, 1,
	//	//back
	//	7, 6, 5,
	//	5, 4, 7,
	//	//bottom
	//	4, 0, 3,
	//	3, 7, 4,
	//	//left
	//	4, 5, 1,
	//	1, 0, 4,
	//	//right
	//	3, 2, 6,
	//	6, 7, 3,
	//};

	GLushort cube_elements[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// left
		16, 17, 18,
		18, 19, 16,
		// right
		20, 21, 22,
		22, 23, 20,
	};



	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);


	GLfloat cube_texcoords[2*4*6] = {
	
		0.0,0.0,
		1.0,0.0,
		1.0,1.0,
		0.0,1.0,
	};

	for (int i = 1; i < 6; i++)
		memcpy(&cube_texcoords[i * 4 * 2], &cube_texcoords[0], 2 * 4 * sizeof(GLfloat));

	glGenBuffers(1, &vbo_tex_coords);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_coords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);

	//GLint compile_ok = GL_FALSE,
	//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//const char *vs_source =
	//#ifdef GL_ES_VERSION_2_0
	//	"#version 100\n"  // OpenGL ES 2.0
	//#else
	//	"#version 120\n"  // OpenGL 2.1
	//#endif
	//	"attribute vec2 coord2d;                  "
	//	"void main(void) {                        "
	//	"  gl_Position = vec4(coord2d, 0.0, 1.0); "
	//	"}";
	//glShaderSource(vs, 1, &vs_source, NULL);
	//glCompileShader(vs);
	//glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	//if (!compile_ok){
	//	cerr << "Error in Vertex Shader" << endl;
	//	return false;
	//}

	//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//const char *fs_source =
	//#ifdef GL_ES_VERSION_2_0
	//	"#version 100\n"  // OpenGL ES 2.0
	//#else
	//	"#version 120\n"  // OpenGL 2.1
	//#endif
	//	"void main(void) {        "
	//	"  gl_FragColor[0] = gl_FragCoord.x/640.0; "
	//	"  gl_FragColor[1] = gl_FragCoord.y/480.0; "
	//	"  gl_FragColor[2] = 1.0; "
	//	"}";

	//
	//glShaderSource(fs, 1, &fs_source, NULL);
	//glCompileShader(fs);
	//glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	//if (!compile_ok){
	//	cerr << "Error in Fragment Shader" << endl;
	//	return false;
	//}
	GLint link_ok = GL_FALSE;
	GLuint vs, fs;

	if ((vs = create_shader("triangle.v.glsl", GL_VERTEX_SHADER)) == 0) return false;
	if ((fs = create_shader("triangle.f.glsl", GL_FRAGMENT_SHADER)) == 0) return false;

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok){
		cerr << "Error in GLinkProgram" << endl;
		print_log(program);
		return false;
	}
	/*const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord2d == -1){
	cerr << "Could not find attribute" << endl;
	return false;
	}*/

	//const char* v_attribute_name = "v_color";
	//attribute_v_colour = glGetAttribLocation(program, v_attribute_name);

	//if (attribute_v_colour == -1){
	//	cerr << "Could not bind attribute " << v_attribute_name << endl;
	//	return false;
	//}

	//const char* uniform_name = "fade";	const char* uniform_tex_name = "mytexture";

	//uniform_fade = glGetUniformLocation(program, uniform_name);
	//if (uniform_fade == -1){
	//	cerr << "Could not bind uniform fade " << uniform_name << endl;
	//	return false;
	//}
	const char* uniform_tex_name = "mytexture";
	uniform_mytexture = glGetUniformLocation(program, uniform_tex_name);
	if (uniform_mytexture == -1){
		cerr << "Could not bind uniform mytexture " << uniform_tex_name << endl;
		return false;
	}

	const char* uniform_m4_name = "m_transform";
	uniform_m_transform = glGetUniformLocation(program, uniform_m4_name);
	if (uniform_m_transform == -1){
		cerr << "Could not bind uniform fade " << uniform_m4_name << endl;
		return false;
	}

	const char* uniform_mvp_name = "mvp";
	uniform_mvp = glGetUniformLocation(program, uniform_mvp_name);
	if (uniform_mvp == -1){
		cerr << "Could not bind uniform fade " << uniform_mvp_name << endl;
		return false;
	}

	const char* attribute_name_3d = "coord3d";
	attribute_coord3d = glGetAttribLocation(program, attribute_name_3d);

	if (attribute_coord3d == -1){
		cerr << "Could not bind attribute " << attribute_name_3d << endl;
		return false;

	}

	const char* tex_attribute_name = "texcoord";
	attribute_texcoord = glGetAttribLocation(program, tex_attribute_name);
	if (attribute_texcoord == -1){
		cerr << "Could not bind attribute" << tex_attribute_name << endl;
		return false;
	}

	return true;
}

void render(SDL_Window* window){
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	//glEnableVertexAttribArray(attribute_coord2d);
	//	
	//glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//glEnableVertexAttribArray(attribute_v_colour);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colours);
	//glVertexAttribPointer(attribute_v_colour, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glEnableVertexAttribArray(attribute_coord2d);
	//glEnableVertexAttribArray(attribute_v_colour);
	//glEnableVertexAttribArray(attribute_coord3d);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	//glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),0);
	//glVertexAttribPointer(attribute_v_colour, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2* sizeof(GLfloat)));
	//glUniform1f(uniform_fade, 0.1);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(uniform_mytexture, 0);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glEnableVertexAttribArray(attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);


	//glEnableVertexAttribArray(attribute_v_colour);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	//glVertexAttribPointer(attribute_v_colour, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(attribute_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_coords);
	glVertexAttribPointer(attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size; glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

		//glVertexAttribPointer(attribute_v_colour, 3, GL_FLOAT, GL_FALSE,sizeof(struct attributes), (GLvoid*)(3* sizeof(GLfloat)));
	//glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes),0);



	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDisableVertexAttribArray(attribute_coord2d);
	//glEnableVertexAttribArray(attribute_v_colour);
	glDisableVertexAttribArray(attribute_coord3d);
	glDisableVertexAttribArray(attribute_v_colour);

	SDL_GL_SwapWindow(window);
};

void free_resources(){
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo_triangle);
	glDeleteBuffers(1, &vbo_cube_vertices);
	//glDeleteBuffers(1, &vbo_cube_colors);
	glDeleteBuffers(1, &ibo_cube_elements);
	glDeleteTextures(1, &texture_id);

};

void logic(){
	/*float cur_fade = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5) / 2 + 0.5;
	glUseProgram(program);
	glUniform1f(uniform_fade, cur_fade);*/

	float move = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5);
	float angle = SDL_GetTicks() / 1000.0 * 45;
	glm::vec3 axis_z(0, 0, 1);
	glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(move, 0.0, 0.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_z);

	glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, glm::value_ptr(m_transform));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));

	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 projection = glm::perspective(45.0f, 1.0f*screen_width / screen_height, 0.1f, 10.0f);

	glm::vec3 axis_y(0, 1, 0);

	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);

	glm::mat4 mvp = projection * view * model * anim;

	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
}
void onResize(int width, int height){
	screen_width = width;
	screen_height = height;
	glViewport(0, 0, screen_width, screen_height);
}
void mainLoop(SDL_Window* window){
	while (true){
		SDL_Event ev;
		while (SDL_PollEvent(&ev)){
			if (ev.type == SDL_QUIT)
				return;
			if (ev.type == SDL_WINDOWEVENT && ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
				onResize(ev.window.data1, ev.window.data2);
			}
		}
		logic();
		render(window);
	}
}

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("My First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL){
		cerr << "Error: can't create window" << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	if (SDL_GL_CreateContext(window) == NULL){
		cerr << "Error: SDL_GL_Createcontext" << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	GLenum glew_status = glewInit();

	if (!GLEW_VERSION_2_0){
		cerr << "Error: your graphics card does not support OpenGL 2.0" << endl;
		return EXIT_FAILURE;
	}

	if (glew_status != GLEW_OK){
		cerr << "Error: GlewInit " << glewGetErrorString(glew_status) << endl;
		return EXIT_FAILURE;
	}

	if (!init_resources()) return EXIT_FAILURE;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mainLoop(window);

	free_resources();

	return EXIT_SUCCESS;

}