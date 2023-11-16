#include "drawingtool.h"

DrawingTool::DrawingTool() : DrawingTool(QColor("Black"))
{
}

DrawingTool::DrawingTool(QColor color)
    : brushColor(color),
      brushSize(1)
{
}

QColor DrawingTool::getToolColor()
{
    return brushColor;
}

void DrawingTool::setToolColor(QColor color)
{
    this->brushColor = color;
}

void DrawingTool::setBrushSize(int size)
{
    brushSize = size;
}

int DrawingTool::getBrushSize()
{
    return brushSize;
}
