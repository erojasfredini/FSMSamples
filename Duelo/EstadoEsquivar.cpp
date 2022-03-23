#include "EstadoEsquivar.h"

#include "EstadoBuscarEnemigo.h"

#include "EstadoGolpeado.h"

#include "EstadoAtacar.h"

#include "EstadoMuerto.h"

#include "EstadoTriunfal.h"

#include "Game.h"

#include "Link.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoEsquivar::EstadoEsquivar(): Estado("EstadoEsquivar")
{}

EstadoEsquivar::EstadoEsquivar(const EstadoEsquivar& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoEsquivar& EstadoEsquivar::operator=(const EstadoEsquivar& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoEsquivar::~EstadoEsquivar()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoEsquivar* EstadoEsquivar::Singleton()
{
	static EstadoEsquivar instancia;
	return &instancia;
}

void EstadoEsquivar::Entrar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	pLink->m_Animacion = Link::TipoAnimacion::Esquivar;
}

void EstadoEsquivar::Ejecutar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);
	FSM& LinkFSM = pEntidad->GetFSM();

	if( pLink->m_Vidas < 1 )
	{
		LinkFSM.CambiarEstado(EstadoMuerto::Singleton());
		return;
	}

	if( pLink->m_Golpeado )
	{
		LinkFSM.CambiarEstado(EstadoGolpeado::Singleton());
		return;
	}

	if( Game::Singleton()->AlmenosUnoMuerto() )
	{
		LinkFSM.CambiarEstado(EstadoTriunfal::Singleton());
		return;
	}

	if( !pLink->_IsEnemigoADistanciaEspada() )
	{
		LinkFSM.CambiarEstado(EstadoBuscarEnemigo::Singleton());
		return;
	}

	if( pLink->m_Estamina >= 19 )
		LinkFSM.CambiarEstado(EstadoAtacar::Singleton());
	else
	{
		pLink->_Esquivar();
		if( !pLink->m_LinkEsquivando.IsFinAnimacion() )//todavia esta atacando, hay que esperar que termine para tomar otra accion
			pLink->m_LinkEsquivando.ReiniciarAnimacion();
	}
}

void EstadoEsquivar::Salir(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	pLink->m_LinkEsquivando.ReiniciarAnimacion();
}