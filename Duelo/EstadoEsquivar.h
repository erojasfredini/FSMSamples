#pragma once

#include "Estado.h"

class EstadoEsquivar: public Estado
{
	private:
		EstadoEsquivar();

		EstadoEsquivar(const EstadoEsquivar& cpy);

		EstadoEsquivar& operator=(const EstadoEsquivar& cpy);
		
	public:
		virtual ~EstadoEsquivar();

		//Nos devuelve la unica instancia de la clase
		static EstadoEsquivar* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};