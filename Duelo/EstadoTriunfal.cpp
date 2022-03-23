#include "EstadoTriunfal.h"

#include "Link.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoTriunfal::EstadoTriunfal(): Estado("EstadoTriunfal")
{}

EstadoTriunfal::EstadoTriunfal(const EstadoTriunfal& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoTriunfal& EstadoTriunfal::operator=(const EstadoTriunfal& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoTriunfal::~EstadoTriunfal()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoTriunfal* EstadoTriunfal::Singleton()
{
	static EstadoTriunfal instancia;
	return &instancia;
}

void EstadoTriunfal::Entrar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	pLink->m_Animacion = Link::TipoAnimacion::Festejando;
}

void EstadoTriunfal::Ejecutar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	//nunca va a salir de este estado
}

void EstadoTriunfal::Salir(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

}