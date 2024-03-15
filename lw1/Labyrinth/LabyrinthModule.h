#pragma once

#include <array>
#include <string>

typedef int CellType;
const int LabyrinthMaxSize = 100;

typedef std::array<CellType, LabyrinthMaxSize> LabytinthLine;
typedef std::array<LabytinthLine, LabyrinthMaxSize> Labyrinth;

Labyrinth ReadLabyrinth(const std::string& inputFileName);
bool IsLabyrintValid(const Labyrinth& labyrinth);
void FindShortestPath(Labyrinth& labyrinth);
void WriteLabyrinth(const std::string& outputFileName, const Labyrinth& labyrinth);