#include <stdio.h>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

void main_DS_and_Algo();
void main_cplusplus();
const float toRadians = (float) 3.14159265 / 180.0f;  // (pie / 180)

Window mainWindow;
std::vector<Mesh *> meshList; // Vector of Meshes
std::vector<Shader> shaderList; //Vector of Shaders

//Vertex Shader File
static const char * vShader = "Shaders/shader.vert";
// Fragment Shader File
static const char * fShader = "Shaders/shader.frag";

void createObjects() // Pyramid
{
	// Index/Element Array for pyramid.
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = { 
	-1.0f, -1.0f, 0.0f,
	 0.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	createObjects();
	CreateShaders();

	/******* For C++ and DS Programming  *****/
	// 1.) Entry Point for DS and Algo Programming
	main_DS_and_Algo();

	// 2.) Entry Point for C++ Programming
	//main_cplusplus();

	/***************************************/

	GLuint uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(),  0.1f, 100.0f);

	//Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		//Get and Handle user Input Events
		glfwPollEvents();

		//Clear Window
		glClearColor(0.0f,0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		glm::mat4 model(1.0f); // Identity Matrix.
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f)); // It will happen first. Always reverse order. Last operation happens first.

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f); // Identity Matrix.
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f)); // It will happen first. Always reverse order. Last operation happens first.

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}

