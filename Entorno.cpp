#include "Entorno.h"
#include <stdint.h>
#include <iostream>
#include <GL/glcorearb.h>
#include <vector>


using namespace std;
using namespace cb;



Entorno::Entorno() {}

//carga las texturas
void Entorno::init() {
	printf("se llama init");
	//carga las texturas

	glGenTextures(1, &textura_suelo);
	glBindTexture(GL_TEXTURE_2D, textura_suelo);
	loadImageFile((char*)"img\\Suelo.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &textura_muro);
	glBindTexture(GL_TEXTURE_2D, textura_muro);
	loadImageFile((char*)"muro.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glGenTextures(1, &textura_pilar);
	glBindTexture(GL_TEXTURE_2D, textura_pilar);
	loadImageFile((char*)"img\\pilar.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glGenTextures(1, &textura_puerta);
	glBindTexture(GL_TEXTURE_2D, textura_puerta);
	loadImageFile((char*)"puerta.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	

	glGenTextures(1, &textura_techo);
	glBindTexture(GL_TEXTURE_2D, textura_techo);
	loadImageFile((char*)"techo.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	

	//crea las listas de render 
	lista_suleo = create_list_Suelos(textura_suelo);
	lista_muro = create_list_Muros(textura_muro);
	lista_pilar = create_list_Pilares(textura_pilar);
	lista_puerta = create_list_Puerta(textura_puerta);
	lista_techo = create_list_Techo(textura_techo);

	// Crear textura para render-to-texture
	glGenTextures(1, &texturaPortal);
	glBindTexture(GL_TEXTURE_2D, texturaPortal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEX_WIDTH, TEX_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
}

// Dibuja el entorno completo
void Entorno::dibujar() {
	glPushMatrix();
	//glLoadIdentity();

	glCallList(lista_suleo);
	
	for (int i = -9; i <= 9; i += 18) {
		for (GLfloat j = -19; j <= 19; j += 9.5) {
			glPushMatrix();
			glTranslatef(i, 0, j);
			glCallList(lista_pilar);
			glPopMatrix();
			colisionables.push_back(AABB(Vec3(i - 1, 0, j - 1), Vec3(i + 1, 5, j + 1))); // AABB de los pilares
		}
	}


	
	
	glPopMatrix();
}

bool Entorno::hayColision(const AABB& caja) const {
	for (const AABB& obj : colisionables) {
		if (caja.colisionaCon(obj)) {
			return true;
		}
	}
	return false;
}

GLuint Entorno::create_list_Suelos(GLuint textura) {
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);
	glPushMatrix();
	glTranslatef(0, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	
	GLfloat v0[3] = { -10, 0, -20 };
	GLfloat v3[3] = { 10, 0, -20 };
	GLfloat v2[3] = { 10, 0,  20 };
	GLfloat v1[3] = { -10, 0,  20 };

	// Aquí dibujamos el suelo usando la función quadtex,
	// con repetición de textura 10x10 para que la textura se repita varias veces.

	quadtex(v0, v1, v2, v3, 0, 10, 0, 5, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glPopMatrix();
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
	uint8_t L = 2.0f; // Longitud del cubo
	uint8_t H = 5.0f; // Altura del cubo
	
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);

	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	GLfloat v0[] = { -L / 2, 0, -L / 2 };
	GLfloat v1[] = { L / 2, 0, -L / 2 };
	GLfloat v2[] = { L / 2, 0,  L / 2 };
	GLfloat v3[] = { -L / 2, 0,  L / 2 };
	GLfloat v4[] = { -L / 2, H, -L / 2 };
	GLfloat v5[] = { L / 2, H, -L / 2 };
	GLfloat v6[] = { L / 2, H,  L / 2 };
	GLfloat v7[] = { -L / 2, H,  L / 2 };

	// Caras laterales con textura
	quadtex(v0, v1, v5, v4, 0, 1, 0, 2, 10, 10); // frontal
	quadtex(v1, v2, v6, v5, 0, 1, 0, 2, 10, 10); // derecha
	quadtex(v2, v3, v7, v6, 0, 1, 0, 2, 10, 10); // trasera
	quadtex(v3, v0, v4, v7, 0, 1, 0, 2, 10, 10); // izquierda


	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
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

void Entorno::dibujarSueloCheckerboard()
{
	const int filas = 40;
	const int columnas = 40;
	const float size = 2.0f;

	GLfloat blanco[3] = { 1.0f, 1.0f, 1.0f };
	GLfloat gris[3] = { 0.6f, 0.6f, 0.6f };

	glPushMatrix();
	glTranslatef(-size * columnas / 2, 0.0f, -size * filas / 2); // Centrar el suelo
	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
			GLfloat* color = ((i + j) % 2 == 0) ? blanco : gris;
			glColor3fv(color);

			GLfloat v0[3] = { j * size, 0.0f, i * size };
			GLfloat v1[3] = { (j + 1) * size, 0.0f, i * size };
			GLfloat v2[3] = { (j + 1) * size, 0.0f, (i + 1) * size };
			GLfloat v3[3] = { j * size, 0.0f, (i + 1) * size };

			quad(v0, v1, v2, v3, 1, 1);
		}
	}
	glPopMatrix();
}
