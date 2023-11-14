#include "drawingtool.h"


DrawingTool::DrawingTool(): color_(QColor("Black"))
{

}

DrawingTool::DrawingTool(int red, int green, int blue, int alpha) : color_(red, green, blue, alpha)
{

}

DrawingTool::DrawingTool(QColor color) : color_(color)
{

}

//DrawingTool::DrawingTool(const DrawingTool& other)
//{
//    color_ = other.color_;
//}

//DrawingTool& DrawingTool::operator=(DrawingTool other)
//{
//    std::swap(color_, other.color_);

//    return *this;
//}

QColor DrawingTool::getToolColor()
{
    return color_;
}

void DrawingTool::setToolColor(QColor color)
{
    color_ = color;
}
