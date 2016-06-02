#include <iostream>

using namespace std;

struct bigint {
    string data;
    bigint() : data("0") { }
    bigint(string x) : data(x) { }
    bigint operator+(bigint &other) {
        this->__reverse(this->data), other.__reverse(other.data);
        int carry = 0;
        string temp;
        int iter = 0, minim = min(this->size(), other.size()), maxim = max(this->size(), other.size());
        int one, two, add;
        for(; iter < minim; iter++) {
            one = this->data[iter] - '0', two = other.data[iter] - '0';
            if(carry + one + two > 9) {
                add = (carry + one + two) % 10;
                carry = (carry + one + two) / 10;
            } else {
                add = carry + one + two;
                carry = 0;
            }
            temp.push_back(add + '0');
        }
        if(iter < maxim) {
            string& remain = this->size() == maxim ? this->data : other.data;
            for(; iter < maxim; iter++) {
                one = remain[iter] - '0';
                if(carry + one > 9) {
                    carry = (carry + one) / 10;
                    add = (carry + one) % 10;
                } else {
                    add = carry + one;
                    carry = 0;
                }
                temp.push_back(add + '0');
            }
        }
        if(carry != 0) {
            temp.push_back(carry + '0');
        }
        __reverse(temp);
        this->__reverse(this->data), other.__reverse(other.data);
        return bigint(temp);
    }
    bigint operator+(bigint &&other) {
        return (*this) + other;
    }
    bigint operator-(bigint &other) {
        this->__reverse(this->data), other.__reverse(other.data);
        int maxim = max(this->size(), other.size()), minim = min(this->size(), other.size());
        int iter = 0, carry = 0, dgt;
        string temp;
        for(; iter < minim; iter++) {
            if(this->data[iter] > other.data[iter]) {
                dgt = this->data[iter] - other.data[iter];
                dgt -= carry;
                carry = 0;
            } else if(this->data[iter] == '0') {
                if(carry == 0 && other.data[iter] == '0') {
                    dgt = 0;
                } else {
                    dgt = (10 - carry - other.data[iter] + '0');
                    carry = 1;
                }
            } else {
                if(carry == 0 && this->data[iter] == other.data[iter]) {
                    dgt = 0;
                } else {
                    dgt = this->data[iter] - carry - '0';
                    dgt = (10 + dgt - (other.data[iter] - '0'));
                    carry = 1;
                }
            }
            temp.push_back(dgt + '0');
        }
        string& remain = maxim == this->size() ? this->data : other.data;
        for(; iter < maxim; iter++) {
            if(carry == 0) {
                temp.push_back(remain[iter]);
            } else {
                if(remain[iter] == '0') {
                    temp.push_back('9');
                } else {
                    temp.push_back(remain[iter] - 1);
                    carry = 0;
                }
            }
        }
        __reverse(this->data), __reverse(other.data);
        __pop_zeros(temp);
        __reverse(temp);
        return bigint(temp);
    }
    bigint operator-(bigint &&other) {
        return (*this) - other;
    }
    bigint& operator--() {
        return *this = (*this) - bigint("1");
    }
    bigint operator++() {
        return *this = (*this) + bigint("1");
    }
    string to_binary() {
        return __to_binary(this->data);
    }
    string divide_by_2(const string &temp) {
        int iter = 0, curr = 0;
        string res;
        for(; iter < temp.size(); iter++) {
            curr = (curr * 10) + temp[iter] - '0';
            if(res.empty() && (curr/2) == 0) {
            } else {
                res.push_back((curr/2) + '0');
            }
            curr %= 2;
        }
        if(res.empty())
            res = "0";
        return res;
    }
    string __to_binary(const string &data) {
        string res, temp = data;
        while(temp.size() > 1 || temp[0] > '0') {
            res.push_back('0' + ((temp.back() - '0') % 2));
            temp = divide_by_2(temp);
        }
        __reverse(res);
        return res;
    }
    void __reverse(string &temp) {
        int upper = temp.size() / 2;
        for(int i = 0; i < upper; i++)  swap(temp[i], temp[temp.size() - i - 1]);
    }
    inline size_t size() {
        return this->data.size();
    }
    friend ostream& operator<<(ostream &os, bigint &b) {
        os << b.data; return os;
    }
    friend ostream& operator<<(ostream &os, bigint &&b) {
        os << b.data; return os;
    }
    inline void __pop_zeros(string &temp) {
        while(temp.size() > 1 && temp.back() == '0')    temp.pop_back();
    }
};

int main() {
    int t;
    cin >> t;
    while(t--) {
        string a, b;
        cin >> a >> b;
        cout << (bigint(a) + bigint(b)) << '\n';
        cout << (bigint(a) - bigint(b)) << '\n';
    }
    return 0;
}
