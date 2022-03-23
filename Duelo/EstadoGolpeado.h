#pragma once

#include "Estado.h"

class EstadoGolpeado: public Estado
{
	private:
		EstadoGolpeado();

		EstadoGolpeado(const EstadoGolpeado& cpy);

		EstadoGolpeado& operator=(const EstadoGolpeado& cpy);
		
	public:
		~EstadoGolpeado();

		//Nos devuelve la unica instancia de la clase
		static EstadoGolpeado* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};