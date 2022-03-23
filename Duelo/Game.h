#pragma once

#include <cassert>
#include <cstdlib>

#include "SFML//Graphics.hpp"
#include "SFML//System.hpp"
#include "SFML//Window.hpp"
#include "SFML//Config.hpp"

#include "Animacion.h"
#include "Link.h"

//Identificadores para las imagenes(sf::Image) almacenadas
//en el mapa m_ManagerDeImagenes
enum IDImagen{LinkVerdeEsquivando, LinkRojoEsquivando,
			  LinkVerdeAtacando  , LinkRojoAtacando,
			  LinkVerdeGolpeado  , LinkRojoGolpeado,
			  LinkVerdeCaminando , LinkRojoCaminando,
			  LinkVerdeTriunfal  , LinkRojoTriunfal,
			  LinkVerdeMuerto    , LinkRojoMuerto};

//Clase principal del juego, contiene toda la estructura de juego
//Este objeto sera el responsable de:
//	-Crear la escena
//	-Dibujar la pantalla
//	-Actualizar el juego
class Game
{
private:

	//Ventana principal
	sf::RenderWindow m_Window;

	sf::Event m_Evento;

	float m_dt;

	//Elementos de la escena:
	//-----------------------
	sf::Text m_EstadoVerde, m_EstadoRojo;
	sf::Font m_TextFont;

	Link *pLinkA, *pLinkB;

	Game();

	Game(const Game& cpy);

	Game& operator=(const Game& cpy);

public:
	//Nos devuelve la unica instancia de la clase
	static Game* Singleton();

	~Game();

	//================================================
	/////////	Game Propiedades publicas	 /////////
	//================================================

	std::map<IDImagen,sf::Texture> m_ManagerDeImagenes;

	sf::Clock clock;

	float dt = 0.0f;

	//================================================
	/////////////	 Game Metodos		 /////////////
	//================================================

	float GetDistanciaEntreEntidades();

	bool AlmenosUnoMuerto();

	//Loop principal del juego
	void Iniciar();

	//Crea la escena
	void CrearEscena();

	//Actualiza la escena
	void Actualizar();

	//Dibuja la escena
	void Dibujar();

	//Carga los recursos a usar
	void LoadRecursos();
};