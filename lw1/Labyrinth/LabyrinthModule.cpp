#include "LabyrinthModule.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

const char EmptyCell = ' ';
const char WallCell = '#';
const char StartPosCell = 'A';
const char FinishPosCell = 'B';
const char PathCell = '.';

const CellType DecodedEmptyCell = 0;
const CellType DecodedWallCell = 1;
const CellType DecodedStartPosCell = 2;
const CellType DecodedFinishPosCell = 3;
const CellType DecodedPathCell = 4;

const int NeighbourRows[] = { -1, 0, 0, 1 };
const int NeighbourColumns[] = { 0, -1, 1, 0 };

struct Point
{
	uint32_t x;
	uint32_t y;
};

struct LabCell
{
	Point coords;
	CellType cellType;
};

struct QueueNode
{
	Point currentPoint;
	Point previousPoint;
};

CellType MapLabyrinthSymbolToCell(char symbol)
{
	switch (symbol)
	{
	case EmptyCell:
		return DecodedEmptyCell;
	case WallCell:
		return DecodedWallCell;
	case StartPosCell:
		return DecodedStartPosCell;
	case FinishPosCell:
		return DecodedFinishPosCell;
	default:
		throw std::runtime_error("No such symbol in labyrinth");
	}
}

char MapCellToLabyrinthSymbol(CellType cell)
{
	switch (cell)
	{
	case DecodedEmptyCell:
		return EmptyCell;
	case DecodedWallCell:
		return WallCell;
	case DecodedStartPosCell:
		return StartPosCell;
	case DecodedFinishPosCell:
		return FinishPosCell;
	case DecodedPathCell:
		return PathCell;
	default:
		throw std::runtime_error("No such cell in labyrinth " + cell);
	}
}

bool IsLabyrintValid(const Labyrinth& labyrinth)
{
	uint32_t countOfStartCells = 0;
	uint32_t countOfEndCells = 0;

	for (uint32_t i = 0; i < labyrinth.size(); i++)
	{
		LabytinthLine labyrinthLine = labyrinth[i];
		for (uint32_t j = 0; j < labyrinthLine.size(); j++)
		{
			CellType labyrinthCell = labyrinthLine[j];
			if (labyrinthCell == DecodedStartPosCell)
			{
				countOfStartCells++;
			}
			if (labyrinthCell == DecodedFinishPosCell)
			{
				countOfEndCells++;
			}
		}
	}

	return countOfStartCells == 1 && countOfEndCells == 1;
}

bool IsCellCoordsValid(Point coords)
{
	return (coords.y >= 0) && (coords.y < LabyrinthMaxSize) && (coords.x >= 0) && (coords.x < LabyrinthMaxSize);
}

LabytinthLine ReadLabyrinthLine(const std::string& labyrinthLine)
{
	size_t i = 0;
	LabytinthLine decodedLine{};
	for (char labyrinthSymbol : labyrinthLine)
	{
		decodedLine[i] = MapLabyrinthSymbolToCell(labyrinthLine[i]);
		i++;
	}

	return decodedLine;
}

Labyrinth ReadLabyrinth(const std::string& inputFileName)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading");
	}

	Labyrinth labyrinth{};
	std::string line;
	uint32_t linePos = 0;

	while (std::getline(inputFile, line))
	{
		if (linePos > LabyrinthMaxSize)
		{
			throw std::runtime_error("Labyrinth height bigger than " + LabyrinthMaxSize);
		}
		if (line.length() > LabyrinthMaxSize)
		{
			throw std::runtime_error("Labyrinth width bigger than " + LabyrinthMaxSize);
		}

		labyrinth[linePos] = ReadLabyrinthLine(line);
		linePos++;
	}

	return labyrinth;
}

Point GetPointCoordsByCellType(const Labyrinth& labyrinth, const CellType cellType)
{
	for (uint32_t i = 0; i < labyrinth.size(); i++)
	{
		LabytinthLine labyrinthLine = labyrinth[i];
		for (uint32_t j = 0; j < labyrinthLine.size(); j++)
		{
			if (CellType cell = labyrinthLine[j]; cell == cellType)
			{
				return Point{ i, j };
			}
		}
	}
	return Point{ LabyrinthMaxSize + 1, LabyrinthMaxSize + 1 };
}

void PrintPath(Labyrinth& labyrinth, const Point& startCellCoords, Point finishCellCoords, const Point previousPoints[LabyrinthMaxSize][LabyrinthMaxSize])
{
	std::stack<Point> invertedPath;
	while (!(startCellCoords.x == finishCellCoords.x && startCellCoords.y == finishCellCoords.y))
	{
		invertedPath.push(finishCellCoords);
		Point tempPoint = previousPoints[finishCellCoords.x][finishCellCoords.y];
		finishCellCoords = tempPoint;
	}
	invertedPath.push(startCellCoords);

	while (!invertedPath.empty())
	{
		Point currentPoint = invertedPath.top();
		invertedPath.pop();
		labyrinth[currentPoint.x][currentPoint.y] = DecodedPathCell;
	}
}

void BFS(Labyrinth& labyrinth, const Point& startCellCoords, const Point& finishCellCoords)
{
	if (!labyrinth[startCellCoords.x][startCellCoords.y] || !labyrinth[finishCellCoords.x][finishCellCoords.y])
	{
		return;
	}
	Point previousPoints[LabyrinthMaxSize][LabyrinthMaxSize];
	bool visited[LabyrinthMaxSize][LabyrinthMaxSize];
	memset(visited, false, sizeof visited);
	visited[startCellCoords.x][startCellCoords.y] = true;
	std::queue<QueueNode> queue;
	QueueNode startPos = { startCellCoords, Point{ LabyrinthMaxSize + 1, LabyrinthMaxSize + 1 } };
	queue.push(startPos);
	previousPoints[startCellCoords.x][finishCellCoords.y] = Point{ LabyrinthMaxSize + 1, LabyrinthMaxSize + 1 };
	while (!queue.empty())
	{
		Point currentCell = queue.front().currentPoint;
		if (currentCell.x == finishCellCoords.x && currentCell.y == finishCellCoords.y)
		{
			PrintPath(labyrinth, startCellCoords, finishCellCoords, previousPoints);
			return;
		}
		queue.pop();
		const int countOfCells = 4;
		for (uint32_t i = 0; i < countOfCells; i++)
		{
			uint32_t nextRow = currentCell.x + NeighbourRows[i];
			uint32_t nextColumn = currentCell.y + NeighbourColumns[i];
			if (IsCellCoordsValid(Point{ nextRow, nextColumn })
				&& (labyrinth[nextRow][nextColumn] == DecodedEmptyCell || labyrinth[nextRow][nextColumn] == DecodedFinishPosCell)
				&& !visited[nextRow][nextColumn])
			{
				visited[nextRow][nextColumn] = true;
				previousPoints[nextRow][nextColumn] = currentCell;
				queue.push(QueueNode{ Point{ nextRow, nextColumn }, currentCell });
			}
		}
	}
}

void FindShortestPath(Labyrinth& labyrinth)
{
	if (!IsLabyrintValid(labyrinth))
	{
		throw std::runtime_error("Incorrect labyrinth");
	}
	Point startPosCoords = GetPointCoordsByCellType(labyrinth, DecodedStartPosCell);
	Point finishPosCoords = GetPointCoordsByCellType(labyrinth, DecodedFinishPosCell);
	BFS(labyrinth, startPosCoords, finishPosCoords);
	labyrinth[startPosCoords.x][startPosCoords.y] = DecodedStartPosCell;
	labyrinth[finishPosCoords.x][finishPosCoords.x] = DecodedFinishPosCell;
}

void WriteLabyrinth(const std::string& outputFileName, const Labyrinth& labyrinth)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFileName + " for writing");
	}
	for (LabytinthLine labyrinthLine : labyrinth)
	{
		for (CellType labyrinthCell : labyrinthLine)
		{
			outputFile << MapCellToLabyrinthSymbol(labyrinthCell);
		}
		outputFile << std::endl;
	}
	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}