#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
using namespace std;
// 定义队列数据结构
class Queue {
private:
    stack<int> s1;
    stack<int> s2;
public:
    void push(int x) {
        s1.push(x);
    }
    int pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int x = s2.top();
        s2.pop();
        return x;
    }
    bool empty() {
        return s1.empty() && s2.empty();
    }
};
// 定义计算矩形最大面积的函数
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n), right(n);
    stack<int> stk;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    while (!stk.empty()) {
        stk.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
    }
    return ans;
}
int main() {
    // 随机生成 10 组数据进行测试
    for (int i = 0; i < 10; i++) {
        vector<int> heights;
        int n = rand() % 105 + 1;
        for (int j = 0; j < n; j++) {
            int height = rand() % 10000;
            heights.push_back(height);
        }
        int area = largestRectangleArea(heights);
        cout << "Test " << i + 1 << ": " << area << endl;
    }
    return 0;
}
