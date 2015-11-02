#include <cstdlib>
#include <iostream>
#include "GL\glew.h"
#include "SDL.h"
#include "shader_utils.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2.lib")
using namespace std;


GLuint program;
GLint attribute_coord2d, attribute_v_colour, uniform_fade, attribute_coord3d, uniform_m_transform;
GLuint vbo_triangle, vbo_triangle_colours;


struct attributes {

	GLfloat coord3d[3];
	GLfloat v_color[3];
};


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

	struct attributes new_triangle_attributes[] = {
		{ { 0.0, 0.8, 0.0 }, { 1.0, 1.0, 0.0 } },
		{ { -0.8, -0.8, 0.0 }, { 0.0, 0.0, 1.0 } },
		{ { 0.8, -0.8, 0.0 }, { 1.0, 0.0, 0.0 } },
	};

	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(new_triangle_attributes), new_triangle_attributes, GL_STATIC_DRAW);

	

	
	
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

	const char* v_attribute_name = "v_color";
	attribute_v_colour = glGetAttribLocation(program, v_attribute_name);

	if (attribute_v_colour == -1){
		cerr << "Could not bind attribute " << v_attribute_name << endl;
		return false;
	}

	const char* uniform_name = "fade";
	uniform_fade = glGetUniformLocation(program, uniform_name);
	if (uniform_fade == -1){
		cerr << "Could not bind uniform fade " << uniform_name << endl;
		return false;
	}

	const char* uniform_m4_name = "m_transform";
	uniform_m_transform = glGetUniformLocation(program, uniform_m4_name);
	if (uniform_m_transform == -1){
		cerr << "Could not bind uniform fade " << uniform_m4_name << endl;
		return false;
	}

	const char* attribute_name_3d = "coord3d";
	attribute_coord3d = glGetAttribLocation(program, attribute_name_3d);

	if (attribute_coord3d == -1){
		cerr << "Could not bind attribute " << attribute_name_3d << endl;
		return false;

	}

	return true;
}

void render(SDL_Window* window){
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
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
	glEnableVertexAttribArray(attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	//glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),0);
	//glVertexAttribPointer(attribute_v_colour, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2* sizeof(GLfloat)));
	//glUniform1f(uniform_fade, 0.1);
	glVertexAttribPointer(attribute_v_colour, 3, GL_FLOAT, GL_FALSE,sizeof(struct attributes), (GLvoid*)(3* sizeof(GLfloat)));
	glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes),0);


	

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisableVertexAttribArray(attribute_coord2d);
	glEnableVertexAttribArray(attribute_v_colour);

	SDL_GL_SwapWindow(window);
};

void free_resources(){
	glDeleteProgram(program); 
	glDeleteBuffers(1, &vbo_triangle);
};

void logic(){
	float cur_fade = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5) / 2 + 0.5;
	glUseProgram(program);
	glUniform1f(uniform_fade, cur_fade);

	float move = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5);
	float angle = SDL_GetTicks() / 1000.0 * 45;
	glm::vec3 axis_z(0, 0, 1);
	glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(move, 0.0, 0.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_z);

	glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
}

void mainLoop(SDL_Window* window){
	while (true){
		SDL_Event ev;
		while (SDL_PollEvent(&ev)){
			if (ev.type == SDL_QUIT)
				return;
		}
		logic();
		render(window);
	}
}

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("My First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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

	mainLoop(window);

	free_resources();

	return EXIT_SUCCESS;

}