#pragma once

#include "Estado.h"

class EstadoTriunfal: public Estado
{
	private:
		EstadoTriunfal();

		EstadoTriunfal(const EstadoTriunfal& cpy);

		EstadoTriunfal& operator=(const EstadoTriunfal& cpy);
		
	public:
		~EstadoTriunfal();

		//Nos devuelve la unica instancia de la clase
		static EstadoTriunfal* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};