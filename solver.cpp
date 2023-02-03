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

class SolutionError
{
    string message;

public:
    SolutionError(string s)
    {
        message = s;
    }
    void display()
    {
        cout << message << endl;
    }
};

class Solver
{

    int n;
    vector<vector<int>> coefficients;
    vector<int> solutions;

public:
    static vector<float> multiply(vector<vector<int>> A, vector<int> B)
    {
        vector<float> res;

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
    static bool checkZeroMatrix(vector<float> M)
    {
        for (auto &x : M)
            if (x != 0)
                return false;
        return true;
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
        int det = determinant(coefficients);
        vector<vector<int>> adj = get_adjoint();
        vector<float> res = multiply(adj, solutions);

        if (det == 0)
        {
            if (checkZeroMatrix(res))
                throw SolutionError("Infinite solutions");
            else
                throw SolutionError("No solutions");
        }

        for (auto &&i : res)
            i /= (float)(det);

        cout << endl
             << "----------Solutions------" << endl;
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
        cout << "-----------System----------" << endl;
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
actual
3
2 5 2 -38
3 -2 4 17
-6 1 -7 -12

3
3 1 1 1
2 0 2 0
5 1 2 2
*/

int main()
{
    try
    {
        cout << "Enter number of equations / variables: ";
        int n;
        cin >> n;
        Solver s(n);
        s.system_input();
        s.display_system();
        s.solve();
    }
    catch (SolutionError err)
    {
        err.display();
    }
    return 0;
}