#include <iostream>

using namespace std;

template <int rows, int cols>
void display(int (&array)[rows][cols]) {
  int i, j;
  cout<<"\n";
  for(i = 0; i<rows; i++) {
      for(j = 0; j<cols; j++) {
        cout<<" ";
        cout<<array[i][j];
      }
      cout<<"\n";
    }
}


int main() {
  int M1[3][3];
  cout<<"Enter your matrix elements: \n";
  int i, j;
    for(i = 0; i<3; i++) {
      for(j = 0; j<3; j++) {
        cout<<"a["<<i<<"]["<<j<<"]: ";
        cin>>M1[i][j];
      }
    }
    display(M1);
  return 0;
}