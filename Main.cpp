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
#include <al.h>
#include <alc.h>
#include <fstream>
#include <thread>



#include "Entorno.h"
#include "Jugador.h"
#include "Reloj.h"
#include "Musica.h"


using namespace std;
using namespace cb;
using namespace std::chrono;


// Globales
static enum {gameplay, debug} mapa;
static bool InformacionHud = false;

const float FPS = 1000; //cantidad de Frames por segundo
static float tiempo_transcurrido = 0.0f;//Tiempo transcurrido desde el ultimo frame
int frames = 0;
float fps_real = 0.0f;
float tiempo_acumulado = 0.0f;

Entorno entorno;
Jugador jugador;
Reloj reloj = Reloj(cb::Vec3(0,1.6,0),180.0f);
ALCdevice* device = alcOpenDevice(nullptr);

// Arreglo para gestionar las teclas pulsadas
bool teclas_presionadas[256] = { false };
bool teclas_presionadas_previas[256] = { false };
bool teclas_especiales[256] = { false };
bool teclas_especiales_previas[256] = { false };
bool musica_reproducida = false;
bool cabina_on = true;
static string hora_str = "";


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
	reproducirMusica("music\\Arkmain.wav");
	musica_reproducida = true;
	entorno.init();
	jugador.init();
	jugador.transportar(0,1.8,-15);
	reloj.init();

	// Menu de popup
	//glutCreateMenu(onMenu);
	//glutAddMenuEntry("ALAMBRICO", 0);
	//glutAddMenuEntry("SOLIDO", 1);
	//glutAddMenuEntry("DOBLE", 2);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Configuracion del motor de render 

	// Configurar el motor de render 
	//glClearColor(0.47f, 0.31f, 0.20f, 1.0f);//Color paredes
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GRISOSCURO);

	// Activar una luz para el spotlight
	glEnable(GL_LIGHT1);
		// Ángulo del cono del foco Foco vitrina
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 75.0f);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f);
		GLfloat luzDifusa[] = { 0.5f, 0.5f, 0.4f, 1.0f };
		GLfloat luzEspecular[] = { 0.50f, 0.50f, 0.50f, 1.0f };
		glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
		glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	//Init luz jugador
	glEnable(GL_LIGHT0);
	// Luz direccional del jugador	
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 80.0f);

	//Init Lus dia/noche
		GLfloat colorDia[] = { 1.0f, 1.0f, 0.9f, 1.0f }; // Luz solar
		GLfloat colorNoche[] = { 0.2f, 0.2f, 0.4f, 1.0f }; // Luz azulada de luna

		glLightfv(GL_LIGHT2, GL_DIFFUSE, colorDia);
		glLightfv(GL_LIGHT2, GL_SPECULAR, colorDia);
		GLfloat posicion[] = { 0.0f, 10.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT2, GL_POSITION, posicion);


	// Init FOG
		GLfloat colorNiebla[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, colorNiebla);
		glFogf(GL_FOG_DENSITY, 0.75f);
		glFogf(GL_FOG_START, 3.0f);
		glFogf(GL_FOG_END, 10.0f);

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

	// Aplica la cámara ANTES de configurar luces
	jugador.aplicarCamara();
	glPushMatrix();

	
	jugador.updateLight();
	
	
	
	// Resto de la escena
	
	if (mapa == debug) {
		ejes();
		entorno.dibujarSueloCheckerboard();
		glDisable(GL_DEPTH_TEST);
		jugador.cabina(cabina_on);
		glDisable(GL_LIGHT1);
	}
	else {
		entorno.dibujar();
		// Luz foco reloj
		glEnable(GL_LIGHT1);
		GLfloat pos[] = { 0.0f, 5.0f, -4.0f, 1.0f };
		GLfloat dir[] = { 0.0f, -1.0f, 0.75f };
		GLfloat difusa[] = { 2.0f, 2.0f, 1.6f, 1.0f };
		GLfloat especular[] = { 2.0f, 2.0f, 2.0f, 1.0f };

		glLightfv(GL_LIGHT1, GL_POSITION, pos);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT1, GL_SPECULAR, especular);
		entorno.drawFaro(tiempo_transcurrido);
		reloj.Draw(tiempo_transcurrido);
		
		jugador.renderizarPersonaje();
		glDisable(GL_DEPTH_TEST);
		jugador.cabina(cabina_on);
		pair<char, bool> interaccion = jugador.Inhora(teclas_presionadas);
	}
	
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT);
	showInfo(InformacionHud);
	glPopAttrib();
	
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	
	
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
	glutCreateWindow("Proyecto 2 Vicente Burdeus");
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
	showEjes();
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int windowHeight = viewport[3];
	// opten ancho de la pantalla


	GLfloat pos[4];
	GLfloat dir[3];
	glGetLightfv(GL_LIGHT0, GL_POSITION, pos);
	glGetLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	// Convertir FPS a entero para que no tenga decimales
	string fps_str = "FPS: " + to_string((int)fps_real);
	string pos_str = "Posicion: (" + to_string(jugador.getX()) + ", " + to_string(jugador.getY()) + ", " + to_string(jugador.getZ()) + ")";
	string vel_str = "Velocidad: " + to_string(jugador.getSpeed());
	string caminfo = "Camara: " + string(jugador.tercera_persona ? "Tercera persona" : "Primera persona");
	string mapa_str = "Mapa: " + string(mapa == gameplay ? "Camara de los secretos" : "Debug");
	string info_str = "Colisones: " + string(jugador.noclip ? "OFF" : "ON");
	string info_casco = "Luz: " + string(glIsEnabled(GL_LIGHT0) ? "ON" : "OFF") +
		" | Pos: (" + to_string(pos[0]) + ", " + to_string(pos[1]) + ", " + to_string(pos[2]) + ", " + to_string(pos[3]) + ")" +
		" | Dir: (" + to_string(dir[0]) + ", " + to_string(dir[1]) + ", " + to_string(dir[2]) + ")";

	// Dibuja el texto en coordenadas de ventana, ajustando Y para que sea desde arriba (por ejemplo, 10 píxeles desde arriba)
	cb::texto(10, windowHeight - 20, fps_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 40, pos_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 60, vel_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 80, caminfo.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 100, mapa_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 120, info_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);
	cb::texto(10, windowHeight - 140, info_casco.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);

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

	// Dibuja ejes RGB
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(-2, 0, 0); // X rojo
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);  // Y verde
	glColor3f(0, 0, 1); glVertex3f(0, 0, 2); glVertex3f(0, 0, 0);  // Z azul
	glEnd();
#if 0
	// Dibuja cruceta blanca semitransparente
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  // Blanco semitransparente (50%)
	// Línea horizontal
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	// Línea vertical
	glVertex3f(0.0f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
#endif
	glDisable(GL_BLEND);

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
	glutTimerFunc(tiempo, onTimer, tiempo);
	update();
}

void update()
{
	int tiempo_actual = glutGet(GLUT_ELAPSED_TIME);
	static int tiempo_anterior = tiempo_actual;
	tiempo_transcurrido = (tiempo_actual - tiempo_anterior) / 1000.0f;
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

	//Camina hacia delante
	if (teclas_presionadas['w'] || teclas_presionadas['W']) {
		jugador.moverAdelante(desplazamiento, entorno);
	}
	//Camina hacia atras
	if (teclas_presionadas['s'] || teclas_presionadas['S']) {
		jugador.moverAdelante(-desplazamiento, entorno);
	}
	// Mueve a la izquierda
	if (teclas_presionadas['a'] || teclas_presionadas['A']) {
		jugador.moverIzquierda(desplazamiento, entorno);
	}
	// Mueve a la derecha
	if (teclas_presionadas['d'] || teclas_presionadas['D']) {
		jugador.moverIzquierda(-desplazamiento, entorno);
	}
	// Inclina izquierda
	if (teclas_presionadas['q'] || teclas_presionadas['Q']) {
		if (!teclas_presionadas_previas['q']) {
			jugador.inclinarIzquierda();
		}
	}
	// Inclina derecha
	if (teclas_presionadas['e'] || teclas_presionadas['E']) {
		if (!teclas_presionadas_previas['e']) {
			jugador.inclinarDerecha();
		}
	}
	// Ajusta la velocidad del jugador
	if (teclas_presionadas['+'] || teclas_especiales[GLUT_KEY_UP]) {
		jugador.addVelocidad(0.1f*60/FPS);
	}
	if (teclas_presionadas['-'] || teclas_especiales[GLUT_KEY_DOWN]) {
		jugador.addVelocidad(-0.1f*60/FPS);
	}
	// Se agacha
	if (teclas_presionadas['c'] || teclas_presionadas['C']) {
		if (!teclas_presionadas_previas['c']) {
			jugador.toggleAgacharse();
		}
	}
	// Enciende la linterna
	if (teclas_presionadas['t'] || teclas_presionadas['T']) {
		if (!teclas_presionadas_previas['t']) {
			jugador.togleLight();
		}
	}
	// Alterna el modo de niebla
	if (teclas_presionadas['n'] || teclas_presionadas['N']) {
		if (!teclas_presionadas_previas['n']) {
			if (glIsEnabled(GL_FOG)) {
				glDisable(GL_FOG);
			}
			else {
				glEnable(GL_FOG);
			}
		}
	}
	// Alterna el modo de iluminación
	if (teclas_presionadas['l'] || teclas_presionadas['L']) {
		if (!teclas_presionadas_previas['l']) {
			if (glIsEnabled(GL_LIGHTING)) {
				glDisable(GL_LIGHTING);
			}
			else {
				glEnable(GL_LIGHTING);
			}
		}
	}
	// Alterna la música
	if (teclas_presionadas['m'] || teclas_presionadas['M']) {
		if (!teclas_presionadas_previas['m']) {
			if (musica_reproducida){
				detenerMusica();
				musica_reproducida = false;
			}
			else {
				reproducirMusica("music\\espreso.wav");
				musica_reproducida = true;
			}
		}
	}
	//alternar noche/dia
	if (teclas_presionadas['i'] || teclas_presionadas['I']) {
		if (!teclas_presionadas_previas['i']) {
			if (glIsEnabled(GL_LIGHT2)) {
				glDisable(GL_LIGHT2);
			}
			else {
				glEnable(GL_LIGHT2);
			}
		}
	}
	// Alterna la cabina
	if (teclas_presionadas['v'] || teclas_presionadas['V']) {
		if (!teclas_presionadas_previas['v']) {
			cabina_on = !cabina_on;
		}
	}
	// Salta
	if (teclas_presionadas[' ']) {
		jugador.iniciarSalto();
	}
	// Alterna colisiones
	if (teclas_especiales[GLUT_KEY_F1]) {
		if (!teclas_especiales_previas[GLUT_KEY_F1]) {
			jugador.noclip = !jugador.noclip; // Alterna el modo noclip
		}
	}
	// Alterna entre mapas
	if (teclas_especiales[GLUT_KEY_F2]) {
		if (!teclas_especiales_previas[GLUT_KEY_F2]) {
			mapa = (mapa == gameplay) ? debug : gameplay;
			if (mapa == gameplay) { jugador.noclip = false; }
			else { jugador.noclip = true; }
		}
	}
	// Alterna la visibilidad del HUD
	if (teclas_especiales[GLUT_KEY_F3]) {
		if (!teclas_especiales_previas[GLUT_KEY_F3]) {
			InformacionHud = !InformacionHud; // Alterna la visibilidad del HUD
		}
	}
	// Vacio
	if (teclas_especiales[GLUT_KEY_F4]) {
		if (!teclas_especiales_previas[GLUT_KEY_F4]) {
			
		}
	}
	// Alterna la tercera persona
	if (teclas_especiales[GLUT_KEY_F5]) {
		if (!teclas_especiales_previas[GLUT_KEY_F5]) {
			jugador.toggleTerceraPersona();
		}
	}
	// Alterna el modo pantalla completa
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
	//Gira la camara
	if (teclas_especiales[GLUT_KEY_RIGHT]) {
		jugador.girar(-5, 0); // Girar a la derecha
	}
	if (teclas_especiales[GLUT_KEY_LEFT]) {
		jugador.girar(5, 0); // Girar a la izquierda
	}

	//Sale del juego
	if (teclas_presionadas[27]) { // ESC para salir
		detenerMusica();
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
	jugador.updateLight();
	

	//Luces
	


	glutPostRedisplay();
}
