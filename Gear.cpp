#include "Gear.h"
#include <cmath>
#include <GL/glut.h>  // Para OpenGL y GLUT
#include <vector>
#include <codebase.h>

// Constructor de la clase Gear
Gear::Gear(float R_externo, float R_interno, float R_primitivo, int dientes, float modulo, float ancho, cb::Vec3 posicion, cb::Vec3 color) {
    this->R_externo = R_externo;
    this->R_interno = R_interno;
    this->R_primitivo = R_primitivo;
    this->dientes = dientes;
    this->modulo = modulo;
    this->ancho = ancho;
    this->color = color;
	this->posicion = posicion;
    this->anguloGiro = 0;
    this->RPM = 0;

	//Esto es para inicializar las listas
    this->toothList = 0;
    this->gearList = 0; 
    this->inerFill = 0;
	this->outerFill = 0;
    
}


// Dibuja el engranaje
void Gear::Draw(float tiempo_transcurrido = 0) {
    CreateSingleToothList();
    CreateGearList();
    CreateFill();
#if 1
    float angulo_por_segundo = (RPM * 360.0f) / 60.0f;
    this->anguloGiro += angulo_por_segundo * tiempo_transcurrido;

    if (anguloGiro > 360.0f) {
        anguloGiro -= 360.0f;
    }
    if (anguloGiro < 0.0f) {
        anguloGiro += 360.0f;
    }

    //printf("angulo:%f angulo pro segundo:%f\n", anguloGiro, angulo_por_segundo);
    glPushMatrix();
    //glRotated(45, 0, 0, 1);
    glTranslatef(posicion.x, posicion.y, posicion.z);
    glRotatef(anguloGiro, 0, 0, 1);
    glCallList(gearList);
    glTranslatef(0, 0, -ancho);
    glCallList(gearList);
    glCallList(inerFill);
    glTranslatef(0, 0, ancho);
    glCallList(outerFill);
    glPopMatrix();
#endif
    //glCallList(toothList);
}

// Cambia las revoluciones por minuto
void Gear::setRPM(float RPM) {
    this->RPM = RPM;
}

// Cambia el angulo de giro
// Esta funcion esta pensada para ajustar la rotacion inicial del engranaje
// Solo se actualiza con el draw
void Gear::setRotation(float anguloGiro) {
	this->anguloGiro = anguloGiro;
}


void Gear::CreateFill() {
    if (inerFill == 0) {
        inerFill = glGenLists(1);
        glNewList(inerFill, GL_COMPILE);
        glColor3f(color.x, color.y, color.z);  // Color del engranaje

        float angulo_diente = 2 * PI / dientes;
        cb::Vec3 p0, p1, p2, p3;

        // Relleno del centro del engranaje
        for (int i = 0; i < dientes; i++) {
            // Coordenadas de los puntos en el borde interno del engranaje
            p0 = cb::Vec3(R_interno * cos(i * angulo_diente), R_interno * sin(i * angulo_diente), 0);
            p1 = cb::Vec3(R_interno * cos((i + 1) * angulo_diente), R_interno * sin((i + 1) * angulo_diente), 0);
            p2 = cb::Vec3(R_interno * cos(i * angulo_diente), R_interno * sin(i * angulo_diente), ancho);
            p3 = cb::Vec3(R_interno * cos((i + 1) * angulo_diente), R_interno * sin((i + 1) * angulo_diente), ancho);
            
			glBegin(GL_LINE_LOOP);
			glColor3b(0, 0, 0);
			glVertex3f(p0.x, p0.y, p0.z);
			glVertex3f(p1.x, p1.y, p1.z);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3f(p3.x, p3.y, p3.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glEnd();
            glColor3f(color.x, color.y, color.z);
            // Crear una cara (quad) entre los puntos
            cb::quad(p0, p2, p3, p1, 1, 1);
        }
        glEndList();
    }

    float angulo_diente = 2 * PI / dientes;

    //Calculo para las proporciones del diente
    float angulo_10 = angulo_diente * 0.1f;
    float angulo_40 = angulo_diente * 0.50f;
    float angulo_50 = angulo_diente * 0.6f;

    float R_exterior = this->R_externo;
    float R_primitivo = this->R_primitivo;
    float R_interior = this->R_interno;


	if (outerFill == 0) {
		outerFill = glGenLists(1);
		glNewList(outerFill, GL_COMPILE);
		glColor3f(color.x, color.y, color.z);  // Color del engranaje
		cb::Vec3 p0, p1, p2, p3, p4, p5, p6, p7, p8, p9;
		// Relleno del centro del engranaje
        //primer lado
		p0 = cb::Vec3(R_primitivo, 0, -ancho); //a'
        p1 = cb::Vec3(R_exterior * cos(angulo_10), R_exterior * sin(angulo_10), -ancho);//A'
        p2 = cb::Vec3(R_exterior * cos(angulo_10), R_exterior * sin(angulo_10), 0);//A
        p3 = cb::Vec3(R_primitivo, 0, 0);//a

		p4 = cb::Vec3(R_exterior * cos(angulo_40), R_exterior * sin(angulo_40), 0);//B
		p5 = cb::Vec3(R_exterior * cos(angulo_40), R_exterior * sin(angulo_40), -ancho);//B'

		p6 = cb::Vec3(R_primitivo * cos(angulo_50), R_primitivo * sin(angulo_50), 0);//b
		p7 = cb::Vec3(R_primitivo * cos(angulo_50), R_primitivo * sin(angulo_50), -ancho);//b'

		p8 = cb::Vec3(R_primitivo * cos(angulo_diente), R_primitivo * sin(angulo_diente), 0);//c
		p9 = cb::Vec3(R_primitivo * cos(angulo_diente), R_primitivo * sin(angulo_diente), -ancho);//c'

        glPushMatrix();
		for (int i = 0; i < dientes; i++) {
			
			cb::quad(p0, p1, p2, p3, 1, 1);
			cb::quad(p1, p5, p4, p2, 1, 1);
			cb::quad(p5, p7, p6, p4, 1, 1);
			cb::quad(p7, p9, p8, p6, 1, 1);
			glBegin(GL_LINE_LOOP);
			glColor3b(0, 0, 0);
			glLineWidth(2.0f);
            glVertex3f(p3.x, p3.y, p3.z);//a
            glVertex3f(p0.x, p0.y, p0.z);//a'
			glVertex3f(p1.x, p1.y, p1.z);//A'
			glVertex3f(p2.x, p2.y, p2.z);//A
            glVertex3f(p3.x, p3.y, p3.z);//a
            glVertex3f(p2.x, p2.y, p2.z);//A
			glVertex3f(p4.x, p4.y, p4.z);//B
			glVertex3f(p5.x, p5.y, p5.z);//B'
            glVertex3f(p1.x, p1.y, p1.z);//A'
            glVertex3f(p5.x, p5.y, p5.z);//B'
            glVertex3f(p7.x, p7.y, p7.z);//b'
			glVertex3f(p6.x, p6.y, p6.z);//b
			glVertex3f(p4.x, p4.y, p4.z);//B
            glVertex3f(p6.x, p6.y, p6.z);//b
			glVertex3f(p8.x, p8.y, p8.z);//c
			glVertex3f(p9.x, p9.y, p9.z);//c'
			glVertex3f(p7.x, p7.y, p7.z);//b'
			
			glEnd();
			glColor3f(color.x, color.y, color.z);
            glRotatef(angulo_diente*(180.0f/PI), 0, 0, 1);
		}
		glPopMatrix();
		glEndList();
	}
}

//Inicializa la lista para crear 1 diante cuadrado
void Gear::CreateSingleToothList() {
    if (toothList == 0) {
        toothList = glGenLists(1);
        glNewList(toothList, GL_COMPILE);

        glColor3f(color.x, color.y, color.z);  //Color

        float angulo_diente = 2 * PI / dientes;

		//Calculo para las proporciones del diente
        float angulo_10 = angulo_diente * 0.1f;
        float angulo_40 = angulo_diente * 0.50f;
        float angulo_50 = angulo_diente * 0.6f;

        float R_exterior = this->R_externo;
        float R_primitivo = this->R_primitivo;
        float R_interior = this->R_interno;
        
		// Dibujamos el diente
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(R_exterior * cos(angulo_10), R_exterior * sin(angulo_10), 0);  // Punto A
        glVertex3f(R_exterior * cos(angulo_40), R_exterior * sin(angulo_40), 0);  // Punto B
        glVertex3f(R_primitivo * cos(0), R_primitivo * sin(0), 0);  // Punto a
        glVertex3f(R_primitivo * cos(angulo_50), R_primitivo * sin(angulo_50), 0);  // Punto b
        glVertex3f(R_interior * cos(0), R_interior * sin(0), 0);  // Punto 1
        glVertex3f(R_interior * cos(angulo_diente), R_interior * sin(angulo_diente), 0);  // Punto 2
        glVertex3f(R_primitivo * cos(angulo_50), R_primitivo * sin(angulo_50), 0);  // Punto b
        glVertex3f(R_primitivo * cos(angulo_diente), R_primitivo * sin(angulo_diente), 0);  // Punto c


        glEnd();
        glEndList();
    }
}



//Inicializa la lista para crear el engranaje completo
void Gear::CreateGearList() {
    if (gearList == 0) {
        gearList = glGenLists(1);
        glNewList(gearList, GL_COMPILE);

        float angulo_diente = (2 * PI) / dientes; // Corrección
        for (int i = 0; i < dientes; i++) {
            float angulo = i * angulo_diente;

            glPushMatrix();

            glRotatef(angulo * 180.0f / PI, 0, 0, 1); // Corrección: rotar sobre Z

            glCallList(toothList);
            glPopMatrix();
        }
        glEndList();
    }
}



