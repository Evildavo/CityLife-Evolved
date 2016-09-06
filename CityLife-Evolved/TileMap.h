#ifndef CITYLIFE_TILE_MAP_H

namespace CityLife {


	// Grid of tile sprites.
	class TileMap {
	public:
		typedef int Index;

		// Creates a tile map.
		// @param source: The source texture. 
		// @param nSourceColumns, nSourceRows: The size of a single tile in the source texture in pixels.
		// @param nColumns, nRows: Number of columns and rows in the tile map.
		TileMap(SDL_Texture* source,
			int nSourceColumns, int nSourceRows,
			int nColumns, int nRows);

		// Sets the tile at the given column and row (zero-based) to the specified source tile index.
		void setTile(int column, int row, int sourceIndex) {
			tileMap[row][column] = sourceIndex;
		}

		// Returns the index of the tile at the given column and row (zero-based) in the source texture.
		int getIndex(int sourceColumn, int sourceRow) const { 
			return sourceRow * nSourceColumns + sourceColumn;
		}

		// Renders the tilemap at the given offset in pixels with a scale multiplier (integer). 
		void render(SDL_Renderer* renderer, int x = 0, int y = 0, int scale = 1);

	private:
		SDL_Texture* source;
		int nSourceColumns, nSourceRows;
		int sourceTileWidth, sourceTileHeight;
		int nColumns, nRows;
		std::vector<std::vector<Index>> tileMap;
	};
	


}

#endif