#include "Jugador.h"
#include <cmath>

using namespace cb;

Jugador::Jugador()
    : posX(0), posY(1.8f), posZ(0), yaw(0), pitch(0), roll(0), velocidad(1.0f), velocidadInclinacion(0.0f){ 
	// Inicialización de variables
    glEnable(GL_LIGHT0);

    GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 0.8f, 1.0f }; // luz cálida
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0f);       // ángulo del cono de luz
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);     // concentración del haz
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.10f); // atenuación constante
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01f); // atenuación lineal
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.001f); // atenuación cuadrática
}



AABB Jugador::getAABB() const {
    const float radio = 0.3f;
    return {
        Vec3(posX - radio, posY,     posZ - radio),
        Vec3(posX + radio, posY + 1.7f, posZ + radio)
    };
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

#include <GL/glu.h>
#include <cmath>

inline float radians(float grados) {
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
        camY = posY - dirY * distancia + alturaExtra;
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
    GLfloat position[] = { posX, posY + 0.2f, posZ, 1.0f }; // Un poco más alto: la frente
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    float yawRad = radians(yaw);
    float pitchRad = radians(pitch);
    GLfloat direction[3];
    if (tercera_persona) {
        direction[0] = cosf(pitchRad) * sinf(yawRad);
        direction[1] = 0.0f;
        direction[2] = -cosf(pitchRad) * cosf(yawRad);
    }
    else {
        direction[0] = cosf(pitchRad) * sinf(yawRad);
        direction[1] = -sinf(pitchRad);
        direction[2] = -cosf(pitchRad) * cosf(yawRad);
    }
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
}

void Jugador::toggleTerceraPersona(){
	tercera_persona = !tercera_persona;
}