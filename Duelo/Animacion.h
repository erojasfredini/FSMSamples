#pragma once

#include "SFML//Graphics.hpp"

//Hereda de Sprite por lo que implementa su misma funcionalidad
//Representa una animacion por celda
//Este objeto sera el responsable de:
//	-Actualizar que seccion de la textura dibujar para que la animacion se reproduzca correctamente
class Animacion: public sf::Sprite
{
private:

	//Las proximas variables se piden al construir la animacion y dicen como se va a interpretar
	//la textura de animacion:

	int m_CeldasX;			 //Cuantas celdas sobre el eje x tenemos?
	int m_CeldasY;			 //Cuantas celdas sobre el eje y tenemos?
	int m_TotalCeldasActivas;//Cantidad de celdas usadas?
	int m_CuadrosPorSegundo; //A cuantos cuadros por segundo reproducimos la animacion?

	//Las proximas variables se calculan o llevan el estado temporal:

	int m_OffsetX; //Separacion sobre el eje x entre 2 celdas
	int m_OffsetY; //Separacion sobre el eje y entre 2 celdas
	int m_CurCelda;//Celda que se esta dibujando en este frame
	float m_time;  //Lleva el tiempo para saber cuando cambiar de celda de animacion

	bool m_Loop;   //Dice si la animacion loopeara

	bool m_FinAnimacion; //Si la animacion no es m_Loop esta bandera dice si ya termino la animacion

public:

	//Parametros:
	//	-CeldasX Cuantas celdas sobre el eje x tenemos?
	//	-CeldasY Cuantas celdas sobre el eje y tenemos?
	//	-TotalCeldasActivas Cantidad de celdas usadas?
	//	-CuadrosPorSegundo A cuantos cuadros por segundo reproducimos la animacion?
	Animacion(int CeldasX, int CeldasY, int TotalCeldasActivas, int CuadrosPorSegundo, bool Loop);

	~Animacion();

	void SetImage(const sf::Texture& Img);

	void SetCuadrosPorSegundo(int CuadrosPorSegundo);

	int GetCuadrosPorSegundo();

	bool IsFinAnimacion();

	void ReiniciarAnimacion();

	int GetFrameActual();

	float GetAvanceFrame();

	//Actualiza la animacion
	//	-El tiempo del ultimo frame
	void Actualizar(float dt);
};