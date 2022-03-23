#pragma once

#include "Estado.h"

class EstadoAtacar: public Estado
{
	private:
		EstadoAtacar();

		EstadoAtacar(const EstadoAtacar& cpy);

		EstadoAtacar& operator=(const EstadoAtacar& cpy);
		
	public:
		virtual ~EstadoAtacar();

		//Nos devuelve la unica instancia de la clase
		static EstadoAtacar* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};