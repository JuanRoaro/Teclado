// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float xTriangulo = 0.0f;
float yTriangulo = 0.0f;
float velocidad = 0.2f;

void dibujarTriangulo() {

	//Utilizar matriz identidad
	glPushMatrix();
	//Transformaciones
	glTranslatef(xTriangulo, yTriangulo, 0.0f);

	//Dibujar vertices
	glBegin(GL_TRIANGLES);
		glColor3f(1, 0.534f, 0.5647f);
		glVertex3f(0, .2, 0);
		glVertex3f(-0.2, -0.2, 0);
		glVertex3f(0.2, 0.2, 0);

		glEnd();

		//Soltar matriz
		glPopMatrix();
}


void dibujar() {
	dibujarTriangulo();
}

void actualizar() {

}

void teclado_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		xTriangulo += velocidad;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		xTriangulo -= velocidad;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		yTriangulo += velocidad;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		yTriangulo -= velocidad;
	}
}

int main()
{
	GLFWwindow * window;

	//Si no se pudo iniciar glfw
	//entonces inicializamos en la ventana
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Si se pudo iniciar GLFW
	//entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana
	//Entonces terminamos la ejecucion

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas (gpu / cpu)
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	glfwSetKeyCallback(window, teclado_callback);


	//Ciclo de dibujo (Draw Loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region del dibujo
		glViewport(0, 0, 1024, 768);
		//Establecer el color del borrado
		glClearColor(0.9, 0.2, 0.2, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		

		//Cambiar Buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

