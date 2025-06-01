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
Se añadió la palabra clave `inline` a la declaración de cada función,
permitiendo así la "multiinstancia" y solucionando los errores de compilación.

En la entrega se ha adjuntado el codebase.h modificado para que sea posible compilarlo una vez entregado.

#endif

#include <iostream>			
#include <cctype> 
#include <sstream>
#include <chrono>
#include <codebase.h>
#include <GLFW/glfw3.h>



#include "Entorno.h"
#include "Jugador.h"



using namespace std;
using namespace cb;
using namespace std::chrono;


// Globales
static enum {gameplay, debug} mapa;
static bool InformacionHud = false;

const float FPS = 60; //cantidad de Frames por segundo
static float tiempo_transcurrido = 0.0f;//Tiempo transcurrido desde el ultimo frame
int frames = 0;
float fps_real = 0.0f;
float tiempo_acumulado = 0.0f;

Entorno entorno;
Jugador jugador;

// Arreglo para gestionar las teclas pulsadas
bool teclas_presionadas[256] = { false };
bool teclas_presionadas_previas[256] = { false };
bool teclas_especiales[256] = { false };
bool teclas_especiales_previas[256] = { false };



// Declaracion de cabezeras (pueden no estar todas incluidas)

void onTimer(int tiempo);
void update();
void init();
void displaySinMostrar();
void display();
static void showInfo(bool enable);
static void showEjes();

void reshape(GLint w, GLint h);

//Eventos o controlers
void tecladoDown(unsigned char key, int x, int y);
void tecladoUp(unsigned char key, int x, int y);
void tecladoEspecialDown(int key, int x, int y);
void tecladoEspecialUp(int key, int x, int y);
void onMouseMove(int x, int y);
void myEntryFunc(int state);


// Inicializaciones (solo una vez)
void init()
{
	cout << "Iniciando Proyecto 2" << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glutSetCursor(GLUT_CURSOR_NONE);

	glutTimerFunc(1000 / FPS, onTimer, 1000 / FPS);

	mapa = gameplay;
	entorno.init();
	jugador.transportar(0,1.8,-17);

	// Menu de popup
	//glutCreateMenu(onMenu);
	//glutAddMenuEntry("ALAMBRICO", 0);
	//glutAddMenuEntry("SOLIDO", 1);
	//glutAddMenuEntry("DOBLE", 2);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

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

	
	jugador.aplicarCamara();
	if (mapa == debug) {
		ejes();
		entorno.dibujarSueloCheckerboard();
		goto FinDibujo;
	}
	// En caso de flujo normal
	entorno.dibujar();
	




	FinDibujo:
	showInfo(InformacionHud);

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
	glutEntryFunc(myEntryFunc);
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

//--Hud---------------------------------------------------

static void showInfo(bool enable) {
	if (!enable) { return; }

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int windowHeight = viewport[3];

	// Convertir FPS a entero para que no tenga decimales
	string fps_str = "FPS: " + to_string((int)fps_real);
	string pos_str = "Posicion: (" + to_string(jugador.getX()) + ", " + to_string(jugador.getY()) + ", " + to_string(jugador.getZ()) + ")";
	string vel_str = "Velocidad: " + to_string(jugador.getSpeed());
	string mapa_str = "Mapa: " + string(mapa == gameplay ? "Camara de los secretos" : "Debug");
	string info_str = "Colisones: " + string(jugador.noclip ? "OFF" : "ON");

	// Dibuja el texto en coordenadas de ventana, ajustando Y para que sea desde arriba (por ejemplo, 10 píxeles desde arriba)
	cb::texto(10, windowHeight - 20, fps_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 40, pos_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 60, vel_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 80, mapa_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 100, info_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	showEjes();
	glPopAttrib();

	
}

static void showEjes()
{
	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);

	// Define viewport pequeño (ej. 100x100 píxeles en esquina inferior izquierda)
	glViewport(vp[0], vp[1], 100, 100);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45, 1.0, 0.1, 10);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Posiciona cámara mini ejes
	glTranslatef(0, 0, -5);

	// Rota según ángulos de cámara para que coincida la orientación
	glRotatef(jugador.getPitch(), 1, 0, 0);
	glRotatef(jugador.getYaw(), 0, 1, 0);
	glRotatef(jugador.getRoll(), 0, 0, 1);

	// Guardar estados y modificar para dibujar ejes siempre visibles
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_LINE_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_DEPTH_TEST);     // IMPORTANTE: desactiva test de profundidad
	glDepthMask(GL_FALSE);        // No escribir en z-buffer

	glLineWidth(4.0f);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(-2, 0, 0); // X rojo
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0); // Y verde
	glColor3f(0, 0, 1); glVertex3f(0, 0, 2); glVertex3f(0, 0, 0); // Z azul
	glEnd();

	// Restaurar estados
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	glPopAttrib();

	// Restaurar matrices y viewport
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glViewport(vp[0], vp[1], vp[2], vp[3]);  // Restaurar viewport original
}

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

void myEntryFunc(int state) {
	//Esto aculta o muestra el cursor al entrar o salir de la ventana
	if (state == GLUT_ENTERED) {
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else {
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
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

	frames++;
	tiempo_acumulado += tiempo_transcurrido;

	if (tiempo_acumulado >= 1.0f) {
		fps_real = frames / tiempo_acumulado;
		frames = 0;
		tiempo_acumulado = 0.0f;
	}

	float factorVelocidad = (teclas_especiales[GLUT_KEY_SHIFT_L] || teclas_especiales[GLUT_KEY_SHIFT_R]) ? 2.0f : 1.0f;
	float desplazamiento = (factorVelocidad * 6 * tiempo_transcurrido);

	if (teclas_presionadas['w'] || teclas_presionadas['W']) {
		jugador.moverAdelante(desplazamiento, entorno);
	}
	if (teclas_presionadas['s'] || teclas_presionadas['S']) {
		jugador.moverAdelante(-desplazamiento, entorno);
	}
	if (teclas_presionadas['a'] || teclas_presionadas['A']) {
		jugador.moverIzquierda(desplazamiento, entorno);
	}
	if (teclas_presionadas['d'] || teclas_presionadas['D']) {
		jugador.moverIzquierda(-desplazamiento, entorno);
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
	if (teclas_especiales[GLUT_KEY_F3]) {
		if (!teclas_especiales_previas[GLUT_KEY_F3]) {
			InformacionHud = !InformacionHud; // Alterna la visibilidad del HUD
		}
	}
	if (teclas_especiales[GLUT_KEY_F2]) {
		if (!teclas_especiales_previas[GLUT_KEY_F2]) {
			mapa = (mapa == gameplay) ? debug : gameplay;
			if (mapa == gameplay) { jugador.noclip = false; }
			else { jugador.noclip = true; }
		}
	}
	if (teclas_especiales[GLUT_KEY_F1]) {
		if (!teclas_especiales_previas[GLUT_KEY_F1]) {
			jugador.noclip = !jugador.noclip; // Alterna el modo noclip
		}
	}
	if (teclas_especiales[GLUT_KEY_F11]) {
		if (!teclas_especiales_previas[GLUT_KEY_F11]) {
			if (glutGet(GLUT_FULL_SCREEN)) {
				glutReshapeWindow(600, 600);
				glutPositionWindow(100, 100);
				glutSetCursor(GLUT_CURSOR_INHERIT);
			}
			else {
				glutFullScreen();
				glutSetCursor(GLUT_CURSOR_NONE);
			}
		}
	}
	if (teclas_presionadas[27]) { // ESC para salir
		exit(0);
	}

	//Copia teclas pulsadas a teclas pulsadas anteriormente (Flancos)
	for (int i = 0; i < 256; i++) {
		teclas_presionadas_previas[i] = teclas_presionadas[i];
		teclas_especiales_previas[i] = teclas_especiales[i];
	}
	if (mapa == debug) { jugador.noclip = true;}
	jugador.actualizarInclinacion(tiempo_transcurrido);
	jugador.actualizarSalto(tiempo_transcurrido);
	jugador.actualizarAgacharse(tiempo_transcurrido);

	glutPostRedisplay();
}
