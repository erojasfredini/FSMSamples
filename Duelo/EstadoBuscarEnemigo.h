#pragma once

#include "Estado.h"

class EstadoBuscarEnemigo: public Estado
{
	private:
		EstadoBuscarEnemigo();

		EstadoBuscarEnemigo(const EstadoBuscarEnemigo& cpy);

		EstadoBuscarEnemigo& operator=(const EstadoBuscarEnemigo& cpy);
		
	public:
		//Nos devuelve la unica instancia de la clase
		static EstadoBuscarEnemigo* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};