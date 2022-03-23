#include "Link.h"

#include "Game.h"
#include "EstadoBuscarEnemigo.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

Link::Link(int ID, sf::Vector2f Posicion, bool Sentido, bool Color): EntidadBase(), m_Pos(Posicion), m_Sentido(Sentido),
					m_Vidas(100),
					m_Estamina(100),
					m_MoverAdelante(false),
					m_Atacar(false),
					m_Esquivar(false),
					m_Golpeado(false),
					m_LinkCaminando(2/*Grilla de la animacion con 2 Celdas en X*/,
										1/*Grilla de la animacion con 1 Celdas en Y*/,
										2/*Las primeras 2 celdas tiene animacion valida(osea todas en este caso)*/,
										4/*Reproducir la animacion a 4 frames por segundo*/,
										true/*Se repetira esta animacion*/),
					m_LinkAtacando (2/*Grilla de la animacion con 2 Celdas en X*/,
										1/*Grilla de la animacion con 1 Celdas en Y*/,
										2/*Las primeras 2 celdas tiene animacion valida(osea todas en este caso)*/,
										2/*Reproducir la animacion a 4 frames por segundo*/,
										false/*No se repetira esta animacion*/),
					m_LinkEsquivando (2/*Grilla de la animacion con 1 Celdas en X*/,
										1/*Grilla de la animacion con 1 Celdas en Y*/,
										2/*Las primeras 1 celdas tiene animacion valida(osea todas en este caso)*/,
										2/*Reproducir la animacion a 1 frames por segundo*/,
										false/*No se repetira esta animacion*/),
					m_LinkGolpeado (2/*Grilla de la animacion con 1 Celdas en X*/,
										1/*Grilla de la animacion con 1 Celdas en Y*/,
										2/*Las primeras 1 celdas tiene animacion valida(osea todas en este caso)*/,
										8/*Reproducir la animacion a 1 frames por segundo*/,
										true/*No se repetira esta animacion*/),
					m_LinkMuerto (1/*Grilla de la animacion con 1 Celdas en X*/,
										1/*Grilla de la animacion con 1 Celdas en Y*/,
										1/*Las primeras 1 celdas tiene animacion valida(osea todas en este caso)*/,
										1/*Reproducir la animacion a 1 frames por segundo*/,
										false/*No se repetira esta animacion*/),
					m_LinkTriunfal (1/*Grilla de la animacion con 1 Celdas en X*/,
										1/*Grilla de la animacion con 1 Celdas en Y*/,
										1/*Las primeras 1 celdas tiene animacion valida(osea todas en este caso)*/,
										1/*Reproducir la animacion a 1 frames por segundo*/,
										false/*No se repetira esta animacion*/)
{
	//Seteamos la imagen con la animacion por celdas en el objeto Animacion(como lo hacemos con cualquier sprite)
	if( Color )
	{
		m_LinkCaminando.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkVerdeCaminando]);

		m_LinkAtacando.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkVerdeAtacando]);

		m_LinkEsquivando.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkVerdeEsquivando]);

		m_LinkGolpeado.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkVerdeGolpeado]);

		m_LinkMuerto.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkVerdeMuerto]);

		m_LinkTriunfal.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkVerdeTriunfal]);
	}else
	{
		m_LinkCaminando.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkRojoCaminando]);

		m_LinkAtacando.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkRojoAtacando]);

		m_LinkEsquivando.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkRojoEsquivando]);

		m_LinkGolpeado.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkRojoGolpeado]);

		m_LinkMuerto.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkRojoMuerto]);

		m_LinkTriunfal.SetImage(Game::Singleton()->m_ManagerDeImagenes[IDImagen::LinkRojoTriunfal]);
	}

	//Empezamos la FSM en el estado BuscarEnemigo
	m_MaquinaDeEstadoFinito.CambiarEstado(EstadoBuscarEnemigo::Singleton());
}

Link::~Link()
{
	//... no hay ningun recurso que liberar asi que no hacemos nada
}

void Link::_Atacar()
{
	m_Atacar = true;
	m_Estamina -= 20;
	//m_LinkAtacando.ReiniciarAnimacion();
}

void Link::_Esquivar()
{
	m_Esquivar = true;
}

bool Link::_IsEnemigoVisible()
{
	if( Game::Singleton()->GetDistanciaEntreEntidades() < 250 )
		return true;
	else
		return false;
}

bool Link::_IsEnemigoADistanciaEspada()
{
	if( Game::Singleton()->GetDistanciaEntreEntidades() < 8 )
		return true;
	else
		return false;
}

void Link::_Hablar(std::string texto)
{

}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

bool Link::IsVivo()
{
	return m_Vidas > 0;
}

bool Link::IsAtacando()
{
	return (m_Atacar && m_LinkAtacando.GetFrameActual() == 1);
}

bool Link::IsGolpeado()
{
	return m_Golpeado;
}

void Link::Danar(int dano)
{
	m_Vidas -= dano;
	if( m_Vidas < 0 )
		m_Vidas = 0;
	m_Golpeado = true;
}

std::string Link::GetNombreEstadoActual()
{
	return m_MaquinaDeEstadoFinito.GetNombreEstadoActual();
}

void Link::Actualizar(float dt)
{
	cachedDt = dt;

	m_MoverAdelante = false;
	m_Atacar        = false;
	m_Esquivar      = false;
	//m_Golpeado      = false;

	//Recuperacion de estamina de cada frame
	m_Estamina += 0.05;
	if( m_Estamina > 100 )
		m_Estamina = 100;

	//Actualiza la maquina de estado finito
	EntidadBase::Actualizar(dt);

	//se mueve hacia el enemigo
	if( m_MoverAdelante )
	{
		if(m_Sentido)//derecha
		{
			m_Pos.x += 1;
		}else{//izquierda
			m_Pos.x -= 1;
		}
	}

	//lo empuja el golpe
	if( m_Golpeado )
	{
		if(m_Sentido)//derecha
		{
			m_Pos.x -= 3;
		}else{//izquierda
			m_Pos.x += 3;
		}
	}
}

void Link::Dibujar(sf::RenderWindow& RW)
{
	switch(m_Animacion)
	{
		case TipoAnimacion::Caminar:
			{
			m_LinkCaminando.setPosition(m_Pos);
			if(m_Sentido)//derecha
				{
					m_LinkCaminando.setScale(-1.0f, 1.0f);// Flip x true
					RW.draw(m_LinkCaminando);
				}else{//izquierda
				m_LinkCaminando.setScale(1.0f, 1.0f);// Flip x false
					RW.draw(m_LinkCaminando);
				}
			m_LinkCaminando.Actualizar(cachedDt);
			}
			break;
		case TipoAnimacion::Atacar:
			{
			m_LinkAtacando.setPosition(m_Pos);
			if(m_Sentido)//derecha
				{
					m_LinkAtacando.setScale(-1.0f, 1.0f);// Flip x true
					RW.draw(m_LinkAtacando);
				}else{//izquierda
					m_LinkAtacando.setScale(1.0f, 1.0f);// Flip x false
					RW.draw(m_LinkAtacando);
				}
			m_LinkAtacando.Actualizar(cachedDt);
			}
			break;
		case TipoAnimacion::Esquivar:
			{
			m_LinkEsquivando.setPosition(m_Pos);
			if(m_Sentido)//derecha
				{
					m_LinkEsquivando.setScale(-1.0f, 1.0f);// Flip x true
					RW.draw(m_LinkEsquivando);
				}else{//izquierda
					m_LinkEsquivando.setScale(1.0f, 1.0f);// Flip x false
					RW.draw(m_LinkEsquivando);
				}
			m_LinkEsquivando.Actualizar(cachedDt);
			}
			break;
		case TipoAnimacion::RecibirGolpe:
			{
				m_LinkGolpeado.setPosition(m_Pos);
				if(m_Sentido)//derecha
					{
						m_LinkGolpeado.setScale(-1.0f, 1.0f);// Flip x true
						RW.draw(m_LinkGolpeado);
					}else{//izquierda
						m_LinkGolpeado.setScale(1.0f, 1.0f);// Flip x false
						RW.draw(m_LinkGolpeado);
					}
				m_LinkGolpeado.Actualizar(cachedDt);
			}
			break;
		case TipoAnimacion::Muerto:
			{
				m_LinkMuerto.setPosition(m_Pos);
				if(m_Sentido)//derecha
					{
						m_LinkMuerto.setScale(-1.0f, 1.0f);// Flip x true
						RW.draw(m_LinkMuerto);
					}else{//izquierda
						m_LinkMuerto.setScale(1.0f, 1.0f);// Flip x false
						RW.draw(m_LinkMuerto);
					}
				m_LinkMuerto.Actualizar(cachedDt);
			}
			break;
		case TipoAnimacion::Festejando:
			{
				m_LinkTriunfal.setPosition(m_Pos);
				if(m_Sentido)//derecha
					{
						m_LinkTriunfal.setScale(-1.0f, 1.0f);// Flip x true
						RW.draw(m_LinkTriunfal);
					}else{//izquierda
						m_LinkTriunfal.setScale(1.0f, 1.0f);// Flip x false
						RW.draw(m_LinkTriunfal);
					}
				m_LinkTriunfal.Actualizar(cachedDt);
			}
			break;
	}
}