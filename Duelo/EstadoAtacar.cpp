#include "EstadoAtacar.h"

#include "EstadoBuscarEnemigo.h"

#include "EstadoGolpeado.h"

#include "EstadoEsquivar.h"

#include "EstadoMuerto.h"

#include "EstadoTriunfal.h"

#include "Game.h"

#include "Link.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoAtacar::EstadoAtacar(): Estado("EstadoAtacar")
{}

EstadoAtacar::EstadoAtacar(const EstadoAtacar& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoAtacar& EstadoAtacar::operator=(const EstadoAtacar& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoAtacar::~EstadoAtacar()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoAtacar* EstadoAtacar::Singleton()
{
	static EstadoAtacar instancia;
	return &instancia;
}

void EstadoAtacar::Entrar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	//iniciamos la animacion de Atacar
	pLink->m_Animacion = Link::TipoAnimacion::Atacar;
}

void EstadoAtacar::Ejecutar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);
	FSM& LinkFSM = pEntidad->GetFSM();

	if( pLink->m_Vidas < 1 )//Si no tiene vidas -> EstadoMuerto
	{
		LinkFSM.CambiarEstado(EstadoMuerto::Singleton());
		return;
	}

	if( pLink->m_Golpeado )//Si esta siendo golpeado -> EstadoGolpeado
	{
		LinkFSM.CambiarEstado(EstadoGolpeado::Singleton());
		return;
	}

	if( !pLink->m_LinkAtacando.IsFinAnimacion() )//todvia esta atacando, hay que esperar que termine para tomar otra accion
		return;

	if( Game::Singleton()->AlmenosUnoMuerto() )//Si el otro esta muerto -> EstadoTriunfal
	{
		LinkFSM.CambiarEstado(EstadoTriunfal::Singleton());
		return;
	}

	if( !pLink->_IsEnemigoADistanciaEspada() )//Si esta lejos -> EstadoBuscarEnemigo
	{
		LinkFSM.CambiarEstado(EstadoBuscarEnemigo::Singleton());
		return;
	}

	auto h = pLink->m_LinkAtacando.GetFrameActual();
	if( pLink->m_Estamina >= 19 && pLink->m_LinkAtacando.GetFrameActual() == 2 && (pLink->m_LinkAtacando.GetAvanceFrame()>0.5f) )
		pLink->_Atacar();
	else
		LinkFSM.CambiarEstado(EstadoEsquivar::Singleton());
}

void EstadoAtacar::Salir(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	//reiniciamos la animacion de atacar
	pLink->m_LinkAtacando.ReiniciarAnimacion();
}