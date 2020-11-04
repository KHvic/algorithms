#include <bits/stdc++.h>
using namespace std;

// MMQueue is a struct to find max or min element while maintaining some window size
struct MMQueue {
    deque<vector<int>> mnq, mxq;
    int len = 0;

    void push(int v) {
        len++;
        int c = 1;
        while(!mnq.empty() && v < mnq.back()[0]){
            c += mnq.back()[1];
            mnq.pop_back();
        }
        mnq.push_back({v,c});
        c = 1;
        while(!mxq.empty() && v > mxq.back()[0]){
            c += mxq.back()[1];
            mxq.pop_back();
        }
        mxq.push_back({v,c});
    }
    void pop() {
        len--;
        if(--mnq.front()[1] <=0) mnq.pop_front();
        if(--mxq.front()[1] <=0) mxq.pop_front();
    }
    int min() {
        return mnq.empty() ? 0 : mnq.front()[0];
    }
    int max() {
        return mxq.empty() ? 0 : mxq.front()[0];
    }
};
