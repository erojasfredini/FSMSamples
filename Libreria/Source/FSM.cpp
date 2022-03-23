#include "FSM.h"

#include <cassert>

#include "EntidadBase.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

FSM::FSM(EntidadBase* EntidadDue�a): 
							m_pEstadoActual(NULL),
							m_pEstadoAnterior(NULL),
							m_pEstadoGlobal(NULL),
							m_pEntidadDue�a(EntidadDue�a)
{
	//nos aseguramos que la entidad due�a no sea NULL
	assert(m_pEntidadDue�a);
}


//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

void FSM::Actualizar(float dt)
{
	//primero ejecutamos el estado gloabal si es que lo hay
	if( m_pEstadoGlobal != NULL )
		m_pEstadoGlobal->Ejecutar(m_pEntidadDue�a);//notar que this puede ser casteado a EntidadBase ya que sera una hija de esta

	//segundo ejecutamos el estado actual si es que lo hay
	if( m_pEstadoActual != NULL )
		m_pEstadoActual->Ejecutar(m_pEntidadDue�a);//notar que this puede ser casteado a EntidadBase ya que sera una hija de esta
}

std::string FSM::GetNombreEstadoActual()
{
	if( m_pEstadoActual )
		return m_pEstadoActual->GetNombre();
	else
		return "";
}

std::string FSM::GetNombreEstadoAnterior()
{
	if( m_pEstadoAnterior )
		m_pEstadoAnterior->GetNombre();
	else
		return "";
}

std::string FSM::GetNombreEstadoGlobal()
{
	if( m_pEstadoGlobal )
		m_pEstadoGlobal->GetNombre();
	else
		return "";
}

void FSM::CambiarEstado(Estado* pNuevoEstado)
{
	//nos aseguramos que tanto el estado actual y el nuevo son validos(tecnicamente que sean distintos de NULL)
	assert(pNuevoEstado);

	//guardamos el estado actual como el anterior
	m_pEstadoAnterior = m_pEstadoActual;

	//salimos de estado anterior
	if( m_pEstadoActual != NULL )
		m_pEstadoActual->Salir(m_pEntidadDue�a);   //notar que this puede ser casteado a EntidadBase ya que hereda de esta

	//reemplazamos el estado anterior por el nuevo
	m_pEstadoActual = pNuevoEstado;

	//entramos al estado nuevo
	m_pEstadoActual->Entrar(m_pEntidadDue�a);   //notar que this puede ser casteado a EntidadBase ya que hereda de esta
}

void FSM::VolverAlEstadoAnterior()
{
	CambiarEstado(m_pEstadoAnterior);
}

bool FSM::RecibirMensaje(const Mensaje& msg)
{
	//enviamos el mensaje a los estados activos para lo tomen y procesen si pueden

	if( m_pEstadoActual && m_pEstadoActual->OnMensaje(m_pEntidadDue�a, msg) )
		return true;//el estado actual tomo y resolvio el mensaje
	
	if( m_pEstadoGlobal && m_pEstadoGlobal->OnMensaje(m_pEntidadDue�a, msg) )
		return true;//el estado global tomo y resolvio el mensaje

	return false;//ni el estado actual ni el global toman y reciben el mensaje
}