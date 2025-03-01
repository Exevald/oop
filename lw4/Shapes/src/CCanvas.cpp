#include "CCanvas.h"
#include <iomanip>

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) const
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(startPoint.x), static_cast<float>(startPoint.y))),
		sf::Vertex(sf::Vector2f(static_cast<float>(endPoint.x), static_cast<float>(endPoint.y)))
	};

	line[0].color = sf::Color(lineColor);
	line[1].color = sf::Color(lineColor);

	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t outlineColor) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}

	polygon.setFillColor(sf::Color(fillColor));
	polygon.setOutlineColor(sf::Color(outlineColor));
	polygon.setOutlineThickness(1.0f);

	m_window.draw(polygon);
}

void CCanvas::FillRect(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor) const
{
	sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	rectangle.setPosition(static_cast<float>(coordinates.x), static_cast<float>(coordinates.y));
	rectangle.setFillColor(sf::Color(fillColor));
	rectangle.setOutlineColor(sf::Color(outlineColor));
	rectangle.setOutlineThickness(1.0f);

	m_window.draw(rectangle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(static_cast<float>(center.x - radius), static_cast<float>(center.y - radius));
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineColor(sf::Color(outlineColor));
	circle.setOutlineThickness(1.0f);

	m_window.draw(circle);
}

std::string CCanvas::Uint32ToHexString(uint32_t value)
{
	std::stringstream ss;
	ss << std::hex << std::setw(6) << std::setfill('0') << value;
	return ss.str();
}
