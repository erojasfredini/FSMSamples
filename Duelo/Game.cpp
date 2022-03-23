#include "Game.h"

#include "Link.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

Game::Game(): m_Window(sf::VideoMode(800,600,32), "Ejemplo: FSM Duelo", sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings()),
		m_dt(1.0f/60)
{
	LoadRecursos();//cargamos los recursos, por ejemplo imagenes, sonidos, fuentes(en este caso solo una imagen, la de la animacion)

	m_Window.setFramerateLimit(60);
}

Game::~Game()
{
	delete pLinkA;
	delete pLinkB;
}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

float Game::GetDistanciaEntreEntidades()
{
	sf::Vector2f posA = pLinkA->GetPosicion();
	sf::Vector2f posB = pLinkB->GetPosicion();

	float dx = posA.x-posB.x;
	float dy = posA.y-posB.y;
	return sqrt(dx*dx+dy*dy);
}

bool Game::AlmenosUnoMuerto()
{
	if( !dynamic_cast<Link*>(pLinkA)->IsVivo()  || !dynamic_cast<Link*>(pLinkA)->IsVivo() )
		return true;
	else
		return false;
}

Game* Game::Singleton()
{
	static Game instancia;
	return &instancia;
}

void Game::CrearEscena()
{
	pLinkA = new Link(0, sf::Vector2f(77,500), true, false);
	pLinkB = new Link(0, sf::Vector2f(600,500), false, true);

	if (!m_TextFont.loadFromFile("../../Duelo/Recursos/arial.ttf"))
	{
		// error
	}

	m_EstadoVerde.setPosition(475.0f, 50.0f);
	m_EstadoVerde.setCharacterSize(30);
	m_EstadoVerde.setFont(m_TextFont);
	m_EstadoVerde.setFillColor(sf::Color::Green);

	m_EstadoRojo.setPosition(25.0f, 50.0f);
	m_EstadoRojo.setCharacterSize(30);
	m_EstadoRojo.setFont(m_TextFont);
	m_EstadoRojo.setFillColor(sf::Color::Red);
}

void Game::Iniciar()
{
	CrearEscena();//creamos la escena... en este caso solo consiste en posicionar el sprite de animacion en una posicion

	while( m_Window.isOpen() )
	{
		//Atrapamos los eventos para cerra la ventana
		while( m_Window.pollEvent(m_Evento) )
		{
			switch( m_Evento.type )
			{
			case sf::Event::Closed:
					m_Window.close();
				break;

			case sf::Event::KeyReleased:
				{
					if( m_Evento.key.code == sf::Keyboard::Escape )
						m_Window.close();
				}
				break;
			}
		}

		Actualizar();    //Actualizamos la escena

		Dibujar();       //Dibujamos todo el juego

	}
}

void Game::Actualizar()
{
	dt = clock.getElapsedTime().asSeconds();
	clock.restart();

	pLinkA->Actualizar(dt);
	pLinkB->Actualizar(dt);


	if( !dynamic_cast<Link*>(pLinkB)->IsGolpeado() && dynamic_cast<Link*>(pLinkA)->IsAtacando() && GetDistanciaEntreEntidades() < 45 )
	{
		dynamic_cast<Link*>(pLinkB)->Danar(20);
	}
	if(  !dynamic_cast<Link*>(pLinkA)->IsGolpeado() && dynamic_cast<Link*>(pLinkB)->IsAtacando() && GetDistanciaEntreEntidades() < 45 )
	{
		dynamic_cast<Link*>(pLinkA)->Danar(20);
	}

	m_EstadoVerde.setString(dynamic_cast<Link*>(pLinkA)->GetNombreEstadoActual());
	m_EstadoRojo.setString(dynamic_cast<Link*>(pLinkB)->GetNombreEstadoActual());
}

void Game::Dibujar()
{
	m_Window.clear();

	dynamic_cast<Link*>(pLinkA)->Dibujar(m_Window);
	dynamic_cast<Link*>(pLinkB)->Dibujar(m_Window);

	m_Window.draw(m_EstadoVerde);
	m_Window.draw(m_EstadoRojo);

	m_Window.display();
}

void Game::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::LinkVerdeCaminando].loadFromFile("../../Duelo/Recursos/Green_Walk_77x64.png") )
			exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkVerdeAtacando].loadFromFile("../../Duelo/Recursos/Green_Stab_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkVerdeEsquivando].loadFromFile("../../Duelo/Recursos/Green_Crouch_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkVerdeGolpeado].loadFromFile("../../Duelo/Recursos/Green_Hit_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkVerdeMuerto].loadFromFile("../../Duelo/Recursos/Green_Dead_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkVerdeTriunfal].loadFromFile("../../Duelo/Recursos/Green_Triumph_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkRojoCaminando].loadFromFile("../../Duelo/Recursos/Red_Walk_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkRojoAtacando].loadFromFile("../../Duelo/Recursos/Red_Stab_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkRojoEsquivando].loadFromFile("../../Duelo/Recursos/Red_Crouch_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkRojoGolpeado].loadFromFile("../../Duelo/Recursos/Red_Hit_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkRojoMuerto].loadFromFile("../../Duelo/Recursos/Red_Dead_77x64.png") )
		exit(0);

	if( !m_ManagerDeImagenes[IDImagen::LinkRojoTriunfal].loadFromFile("../../Duelo/Recursos/Red_Triumph_77x64.png") )
		exit(0);
}