#include "drawingtool.h"


DrawingTool::DrawingTool(): DrawingTool(QColor("Black"))
{

}

DrawingTool::DrawingTool(QColor color) : color_(color), brushSize(1)
{

}

QColor DrawingTool::getToolColor()
{
    return color_;
}

void DrawingTool::setToolColor(QColor color)
{
    color_ = color;
}

void DrawingTool::setBrushSize(int size)
{
    brushSize = size;
}

int DrawingTool::getBrushSize()
{
    return brushSize;
}
