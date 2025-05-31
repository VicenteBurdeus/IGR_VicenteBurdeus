#include "Entorno.h"
#include <stdint.h>
#include <iostream>

using namespace std;
using namespace cb;



Entorno::Entorno() {
	// Constructor por defecto
	// Inicializa las texturas y listas de render
	init();
}

//carga las texturas
void Entorno::init() {
	printf("se llama init");
	//carga las texturas

	glGenTextures(1, &textura_suelo);
	glBindTexture(GL_TEXTURE_2D, textura_suelo);
	loadImageFile((char*)"img\\Suelo.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#if 0
	glGenTextures(1, &textura_muro);
	glBindTexture(GL_TEXTURE_2D, textura_muro);
	loadImageFile((char*)"muro.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glGenTextures(1, &textura_pilar);
	glBindTexture(GL_TEXTURE_2D, textura_pilar);
	loadImageFile((char*)"pilar.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenTextures(1, &textura_puerta);

	glBindTexture(GL_TEXTURE_2D, textura_puerta);
	loadImageFile((char*)"puerta.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenTextures(1, &textura_puerta);

	glBindTexture(GL_TEXTURE_2D, textura_techo);
	loadImageFile((char*)"techo.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenTextures(1, &textura_techo);
#endif
	//crea las listas de render 
	lista_suleo = create_list_Suelos(textura_suelo);
#if 0
	lista_muro = create_list_Muros(textura_muro);
	lista_pilar = create_list_Pilares(textura_pilar);
	lista_puerta = create_list_Puerta(textura_puerta);
	lista_techo = create_list_Techo(textura_techo);
#endif

}

// Dibuja el entorno completo
void Entorno::dibujar() const {
	glPushMatrix();
	//glLoadIdentity();

	glCallList(lista_suleo);
	

	glPopMatrix();
}

GLuint Entorno::create_list_Suelos(GLuint textura) {
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);
	
	glTranslatef(0, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	
	GLfloat v0[3] = { -20, 0, -20 };
	GLfloat v3[3] = { 20, 0, -20 };
	GLfloat v2[3] = { 20, 0,  20 };
	GLfloat v1[3] = { -20, 0,  20 };

	// Aquí dibujamos el suelo usando la función quadtex,
	// con repetición de textura 10x10 para que la textura se repita varias veces.

	quadtex(v0, v1, v2, v3, 0, 10, 0, 10, 20, 20);
	glDisable(GL_TEXTURE_2D);

	glEndList();
	//printf("Sea a generado la lista %d", lista);
	return lista;
}
GLuint Entorno::create_list_Muros(GLuint textura) {
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	// Dibuja un muro simple
	GLfloat v0[3] = { -50, 0, -50 };
	GLfloat v1[3] = { -50, 10, -50 };
	GLfloat v2[3] = { -50, 10, 50 };
	GLfloat v3[3] = { -50, 0, 50 };
	quadtex(v0, v1, v2, v3, 0, 10, 0, 10, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glEndList();
	return 0;
}
GLuint Entorno::create_list_Pilares(GLuint textura) {
	uint8_t L = 1.0f; // Longitud del cubo
	uint8_t H = 10.0f; // Altura del cubo
	
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, textura);

	GLfloat v0[] = { -L / 2, 0, -L / 2 };
	GLfloat v1[] = { L / 2, 0, -L / 2 };
	GLfloat v2[] = { L / 2, 0,  L / 2 };
	GLfloat v3[] = { -L / 2, 0,  L / 2 };
	GLfloat v4[] = { -L / 2, H, -L / 2 };
	GLfloat v5[] = { L / 2, H, -L / 2 };
	GLfloat v6[] = { L / 2, H,  L / 2 };
	GLfloat v7[] = { -L / 2, H,  L / 2 };

	// Caras laterales con textura
	quadtex(v0, v1, v5, v4, 0, 1, 0, 1, 10, 10); // frontal
	quadtex(v1, v2, v6, v5, 0, 1, 0, 1, 10, 10); // derecha
	quadtex(v2, v3, v7, v6, 0, 1, 0, 1, 10, 10); // trasera
	quadtex(v3, v0, v4, v7, 0, 1, 0, 1, 10, 10); // izquierda

	// No dibujamos superior ni inferior para transparencia

	glEndList();
	return lista;
}
GLuint Entorno::create_list_Puerta(GLuint textura) {
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	// Dibuja una puerta simple
	GLfloat v0[3] = { -1, 0, -0.1f };
	GLfloat v1[3] = { 1, 0, -0.1f };
	GLfloat v2[3] = { 1, 2, -0.1f };
	GLfloat v3[3] = { -1, 2, -0.1f };
	quadtex(v0, v1, v2, v3, 0, 10, 0, 10, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glEndList();
	return lista;
}
GLuint Entorno::create_list_Techo(GLuint textura) {
	//pone el landscape la textura 
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	GLfloat v0[3] = { -50, 10, -50 };
	GLfloat v1[3] = { 50, 10, -50 };
	GLfloat v2[3] = { 50, 10, 50 };
	GLfloat v3[3] = { -50, 10, 50 };
	quadtex(v0, v1, v2, v3, 0, 10, 0, 10, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glEndList();
	return lista;
}
