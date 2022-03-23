#include "SFMLRenderer.h"

SFMLRenderer::SFMLRenderer(RenderWindow *window)
{
	wnd=window;
}

SFMLRenderer::~SFMLRenderer(void)
{ }

void SFMLRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape poligono;
	poligono.setFillColor(Color(0, 0, 0, 0));

	poligono.setOutlineColor(box2d2SFMLColor(color));

	poligono.setPointCount(vertexCount);
	for(int i = 0; i < vertexCount; ++i)
		poligono.setPoint(i, Vector2f(vertices[i].x, vertices[i].y));

	wnd->draw(poligono);
}

void SFMLRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){

	sf::ConvexShape poligono;
	poligono.setFillColor(box2d2SFMLColor(color));

	poligono.setOutlineColor(box2d2SFMLColor(color));

	poligono.setPointCount(vertexCount);
	for(int i = 0; i < vertexCount; ++i)
		poligono.setPoint(i, Vector2f(vertices[i].x, vertices[i].y));

	wnd->draw(poligono);
}

void SFMLRenderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(center.x, center.y);
	circle.setFillColor(Color(0, 0, 0, 0));
	circle.setOutlineColor(box2d2SFMLColor(color));

	wnd->draw(circle);
}

void SFMLRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(center.x, center.y);
	circle.setFillColor(box2d2SFMLColor(color));

	circle.setOutlineColor(box2d2SFMLColor(color));

	wnd->draw(circle);
}

void SFMLRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(p1.x, p1.y), box2d2SFMLColor(color)),
		sf::Vertex(sf::Vector2f(p2.x, p2.y), box2d2SFMLColor(color))
	};

	wnd->draw(line, 2, sf::Lines);
}

void SFMLRenderer::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
	const float k_axisScale = 20.0f;
	p2 = p1 + k_axisScale * xf.q.GetXAxis();

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(p1.x, p1.y), Color::Red),
		sf::Vertex(sf::Vector2f(p2.x, p2.y), Color::Red)
	};
	wnd->draw(line, 2, sf::Lines);


	p2 = p1 + k_axisScale * xf.q.GetYAxis();

	sf::Vertex line2[] =
	{
		sf::Vertex(sf::Vector2f(p1.x, p1.y), Color::Green),
		sf::Vertex(sf::Vector2f(p2.x, p2.y), Color::Green)
	};
	wnd->draw(line2, 2, sf::Lines);
}

void SFMLRenderer::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	// Box2D utiliza un diametro fijo de 8.0f que es exagerado, por eso usamos uno de 1.0f
	//const float radius = size / 2.0f;
	const float radius = 0.5f;
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(p.x, p.y);
	circle.setFillColor(box2d2SFMLColor(color));

	circle.setOutlineColor(box2d2SFMLColor(color));

	wnd->draw(circle);
}

void SFMLRenderer::DrawString(int x, int y, const char* string, ...)
{
	sf::Text text;

	text.setString(string);
	text.setPosition(x, y);

	wnd->draw(text);
}

void SFMLRenderer::DrawAABB(b2AABB* aabb, const b2Color& color)
{
	const auto halfSize = aabb->GetExtents();
	sf::RectangleShape rectangle(sf::Vector2f(halfSize.x, halfSize.y) * 2.0f);
	rectangle.setOrigin(halfSize.x, halfSize.y);
	const auto center = aabb->GetCenter();
	rectangle.setPosition(center.x, center.y);
	rectangle.setFillColor(Color(0, 0, 0, 0));
	rectangle.setOutlineColor(box2d2SFMLColor(color));

	wnd->draw(rectangle);
}

Color SFMLRenderer::box2d2SFMLColor(const b2Color& _color)
{
	Uint8 R, G, B;
	R = (Uint8)(_color.r * 255);
	G = (Uint8)(_color.g * 255);
	B = (Uint8)(_color.b * 255);

	return Color(R,G,B);
}