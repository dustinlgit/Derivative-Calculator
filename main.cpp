#include <iostream>
#include <vector>
using namespace std;

class Matrix{
public:
    template <int rows, int columns>
    void input(int (&matrixArray)[rows][columns]){
        
    }

    /*int rref(){}
    int wronskian(){}
    int cramers(){}*/
};

    int main(){
        int rows, columns;
        cout << "How many rows and colums?: ";
        cin >> rows >> columns;

        int matrixArray[rows][columns];
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cout << "["<<i<<"]["<<j<<"]: ";
                cin >> matrixArray[i][j];
            }
        }
        

    }

