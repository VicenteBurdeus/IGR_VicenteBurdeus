#include "Entorno.h"
#include <stdint.h>
#include <iostream>
#include <GL/glcorearb.h>
#include <GL/GLU.h>
#include <vector>
#include <cmath>


#include "codebase.h"
#include "Circulos.h"
#include <chrono>


using namespace std;
using namespace cb;



Entorno::Entorno() {}

//carga las texturas
void Entorno::init() {
	printf("se llama init\n");
	//carga las texturas

	glGenTextures(1, &textura_suelo);
	glBindTexture(GL_TEXTURE_2D, textura_suelo);
	loadImageFile((char*)"img\\suelo.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &textura_muro);
	glBindTexture(GL_TEXTURE_2D, textura_muro);
	loadImageFile((char*)"img\\muro.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#if 1
	glGenTextures(1, &textura_pilar);
	glBindTexture(GL_TEXTURE_2D, textura_pilar);
	loadImageFile((char*)"img\\pilar.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#endif
	glGenTextures(1, &textura_techo);
	glBindTexture(GL_TEXTURE_2D, textura_techo);
	loadImageFile((char*)"img\\techo.jpg");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	

	//crea las listas de render 
	lista_suleo = create_list_Suelos(textura_suelo);
	lista_muro = create_list_Muros(textura_muro);
	lista_pilar = create_list_Pilares(textura_suelo);
	lista_techo = create_list_Techo(textura_techo);

}

// Dibuja el entorno completo
void Entorno::dibujar() {
	glPushMatrix();
	//glLoadIdentity();

	for (int k = -3; k <= 3; k++) {
		glPushMatrix();
		Vec3 pos = Vec3(20 * k, 0, 30 * k);//<-- Por algun motivo al hacer los calculos directamente en la funcion estos dan 0
		glTranslatef(pos.x, pos.y, pos.z);
		
		//cout << "Dibujando entorno en posicion: " << pos.x << ", " << pos.y << ", " << pos.z << endl;


		glCallList(lista_suleo);
		//Pilares
		for (int i = -10; i <= 10; i += 20) {
			for (GLfloat j = -20; j <= 20; j += 10) {
				if (!colisionables_generados) {
					colisionables.push_back(AABB(Vec3(i - 1, 0, j - 1), Vec3(i + 1, 5, j + 1))); // AABB de los pilares
				}
				if (i == -10 && j < 0) {
					continue;
				}
				glPushMatrix();
				glTranslatef(i, 0, j);
				glCallList(lista_pilar);
				glPopMatrix();
				
			}
		}
		//Muros
		glPushMatrix();
		glTranslatef(10, 0, -20);
		glCallList(lista_muro);
		glTranslatef(0, 0, 10);
		glCallList(lista_muro);
		glTranslatef(0, 0, 10);
		glCallList(lista_muro);
		glTranslatef(0, 0, 20);
		glRotatef(-90, 0, 1, 0);
		glCallList(lista_muro);
		glTranslatef(0, 0, 10);
		glCallList(lista_muro);
		glTranslatef(0, 0, 10);
		glRotatef(-90, 0, 1, 0);
		glCallList(lista_muro);
		glTranslatef(0, 0, 10);
		glCallList(lista_muro);
		glTranslatef(0, 0, 10);
		glCallList(lista_muro);
		glTranslatef(0, 0, 20);
		glRotatef(-90, 0, 1, 0);
		glCallList(lista_muro);
		glTranslatef(0, 0, 10);
		glCallList(lista_muro);
		glPopMatrix();

		glCallList(lista_techo);

		glPopMatrix();
	}

	
	
	if (!colisionables_generados) {
		colisionables.push_back(AABB(Vec3(-10, 0, -20), Vec3(10, 5, -20)));
		colisionables.push_back(AABB(Vec3(10, 0, 20), Vec3(-10, 5, 20)));
		colisionables.push_back(AABB(Vec3(10, 0, -20), Vec3(10, 5, 10)));
		colisionables.push_back(AABB(Vec3(-10, 0, -10), Vec3(-10, 5, 20)));
		portales.push_back({ AABB(Vec3(-10, 0, -20), Vec3(-13, 4, -10)), Vec3(20, 0, 30) }); // Portal de entrada	
		portales.push_back({ AABB(Vec3(10, 0, 20), Vec3(13, 4, 10)), Vec3(-20, 0, -30) }); // Portal de salida
		colisionables.push_back(AABB(cb::Vec3(-2.2f, -2.5f, -0.5f), cb::Vec3(2.2f, 4.5f, 0.5f))); // AABB del portal de entrada
	}
	colisionables_generados = true;
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
	//glTranslatef(0, 0, 0);
	glPushAttrib(GL_LIGHTING_BIT | GL_TEXTURE_BIT);
	GLfloat mat_ambient[] = { 0.1f, 0.1f, 0.1f, 0.2f };  // ambiente
	GLfloat mat_diffuse[] = { 0.2f, 0.2f, 0.2f, 0.2f };  // color base
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // sin brillo especular
	GLfloat mat_shininess[] = { 1.0f };                   // sin brillo

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	
	GLfloat v0[3] = { -10, 0, -20 };
	GLfloat v3[3] = { 10, 0, -20 };
	GLfloat v2[3] = { 10, 0,  20 };
	GLfloat v1[3] = { -10, 0,  20 };

	// Aquí dibujamos el suelo usando la función quadtex,
	// con repetición de textura 10x10 para que la textura se repita varias veces.

	quadtex(v0, v1, v2, v3, 0, 10, 0, 5, 50, 50);
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
	glPushAttrib(GL_LIGHTING_BIT | GL_TEXTURE_BIT);
	GLfloat mat_ambient[] = { 0.1f, 0.1f, 0.1f, 0.2f };  // ambiente
	GLfloat mat_diffuse[] = { 0.2f, 0.2f, 0.2f, 0.2f };  // color base
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // sin brillo especular
	GLfloat mat_shininess[] = { 1.0f };                   // sin brillo

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	// Dibuja un muro simple
	GLfloat v0[3] = { 0, 0, 0 };
	GLfloat v1[3] = { 0, 10, 0 };
	GLfloat v2[3] = { 0, 10, 10 };
	GLfloat v3[3] = { 0, 0, 10 };
	quadtex(v0, v3, v2, v1, 0, 2, 0, 2, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glEndList();
	return lista;
}
GLuint Entorno::create_list_Pilares(GLuint textura) {
	uint8_t L = 2.0f; // Longitud del cubo
	uint8_t H = 6.0f; // Altura del cubo
	
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);

	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // ambiente
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // color base
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // sin brillo especular
	GLfloat mat_shininess[] = { 0.0f };                   // sin brillo

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
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

#if 1
	// Caras laterales con textura
	quadtex(v0, v4, v5, v1, 0, 2, 0, 1, 10, 10); // frontal
	quadtex(v1, v5, v6, v2, 0, 2, 0, 1, 10, 10); // derecha
	quadtex(v2, v6, v7, v3, 0, 2, 0, 1, 10, 10); // trasera
	quadtex(v3, v7, v4, v0, 0, 2, 0, 1, 10, 10); // izquierda
#else
	// Caras laterales con textura
	quadtex(v0, v1, v5, v4, 0, 1, 0, 1, 10, 10); // frontal
	quadtex(v1, v2, v6, v5, 0, 1, 0, 1, 10, 10); // derecha
	quadtex(v2, v3, v7, v6, 0, 1, 0, 1, 10, 10); // trasera
	quadtex(v3, v0, v4, v7, 0, 1, 0, 1, 10, 10); // izquierda



#endif

	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glEndList();
	return lista;
}
GLuint Entorno::create_list_Techo(GLuint textura) {
	//pone el landscape la textura 
	vector<cb::Vec3> lado1 = puntosCirculoTecho(15);
	vector<cb::Vec3> lado2;
	for (const auto& punto : lado1) {
		lado2.push_back(cb::Vec3(punto.x, punto.y, 20));
	}

	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	for (size_t i = 0; i < lado1.size()-1; ++i) {
		// Dibuja un cuadrilatero entre los puntos correspondientes de lado1 y lado2
		GLfloat v0[3] = { lado1[i].x, lado1[i].y, lado1[i].z };
		GLfloat v1[3] = { lado2[i].x, lado2[i].y, lado2[i].z };
		GLfloat v2[3] = { lado2[(i + 1) % lado2.size()].x, lado2[(i + 1) % lado2.size()].y, lado2[(i + 1) % lado2.size()].z };
		GLfloat v3[3] = { lado1[(i + 1) % lado1.size()].x, lado1[(i + 1) % lado1.size()].y, lado1[(i + 1) % lado1.size()].z };
		quadtex(v2, v3, v0, v1, 0, 10, 0, 1, 20, 20);
	}

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

	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);
	glPushMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess[] = { 0.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glTranslatef(-size * columnas / 2, 0.0f, -size * filas / 2);

	GLfloat normal[3] = { 0.0f, 1.0f, 0.0f };

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

			glBegin(GL_QUADS);
			glNormal3fv(normal);
			glVertex3fv(v0);
			glVertex3fv(v3);
			glVertex3fv(v2);
			glVertex3fv(v1);
			glEnd();
		}
	}

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPopAttrib();
}

void Entorno::drawFaro(int tiempo_transcurrido) {
	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	// Colores comunes para las dos luces móviles
	GLfloat light_diffuse[] = { 1.0f, 0.9f, 0.7f, 1.0f };
	GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light_specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };

	// Base del faro (no rota)
	drawcilindro(cb::Vec3(0, 0, 12.5f), 0.5f, 0.5f, 1.0f, textura_pilar);
	drawcilindro(cb::Vec3(0, 1.0f, 12.5f), 0.5f, 1.0f, 0.5f, textura_pilar);
	drawcilindro(cb::Vec3(0, 1.5f, 12.5f), 1.0f, 0.5f, 0.0f, textura_techo);
	drawcilindro(cb::Vec3(0, 1.5f, 12.5f), 0.5f, 0.5f, 1.0f, textura_pilar);
	drawcilindro(cb::Vec3(0, 2.5f, 12.5f), 0.5f, 1.0f, 0.0f, textura_techo);
	drawcilindro(cb::Vec3(0, 2.5f, 12.5f), 1.0f, 0.5f, 0.5f, textura_pilar);

	// Tiempo y ángulo
	using namespace std::chrono;
	auto ahora = system_clock::now();
	auto duracion = ahora.time_since_epoch();
	auto ms = duration_cast<milliseconds>(duracion).count();
	float segundos_flotante = (ms % 60000) / 1000.0f;
	float angulo = fmod(segundos_flotante * 120.0f, 360.0f); // 120°/s → rotación cada 3s

	// Parte giratoria
	glPushMatrix();
	glTranslated(0.0f, 1.5f, 12.5f); // Subimos al nivel giratorio
	glRotatef(angulo, 0.0f, 1.0f, 0.0f); // Rotación
	glTranslated(0.0f, 0.0f, 0.80f); // Colocamos los focos

	// Definir las luces aquí para que se muevan con el faro
	GLfloat light2_pos[] = { -0.0f, 0.50f, -0.20f, 0.0f }; // Delante
	GLfloat light3_pos[] = { -0.0f, 0.50f, 1.20f, 0.0f }; // Detrás


	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
	

	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);


	//cambia cada segundo
	static GLuint texture_foco = rand() % 5;

	// Focos giratorios
	drawcilindro(cb::Vec3(0, 100, 0), 0.1f, 0.1f, 1.0f, ((((ms)/ 3000)) % 4)+1);
	glTranslated(0.0f, 0.0f, -1.60f);
	drawcilindro(cb::Vec3(0, 100, 0), 0.1f, 0.1f, 1.0f, (((ms-1500)/3000) % 4)+1);

	glPopMatrix(); // Salimos de la parte giratoria
	glPopMatrix();
	glPopAttrib();
}

void Entorno::drawcilindro(cb::Vec3 pos_base, GLfloat rad, GLfloat rad_2, GLfloat altura, GLuint texture) {
	glPushMatrix();
	if (pos_base.y == 100) {
		//printf("Posicion del cilindro: %f, %f, %f\n", pos_base.x, pos_base.y, pos_base.z);
	}
	else {
		glTranslated(pos_base.x, pos_base.y, pos_base.z);
	}
	//calcula los puntos de la base
	vector<pair<cb::Vec3, cb::Vec3>> puntos_cilindro;
	for (int i = 0; i <= 360; i += 10) {
		float angulo = rad(i);
		float x = rad * cos(angulo);
		float z = rad * sin(angulo);
		float x_2 = rad_2 * cos(angulo);
		float z_2 = rad_2 * sin(angulo);
		
		puntos_cilindro.push_back({ cb::Vec3(x, 0, z), cb::Vec3(x_2, altura, z_2) });	
	}
	// Dibuja las caras laterales del cilindro
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (size_t i = 0; i < puntos_cilindro.size(); ++i) {
		cb::Vec3 base1 = puntos_cilindro[i].first;
		cb::Vec3 base2 = puntos_cilindro[(i + 1) % puntos_cilindro.size()].first;
		cb::Vec3 cima1 = puntos_cilindro[i].second;
		cb::Vec3 cima2 = puntos_cilindro[(i + 1) % puntos_cilindro.size()].second;
		cb::quadtex(base1, cima1, cima2, base2, 0, 1.0f, 0, 0.125f, 1, 11);
	}
	glPopMatrix();
}

Vec3 Entorno::pasapuertas(const AABB caja) const {
	for (const auto& portal_ : portales) {
		if (caja.colisionaCon(portal_.caja)) {
			//printf("Colision con portal detectada. Posicion de salida: %f, %f, %f\n", portal_.salida.x, portal_.salida.y, portal_.salida.z);
			// Si colisiona con el portal, devuelve la posición de destino
			return portal_.salida;
		}
		//printf("No colision con portal detectada entre caja %f/%f %f/%f y caja portal %f/%f %f/%f\n",
		//	caja.min.x, caja.max.x, caja.min.z, caja.max.z,
		//	portal_.caja.min.x, portal_.caja.max.x, portal_.caja.min.z, portal_.caja.max.z);
	}
	return Vec3(0, 0, 0);
}