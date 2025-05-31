#pragma once
#include "codebase.h"

class Entorno {
public:
    
	bool niebla = 0; // Indica si hay niebla o no
    bool iluminacion = true;
	bool dia = true; // Indica si es de dia o de noche

	Entorno(); // Constructor por defecto
    void dibujar() const;          // Dibuja el entorno completo
	void init();

private:
	GLuint lista_suleo = 0;
	GLuint textura_suelo = 0;
	
	GLuint lista_muro = 0;
	GLuint textura_muro = 0;
	
	GLuint lista_pilar = 0;
	GLuint textura_pilar = 0;
	
	GLuint lista_puerta = 0;
	GLuint textura_puerta = 0;

	GLuint lista_techo = 0;
	GLuint textura_techo = 0;

	GLuint create_list_Suelos(GLuint textura);         // Dibuja los suelos
	GLuint create_list_Muros(GLuint textura);          // Dibuja los muros
	GLuint create_list_Pilares(GLuint textura);        // Dibuja los pilares
	GLuint create_list_Puerta(GLuint textura);     // Dibuja las puertas
	GLuint create_list_Techo(GLuint textura);          // Dibuja el techo
    // Otros elementos como muros, texturas, etc.
};
 