#include <iostream>
#include <vector>
using namespace std;


void displaySudoku(int arr[9][9]) {                 //printing every element of the sudoku board
    cout << "-------------------------" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            cout << arr[j][i] << " ";
        cout << endl;
    }
    cout << "-------------------------" << endl;

}

bool isallowed(int arr[9][9], int row, int col, int n)        //checking current row and column
{
    if (arr[row][col] != 0) return false;
    bool result = true;
    int grid_x = (col / 3) * 3;
    int grid_y = (row / 3) * 3;
    for (int i = 0; i < 9; i++) {
        if (arr[row][i] == n) { result = false; break; }        //for rows
        if (arr[i][col] == n) { result = false; break; }        //columns
        if (arr[grid_y + i / 3][grid_x + i % 3] == n) { result = false; break; }
    }
    return result;
}

void nextEmpty(int arr[9][9], int row, int col, int& rowNext, int& colNext)
{

    int Next_index = 9 * 9 + 1;
    for (int i = row * 9 + col + 1; i < 9 * 9; i++) {
        if (arr[i / 9][i % 9] == 0) {

            Next_index = i;
            break;
        }
    }
    rowNext = Next_index / 9;
    colNext = Next_index % 9;
    //cout << row << "," << col << "|" << rowNext << "," << colNext << endl;
}

void Array_copy(int arr[9][9], int arrCpy[9][9]) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            arrCpy[j][i] = arr[j][i];
}
std::vector<int> find_valid(int arr[9][9], int row, int col) {
    vector<int> valid = {};
    for (int n = 1; n <= 9; n++)
        if (isallowed(arr, row, col, n)) valid.push_back(n);
    return valid;
}


bool solve_Sudoku(int arr[9][9], int row, int col)
{
    //system("cls");
    //printSudoku9x9(arr);

    if (row > 8) return true;
    if (arr[row][col] != 0) {
        int rowNext, colNext;
        nextEmpty(arr, row, col, rowNext, colNext);
        return solve_Sudoku(arr, rowNext, colNext);
    }

    std::vector<int> valid = find_valid(arr, row, col);

    if (valid.size() == 0) {
        
        return false; 
    
    };

    bool result = false;
    for (int i = 0; i < valid.size(); i++) {
        int n = valid[i];
        int arrCpy[9][9];
        Array_copy(arr, arrCpy);
        //cout << "(" << row << "," << col << ") =>" << n << endl;
        arrCpy[row][col] = n;
        int rowNext = row;
        int colNext = col;
        nextEmpty(arrCpy, row, col, rowNext, colNext);
        if (solve_Sudoku(arrCpy, rowNext, colNext)) {
            Array_copy(arrCpy, arr);
            result = true;
            break;
        }
    }
    return result;
}


int main(int argc, char** argv)
{
    int board[9][9] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
    int board2[9][9] = {
        {8,0,0,0,0,0,0,0,0},
        {0,0,3,6,0,0,0,0,0},
        {0,7,0,0,9,0,2,0,0},
        {0,5,0,0,0,7,0,0,0},
        {0,0,0,0,4,5,7,0,0},
        {0,0,0,1,0,0,0,3,0},
        {0,0,1,0,0,0,0,6,8},
        {0,0,8,5,0,0,0,1,0},
        {0,9,0,0,0,0,4,0,0}
    };
    
    if (solve_Sudoku(board, 0, 0)) cout << "successfully solved board 1!" << std::endl;
    displaySudoku(board);
    if (solve_Sudoku(board2, 0, 0)) cout << "successfully solved board 2!" << std::endl;
    displaySudoku(board2);

    return 0;
}