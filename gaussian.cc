#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
template<typename T>
void gaussian(vector<vector<T> > m) {
    if(m.empty())   return ;
    int no_rows = m.size(), no_cols = m[0].size();
    for(int row = 0, col = 0; row < no_rows and col < no_cols; col++) {
        if(m[row][col] == 0) {
            int f = -1;
            for(int i = row+1; i < no_rows; i++) {
                if(m[i][col] != 0) { f = i; break; }
            }
            if(f == -1) continue;
            swap(m[f], m[row]);
        }
        for(int c = col+1; c < no_cols; c++)  m[row][c] /= m[row][col];
        m[row][col] = 1;
        for(int r = row+1; r < no_rows; r++) {
            double temp = m[r][col];
            for(int c = col; c < no_cols; c++) {
                m[r][c] -= m[row][c] * temp;
            }
        }
        row++;
    } // m is now in Reduced Echelon
    // Back Substitution
    vector<T> vals(m[0].size() - 1, 0);
    for(int r = m.size() - 1; r >= 0; r--) {
        int f = -1;
        for(int c = 0; c < m[0].size() - 1; c++) {
            if(m[r][c]) {
                f = c; break;
            }
        }
        if(f != -1) {
            T rhs = m[r].back();
            for(int i = f+1; i < m[r].size() - 1; i++) {
                rhs -= m[r][i] * vals[i];
            }
            rhs /= m[r][f];
            vals[f] = rhs;
        }
    }
}

const int BT_LEN = 10;
void gaussian(vector<bitset<BT_LEN> > a, int no_rows, int no_cols) {
    for(int row = 0, col = 0; row < no_rows and col < no_cols; col++) {
        if(!a[row][col]) {
            int f = -1;
            for(int i = row+1; i < no_rows; i++) {
                if(a[i][col]) { f = i; break; }
            }
            if(f == -1) { continue; }
            swap(a[row], a[f]);
        }
        for(int i = row+1; i < no_rows; i++) { if(a[i][col]) a[i] ^= a[row]; }
        row++;
    } // a is now in Reduced Echelon
}
