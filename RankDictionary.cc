#include <vector>
using namespace std;

struct RankDictionary {
    typedef unsigned int u32;
    int length, blockslength;
    vector<u32> blocks, ranktable;
    RankDictionary(int len) : length(len) {
        blocks.resize((blockslength = (len + 31) / 32));
    }
    void set(int pos) { blocks[pos / 32] |= 1 << pos % 32; }
    bool get(int pos) { return blocks[pos / 32] & (1 << pos % 32); }
    void build() {
        ranktable.resize(blocks.size());
        ranktable[0] = popcount(blocks[0]);
        for(int i = 1; i < ranktable.size(); i++) {
            ranktable[i] += ranktable[i-1] + popcount(blocks[i]);
        }
    }
    inline int rank(int pos) const {
        int b = pos / 32, i = pos % 32;
        return ranktable[b] - popcount(blocks[b] >> (i + 1));
    }
    inline int rank(bool b, int pos) const {
        return b ? rank(pos) : pos - rank(pos) + 1;
    }
    inline int rank(bool b, int i, int j) const {
        return rank(b, j) - (i == 0 ? 0 : rank(b, i-1));
    }
private:
	static inline int popcount(u32 x) {
		x = x - ((x >> 1) & 0x55555555);
		x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
		return ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
	}
};
