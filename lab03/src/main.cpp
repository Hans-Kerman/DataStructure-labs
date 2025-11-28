#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <map>
#include <stack>
using namespace std;

map<char, string> rule_list;
void add_rule(char c, string_view phrase);
string rule1(char c);
string rule2(auto &it);
void push_string2stack(const string &str, stack<char> &s);
void sync_list();

int main() {
    add_rule('B', "tAdA");
    add_rule('A', "sae");
    sync_list();
    string maou_in, maou_out = "", maou_temp = "";
    cin >> maou_in;
    for (char maou_in_c : maou_in) {
        maou_temp += rule1(maou_in_c);
    }
    auto it = maou_temp.begin();
    while (it != maou_temp.end()) {
        if (*it == '(') {   //检测到嵌套的内部括号 -> 调用rule2并把输出的string压入栈中
            it = next(it);
            string inner_op = rule2(it);
            maou_out += inner_op;
        } else {
            string s(1, *it);
            maou_out += s;
            it = next(it);
        }
    }
    cout << "魔王说的是：" << maou_out << endl;
    string result = (maou_out == "saeadacabatsaedsae") ? "check" : "fail";
    cout << result;
    return 0;
}

void add_rule(char c, string_view phrase) {
    if ('A' <= c && c <= 'Z') {
        if (!rule_list.contains(c)) {
            rule_list[c] = phrase;
        }
    }
}

string rule1(char c) {
    auto it = rule_list.find(c);
    if (it != rule_list.end()) {
        return it->second; 
    } else {
        string s(1, c);
        return s;
    }
}

void sync_list() {
    for (auto& [key, value] : rule_list) {
        string op = "";
        for (char inner_value : value) {
            op += rule1(inner_value);
        }
        value = op;     //修改引用
        //rule_list[value] = op;
    }
}

void push_string2stack(const string &str, stack<char> &s) {
    for (char c : str) {
        s.push(c);
    }
}

string rule2(auto &it) {
    char theta = *it;
    it = next(it);
    string op(1, theta);
    stack<char> s;
    while (*it != ')') {
        if (*it == '(') {   //检测到嵌套的内部括号 -> 调用rule2并把输出的string压入栈中
            it = next(it);
            string inner_op = rule2(it);
            push_string2stack(inner_op, s);
        } else {
            s.push(*it);
            it = next(it);
        }
    }
    it = next(it);

    while (!s.empty()) {
        op = op + s.top();
        s.pop();
        op += op[0];
    }
    return op;
}
