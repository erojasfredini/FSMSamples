#include "EstadoMuerto.h"

#include "Link.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoMuerto::EstadoMuerto(): Estado("EstadoMuerto")
{}

EstadoMuerto::EstadoMuerto(const EstadoMuerto& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoMuerto& EstadoMuerto::operator=(const EstadoMuerto& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoMuerto::~EstadoMuerto()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoMuerto* EstadoMuerto::Singleton()
{
	static EstadoMuerto instancia;
	return &instancia;
}

void EstadoMuerto::Entrar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	pLink->m_Animacion = Link::TipoAnimacion::Muerto;
}

void EstadoMuerto::Ejecutar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	//nunca va a salir de este estado
}

void EstadoMuerto::Salir(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

}