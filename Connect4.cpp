#include<iostream>
using namespace std;


// Connect4 attempt

bool validInput(char map[6][7], int column){
    // Gotta check if it is a valid row (only 1-7)
    if (column < 0 || column > 6){
        cout << "Not a valid row value!" << endl;
        return false;
    }else{
        // Gotta check if the row is not full
        bool full = true;
        for (int i = 0; i < 6; i++){
            if (map[i][column] == '-'){
                full = false;
            }
        }
        //cout << "The column " << column << " is (1 = full, 0 = not full)" << full << endl;
        if (full){
            cout << "The column is full!" << endl;
        }
        return (!full);
    }
    return false; // Just so c++ doesnt scream at me
}

bool mapFull(char map[6][7]){
    bool full = true;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            if (map[i][j] == '-'){
                full = false;
            }
        }
    }
    return full;
}
void printMap(char map[6][7]){
    cout << endl;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            if (j==0){
                cout <<"|";
            }
            if (j == 6){
                cout << map[i][j] << "|"<<endl;
                //cout << endl;
            }else{
                cout << map[i][j] << '|';
            }
        }
    }
    cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
    cout << " 1 2 3 4 5 6 7" << endl<<endl;
}

void updateMap(char map[6][7], int inputCol, int currentPlayer){
    //We know that the input is valid and that there is an empty space in the column
    // Now we need to identify the lowest row and put the space in there
    // Player 1 will be o and player 2 will be +
    char currentChar;

    if (currentPlayer == 1){
        currentChar = 'o';   
    }else{currentChar = '+';}

    // Goes from down to up, and that way it clears the first blank row it sees
    for (int i = 5; i >= 0; i--){
        if (map[i][inputCol] == '-'){
            map[i][inputCol] = currentChar;
            break;
        }
    }
}

bool checkHorizontalWin(char map[6][7], int currentPlayer){
    // We gonna check the rows and see if there are any 4 connected in one row

    // We have 7 cols. 7-4 = 3
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
            if ((map[i][j] == map[i][j+1]) && (map[i][j+1] == map[i][j+2]) && (map[i][j+2] == map[i][j+3]) && (map[i][j] != '-')){
                if (currentPlayer == 1){
                    cout << "Player 1 won horizontally!" << endl;
                    return true;
                }else{
                    cout << "Player 2 won horizontally!" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

//Does not work
bool checkVerticalWin(char map[6][7], int currentPlayer){
    for (int j = 0; j < 7; j++){
        for (int i = 0; i < 3; i++){
            if ((map[i][j] == map[i+1][j]) && (map[i+1][j] == map[i+2][j]) && (map[i+2][j] == map[i+3][j]) && (map[i][j] != '-')){
                if (currentPlayer == 1){
                    cout << "Player 1 won vertically!" << endl;
                    return true;
                }else{
                    cout << "Player 2 won vertically!" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkDiagonalWin(char map[6][7], int currentPlayer){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            if ((map[i][j] == map[i+1][j+1]) && (map[i+1][j+1] == map[i+2][j+2]) && (map[i+2][j+2] == map[i+3][j+3]) && (map[i][j] != '-')){
                if (currentPlayer == 1){
                    cout << "Player 1 won diagonally!" << endl;
                    return true;
                }else{
                    cout << "Player 2 won diagonally!" << endl;
                    return true;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 6; j >= 3; j--){
            if((map[i][j] == map[i+1][j-1]) && (map[i+1][j-1] == map[i+2][j-2]) && (map[i+2][j-2] == map[i+3][j-3]) && (map[i][j] != '-')){
                if (currentPlayer == 1){
                    cout << "Player 1 won diagonally!" << endl;
                    return true;
                }else{
                    cout << "Player 2 won diagonally!" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

int main(){
    char map[6][7]; //6 rows and 7 columns for connect 4. Row major form
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            map[i][j] = '-';
        }
    }
    printMap(map);

    int userInput = 1;
    int currentPlayer = 2;

    while(true){
        if (currentPlayer%2 == 0){
            currentPlayer = 1;
        }else{
            currentPlayer = 2;
        }

        if (currentPlayer == 1){
            cout << "Player 1 turn. Enter 0 to quit or enter a column (1-7): ";
        }else{cout << "Player 2 turn. Enter 0 to quit or enter a column (1-7): ";}
        
        cin >> userInput;
        userInput = userInput -1;

        if (userInput == -1){
            cout << "Ok u suck game over." << endl;
            break;
        }else{
            if (!validInput(map,userInput)){
                if (currentPlayer == 1){
                    currentPlayer = 2;
                }else{currentPlayer = 1;}

                continue;
            }
            updateMap(map,userInput,currentPlayer);
            printMap(map);

            if (checkHorizontalWin(map,currentPlayer)){
                break;
            }
            if (checkVerticalWin(map,currentPlayer)){
                break;
            }
            if (checkDiagonalWin(map,currentPlayer)){
                break;
            }
            if(mapFull(map)){
                cout << "The map is full. Game over." << endl;
                break;
            }
        }
    }
}