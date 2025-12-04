#include <cstddef>
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
vector<char> variable_list; //变元的列表

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
        bool result;
        if (find(begin(tree_node_operators), end(tree_node_operators), this->data) == end(tree_node_operators)) {
            //不是运算符
            result = variables[data];
        }
        switch (data) {
            case '&':result = (left->isTrue() && right->isTrue());break;
            case '|':result = (left->isTrue() || right->isTrue());break;
            case '>':result = !(left->isTrue() == true && right->isTrue() == false);break;
        }
        return not_symb ? result : !result;
    }
};

Node* make_tree(queue<char> postfix);
queue<char> toPostfix();//读取输入，抛掉空格，返回一个后缀表达式字符串

int main() {
    Node* root = make_tree(toPostfix());
    variable_list.reserve(variables.size());
    for (const auto& [k, v] : variables) {
        variable_list.push_back(k);
    }
    cout << "真值表：" << endl;
    bool answer = true;
    for (size_t i = 0; i < (1 << variable_list.size()); i++) {
        for (size_t j = 0;j < variable_list.size(); j++) {
            char current_var = variable_list[j];
            bool value = ((i >> j) & 1);
            variables[current_var] = value;
        }
        for (const auto& [k, v] : variables) {
            cout << k << ":" << v << ",";   
        }
        if (!root->isTrue()) {
            answer = false;
        }
        cout << "输出：" << root->isTrue() << endl;
    }
    if (!answer) {
        cout << "不";
    } 
    cout << "是永真式";
    return 0;
}


queue<char> toPostfix() {
    vector<char> tmp;
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ') {
            if (ch == '!' && !tmp.empty() && tmp.back() == '!') {
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

Node* make_tree(queue<char> postfix) {
    stack<Node*> tmp;
    char c;
    while (!postfix.empty()) {
        c = postfix.front();
        if (operator_priorities.count(c) == 0) {
            //是变元
            if (variables.count(c) == 0) {
                //新变元
                variables[c] = false;
            }
            tmp.push(new Node(c, true, nullptr, nullptr));
        } else if (c == '!') {
            tmp.top()->not_symb = !tmp.top()->not_symb;
        } else {
            //普通运算符
            Node* rightnode = tmp.top();
            tmp.pop();
            Node* leftnode = tmp.top();
            tmp.pop();
            tmp.push(new Node(c, true, leftnode, rightnode));
        }
        postfix.pop();
    }
    return tmp.top();
}
