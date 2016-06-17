#include <vector>
#include <bitset>
using namespace std;
const int BT_LEN = 10;
vector<bitset<BT_LEN> > gaussian(vector<bitset<BT_LEN> > a, int no_rows, int no_cols) {
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
    return a;
}
