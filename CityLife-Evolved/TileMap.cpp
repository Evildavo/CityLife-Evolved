#include "pch.h"
#include "TileMap.h"

namespace CityLife {

	TileMap::TileMap(SDL_Texture* source,
		int nSourceColumns, int nSourceRows,
		int nColumns, int nRows)
		:
		source(source), nSourceColumns(nSourceColumns), nSourceRows(nSourceRows),
		nColumns(nColumns), nRows(nRows)
	{
		int w, h;
		SDL_QueryTexture(source, NULL, NULL, &w, &h);
		sourceTileWidth = w / nSourceColumns;
		sourceTileHeight = h / nSourceRows;

		// Create the map.
		const Index DEFAULT_INDEX = 0;
		for (int i = 0; i < nRows; i++) {
			std::vector<Index> row;
			for (int j = 0; j < nColumns; j++) {
				row.push_back(DEFAULT_INDEX);
			}
			tileMap.push_back(row);
		}
	}

	void TileMap::render(SDL_Renderer* renderer, int x, int y, int scale) {
		SDL_Rect sourceRect, destinationRect;
		Index index;
		for (int row = 0; row < nRows; row++) {
			for (int column = 0; column < nColumns; column++) {
				index = tileMap[row][column];
				sourceRect.x = (index % nSourceColumns) * sourceTileWidth;
				sourceRect.y = int(index / nSourceColumns) * sourceTileHeight;
				sourceRect.w = sourceTileWidth;
				sourceRect.h = sourceTileHeight;
				destinationRect.x = x + column * sourceTileWidth * scale;
				destinationRect.y = y + row * sourceTileHeight * scale;
				destinationRect.w = sourceTileWidth * scale;
				destinationRect.h = sourceTileHeight * scale;
				SDL_RenderCopy(renderer, source, &sourceRect, &destinationRect);
			}
		}
	}

}