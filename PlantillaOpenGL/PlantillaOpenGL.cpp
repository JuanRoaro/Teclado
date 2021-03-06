// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

//Declaramos apuntador de ventana
GLFWwindow *window;

float xTriangulo = 0.3f;
float yTriangulo = 0.0f;
float anguloTriangulo = 0.0f;
float velocidadAngular = 360.0f;

float anguloTrayectoria = 2.0;

float xCuadrado = -0.3f;
float yCuadrado = 0.0f;

float velocidad = 1.0f;
float aceleracion = 0.2f;
float desaceleracion = 0.2f;
float velocidadActual = 0.0f;

float tiempoAnterior = 0.0f;
float tiempoActual = 0.0f;
float tiempoDiferencial = 0.0f;

bool colision = false;

void moverTriangulo() {
	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);

	if (estadoTeclaDerecha == GLFW_PRESS) {
		anguloTriangulo -= velocidadAngular * tiempoDiferencial;
		if (anguloTriangulo < 0) {
			anguloTriangulo += 360;
			if (anguloTriangulo >= 90) {
				cout << ">= 90";
			}
		}
	}
	if (estadoTeclaIzquierda == GLFW_PRESS) {
		anguloTriangulo += velocidadAngular * tiempoDiferencial;
		if (anguloTriangulo > 360) {
			anguloTriangulo -= 360;
		}
	}
	if (estadoTeclaArriba == GLFW_PRESS) {
		anguloTrayectoria = anguloTriangulo;
		if (velocidadActual <= velocidad) {
			velocidadActual += aceleracion * tiempoDiferencial;
		}
		else if (velocidadActual >= 0) {
			aceleracion -= aceleracion * tiempoDiferencial;
			if (velocidadActual < 0) {
				velocidadActual = 0.0f;
			}
		}
	}

	xTriangulo += cos((anguloTrayectoria + 90.0f) * 3.14159f / 180.0f)*velocidadActual*tiempoDiferencial;

	if (xTriangulo < -1.05f)
	{
		xTriangulo += 2.05;
	}
	else if (xTriangulo > 1.05f)
	{
		xTriangulo += -2.05;
	}

	yTriangulo += sin((anguloTrayectoria + 90.0f) * 3.14159f / 180.0f)*velocidadActual*tiempoDiferencial;

	if (yTriangulo < -1.05f)
	{
		yTriangulo += 2.05;
	}
	else if (yTriangulo > 1.05f)
	{
		yTriangulo += -2.05;
	}
}

void moverCuadrado() {
	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_D);
	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_A);
	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_W);
	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_S);

	if (estadoTeclaDerecha == GLFW_PRESS) {
		xCuadrado += velocidad * tiempoDiferencial;
	}
	if (estadoTeclaIzquierda == GLFW_PRESS) {
		xCuadrado -= velocidad * tiempoDiferencial;
	}
	if (estadoTeclaArriba == GLFW_PRESS) {
		yCuadrado += velocidad * tiempoDiferencial;
	}
	if (estadoTeclaAbajo == GLFW_PRESS) {
		yCuadrado -= velocidad * tiempoDiferencial;
	}
}


void dibujarCuadrado() {
	glPushMatrix();

	//transformaciones
	glTranslatef(xCuadrado, yCuadrado, 0.0f);


	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0);
	glVertex3f(-0.1, 0.1, 0);
	glVertex3f(0.1, 0.1, 0);
	glVertex3f(0.1, -0.1, 0);
	glVertex3f(-0.1, -0.1, 0);
	glEnd();
	glPopMatrix();
}

void dibujarTraingulo() {
	glPushMatrix();

	//transformaciones
	glTranslatef(xTriangulo, yTriangulo, 0.0f);
	glRotatef(anguloTriangulo, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	glColor3f(0.8, 0, 0);
	glVertex3f(0, 0.08, 0);
	glVertex3f(0.05, -0.08, 0);
	glVertex3f(-0.05, -0.08, 0);
	glEnd();
	glPopMatrix();
}

void dibujar() {
	dibujarTraingulo();
	dibujarCuadrado();
}

int n = 0;

void checarColisiones() {
	//si el triangulo colisiona con el cuadrado
	colision = (xTriangulo - 0.2 < xCuadrado + 0.1 && xTriangulo + 0.2 > xCuadrado - 0.1) && (yTriangulo - 0.2 < yCuadrado + 0.1 && yTriangulo + 0.2 > yCuadrado - 0.1);

	if (colision) {
		cout << "Colision" << n++ << endl;
	}

}

void actualizar() {
	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;
	tiempoAnterior = tiempoActual;

	moverTriangulo();
	moverCuadrado();
	checarColisiones();
}

void teclado_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo += velocidad;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo -= velocidad;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo += velocidad;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo -= velocidad;
	}
}

int main()
{


	//si no se pudo inicializar glfw terminamos ejecución
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//si se pudo iniciar GLFW entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//UNa vez establecido el contexto activamos funciones modernas (CPU/GPU)
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//glfwSetKeyCallback(window, teclado_callback);

	tiempoAnterior = glfwGetTime();

	//Cilco de dibijo (Draw loop)
	while (!glfwWindowShouldClose(window)) {


		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Esctablece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

