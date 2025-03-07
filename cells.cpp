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
        // If 4, return the four directions.
        return { {-1,0}, {1,0}, {0,-1}, {0,1} };
    } 
    else {
        // if 8, return the eight directions.
        return { {-1,0}, {1,0}, {0,-1}, {0,1},
                 {-1,-1}, {-1, 1}, {1,-1}, {1,1}};
        }

    }

 // countCells Method: Count number of cells within a blob at a given starting cell.   
int countCells(std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited, int r, int c, int CONN_type) {
    // Initialize rows and cols based on grid size.
    int rows = grid.size();
    int cols = grid[0].size();

    // Base Case: If the cell is out of bounds, empty, or visited, end method by return else continue.
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0 || visited[r][c]) {
        return 0;
    }

    // Mark cell as visited.
    visited[r][c] = true;
    // Initialize cell count to 1 for first cell after base case check.
    int count = 1;

    // Loop through neighbors using neighboring directions from getNeighbors.
    for (const auto& direction : getNeighbors(CONN_type)) {
        // Calculate neighbor row and col from current row and col and directional row and col.
        int neighRow = r + direction.first;
        int neighCol = c + direction.second;
        // Call countCells to recursively count cells and add to cell count.
        count += countCells(grid, visited, neighRow, neighCol, CONN_type);

    }
    // Return count.
    return count;    

}

// Main
int main(int argc, char* argv[]) {
    // For debugging purposes.
    if (argc != 7) {
        std::cout << "Error: incorrect amount of arguements." << std::endl;
        return 1;
    }

    // Store command line arguements in corresponding variables
    std::string fileName = argv[1];
    int M = std::stoi(argv[2]);
    int N = std::stoi(argv[3]);
    int X = std::stoi(argv[4]) - 1; // Subtracting 1 to account for index starting at 0.
    int Y = std::stoi(argv[5]) - 1; // Subtracting 1 to account for index starting at 0.
    int CONN = std::stoi(argv[6]);

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

    // Call countCells and store result in cells.
    int cells = countCells(grid, visited, X, Y, CONN);

    // Output result.
    std::cout << cells << std::endl;

    return 0;
}
