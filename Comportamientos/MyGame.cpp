#include "MyGame.h"

#include <Box2D/Box2D.h>

#include <Matematica.h>

#include <limits>

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

MyGame::MyGame(): Game(sf::VideoMode(800,600,32), "Ejemplo: FSM Duelo", sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(), 60)
{
	#ifdef _DEBUG
		pRenderer = new SFMLRenderer(&m_Window);
		pRenderer->SetFlags(std::numeric_limits<uint32>::max());
		m_World.SetDebugDraw(pRenderer);
	#endif
}

MyGame::~MyGame()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

MyGame* MyGame::Singleton()
{
	static MyGame instancia;
	return &instancia;
}

void MyGame::CrearEscena()
{
	sf::Texture* img = &m_ManagerDeImagenes[IDImagen::VehiculoParticula];
	sf::Texture* imgCobarde = &m_ManagerDeImagenes[IDImagen::VehiculoCobardeParticula];
	float escala = 0.2f;

	b2BodyDef cuerpo;
	cuerpo.type        = b2BodyType::b2_dynamicBody;
	b2FixtureDef adorno;
	adorno.restitution = 0.0;
	adorno.isSensor    = false;
	adorno.friction    = 0.3f;
	adorno.density     = 0.01f;//Masa de 26.214399
	b2PolygonShape* pRectangulo = new b2PolygonShape();
	pRectangulo->SetAsBox(img->getSize().x/2*escala, img->getSize().y/2*escala, b2Vec2(0,0), 0);
	adorno.shape       = pRectangulo;

	cuerpo.position = b2Vec2(100, 100);
	cuerpo.angle    = 0;

	m_pAutoFantastico = new Vehiculo(cuerpo, adorno, escala, img);

	m_pAutoFantastico->m_FuerzaSteeringMax = 600;
	m_pAutoFantastico->m_VelocidadMax = 40;

	//m_pAutoFantastico->GetSteeringBehaviors().BuscarOn();
	//m_pAutoFantastico->GetSteeringBehaviors().ArribarOn();
	//m_pAutoFantastico->GetSteeringBehaviors().DeambularOn();
	m_pAutoFantastico->GetSteeringBehaviors().InterceptarOn();
	m_pAutoFantastico->GetSteeringBehaviors().m_PesoInterceptar = 20.0f;
	m_pAutoFantastico->GetSteeringBehaviors().EvadirObstaculosOn();
	m_pAutoFantastico->GetSteeringBehaviors().m_PesoEvadirObstaculos = 14.0f;
	m_pAutoFantastico->GetSteeringBehaviors().EvadirParedesOn();
	m_pAutoFantastico->GetSteeringBehaviors().m_PesoEvadirParedes = 14.0f;

	SteeringBehaviors::Sensores sensor1 = SteeringBehaviors::Sensores(m_pAutoFantastico, 0.0f);
	m_pAutoFantastico->GetSteeringBehaviors().m_Sensores.push_back(sensor1);
	SteeringBehaviors::Sensores sensor2 = SteeringBehaviors::Sensores(m_pAutoFantastico, 3.1415f/4);
	m_pAutoFantastico->GetSteeringBehaviors().m_Sensores.push_back(sensor2);
	SteeringBehaviors::Sensores sensor3 = SteeringBehaviors::Sensores(m_pAutoFantastico, -3.1415f/4);
	m_pAutoFantastico->GetSteeringBehaviors().m_Sensores.push_back(sensor3);

	// Auto fantastico cobarde
	cuerpo.position = b2Vec2(700, 500);
	cuerpo.angle    = 0;

	m_pAutoFantasticoCobarde = new Vehiculo(cuerpo, adorno, escala, imgCobarde);

	m_pAutoFantasticoCobarde->m_FuerzaSteeringMax = 300;
	m_pAutoFantasticoCobarde->m_VelocidadMax = 40;

	//m_pAutoFantasticoCobarde->GetSteeringBehaviors().EscaparOn();
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().EsconderseOn();
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().EvadirObstaculosOn();
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().EvadirParedesOn();

	SteeringBehaviors::Sensores sensor4 = SteeringBehaviors::Sensores(m_pAutoFantastico, 0.0f);
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().m_Sensores.push_back(sensor1);
	SteeringBehaviors::Sensores sensor5 = SteeringBehaviors::Sensores(m_pAutoFantastico, 3.1415f/4);
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().m_Sensores.push_back(sensor2);
	SteeringBehaviors::Sensores sensor6 = SteeringBehaviors::Sensores(m_pAutoFantastico, -3.1415f/4);
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().m_Sensores.push_back(sensor3);


	m_pAutoFantastico->GetSteeringBehaviors().m_pPresa = m_pAutoFantasticoCobarde;
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().m_pAcechador = m_pAutoFantastico;

	// Obstaculos
	for(int i=0; i < 6 ; ++i)
	{
		cuerpo.type        = b2BodyType::b2_staticBody;
		adorno.restitution = 0.2;
		adorno.isSensor    = false;
		adorno.friction    = 0.3f;
		adorno.density     = 0.01f;//Masa de 45.32
		b2CircleShape* pCirculo = new b2CircleShape();
		pCirculo->m_radius = 40;
		adorno.shape       = pCirculo;

		cuerpo.position = b2Vec2((rand()/(float)RAND_MAX)*400+200, (rand()/(float)RAND_MAX)*400+100);
		cuerpo.angle    = 0;

		sf::CircleShape* circulo = new sf::CircleShape(pCirculo->m_radius);
		circulo->setFillColor(sf::Color::Green);

		Obstaculos.push_back( new EntidadEscena(cuerpo, adorno, circulo) );
	}
	m_pAutoFantastico->GetSteeringBehaviors().m_pObstaculos = &Obstaculos;
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().m_pObstaculos = &Obstaculos;

	// Paredes

	//Pared de arriba
	cuerpo.type        = b2BodyType::b2_staticBody;
	adorno.restitution = 0.2;
	adorno.isSensor    = false;
	adorno.friction    = 0.3f;
	adorno.density     = 0.01f;
	pRectangulo->SetAsBox(400, 10, b2Vec2(0.0f, 0.0f), 0);
	adorno.shape       = pRectangulo;

	cuerpo.position = b2Vec2(400, 0);
	cuerpo.angle    = 0;
	sf::RectangleShape* rectangulo = new sf::RectangleShape(sf::Vector2f(800.0f,  20.0f));
	rectangulo->setFillColor(sf::Color::Green);

	Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
	ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, rectangulo) );

	//Pared de abajo
	cuerpo.position = b2Vec2(400, 600);

	Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(0.0f, -1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
	ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, rectangulo) );

	//Pared de izquierda
	cuerpo.position = b2Vec2(0, 300);
	cuerpo.angle = 3.1415f/2.0f;

	Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(1.0f,0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
	ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, rectangulo) );

	//Pared de derecha
	cuerpo.position = b2Vec2(800, 300);
	cuerpo.angle = 3.1415f/2.0f;

	Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(-1.0f,0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
	ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, rectangulo) );



	m_pAutoFantastico->GetSteeringBehaviors().m_pParedes = &Paredes;
	m_pAutoFantasticoCobarde->GetSteeringBehaviors().m_pParedes = &Paredes;
}

void MyGame::Actualizar(const float dt)
{
	m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo = sf::Vector2f(sf::Mouse::getPosition());

	m_pAutoFantastico->Actualizar(dt);

	m_pAutoFantasticoCobarde->Actualizar(dt);

	for(int i=0; i < Obstaculos.size() ; ++i)
		Obstaculos[i]->Actualizar(dt);

	for(int i=0; i < ParedesEscena.size() ; ++i)
		ParedesEscena[i]->Actualizar(dt);

	m_World.Step(m_dt, 10, 10);

	m_World.ClearForces();
}

void MyGame::Dibujar(const float dt)
{
	m_Window.clear();

	m_pAutoFantastico->Dibujar(m_Window);

	m_pAutoFantasticoCobarde->Dibujar(m_Window);

	for(int i=0; i < Obstaculos.size() ; ++i)
		Obstaculos[i]->Dibujar(m_Window);

	for(int i=0; i < ParedesEscena.size() ; ++i)
		ParedesEscena[i]->Dibujar(m_Window);

	#ifdef _DEBUG
		m_World.DebugDraw();

		/*
		b2Transform T = m_pAutoFantastico->m_pCuerpo->GetTransform();
		b2Vec2 adelante(1.0f, 0.0f);
		adelante = b2Mul(T.R, adelante);//transformamos al mundo
		adelante.Normalize();
		adelante *= 200;
		b2Vec2 pos = b2Vec2( m_pAutoFantastico->GetPosicion().x, m_pAutoFantastico->GetPosicion().y );
		pRenderer->DrawSegment(pos, pos+adelante, b2Color(1.0f, 0.0f, 1.0f));
		*/

		//Buscar y Arribar DEBUG
		if( m_pAutoFantastico->GetSteeringBehaviors().isBuscarOn() ||  m_pAutoFantastico->GetSteeringBehaviors().isArribarOn() )
		{
			sf::Vertex objetivo[] =
			{
				sf::Vertex(m_pAutoFantastico->GetPosicion(), sf::Color::White),
				sf::Vertex(m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo, sf::Color::White)
			};

			m_Window.draw(objetivo, 2, sf::Lines);
		}

		//Escapar DEBUG
		if( m_pAutoFantastico->GetSteeringBehaviors().isEscaparOn() )
		{
			sf::CircleShape peligro = sf::CircleShape(5.0f);
			peligro.setFillColor(sf::Color::Red);
			peligro.setPosition(m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo);

			m_Window.draw(peligro);
		}

		//Deambular DEBUG
		if( m_pAutoFantastico->GetSteeringBehaviors().isDeambularOn() )
		{
			b2Vec2 aux = b2Mul(m_pAutoFantastico->GetTransformacion(),b2Vec2(m_pAutoFantastico->GetSteeringBehaviors().m_DeambularDistancia,0.0f));
			sf::CircleShape DeambularCirculo = sf::CircleShape(m_pAutoFantastico->GetSteeringBehaviors().m_DeambularRadio);
			DeambularCirculo.setFillColor(sf::Color(0, 0, 0, 0));
			DeambularCirculo.setOutlineColor(sf::Color::Yellow);
			DeambularCirculo.setOutlineThickness(1.0f);
			DeambularCirculo.setPosition(sf::Vector2f(aux.x, aux.y));

			m_Window.draw(DeambularCirculo);

			aux = b2Mul(m_pAutoFantastico->GetTransformacion(),b2Vec2(m_pAutoFantastico->GetSteeringBehaviors().m_DeambularObjetivo.x+m_pAutoFantastico->GetSteeringBehaviors().m_DeambularDistancia,m_pAutoFantastico->GetSteeringBehaviors().m_DeambularObjetivo.y));
			sf::CircleShape DeambularObjetivo = sf::CircleShape(2.0f);
			DeambularObjetivo.setFillColor(sf::Color(255, 0, 0, 255));
			DeambularObjetivo.setPosition(sf::Vector2f(aux.x, aux.y));

			m_Window.draw(DeambularObjetivo);
		}

		//Interceptar DEBUG
		if( m_pAutoFantastico->GetSteeringBehaviors().isInterceptarOn() )
		{
			sf::CircleShape predicion = sf::CircleShape(5.0f);
			predicion.setFillColor(sf::Color::Magenta);
			predicion.setPosition(m_pAutoFantastico->GetSteeringBehaviors().m_InterceptarPosicionPredicion);

			m_Window.draw(predicion);
		}

		//Evadir DEBUG
		if( m_pAutoFantastico->GetSteeringBehaviors().isEvadirOn() )
		{
			sf::CircleShape predicion = sf::CircleShape(5.0f);
			predicion.setFillColor(sf::Color::Red);
			predicion.setPosition(m_pAutoFantastico->GetSteeringBehaviors().m_EvadirPosicionPredicion);

			m_Window.draw(predicion);
		}

		//Evadir obstaculos DEBUG
		if( m_pAutoFantastico->GetSteeringBehaviors().isEvadirObstaculosOn() )
		{
			float largoRectanguloColision = m_pAutoFantastico->GetSteeringBehaviors().m_EvadirObstaculosRectanguloMin +
				(Norma(m_pAutoFantastico->GetVelocidadLineal())/m_pAutoFantastico->GetVelocidadMax()) * m_pAutoFantastico->GetSteeringBehaviors().m_EvadirObstaculosRectanguloMin;
			b2Vec2 P1 = b2Vec2( 0.0f, m_pAutoFantastico->GetBoundingCircleRadio() );
			b2Vec2 P2 = b2Vec2( largoRectanguloColision, m_pAutoFantastico->GetBoundingCircleRadio() );
			b2Vec2 P3 = b2Vec2( largoRectanguloColision, -m_pAutoFantastico->GetBoundingCircleRadio() );
			b2Vec2 P4 = b2Vec2( 0.0f, -m_pAutoFantastico->GetBoundingCircleRadio() );
			b2Transform LtoW = m_pAutoFantastico->GetTransformacion();
			P1 = b2Mul(LtoW, P1);
			P2 = b2Mul(LtoW, P2);
			P3 = b2Mul(LtoW, P3);
			P4 = b2Mul(LtoW, P4);
			sf::ConvexShape EvadirCaja;
			EvadirCaja.setPointCount(4);
			EvadirCaja.setPoint(0, sf::Vector2f(P1.x, P1.y));
			EvadirCaja.setPoint(1, sf::Vector2f(P2.x, P2.y));
			EvadirCaja.setPoint(2, sf::Vector2f(P3.x, P3.y));
			EvadirCaja.setPoint(3, sf::Vector2f(P4.x, P4.y));
			EvadirCaja.setOutlineThickness(1.0f);
			EvadirCaja.setOutlineColor(sf::Color::Yellow);
			EvadirCaja.setFillColor(sf::Color(0, 0, 0, 0));

			m_Window.draw(EvadirCaja);


			b2Vec2 PosicionColision = b2Mul(LtoW, m_pAutoFantastico->GetSteeringBehaviors().m_EvadirObstaculosPuntoCercaColision);
			sf::CircleShape ColisionPunto = sf::CircleShape(2.0f);
			ColisionPunto.setFillColor(sf::Color(255, 0, 0, 255));

			ColisionPunto.setPosition(PosicionColision.x,PosicionColision.y);
			m_Window.draw(ColisionPunto);

			b2Vec2 PosicionObjeto = b2Mul(LtoW, m_pAutoFantastico->GetSteeringBehaviors().m_EvadirObstaculosPuntoObjetoColision);
			sf::CircleShape ColisionObjeto = sf::CircleShape(2.0f);
			ColisionObjeto.setFillColor(sf::Color(0, 0, 255, 255));

			ColisionObjeto.setPosition(PosicionObjeto.x,PosicionObjeto.y);
			m_Window.draw(ColisionObjeto);

			//Circulo sobre vehiculo
			/*sf::Shape BBCircle = sf::Shape::Circle( sf::Vector2f(0,0),
													m_pAutoFantastico->GetBoundingCircleRadio(),
													sf::Color(0,0,0,0), 1.0f, sf::Color::Yellow);
			BBCircle.SetPosition(m_pAutoFantastico->GetPosicion().x,m_pAutoFantastico->GetPosicion().y);
			m_Window.Draw(BBCircle);
			*/
			//Circulo expandido sobre choque
			sf::CircleShape BBCircle = sf::CircleShape(m_pAutoFantastico->GetSteeringBehaviors().m_EvadirObstaculosRadioExpandido);
			BBCircle.setFillColor(sf::Color(0, 0, 0, 0));
			BBCircle.setOutlineThickness(1.0f);
			BBCircle.setOutlineColor(sf::Color::Yellow);

			b2Vec2 cir = b2Mul(LtoW, m_pAutoFantastico->GetSteeringBehaviors().m_EvadirObstaculosPuntoObjetoColision);
			BBCircle.setPosition(cir.x, cir.y);
			m_Window.draw(BBCircle);
		}

		//Evadir paredes DEBUG
		if( m_pAutoFantastico->GetSteeringBehaviors().isEvadirObstaculosOn() )
		{
			std::vector<SteeringBehaviors::Sensores> &sensores = m_pAutoFantastico->GetSteeringBehaviors().m_Sensores;
			for(int s=0; s < sensores.size() ; ++s)
			{
				sf::Vertex normal[] =
				{
					sf::Vertex(sensores[s].GetOrigen(), sf::Color::Green),
					sf::Vertex(sensores[s].GetOrigen() + sf::Vector2f(sensores[s].GetDireccion().x * 200, sensores[s].GetDireccion().y * 200), sf::Color::Green)
				};

				m_Window.draw(normal, 1.0f, sf::Lines);

				//Colisiones
				sf::CircleShape ColisionPunto = sf::CircleShape(2.0f);
				ColisionPunto.setFillColor(sf::Color(255, 0, 0, 255));

				ColisionPunto.setPosition(m_pAutoFantastico->GetSteeringBehaviors().m_EvadirParedesPuntoColision[0].x,m_pAutoFantastico->GetSteeringBehaviors().m_EvadirParedesPuntoColision[0].y);
				m_Window.draw(ColisionPunto);
				ColisionPunto.setPosition(m_pAutoFantastico->GetSteeringBehaviors().m_EvadirParedesPuntoColision[1].x,m_pAutoFantastico->GetSteeringBehaviors().m_EvadirParedesPuntoColision[1].y);
				m_Window.draw(ColisionPunto);
				ColisionPunto.setPosition(m_pAutoFantastico->GetSteeringBehaviors().m_EvadirParedesPuntoColision[2].x,m_pAutoFantastico->GetSteeringBehaviors().m_EvadirParedesPuntoColision[2].y);
				m_Window.draw(ColisionPunto);
			}

		}

		//Esconderse DEBUG
		if( m_pAutoFantasticoCobarde->GetSteeringBehaviors().isEsconderseOn() )
		{
			std::vector<sf::Vector2f> &escondites = m_pAutoFantasticoCobarde->GetSteeringBehaviors().m_EscondersePuntoEscondito;
			for(int e=0; e < escondites.size() ; ++e)
			{
				sf::CircleShape ECircle = sf::CircleShape(2.0f);
				ECircle.setFillColor(sf::Color(255, 0, 0, 255));
				ECircle.setPosition(escondites[e].x, escondites[e].y);
				m_Window.draw(ECircle);
			}
		}

	#endif

	m_Window.display();
}

void MyGame::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::VehiculoParticula].loadFromFile("../../Comportamientos/Recursos/Vehiculo2.png") )
			exit(0);
	if( !m_ManagerDeImagenes[IDImagen::VehiculoCobardeParticula].loadFromFile("../../Comportamientos/Recursos/VehiculoCobarde2.png") )
			exit(0);
}