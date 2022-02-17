#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int N = 3;//配列のサイズ

//係数Aの中身を表示する関数
void show_A(int N, vector<vector<double>> A){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << A.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

//定数Bの中身を表示する関数
void show_B(int N, vector<double> B){
    for(int i = 0; i < N; i++){
        cout << B.at(i) << endl;
    }
}

//解Xの中身を表示する関数
void show_X(int N, vector<double> X){
    for(int i = 0; i < N; i++){
        cout << "X" << i << " = " << X.at(i) << endl;
    }
}

//ピボット(行列の要素)の同じ列の中で最も大きい値を持つ場所の添え字を返す.引数のkは操作する列の添え字を意味する
int pivot_index(int N, vector<vector<double>> &A, int k){
    vector<double> D(N);
    int index = 0;

    for(int l = k; l < N; l++){
        D.at(l) = A.at(l).at(k) * A.at(l).at(k);
    }
    sort(D.begin(), D.end());
    double max = D[N - 1];//最大値を保存
    if(max < 0.00000001){
        cout << "The solution is not uniquely determined" << endl;
        exit(0);
    }

    for(int i = 0; i < N; i++){
        if(max == D.at(i)) index = i;
    }
    return index;//最大要素がある行のインデックスを返す
}

//選択したピボット(行列の要素)の行をk行目の列と総入れ替えする関数
void change_line(int N, vector<vector<double>> &A, vector<double> &B, int k, int index){
    double S;
    double T;

    T = B.at(k);
    B.at(k) = B.at(index);
    B.at(index) = T;

    for(int i = 0; i < N; i++){//k,indexで行，iで列を操作して，index行目をk行目と総入れ替え
        S = A.at(k).at(i);
        A.at(k).at(i) = A.at(index).at(i);
        A.at(index).at(i) = S;
    }
}

void remove_element(int N, vector<vector<double>> &A, vector<double> &B, int k, int i){
    double r = A.at(i).at(k) / A.at(k).at(k);

    for(int l = k; l < N; l++){
        A.at(i).at(l) = A.at(i).at(l) - r * A.at(k).at(l);
    }

    B.at(i) = B.at(i) - r * B.at(k);
}

//ガウスの消去法により行列を対角化
void gauss(int N, vector<vector<double>> &A, vector<double> &B){
    int p = 0;
    for(int k = 0; k < N - 1; k++){
        p = pivot_index(N, A, k);
        change_line(N, A, B, k, p);
        for(int i = k + 1; i < N; i++){
            remove_element(N, A, B, k, i);
        }
    }
}

void calc_ans(int N, vector<vector<double>> &A, vector<double> &B, vector<double> &X){
    X.at(N - 1) = B.at(N - 1) / A.at(N - 1).at(N - 1);
    for(int i = N - 2; i >= 0; i--){
        double S = 0;
        for(int j = i + 1; j < N; j++){
            S = S + A.at(i).at(j) * X.at(j);
            X.at(i) = (B.at(i) - S) / A.at(i).at(i);
        }
    }
}

int main(){
    vector<vector<double>> A = {{3, 6, 2}, {1, 2, 8}, {7, 3, 3}};
    vector<double> B = {32, 40, 35};
    vector<double> X(N);

    show_A(N, A);
    cout << endl;
    show_B(N, B);
    cout << endl;

    cout << "Triangulation" << endl;
    gauss(N, A, B);

    show_A(N, A);
    cout << endl;
    show_B(N, B);
    cout << endl;

    calc_ans(N, A, B, X);
    cout << "answers" << endl;
    show_X(N, X);
    
    return 0;
}