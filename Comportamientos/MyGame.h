#pragma once

#include <cassert>
#include <cstdlib>

#include "SFML//Graphics.hpp"
#include "SFML//System.hpp"
#include "SFML//Window.hpp"
#include "SFML//Config.hpp"

#include "SFMLRenderer.h"

#include "Game.h"
#include "Vehiculo.h"

//Identificadores para las imagenes(sf::Image) almacenadas
//en el mapa m_ManagerDeImagenes
enum IDImagen{VehiculoParticula, VehiculoCobardeParticula};

//Clase principal del juego, contiene toda la estructura de juego
//Este objeto sera el responsable de:
//	-Crear la escena
//	-Dibujar la pantalla
//	-Actualizar el juego
class MyGame: public Game
{
private:

	#ifdef _DEBUG
		SFMLRenderer* pRenderer;
	#endif

	MyGame();

	MyGame(const MyGame& cpy);

	MyGame& operator=(const MyGame& cpy);

	Vehiculo* m_pAutoFantastico;
	Vehiculo* m_pAutoFantasticoCobarde;

	std::vector<EntidadEscena*> Obstaculos;
	std::vector<SteeringBehaviors::Pared*>			Paredes;
	std::vector<EntidadEscena*> ParedesEscena;

public:
	//Nos devuelve la unica instancia de la clase
	static MyGame* Singleton();

	~MyGame();

	//================================================
	/////////	Game Propiedades publicas	 /////////
	//================================================

	std::map<IDImagen,sf::Texture> m_ManagerDeImagenes;

	//================================================
	/////////////	 Game Metodos		 /////////////
	//================================================

	//Crea la escena
	virtual void CrearEscena() override;

	//Actualiza la escena
	virtual void Actualizar(const float dt) override;

	//Dibuja la escena
	virtual void Dibujar(const float dt) override;

	//Carga los recursos a usar
	virtual void LoadRecursos() override;
};