#include "bits/stdc++.h"

using namespace std;

double GaussElimination(std::vector<std::vector<double>> &matrix) {
    int N = static_cast<int>(matrix.size());
    double ans = 1;

    for (int i = 0; i < N; ++i) {
        if(matrix[i][i] == 0.0){
            int j;
            for( j = i + 1; j < N; j++){
                if(matrix[j][i] != 0.0){
                    matrix[i].swap(matrix[j]);
                    ans *= -1;
                    break;
                }
            }
            if(j == N)
                return 0.0;
        }
        ans *= matrix[i][i];

        for(int j = i + 1; j < N; j++){
            double taghsim = matrix[j][i] / matrix[i][i];
            for(int k = i; k < N; k++)
                matrix[j][k] -= taghsim * matrix[i][k];
        }
    }
    return ans;
}

double Laplacedeterminant(vector<vector<double>> &matrix){
    int N = static_cast<int>(matrix.size());

    if(N == 1)
        return matrix[0][0];

    double ans = 0.0;
    int sign = -1;

    for(int i = 0; i < N; i++){
        sign *= -1;
        vector<vector<double>> submatrix;
        for(int j = 0; j < N; j++){
            vector<double> rows;
            for(int k = 0; k < N; k++){
                if(k != i && j != 0) {
                    rows.push_back(matrix[j][k]);
                }
            }
            if(!rows.empty())
                submatrix.push_back(rows);
        }
        ans += matrix[0][i] * sign * Laplacedeterminant(submatrix);

    }
    return ans;
}

vector<vector<double>> submatrix(vector<vector<double>> &matrix, int size, int row, int col){
    vector<vector<double>> sub;
    for(int i = 0; i < size; i++){
        vector<double> rowsub;
        for(int j = 0; j < size; j++)
            if(i != row && j != col)
                rowsub.push_back(matrix[i][j]);

        if(!rowsub.empty())
            sub.push_back(rowsub);
    }
    return sub;
}

double omidRezaiifar(vector<vector<double>> &matrix){
    int N = static_cast<int>(matrix.size());
    if(N == 1)
        return matrix[0][0];
    if(N == 2)
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);

    vector<vector<double>> top;
    vector<double> row1;
    vector<double> row2;

    vector<vector<double>> one = submatrix(matrix, N, 0, 0); row1.push_back(omidRezaiifar(one));
    vector<vector<double>> two = submatrix(matrix, N, 0, N - 1); row1.push_back(omidRezaiifar(two));
    vector<vector<double>> three = submatrix(matrix, N, N - 1, 0); row2.push_back(omidRezaiifar(three));
    vector<vector<double>> four = submatrix(matrix, N, N - 1, N - 1); row2.push_back(omidRezaiifar(four));

    top.push_back(row1); top.push_back(row2);

    vector<vector<double>> taghsim;
    for(int i = 0; i < N; i++){
        vector<double> rowsub;
        for(int j = 0; j < N; j++)
            if(i != 0 && j != 0 && i != N - 1 && j != N - 1)
                rowsub.push_back(matrix[i][j]);

        if(!rowsub.empty())
            taghsim.push_back(rowsub);
    }

    return omidRezaiifar(top) / omidRezaiifar(taghsim);
}

int main(){
    int N1 = 0; int N2 = 0;
    vector<string> name;
    ifstream names("names.txt");
    if(!names.is_open()){
        cout << "No such a file as names!";
        exit(0);
    }
    else{
        string line;
        while(getline(names, line)){
            name.push_back(line);
        }
    }
    names.close();
    int input;
    select :
    while(true) {
        cout << "\n\nTest Cases : \n";
        int temp = 1;
        for (auto X: name) {
            cout << temp << ")" << X << endl;
            temp++;
        }
        cout << temp << ")Exit\n";
        cin >> input;
        if(input == temp){
            exit(0);
        }
        else if(input > 0 && input < temp){
            string T = "TestCase/" + name[input - 1] + ".txt";
            ifstream Testcase(T);

            if(!Testcase.is_open()){
                cout << "No such a file!";
                exit(0);
            }
            else{
                N2 = 0;
                vector<vector<double>> matrix;
                string line;
                while(getline(Testcase, line)){
                    vector<double> row;
                    N1 = 0;
                    N2++;
                    for(char i : line) {
                        if (i >= '0' && i <= '9') {
                            row.push_back(i - '0');
                            N1++;
                        }
                    }
                    matrix.push_back(row);
                }
                Testcase.close();
                if(N1 == N2) {
                    cout << "\n\nGaussElimination :" << GaussElimination(matrix);
                    cout << "\nLaplace :" << Laplacedeterminant(matrix);
                    cout << "\nOmidRezaiifar :" << omidRezaiifar(matrix);
                }
                else
                    cout << "\\nUndefined\n";

            }
        }
        else{
            cout << "Select available number! \n";
            goto select;
        }
    }
    return 0;
}