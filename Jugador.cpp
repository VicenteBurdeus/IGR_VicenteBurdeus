#include "Jugador.h"
#include <cmath>
#include <GL/glu.h>
#include <string>
#include <chrono>

using namespace cb;

Jugador::Jugador()
    : posX(0), posY(1.8f), posZ(0), 
    yaw(0), pitch(0), roll(0), 
    velocidad(1.0f), velocidadInclinacion(0.0f){ 
}

void Jugador::init() {

    glGenTextures(1, &textura_cabina);
    glBindTexture(GL_TEXTURE_2D, textura_cabina);
    loadImageFile((char*)"img\\cabina.png");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

AABB Jugador::getAABB() const {
    const float radio = 0.3f;
    return {
        Vec3(posX - radio, posY,     posZ - radio),
        Vec3(posX + radio, posY + 1.7f, posZ + radio)
    };
}

AABB zona_reloj = {
	Vec3(-2.5, 0.0f, 0),
	Vec3(2.5, 2.0f, -10)
};
pair<char, bool> Jugador::Inhora(bool *input) const {
	if (zona_reloj.colisionaCon(Jugador::getAABB()) &&
    (yaw>270 || yaw < 90) && (pitch>-45 && pitch<45)){
        
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int windowWidth =(int)viewport[2] / 2;
        int windowHeight = (int)viewport[3]/3;
		//printf("punto de dibujo: %d, %d\n", windowWidth, windowHeight);
        glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT);
        glMatrixMode(GL_PROJECTION);
		
        glPushMatrix();
        glLoadIdentity();

        gluOrtho2D(0, windowWidth, 0, windowHeight);  // sistema 2D

        glMatrixMode(GL_MODELVIEW);;
        glColor3f(1.0f, 1.0f, 1.0f);

        string interac_str = "Pulsa F para ver la hora";

		if (input && input['f']) {
            auto ahora = std::chrono::system_clock::now();
            auto tiempo = std::chrono::system_clock::to_time_t(ahora);
            std::tm hora_local;
            localtime_s(&hora_local, &tiempo); // Versión segura

            int hora = hora_local.tm_hour;
            int minuto = hora_local.tm_min;
            int segundo = hora_local.tm_sec;

            interac_str = "Son las " + std::to_string(hora) + ":" +
                std::to_string(minuto) + ":" +
                std::to_string(segundo) +
                (hora >= 12 ? " PM" : " AM");
        }
        cb::texto(windowWidth, windowHeight, interac_str.c_str(), BLANCO, GLUT_BITMAP_HELVETICA_18, false);



        glPopMatrix(); // modelview
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

    }
	return std::make_pair('f', false);
}


void Jugador::intentarMover(float dx, float dz, float delta, const Entorno& entorno) {
    float nuevoX = posX + dx * delta * velocidad;
    float nuevoZ = posZ + dz * delta * velocidad;

	if (noclip) {
		// Modo noclip, simplemente actualizar posición
		posX = nuevoX;
		posZ = nuevoZ;
		return;
	}

    AABB nuevaBox = {
        Vec3(nuevoX - 0.3f, posY, nuevoZ - 0.3f),
        Vec3(nuevoX + 0.3f, posY + 1.7f, nuevoZ + 0.3f)
    };

    Vec3 aux = entorno.pasapuertas(nuevaBox);
    if (aux.x != 0 || aux.y != 0 || aux.z != 0) {
		posX = nuevoX + aux.x;
		posZ = nuevoZ + aux.z;
		return;
    }
    

    if (!entorno.hayColision(nuevaBox)) {
        // Movimiento sin colisión, actualizar posición
        posX = nuevoX;
        posZ = nuevoZ;
        return;
    }

    // Intentar mover solo en X
    nuevoX = posX + dx * delta * velocidad;
    nuevoZ = posZ;  // sin cambio en Z

    AABB boxX = {
        Vec3(nuevoX - 0.3f, posY, nuevoZ - 0.3f),
        Vec3(nuevoX + 0.3f, posY + 1.7f, nuevoZ + 0.3f)
    };

    if (!entorno.hayColision(boxX)) {
        posX = nuevoX;
        return;
    }

    // Intentar mover solo en Z
    nuevoX = posX;  // sin cambio en X
    nuevoZ = posZ + dz * delta * velocidad;

    AABB boxZ = {
        Vec3(nuevoX - 0.3f, posY, nuevoZ - 0.3f),
        Vec3(nuevoX + 0.3f, posY + 1.7f, nuevoZ + 0.3f)
    };

    if (!entorno.hayColision(boxZ)) {
        posZ = nuevoZ;
    }

    // Si llegamos aquí, colisiona en todos los intentos y no se mueve.
    
}

void Jugador::renderizarPersonaje() {
    if (!tercera_persona) { return; }
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
	glTranslatef(posX, posY-1.3f, posZ);
	glRotatef(yaw - 90, 0, 1, 0);
	//glRotatef(, 1, 0, 0);
	glRotatef(roll, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f); // Color verde
    glutSolidTeapot(0.5f);
	glPopMatrix();
	glPopAttrib();
}

void Jugador::moverAdelante(float delta, const Entorno& entorno) {
    float dx = sinf(radians(yaw));
    float dz = cosf(radians(yaw));
    intentarMover(dx, dz, delta, entorno);
}

void Jugador::moverAtras(float delta, const Entorno& entorno) {
    moverAdelante(-delta, entorno);
}
void Jugador::moverDerecha(float delta, const Entorno& entorno) {
    float rad = radians(yaw - 90);
    intentarMover(sinf(rad), cosf(rad), delta, entorno);
}
void Jugador::moverIzquierda(float delta, const Entorno& entorno) {
    float rad = radians(yaw + 90);
    intentarMover(sinf(rad), cosf(rad), delta, entorno);
}


void Jugador::transportar(float x, float y, float z) {
    transportar(x, y, z, yaw, pitch);
}
void Jugador::transportar(float x, float y, float z, float nuevoYaw, float nuevoPitch) {
    posX = x;
    posY = y;
    posZ = z;
    yaw = nuevoYaw;
    pitch = nuevoPitch;
}
void Jugador::addPosicion(cb::Vec3 pos) {
	posX += pos.x;
	posY += pos.y;
	posZ += pos.z;
}
void Jugador::girar(float vertical,float horizontal) {
    yaw += vertical;
	pitch += horizontal;
    if (yaw >= 360.0f) yaw -= 360.0f;
    else if (yaw < 0) yaw += 360.0f;
	if (pitch >= 89.0f) pitch = 89.0f;
	else if (pitch <= -89.0f) pitch = -89.0f;
}

void Jugador::inclinarIzquierda() {
    if (objetivoRoll == -10.0f) {
        objetivoRoll = 0.0f;
    }
    else {
        objetivoRoll = -10.0f;
    }
    velocidadInclinacion = (objetivoRoll - roll) / 0.25f;
}
void Jugador::inclinarDerecha() {
    if (objetivoRoll == 10.0f) {
        objetivoRoll = 0.0f;
    }
    else {
        objetivoRoll = 10.0f;
    }
    velocidadInclinacion = (objetivoRoll - roll) / 0.25f;
}


float Jugador::getRoll() const {
    return roll;
}
float Jugador::getYaw() const {
    return yaw;
}
float Jugador::getPitch() const {
	return pitch;
}
float Jugador::getSpeed() const {
	return velocidad;
}

float Jugador::getX() const { return posX; }
float Jugador::getY() const { return posY; }
float Jugador::getZ() const { return posZ; }

void Jugador::addVelocidad(float delta) {
	velocidad += delta;
	if (velocidad < 0.1f) velocidad = 0.1f; // Velocidad mínima
	if (velocidad > 10.0f) velocidad = 10.0f; // Velocidad máxima
}


inline static float radians(float grados) {
    return grados * 3.14159265f / 180.0f;
}

void Jugador::aplicarCamara() const {
    // Calcular dirección de mirada
    float yawRad = radians(yaw);
    float pitchRad = radians(pitch);

    float dirX = cosf(pitchRad) * sinf(yawRad);
    float dirY = sinf(pitchRad);
    float dirZ = cosf(pitchRad) * cosf(yawRad);

    // Ajustes de cámara
    float distancia = 4.0f;       // más lejos para ver bien al personaje
    float alturaExtra = 0.0f;     // para ver desde arriba un poco
	
    // Variables compartidas
    float camX, camY, camZ;
    float lookAtX, lookAtY, lookAtZ;

    if (tercera_persona) {
        float distancia = 4.0f;
        float alturaExtra = 0.0f;

        // Cámara detrás del personaje
        camX = posX - dirX * distancia;
        camY = max(posY - dirY * distancia + alturaExtra,0);
        camZ = posZ - dirZ * distancia;
    }
    else {
        // Cámara en primera persona (POV)
        camX = posX;
        camY = posY;
        camZ = posZ;

        glRotatef(roll, 0, 0, 1); // opcional
    }

    // Hacia dónde mira (siempre igual)
    lookAtX = posX + dirX;
    lookAtY = posY + dirY;
    lookAtZ = posZ + dirZ;

    gluLookAt(
        camX, camY, camZ,
        lookAtX, lookAtY, lookAtZ,
        0.0f, 1.0f, 0.0f
    );

}
void Jugador::toggleTerceraPersona() {
    tercera_persona = !tercera_persona;
}

float Jugador::radians(float grados) {
    return grados * (3.14159265359f / 180.0f);
}
void Jugador::actualizarInclinacion(float deltaTime) {
    if (fabs(objetivoRoll - roll) > 0.01f) {
        roll += velocidadInclinacion * deltaTime;

        // Limita para no pasarse del objetivo
        if ((velocidadInclinacion > 0 && roll > objetivoRoll) ||
            (velocidadInclinacion < 0 && roll < objetivoRoll)) {
            roll = objetivoRoll;
            velocidadInclinacion = 0.0f;
        }
    }
}
void Jugador::toggleAgacharse() {
    agachado = !agachado;
    altura_objetivo = agachado ? altura_agachado : altura_normal;
    velocidad = agachado ? velocidad_agachado : velocidad_normal;
}
void Jugador::actualizarAgacharse(float deltaTime) {
    // Solo actualiza si aún no estamos en la altura objetivo
    if (fabs(posY - altura_objetivo) > 0.01f) {
        float direccion = (altura_objetivo > posY) ? 1.0f : -1.0f;
        posY += direccion * velocidad_agachar * deltaTime;

        // Clamp final
        if ((direccion > 0 && posY > altura_objetivo) || (direccion < 0 && posY < altura_objetivo)) {
            posY = altura_objetivo;
        }
    }
}
void Jugador::iniciarSalto() {
    if (!saltando && !agachado) {
        saltando = true;
        salto_posY_inicial = posY;
        salto_tiempo = 0.0f;
    }
}
void Jugador::actualizarSalto(float deltaTime) {
    if (!saltando) return;

    salto_tiempo += deltaTime;
    if (salto_tiempo > salto_duracion) {
        // Fin del salto
        saltando = false;
        posY = agachado ? altura_agachado : altura_normal;
        return;
    }

    // Movimiento parabólico simple: y = -4h * (t/T - 0.5)^2 + h
    float t = salto_tiempo / salto_duracion;
    float altura_salto = -4.0f * salto_altura_max * (t - 0.5f) * (t - 0.5f) + salto_altura_max;

    posY = (agachado ? altura_agachado : altura_normal) + altura_salto;
}
void Jugador::togleLight() {
	if (glIsEnabled(GL_LIGHT0)) {
		glDisable(GL_LIGHT0);
	}
    else {
        glEnable(GL_LIGHT0);
    }
}

void Jugador::updateLight() {
    // Luz del jugadorf
    float yawRad = radians(yaw);
    float pitchRad = radians(pitch);

    GLfloat posj[] = { posX, posY+0.2f, posZ, 1.0f };
    GLfloat dirj[] = {cosf(pitchRad) * sinf(yawRad),sinf(pitchRad),cosf(pitchRad) * cosf(yawRad)};
	if (tercera_persona) {
		posj[1] += 1.0f; // Ajustar altura si es tercera persona
	} 
    GLfloat difusaj[] = { 2.0f, 2.0f, 1.6f, 1.0f };
    GLfloat especularj[] = { 0.6f, 0.6f, 0.6f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, posj);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirj);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusaj);
    glLightfv(GL_LIGHT0, GL_SPECULAR, especularj);
    return;

}

void Jugador::cabina(bool enable) {
    if (!enable) { return; }
	if (tercera_persona) { return; }

    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, viewport[2], 0, viewport[3]);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura_cabina);  // Esta textura debe tener canal alpha

    // Dibujamos un quad del tamaño de la pantalla
    glColor4f(1.0, 1.0, 1.0, 1.0); // Blanco total, alpha se toma de la textura
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(viewport[2], 0);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(viewport[2], viewport[3]);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, viewport[3]);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopAttrib();
}
