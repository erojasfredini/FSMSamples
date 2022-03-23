//-----------------------------------------------------
//Clase utilitaria que provee los callbacks requeridos 
//por SFML para dibujar los objetos que esta simulando
//-----------------------------------------------------

#pragma once
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

using namespace sf;

class SFMLRenderer : public b2Draw//b2DebugDraw
{
private:
	RenderWindow *wnd;

public:
	SFMLRenderer(RenderWindow *window);
	~SFMLRenderer(void);

	inline Color box2d2SFMLColor(const b2Color &_color);
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	void DrawTransform(const b2Transform& xf) override;
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;
	void DrawString(int x, int y, const char* string, ...);
	void DrawAABB(b2AABB* aabb, const b2Color& color);
};