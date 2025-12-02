#include <codecvt>
#include <cstdio>
#include <deque>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <algorithm>
#include <string_view>
#include <map>
#include <stack>
#include <vector>
using namespace std;

const char tree_node_operators[] = {'&', '|', '>'};
const static std::map<char, int> operator_priorities = {// 操作符, 优先级
    { '!', 4 },
    { '&', 3 },
    { '|', 2 },
    { '>', 1 }
};
map<char, bool> variables; //变元->布尔

struct Node {
    char data;
    bool not_symb;//如果有取反，就False，运算里直接AND它
    Node* left;
    Node* right;
    
    Node(char data, bool not_symb, Node* left, Node* right) {
        this->data = data;
        this->not_symb = not_symb;
        this->left = left;
        this->right = right;
    }
    bool isTrue() {
        if (find(begin(tree_node_operators), end(tree_node_operators), this->data) == end(tree_node_operators)) {
            //不是运算符
            return variables[data];
        }
        bool result;
        switch (data) {
            case '&':result = (left->isTrue() && right->isTrue()) && not_symb;break;
            case '|':result = (left->isTrue() || right->isTrue()) && not_symb;break;
            case '>':result = !(left->isTrue() == true && right->isTrue() == false) && not_symb;break;
        }
        return not_symb ? result : !result;
    }
};

Node* make_tree();
queue<char> toPostfix();//读取输入，抛掉空格，返回一个后缀表达式字符串

int main() {

    return 0;
}


queue<char> toPostfix() {
    vector<char> tmp;
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ') {
            if (ch == '!' && tmp.back() == '!') {
                tmp.pop_back();
            } else {            
                tmp.push_back(ch);
            }
        }
    }
    queue<char> output;
    stack<char> op_stack;
    for (char c : tmp) {
        if (operator_priorities.count(c) == 0) {
            if (c == '(') {
                op_stack.push('(');
            } else if (c == ')') {
                while (!op_stack.empty() && op_stack.top() != '(') {
                    output.push(op_stack.top());
                    op_stack.pop();
                }
                if (!op_stack.empty()) {
                    op_stack.pop();
                }
            } else {
                output.push(c);
            }
        } else {//是运算符
            while (
                !op_stack.empty() && 
                op_stack.top() != '(' && 
                operator_priorities.at(op_stack.top()) >= operator_priorities.at(c)
            ) {
                output.push(op_stack.top());
                op_stack.pop();
            }
            op_stack.push(c);
        }
    }
    while (!op_stack.empty()) {
        if (op_stack.top() == '(') {
            cout << "检测到输入错误:不匹配的括号";
        } else {
            output.push(op_stack.top());
        }
        op_stack.pop();
    }
    return output;
}
