#include <iostream>
#include <stack>
#include <cmath>
using namespace std;
// 定义运算符优先级表
int priority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}
// 定义计算函数
double calculate(double a, double b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}
// 定义字符串计算器函数
double stringCalculator(string str) {
    stack<double> nums; // 数字栈
    stack<char> ops;    // 运算符栈
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            continue;
        }
        else if (isdigit(str[i])) {
            double num = 0;
            while (i < str.length() && isdigit(str[i])) {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            i--;
            nums.push(num);
        }
        else if (str[i] == '(') {
            ops.push(str[i]);
        }
        else if (str[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = nums.top();
                nums.pop();
                double a = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                nums.push(calculate(a, b, op));
            }
            ops.pop();
        }
        else {
            while (!ops.empty() && priority(ops.top()) >= priority(str[i])) {
                double b = nums.top();
                nums.pop();
                double a = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                nums.push(calculate(a, b, op));
            }
            ops.push(str[i]);
        }
    }
    while (!ops.empty()) {
        double b = nums.top();
        nums.pop();
        double a = nums.top();
        nums.pop();
        char op = ops.top();
        ops.pop();
        nums.push(calculate(a, b, op));
    }
    if (nums.empty()) {
        return 0;
    }
    else {
        return nums.top();
    }
}
int main() {
    string str = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    double result = stringCalculator(str);
    cout << "Result: " << result << endl;
    return 0;
}