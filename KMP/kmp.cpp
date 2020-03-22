#include <bits/stdc++.h>
using namespace std;

vector<int> preprocess(string s)
{
    vector<int> backtable(s.size() + 1);
    backtable[0] = -1;
    int i = 0, j = -1;
    while (i < s.size())
    {
        while (j >= 0 && s[i] != s[j])
            j = backtable[j];
        backtable[++i] = ++j;
    }
    return backtable;
}

// return index of first matching target substring
int kmp(string str, string target)
{
    if (target.empty())
        return 0;
    else if (target.size() > str.size())
        return -1;
    vector<int> backtable = preprocess(target);
    int i = 0, j = 0;
    while (i < str.size())
    {
        while (j >= 0 && str[i] != target[j])
            j = backtable[j];
        i++, j++;
        if (j == target.size())
            return i - j;
    }
    return -1;
}
int main()
{
    string str, target;
    cin >> str >> target;
    cout << kmp(str, target) << endl;
}
