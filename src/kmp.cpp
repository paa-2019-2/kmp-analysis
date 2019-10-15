#include <bits/stdc++.h>

using namespace std;

string s, t;
vector<int> b;
int n, m;

int adjust_index_lps(int j, int i, vector<int> l) {
    if (j <= 0 or s[i] == s[j]) {
        return j;   
    }
    return adjust_index_lps(l[j-1], i, l);
}

vector<int> prefix_function(int i, int j, vector<int> l) {
    if (i >= n) {
        return l;
    }
    { // let x 
        int x = adjust_index_lps(j, i, l);
        if (s[i] == s[x]) {
            l.push_back(x+1);
            return prefix_function(i+1, x+1, l);
        }
        else {
            l.push_back(x);
            return prefix_function(i+1, x, l);
        }
    }  
}

std::vector<int> lps() {
    vector<int> l;
    l.push_back(0);
    return prefix_function(1, 0, l);
}


int adjust_index_kmp(int i, int j) {
    if(j <= 0 || s[j] == t[i]) {
        return j;
    }
    return adjust_index_kmp(i, b[j - 1]);
}

vector<int> kmp_search(int i, int j, vector<int> ans) {
    if(i >= m) {
        return ans;
    }
    {
        int x = adjust_index_kmp(i, j);
        if(s[x] == t[i]) {
            if(x + 1 == n) {
                ans.push_back(i - n + 1);
                return kmp_search(i + 1, b[x], ans);
            }
            else {
                return kmp_search(i + 1, x + 1, ans);
            }
        }
        else {
            if(x == n) {
                ans.push_back(i - n + 1);
                return kmp_search(i + 1, b[x - 1], ans);
            }
            else {
                return kmp_search(i + 1, x, ans);
            }
        }
    }
}

vector<int> kmp(string pattern, string text) {
    n = pattern.size();
    m = text.size();
    b = lps();
    vector<int> v;
    return kmp_search(0,0,v);
}

int main() { // kmp
    cin >> s >> t;
    auto v = kmp(s, t);

    for(auto a : v) {
        cout << a << " ";
    }
    cout << endl;
}

