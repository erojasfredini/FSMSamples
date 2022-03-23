#pragma once

#include <string>

#include "Animacion.h"
#include "EntidadBase.h"

class Link: public EntidadBase
{
	private:
		//Cuantas vidas tiene
		int m_Vidas;

		//Cuenta estamina tiene
		float m_Estamina;

		//Si es true mira a la derecha, si es false a la izquierda
		bool m_Sentido;

		//Si se esta moviendo hacia adelante
		bool m_MoverAdelante;

		//Si se esta atacando
		bool m_Atacar;

		bool m_Esquivar;

		bool m_Golpeado;

		int m_TiempoAtontado;

		float cachedDt = 0.0f;

		sf::Vector2f m_Pos;

		Animacion m_LinkCaminando;
		Animacion m_LinkAtacando;
		Animacion m_LinkEsquivando;
		Animacion m_LinkGolpeado;
		Animacion m_LinkMuerto;
		Animacion m_LinkTriunfal;

		void _Atacar();

		void _Esquivar();

		bool _IsEnemigoVisible();

		bool _IsEnemigoADistanciaEspada();

		void _Hablar(std::string texto);

	public:
		friend class EstadoBuscarEnemigo;
		friend class EstadoAtacar;
		friend class EstadoEsquivar;
		friend class EstadoGolpeado;
		friend class EstadoMuerto;
		friend class EstadoTriunfal;

		enum TipoAnimacion{Atacar, Caminar, Esquivar, RecibirGolpe, Muerto, Festejando};
		TipoAnimacion m_Animacion;

		Link(int ID, sf::Vector2f Posicion, bool Sentido, bool Color);

		~Link();

		sf::Vector2f GetPosicion() { return m_Pos; }

		bool IsVivo();

		bool IsAtacando();

		bool IsGolpeado();

		void Danar(int dano);

		std::string GetNombreEstadoActual();

		//Debe estar implementado(para que esta clase no sea abstracta) ya que lo requiere EntidadBase
		virtual void Actualizar(float dt) override;

		void Dibujar(sf::RenderWindow& RW);
};