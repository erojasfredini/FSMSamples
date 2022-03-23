#pragma once

#include "Estado.h"

class EstadoMuerto: public Estado
{
	private:
		EstadoMuerto();

		EstadoMuerto(const EstadoMuerto& cpy);

		EstadoMuerto& operator=(const EstadoMuerto& cpy);
		
	public:
		virtual ~EstadoMuerto();

		//Nos devuelve la unica instancia de la clase
		static EstadoMuerto* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};