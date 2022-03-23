#include "EstadoGolpeado.h"

#include "EstadoBuscarEnemigo.h"

#include "EstadoMuerto.h"

#include "EstadoAtacar.h"

#include "EstadoEsquivar.h"

#include "Link.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoGolpeado::EstadoGolpeado(): Estado("EstadoGolpeado")
{}

EstadoGolpeado::EstadoGolpeado(const EstadoGolpeado& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoGolpeado& EstadoGolpeado::operator=(const EstadoGolpeado& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoGolpeado::~EstadoGolpeado()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoGolpeado* EstadoGolpeado::Singleton()
{
	static EstadoGolpeado instancia;
	return &instancia;
}

void EstadoGolpeado::Entrar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	pLink->m_Animacion = Link::TipoAnimacion::RecibirGolpe;

	pLink->m_TiempoAtontado = 30;
}

void EstadoGolpeado::Ejecutar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);
	FSM& LinkFSM = pEntidad->GetFSM();

	if( pLink->m_Vidas < 1 )
	{
		LinkFSM.CambiarEstado(EstadoMuerto::Singleton());
		return;
	}

	if( pLink->m_TiempoAtontado > 0 )
	{
		--pLink->m_TiempoAtontado;
		return;
	}

	if( !pLink->_IsEnemigoADistanciaEspada() )
	{
		LinkFSM.CambiarEstado(EstadoBuscarEnemigo::Singleton());
		return;
	}else
	{
		LinkFSM.CambiarEstado(EstadoAtacar::Singleton());
		return;
	}
}

void EstadoGolpeado::Salir(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	pLink->m_Golpeado = false;
}