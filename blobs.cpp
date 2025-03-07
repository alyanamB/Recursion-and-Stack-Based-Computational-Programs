#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>

// getNeighbors Method: return different neighbor directions/points.
std::vector<std::pair<int,int>> getNeighbors(int CONN_type) {
    // Check if connection type is 4 or 8.
    if (CONN_type == 4) {
        // If 4, return the four neighbor directions.
        return { {-1,0}, {1,0}, {0,-1}, {0,1} };
    } 
    else {
        // if 8, return the eight neighbor directions.
        return { {-1,0}, {1,0}, {0,-1}, {0,1},
                 {-1,-1}, {-1, 1}, {1,-1}, {1,1}};
        }

    }

// countBlobs Methods: Count the blobs in the grid.
void countBlobs(std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited, int r, int c, int CONN_type) {
    // Initialize rows and cols based on grid size.
    int rows = grid.size();
    int cols = grid[0].size();

    // Base Case: If the cell is out of bounds, empty, or visited,end method by return else continue.
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0 || visited[r][c]) {
        return;
    }

    // Mark cell as visited.
    visited[r][c] = true;

    // Loop through neighbors using neighboring directions from getNeighbors.
    for (const auto& direction : getNeighbors(CONN_type)) {
        // Calculate neighbor row and col from current row and col and directional row and col.
        int neighRow = r + direction.first;
        int neighCol = c + direction.second;
        // Call countBlobs to recursively mark all connected cells in a blob as visited and check the neighboring cells.
        countBlobs(grid, visited, neighRow, neighCol, CONN_type);

    }  
}

// Main. 
int main(int argc, char* argv[]) {
    // For debugging purposes.
    if (argc != 5) {
        std::cout << "Error: incorrect amount of arguements." << std::endl;
        return 1;
    }

    // Store command line arguements in corresponding variables.
    std::string fileName = argv[1];
    int M = std::stoi(argv[2]);
    int N = std::stoi(argv[3]);
    int CONN = std::stoi(argv[4]);

    // Open file using ifstream.
    std::ifstream file(fileName);

    // For debugging purposes.
    if (!file) {
        std::cout << "Could not open file." << std::endl;
        return 1;
    }

    // 2D vector to store grid.
    std::vector<std::vector<int>> grid(M, std::vector<int>(N));
    // Parse through file and input values into grid 2D vector.
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            file >> grid[i][j];
        }
    }

    // Initialize 2D vector visited that stores visited cells.
    std::vector<std::vector<bool>> visited(M, std::vector<bool>(N, false));
    // Initialize blobCount. 
    int blobCount = 0;

    // Iterate through entire grid of cells.
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // Check if cell is part of a blob and is not visited yet.
            if (grid[i][j] == 1 && !visited[i][j]) {
                // Call countBlobs.
                countBlobs(grid, visited, i, j, CONN);
                // Add to blobCount.
                blobCount++;
            }
        }
    }

    // Output result.
    std::cout << blobCount << std::endl;
    return 0;
}
