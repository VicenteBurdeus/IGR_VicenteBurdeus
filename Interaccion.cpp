#if 0
* ***************************************************
Rubik.cpp

Segundo proyecto de la asignatura de IGR

@author Vicente Burdeus Sanchez
@version 2025, Junio

****************************************************

La base de este proyecto está tomada del ejemplo de interacción(y otras prácticas)
de la asignatura de Informática Gráfica de la ETSINF / UPV.

//    _____ __  __ _____   ____  _____ _______       _   _ _______ ______ 
//   |_   _|  \/  |  __ \ / __ \|  __ |__   __|/\   | \ | |__   __|  ____|
//     | | | \  / | |__) | |  | | |__) | | |  /  \  |  \| |  | |  | |__   
//     | | | |\/| |  ___/| |  | |  _  /  | | / /\ \ | . ` |  | |  |  __|  
//    _| |_| |  | | |    | |__| | | \ \  | |/ ____ \| |\  |  | |  | |____ 
//   |_____|_|  |_|_|     \____/|_|  \_\ |_/_/    \_|_| \_|  |_|  |______|
//                                                                        

Se ha usado como referencia para el desarrollo de este proyecto el código
de conanwu777. Aunque no se ha usado su código directamente, algunas funciones
del mismo han sido modificadas y utilizadas en este proyecto :
https://github.com/conanwu777/rubik?tab=readme-ov-file

Asimismo, se han utilizado IAs(GitHub Copilot) durante el desarrollo
del proyecto, especialmente en la generación de comentarios.

El código de codebase.h ha sido modificado para poder ser incluido múltiples veces.
Al no estar separado en dos partes(.h y.cpp), daba errores al ser incluido varias veces,
por lo que se añadió la palabra clave `inline` a la declaración de cada función,
permitiendo así la "multiinstancia" y solucionando los errores de compilación.

En la entrega se ha adjuntado el codebase.h modificado para que sea posible compilarlo una vez entregado.

#endif

#include <iostream>			
#include <codebase.h>
#include <cctype> 
#include "Entorno.h"
#include "Jugador.h"



using namespace std;
using namespace cb;


// Globales
static enum {ALAMBRICO,SOLIDO,DOBLE} modo;
static float giroxTR = 0, giroyTR = 0, giroxTA = 0, giroyTA = 0;
int xanterior, yanterior;
GLubyte objeto[1];

const float FPS = 60; //cantidad de Frames por segundo
static float tiempo_transcurrido = 0.0f;//Tiempo transcurrido desde el ultimo frame

Entorno entorno;
Jugador jugador;

// Arreglo para gestionar las teclas pulsadas
bool teclas_presionadas[256] = { false };
bool teclas_presionadas_previas[256] = { false };
bool teclas_especiales[256] = { false };



// Declaracion de cabezeras (pueden no estar todas incluidas)

void onTimer(int tiempo);
void update();
void onMenu(int valor);
void init();
void displaySinMostrar();
void display();
void reshape(GLint w, GLint h);
void onKey(unsigned char tecla, int x, int y);
void onClick(int boton, int estado, int x, int y);
void onDrag(int x, int y);

void tecladoDown(unsigned char key, int x, int y);
void tecladoUp(unsigned char key, int x, int y);
void tecladoEspecialDown(int key, int x, int y);
void tecladoEspecialUp(int key, int x, int y);
void onMouseMove(int x, int y);


// Callback de atencion al menu de popup
void onMenu(int valor)
{
	if (valor == 0) modo = ALAMBRICO;
	else if (valor == 1) modo = SOLIDO;
	else modo = DOBLE;

	glutPostRedisplay();
}

// Inicializaciones (solo una vez)
void init()
{
	cout << "Iniciando Proyecto 2" << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glutSetCursor(GLUT_CURSOR_NONE);

	//Lanza lo timer para habilitar los FPS
	glutTimerFunc(1000 / FPS, onTimer, 1000 / FPS);

	//Jugador se autoinicializa
	entorno.init();
	// Menu de popup
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Configuracion del motor de render 
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

// Render en backbuffer 
void displaySinMostrar()
{
    // Se hace lo mismo que en display() pero sin hacer swapbuffers
    // Cada objeto seleccionable se pinta de un color solido diferente

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ejes();

	
	jugador.aplicarCamara();//Esto mueve la camara solidaria el "jugador"

	entorno.dibujar();//Genera el entorno
}

// Callback de atencion al redibujado
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ejes();

	
	jugador.aplicarCamara();//Esto mueve la camara solidaria el "jugador"

	entorno.dibujar();//Genera el entorno
	

	glutSwapBuffers();
}

// Callback de atencion al redimensionado
void reshape(GLint w, GLint h)
{
	float relacionAspecto = float(w) / h;
	glViewport(0, 0, w, h);

	// Definir la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
    // Para mantener la relacion de aspecto en Ortografica
	if(relacionAspecto>1)
		glOrtho(-2*relacionAspecto, 2*relacionAspecto, -2, 2, -20, 20);
	else
		glOrtho(-2, 2, -2/relacionAspecto, 2/relacionAspecto, -20, 20);
	*/

	gluPerspective(30, relacionAspecto, 0.1, 100);
}


// Programa principal
int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Proyecto 2");
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	//Teclado
	glutKeyboardFunc(tecladoDown);
	glutKeyboardUpFunc(tecladoUp);
	glutSpecialFunc(tecladoEspecialDown);
	glutSpecialUpFunc(tecladoEspecialUp);
	//Raton
	glutPassiveMotionFunc(onMouseMove);
	// Bucle de atencion a eventos
	glutMainLoop();
}


//--Gestor de eventos de teclado--------------------------

void tecladoDown(unsigned char key, int x, int y) {
	key = tolower(key);
	teclas_presionadas[key] = true;
}

void tecladoUp(unsigned char key, int x, int y) {
	key = tolower(key);
	teclas_presionadas[key] = false;
}

void tecladoEspecialDown(int key, int x, int y) {teclas_especiales[key] = true;}
void tecladoEspecialUp(int key, int x, int y) {teclas_especiales[key] = false;}


//--Raton-------------------------------------------------

void onMouseMove(int x, int y) {
	int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	if (x == cx && y == cy)
		return; // No mover la cámara si ya está centrado (evita bucles infinitos)

	float sensibilidad = 0.05f;
	float deltaX = (x - cx) * sensibilidad;
	float deltaY = (y - cy) * sensibilidad;

	jugador.girar(-deltaX,-deltaY);


	// Reposicionar el cursor al centro
	glutWarpPointer(cx, cy);
}

//--Gestor de tiempo--------------------------------------

void onTimer(int tiempo)
{
	//glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);
	glutTimerFunc(tiempo, onTimer, tiempo);
	update();
}

void update()
{
	int tiempo_actual = glutGet(GLUT_ELAPSED_TIME);
	static int tiempo_anterior = tiempo_actual;
	float tiempo_transcurrido = (tiempo_actual - tiempo_anterior) / 1000.0f;
	tiempo_anterior = tiempo_actual;

	

	float factorVelocidad = (teclas_especiales[GLUT_KEY_SHIFT_L] || teclas_especiales[GLUT_KEY_SHIFT_R]) ? 2.0f : 1.0f;
	float desplazamiento = (factorVelocidad * 100 * tiempo_transcurrido / FPS);

	if (teclas_presionadas['w'] || teclas_presionadas['W']) {
		jugador.moverAdelante(desplazamiento);
	}
	if (teclas_presionadas['s'] || teclas_presionadas['S']) {
		jugador.moverAtras(desplazamiento);
	}
	if (teclas_presionadas['a'] || teclas_presionadas['A']) {
		jugador.moverIzquierda(desplazamiento);
	}
	if (teclas_presionadas['d'] || teclas_presionadas['D']) {
		jugador.moverDerecha(desplazamiento);
	}
	if (teclas_presionadas['q'] || teclas_presionadas['Q']) {
		if (!teclas_presionadas_previas['q']) {
			jugador.inclinarIzquierda();
		}
	}
	if (teclas_presionadas['e'] || teclas_presionadas['E']) {
		if (!teclas_presionadas_previas['e']) {
			jugador.inclinarDerecha();
		}
	}
	if (teclas_presionadas['+']) {
		jugador.addVelocidad(0.1f*60/FPS);
	}
	if (teclas_presionadas['-']) {
		jugador.addVelocidad(-0.1f*60/FPS);
	}
	if (teclas_presionadas['c'] || teclas_presionadas['C']) {
		if (!teclas_presionadas_previas['c']) {
			jugador.toggleAgacharse();
		}
	}
	if (teclas_presionadas[' ']) {
		jugador.iniciarSalto();
	}
	if (teclas_presionadas[27]) { // ESC para salir
		exit(0);
	}

	//Copia teclas pulsadas a teclas pulsadas anteriormente
	for (int i = 0; i < 256; i++) {
		teclas_presionadas_previas[i] = teclas_presionadas[i];
	}

	jugador.actualizarInclinacion(tiempo_transcurrido);
	jugador.actualizarSalto(tiempo_transcurrido);
	jugador.actualizarAgacharse(tiempo_transcurrido);

	glutPostRedisplay();
}

