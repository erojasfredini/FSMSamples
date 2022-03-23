#include "Animacion.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

Animacion::Animacion(int CeldasX, int CeldasY, int TotalCeldasActivas, int CuadrosPorSegundo, bool Loop):
	m_CeldasX(CeldasX), m_CeldasY(CeldasY), m_TotalCeldasActivas(TotalCeldasActivas), m_CuadrosPorSegundo(CuadrosPorSegundo),
		m_time(0.0f), m_CurCelda(0), m_Loop(Loop), m_FinAnimacion(false)
{}

Animacion::~Animacion()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

void Animacion::SetImage(const sf::Texture& Img)
{
	sf::Sprite::setTexture(Img);
	int w = Img.getSize().x;
	int h = Img.getSize().y;

	m_OffsetX = w/m_CeldasX;
	m_OffsetY = h/m_CeldasY;

	sf::IntRect CeldaActual(m_OffsetX*(m_CurCelda%m_CeldasX), m_OffsetY*(int)(m_CurCelda/m_CeldasX),
								m_OffsetX*(m_CurCelda%m_CeldasX)+m_OffsetX, m_OffsetY*(int)(m_CurCelda/m_CeldasX)+m_OffsetY);
	this->setTextureRect(CeldaActual);
}

void Animacion::SetCuadrosPorSegundo(int CuadrosPorSegundo)
{
	m_CuadrosPorSegundo = CuadrosPorSegundo;
}

int Animacion::GetCuadrosPorSegundo()
{
	return m_CuadrosPorSegundo;
}

bool Animacion::IsFinAnimacion()
{
	return m_FinAnimacion;
}

void Animacion::ReiniciarAnimacion()
{
	m_CurCelda = 0;
	m_time = 0;
	m_FinAnimacion = false;
}

int Animacion::GetFrameActual()
{
	return m_CurCelda;
}

float Animacion::GetAvanceFrame()
{
	return (m_time/(1.0f/m_CuadrosPorSegundo));
}

void Animacion::Actualizar(float dt)
{
	m_time += dt;
	if( m_time >= (1.0f/m_CuadrosPorSegundo) )
	{
		m_time -= (1.0f/m_CuadrosPorSegundo);
		if( m_CurCelda >= m_TotalCeldasActivas )
			if( m_Loop )
				m_CurCelda = 0;
			else
				m_FinAnimacion = true;
		else
		{
			sf::IntRect CeldaActual(m_OffsetX*(m_CurCelda%m_CeldasX), m_OffsetY*(int)(m_CurCelda/m_CeldasX),
									m_OffsetX*(m_CurCelda%m_CeldasX)+m_OffsetX, m_OffsetY*(int)(m_CurCelda/m_CeldasX)+m_OffsetY);
			this->setTextureRect(CeldaActual);

			++m_CurCelda;
		}
	}
}