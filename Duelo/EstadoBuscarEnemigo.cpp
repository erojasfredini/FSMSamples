#include "EstadoBuscarEnemigo.h"

#include "EstadoAtacar.h"

#include "Link.h"
#include <cstdlib>

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoBuscarEnemigo::EstadoBuscarEnemigo(): Estado("EstadoBuscarEnemigo")
{}

EstadoBuscarEnemigo::EstadoBuscarEnemigo(const EstadoBuscarEnemigo& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoBuscarEnemigo& EstadoBuscarEnemigo::operator=(const EstadoBuscarEnemigo& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoBuscarEnemigo* EstadoBuscarEnemigo::Singleton()
{
	static EstadoBuscarEnemigo instancia;
	return &instancia;
}

void EstadoBuscarEnemigo::Entrar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	int random = rand()%2;
	switch(random)
	{
		case 0:
			pLink->_Hablar("A la carga");
			break;
		case 1:
			pLink->_Hablar("...");
			break;
	}

	pLink->m_Animacion = Link::TipoAnimacion::Caminar;
}

void EstadoBuscarEnemigo::Ejecutar(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);
	FSM& LinkFSM = pEntidad->GetFSM();

	if( pLink->_IsEnemigoADistanciaEspada() )
	{
		LinkFSM.CambiarEstado(EstadoAtacar::Singleton());
		return;
	}

	if( pLink->_IsEnemigoVisible() )
	{
		int random = rand()%3;
		switch(random)
		{
			case 0:
				pLink->_Hablar("Te voy a hacer cajeta!");
				break;
			case 1:
				pLink->_Hablar("AHHHHHHHHHH!!!!!");
				break;
			case 2:
				pLink->_Hablar("Sos boleta!!!");
				break;
		}
	}

	pLink->m_MoverAdelante = true;
}

void EstadoBuscarEnemigo::Salir(EntidadBase* pEntidad)
{
	Link* pLink = dynamic_cast<Link*>(pEntidad);

	//no hace nada en particular
}