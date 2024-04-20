#include <iostream>
#include <vector>
using namespace std;

class Matrix{
public:
    void display(const vector<vector<int>>& matrix) {
        int i, j;
        cout<<"\n";
        for(const auto& row : matrix) {
            for(int val : row) {
                cout<<" ";
                cout<<val;
            }
            cout<<"\n";
        }
    }

    int wronskian(const vector<vector<int>>& matrix){
        int rows = matrix.size();
        int columns = matrix[0].size();
        if(rows != columns){
            cout << "Can not find wronskian of an unbalanced matrix.\n";
            return 0;
        }
        if(rows == 2)
           return (matrix[0][0] * matrix[0][1]) - (matrix[1][0] * matrix[1][1]);
        
        return 0;
    }
    
    /*  
    int rref(){}
    int cramers(){}*/
};

    int main(){
        int rows, columns;
        cout << "How many rows and colums?: ";
        cin >> rows >> columns;

        vector<vector<int>> matrixArr(rows, vector<int>(columns));
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cout << "["<<i<<"]["<<j<<"]: ";
                cin >> matrixArr[i][j];
            }
        }

        Matrix m1;
        m1.display(matrixArr);

        return 0;
    }

