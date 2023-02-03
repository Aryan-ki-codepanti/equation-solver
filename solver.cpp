#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
void displayV(vector<vector<int>> v)
{
    for (auto &&i : v)
    {
        for (auto &&j : i)
            cout << j << " ";
        cout << endl;
    }
}

class Solver
{

    int n;
    vector<vector<int>> coefficients;
    vector<int> solutions;

public:
    static vector<int> multiply(vector<vector<int>> A, vector<int> B)
    {
        vector<int> res;

        int s;
        for (int row = 0; row < A.size(); row++)
        {
            s = 0;
            for (int col = 0; col < A.size(); col++)
                s += A[row][col] * B[col];
            res.push_back(s);
        }
        return res;
    }

    static vector<vector<int>> transpose(vector<vector<int>> M)
    {
        int n = M.size();
        vector<vector<int>> res(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                res[i][j] = M[j][i];
        }

        return res;
    }

    static vector<vector<int>> remainingMatrix(vector<vector<int>> M, int r, int c)
    {
        int n = M.size();
        vector<vector<int>> delMatrix;

        for (int i = 0; i < n; i++)
        {
            if (i == r)
                continue;

            vector<int> temp;
            for (int j = 0; j < n; j++)
            {
                if (j == c)
                    continue;
                temp.push_back(M[i][j]);
            }
            delMatrix.push_back(temp);
        }

        return delMatrix;
    }

    static int cofactor(vector<vector<int>> M, int i, int j)
    {
        return pow(-1, i + j + 2) * determinant(remainingMatrix(M, i, j));
    }

    static int determinant(vector<vector<int>> M)
    {
        int n = M.size();
        if (n == 1)
            return M[0][0];

        else if (n == 2)
            return M[0][0] * M[1][1] - M[0][1] * M[1][0];

        int s = 0;
        for (int col = 0; col < n; col++)
            s += pow(-1, col + 2) * M[0][col] * determinant(remainingMatrix(M, 0, col));
        return s;
    }

    Solver(int n)
    {
        this->n = n;
        solutions.resize(n);
        coefficients.resize(n);
    }

    void solve()
    {
        vector<vector<int>> adj = get_adjoint();

        cout << "ADJ" << endl;
        displayV(adj);

        int det = determinant(coefficients);
        cout << "det " << det << endl;

        vector<int> res = multiply(adj, solutions);
        for (auto &&i : res)
            i /= det;

        for (int i = 0; i < res.size(); i++)
            cout << "x" << i << " = " << res[i] << endl;
    }

    vector<vector<int>> get_adjoint()
    {
        vector<vector<int>> adj;
        for (int i = 0; i < n; i++)
        {
            vector<int> v;
            for (int j = 0; j < n; j++)
                v.push_back(cofactor(coefficients, i, j));
            adj.push_back(v);
        }

        return transpose(adj);
    }

    void system_input()
    {
        cout << "Enter system" << endl;
        int x;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> x;
                coefficients[i].push_back(x);
            }
            cin >> solutions[i];
        }
    }
    void display_system()
    {
        int x;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                x = coefficients[i][j];
                if (x > 0)
                    cout << "+";

                cout << x << "x" << j << " ";
            }
            cout << "= " << solutions[i] << endl;
        }
    }
};
/*
6 1 1 2
4 -2 5 2
2 8 7 0

1 9 3 2
2 5 4 2
3 7 8 0

actual

2 5 2 -38
3 -2 4 17
-6 1 -7 -12

3 1 1 1
2 0 2 0
5 1 2 2
*/

int main()
{

    int n;
    // vector<vector<int>> res(n, vector<int>(n, 0));
    // displayV(res);
    cin >> n;
    Solver s(n);
    s.system_input();
    s.display_system();
    s.solve();
    return 0;
}