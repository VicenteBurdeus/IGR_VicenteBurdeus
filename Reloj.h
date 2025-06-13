#pragma once
#include <vector>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <chrono>

#include "Gear.h"
#include "codebase.h"

class Reloj
{
public:
	
	Reloj(cb::Vec3 pos, float escala) {
		
		posx = pos.x;
		posy = pos.y;
		posz = pos.z;
		escala = escala;
		rotacion = 0;
		// Inicializa los engranajes
		engranajes.push_back(new Gear(1.5f, 1.3f, 1.45f, 60, 0.1f, 0.2f, cb::Vec3(0.0f + posx, 0.0f + posy, 0.0f + posz), cb::Vec3(0, 1, 1)));//Horas
		engranajes.push_back(new Gear(0.2917f, 0.1f, 0.2417f, 10, 0.1f, 0.3f, cb::Vec3(-1.23156f + posx, 1.23156f + posy, 0.0f + posz), cb::Vec3(1, 0, 0)));
		engranajes.push_back(new Gear(0.85f, 0.1f, 0.8f, 30, 0.2f, 0.15f, cb::Vec3(-1.23156f + posx, 1.23156f + posy, -0.3f + posz), cb::Vec3(1, 0, 0)));
		engranajes.push_back(new Gear(0.85f / 5.0f + 0.05f, 0.0f, 0.85f / 5.0f, 6, 0.2f, 0.30f, cb::Vec3(-0.5174f + posx, 0.5174f + posy, -0.15f + posz), cb::Vec3(0, 1, 0)));
		engranajes.push_back(new Gear(0.85f / 2.50f + 0.05f, 0.0f, 0.85f / 2.50f, 18, 0.3f, 0.15f, cb::Vec3(-0.5174f + posx, 0.5174f + posy, 0.0f + posz), cb::Vec3(0, 1, 0)));
		engranajes.push_back(new Gear(0.85f / 7.5f + 0.05f, 0.0f, 0.85f / 7.5f, 6, 0.3f, 0.15f, cb::Vec3(-0.3295f + posx, 0.050457f + posy, 0.0f + posz), cb::Vec3(1, 0, 1)));
		engranajes.push_back(new Gear(0.85f / 5.0f + 0.05f, 0.1f, 0.85f / 5.0f, 9, 0.1f, 0.15f, cb::Vec3(0.0f + posx, 0.0f + posy, 0.0f + posz), cb::Vec3(1, 0, 0)));
		
		engranajes[0]->setRPM(-1.0f / 60.0f);
		engranajes[1]->setRPM(0.1f);
		engranajes[1]->setRotation(4.5f);//ajuste para que engrane 
		engranajes[2]->setRPM(0.1f);
		engranajes[3]->setRPM(-0.5f);
		engranajes[3]->setRotation(30.0f);//ajuste para que engrane
		engranajes[4]->setRPM(-0.5f);
		engranajes[4]->setRotation(5.0f);//ajuste para que engrane
		engranajes[5]->setRPM(1.5f);
		engranajes[5]->setRotation(0.0f);//ajuste para que engrane
		engranajes[6]->setRPM(-1.0f);//60rpm



	}

	void init() {
		// Genera las listas de OpenGL
		Generar_listas();
		generarcajatrasparente();
	}

	void Draw(float deltaTime) {
		anguloMinutero -= 6.0 * deltaTime; // 6 grados por segundo
		if (anguloMinutero <= 360.0f) {
			anguloMinutero += 360.0f;
		}
		anguloSegundero -= 0.1f * deltaTime; // 6 grados por segundo
		if (anguloSegundero <= 360.0f) {
			anguloSegundero += 360.0f;
		}
		
		auto ahora = std::chrono::system_clock::now();
		auto tiempo = std::chrono::system_clock::to_time_t(ahora);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			ahora.time_since_epoch()) % 1000;

		struct tm localTime;
		localtime_s(&localTime, &tiempo);

		// Cálculo con milisegundos
		float segundosConMs = localTime.tm_sec + ms.count() / 1000.0f;

		 anguloSegundero = 360.0f - (localTime.tm_min * 6.0f) - (segundosConMs * 0.1f); // 6° por minuto, 0.1° por segundo
		 anguloMinutero = 360.0f - (segundosConMs * 6.0f); // 6° por segundo

		// Actualiza los engranajes
		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		//glDisable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		glRotated(180, 0, 1, 0);
		for (auto& gear : engranajes) {
			gear->Draw(deltaTime);
		}
		glTranslated(posx, posy, posz);
		// Dibuja el minutero
		glCallList(Marcas);
		glPushMatrix();
		glRotated(90, 0, 0, 1);
		glRotated(anguloMinutero, 0, 0, 1);
		glCallList(Minutero);
		glRotated(-anguloMinutero, 0, 0, 1);
		glPopMatrix();
		// Dibuja el segundero
		glPushMatrix();
		glRotatef(anguloSegundero - 90, 0, 0, 1);
		glColor3f(0, 0, 1);
		glTranslatef(-1.5f, 0.0f, 0.0f);
		glScalef(0.5f, 1.0f, 1.0f);
		glCallList(Minutero);
		glPopMatrix();
		glCallList(Cajatransparente);

		
		glPopAttrib();
		glPopMatrix();
		// Actualiza los minuteros
		
	}
	

private:

	GLfloat posx = 0;
	GLfloat posy = 0;
	GLfloat posz = 0;
	GLfloat escala = 1.0f;
	GLfloat rotacion = 0.0f;

	std::vector<Gear*> engranajes;

	GLuint Minutero = 0;
	GLuint Segundero = 0;
	GLuint Marca = 0;
	GLuint Marcas = 0;
	GLuint Cajatransparente = 0;

	GLfloat anguloMinutero = 0.0f;
	GLfloat anguloSegundero = 0.0f;

	void Generar_listas() {
		Minutero = glGenLists(1);
		glNewList(Minutero, GL_COMPILE);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.10f, 0.1f, 0.0f);
		glVertex3f(0.10f, -0.1f, 0.0f);
		glVertex3f(0.15f, 0.0f, 0.05f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.10f, 0.1f, 0.0f);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3b(0, 0, 0);
		glLineWidth(2.0f);
		glVertex3f(0.10f, 0.1f, 0.0f);
		glVertex3f(0.10f, -0.1f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.10f, 0.1f, 0.0f);
		glVertex3f(0.15f, 0.0f, 0.05f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.15f, 0.0f, 0.05f);
		glVertex3f(0.10f, -0.1f, 0.0f);
		glEnd();
		glEndList();


		//Marcas
		Marca = glGenLists(1);
		glNewList(Marca, GL_COMPILE);
		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
		glPushMatrix();
		glRotated(90, 0, 0, 1);//La primera marca esta a las 12
		glTranslated(1.0f, 0.0f, -0.2f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.2f);
		glVertex3f(0.1f, 0.1f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.2f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3b(0, 0, 0);
		glLineWidth(2.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);//a
		glVertex3f(0.1f, -0.1f, 0.0f);//a-b
		glVertex3f(0.0f, 0.0f, 0.2f);//b-z
		glVertex3f(-0.1f, -0.1f, 0.0f);//z-a
		glVertex3f(0.1f, 0.1f, 0.0f);//a-c
		glVertex3f(0.0f, 0.0f, 0.2f);//c-z
		glVertex3f(0.1f, 0.1f, 0.0f);//z-c
		glVertex3f(-0.1f, 0.1f, 0.0f);//c-d
		glVertex3f(0.0f, 0.0f, 0.2f);//d-z
		glVertex3f(-0.1f, 0.1f, 0.0f);//z-d
		glVertex3f(0.1f, -0.1f, 0.0f);//d-b
		glEnd();

		glPopMatrix();
		glPopAttrib();
		glEndList();



	}
	void generarcajatrasparente() {
		Cajatransparente = glGenLists(1);
		glNewList(Cajatransparente, GL_COMPILE);
		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
		glPushMatrix();
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.8 };
		GLfloat mat_shininess[] = { 100.0 };

		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
		// Activar blending para transparencia
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Desactivar lighting si quieres un color más puro
		//glDisable(GL_LIGHTING);

		// Configurar modelo de sombreado
		glShadeModel(GL_SMOOTH);


		// Color transparente (RGBA)
		glColor4f(0.5f, 0.8f, 1.0f, 0.3f);  // Azul claro con 30% opacidad

		cb::Vec3 v0 = cb::Vec3(-2.2f, -2.5f, -0.5f); // abajo izq
		cb::Vec3 v1 = cb::Vec3(2.2f, -2.5f, -0.5f);  // abajo der
		cb::Vec3 v2 = cb::Vec3(2.2f, 2.5f, -0.5f);   // arriba der
		cb::Vec3 v3 = cb::Vec3(-2.2f, 2.5f, -0.5f);  // arriba izq
		cb::Vec3 v4 = cb::Vec3(-2.2f, -2.5f, 0.5f);  // fondo abajo izq
		cb::Vec3 v5 = cb::Vec3(2.2f, -2.5f, 0.5f);   // fondo abajo der
		cb::Vec3 v6 = cb::Vec3(2.2f, 2.5f, 0.5f);    // fondo arriba der
		cb::Vec3 v7 = cb::Vec3(-2.2f, 2.5f, 0.5f);   // fondo arriba izq

		// Dibujar solo los lados verticales (no base ni tapa)
		glBegin(GL_QUADS);

		// Cara frontal
		glVertex3d(v0.x, v0.y, v0.z);
		glVertex3d(v1.x, v1.y, v1.z);
		glVertex3d(v2.x, v2.y, v2.z);
		glVertex3d(v3.x, v3.y, v3.z);

		// Cara derecha
		glVertex3d(v1.x, v1.y, v1.z);
		glVertex3d(v5.x, v5.y, v5.z);
		glVertex3d(v6.x, v6.y, v6.z);
		glVertex3d(v2.x, v2.y, v2.z);

		// Cara trasera
		glVertex3d(v5.x, v5.y, v5.z);
		glVertex3d(v4.x, v4.y, v4.z);
		glVertex3d(v7.x, v7.y, v7.z);
		glVertex3d(v6.x, v6.y, v6.z);

		// Cara izquierda
		glVertex3d(v4.x, v4.y, v4.z);
		glVertex3d(v0.x, v0.y, v0.z);
		glVertex3d(v3.x, v3.y, v3.z);
		glVertex3d(v7.x, v7.y, v7.z);

		// Cara superior
		glVertex3d(v3.x, v3.y, v3.z);
		glVertex3d(v2.x, v2.y, v2.z);
		glVertex3d(v6.x, v6.y, v6.z);
		glVertex3d(v7.x, v7.y, v7.z);
		glEnd();

		// Restaurar estado
		glPopMatrix();
		glPopAttrib();
		glEndList();
	}

	

};

