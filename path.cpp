#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <limits>

// getNeighbors Method: return different neighbor directions/points.
std::vector<std::pair<int,int>> getNeighbors() {
        // return the four directions.
        return { {-1,0}, {1,0}, {0,-1}, {0,1} };
    }

// findLowestHighest Method: find and return lowest and highest elevation points.
std::pair<std::pair<int, int>, std::pair<int, int>> findLowestHighest(const std::vector<std::vector<int>>& grid) {
    // Initialize rows and cols based on grid size.
    int M = grid.size();
    int N = grid[0].size();

    // Initialize to max and min values.
    int minE = std::numeric_limits<int>::max();
    int maxE = std::numeric_limits<int>::min();

    // Declare pair variables lowest and highest.
    std::pair<int, int> lowest, highest;

    // Loop through the grid.
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // Check if cell elevation is lower than min elevation.
            if (grid[i][j] < minE) {
                // Replace min elevation with current grid point.
                minE = grid[i][j];
                // Store grid point in lowest.
                lowest = {i, j};
            }
            // Check if cell elevation is higher than max elevation.
            if (grid[i][j] > maxE) {
                // Replace max elevation with current grid point.
                maxE = grid[i][j];
                // Store grid point in highest.
                highest = {i, j};
            }
        }
    }
    
    // Return lowest and highest as pair.
    return {lowest, highest};
}

// Check if path between lowest elevation to highest elevation exists. 
bool checkPath(const std::vector<std::vector<int>>& grid, int row_1, int col_1, int row_M, int col_N) {
    // Initialize rows and cols based on grid size.
    int M = grid.size();
    int N = grid[0].size();
    // Declare 2D visited vector.
    std::vector<std::vector<bool>> visited(M, std::vector<bool>(N, false));
    // Declare queue.
    std::queue<std::pair<int, int>> queue;
    // Push starting cell.
    queue.push({row_1, col_1});
    // Mark it as visited.
    visited[row_1][col_1] = true;

    // store neighbor directions from getNeighbor.
    auto directions = getNeighbors();

    // Loop through queue while queue is not empty.
    while(!queue.empty()) {
        // Store front cell point, remove front cell.
        auto [currentRow, currentCol] = queue.front();
        queue.pop();

        // Check if current cell is highest elevation cell.  
        if (currentRow == row_M && currentCol == col_N) {
            // Return true, path found.
            return true;
        }

        // Loop through all directions.
        for (const auto& dir : directions) {
            // Calculate new row and col from current row and col and directional row and col.
            int newRow = currentRow + dir.first;
            int newCol = currentCol + dir.second;

            // Check if new cell is in bounds and not visited.
            if (newRow >= 0 && newRow < M && newCol >= 0 && newCol < N && !visited[newRow][newCol]) {
                // Check if new cell's elevation is greater than or equal to current cell's elevation.
                if (grid[newRow][newCol] >= grid[currentRow][currentCol]) {
                    // Mark new cell as visited.
                    visited[newRow][newCol] = true;
                    // Add new cell to queue.
                    queue.push({newRow, newCol});
                }
            }
         }
      }
    // Base Case return statement.
    return false;
}

// to_string Method: format output as string.
std::string to_string(int Lr, int Lc, int Hr, int Hc, bool ifPath) {
    // Declare string variable.
    std::string pathStatus;
    // If path exists pathStatus equals yes.
    if (ifPath) {
        pathStatus = "yes";
    }
    // If path does not exists pathStatus equals no.
     else {
        pathStatus = "no";
    }

    // Return string format of output.
    return std::to_string(Lr + 1) + " " + std::to_string(Lc + 1) + " " + 
           std::to_string(Hr + 1) + " " + std::to_string(Hc + 1) + " " + pathStatus;

}

// Main.
int main(int argc, char* argv[]) {
    // For debugging purposes.
    if (argc != 4) {
        std::cout << "Error: incorrect amount of arguements." << std::endl;
        return 1;
    }

    // Store command line arguements in corresponding variables.
    std::string fileName = argv[1];
    int M = std::stoi(argv[2]);
    int N = std::stoi(argv[3]);

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

    // Call findHighestLowest method and store pair in pair [lowest, highest].
    auto [lowest, highest] = findLowestHighest(grid);
    // Store lowest x and y values separately.
    int Lr = lowest.first, Lc = lowest.second;
    // Store highest x and y values separately.
    int Hr = highest.first, Hc = highest.second;

    // Call checkPath and store in ifPath bool.
    bool ifPath = checkPath(grid, Lr, Lc, Hr, Hc);

    // Print output.
    std::cout << to_string(Lr, Lc, Hr, Hc, ifPath) << std::endl;

    return 0;
}
