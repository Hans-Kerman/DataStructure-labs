#include <iostream>

using namespace std;

struct Node{
    int id;
    int pwd;
    Node* pre;
    Node* nxt;
    Node(int id, int pwd, Node* pre, Node* nxt) {
        this->id = id;
        this->pwd = pwd;
        this->pre = pre;
        this->nxt = nxt;
    }
};

Node* head = nullptr;
Node* cur = nullptr;
int m, n;
void add_node(Node* addon);
int del_node();

int main() {
    head = new Node(-1, -1, nullptr, nullptr);
    head->pre = head;
    head->nxt = head;
    int num;
    cout << "输入n" << endl;
    cin >> n;
    cout << "输入n个数组成密码" << endl;
    for (int i = 1; i <= n; i++) {
        cin >> num;
        Node* temp = new Node(i, num, head->pre, head);
        add_node(temp);
    }
    m = 1;
    cur = head;
    while (n >= 1) {
        cout << del_node() << " ";
    }
    return 0;
}

void add_node(Node* addon) {
    head->pre->nxt = addon;
    head->pre = addon;
}

int del_node() {
    m = m % n;
    if (m <= n / 2) {
        if (m == 0) {
            cur = cur->nxt;
        }
        //cout << "顺时针";
        while (m--) {
            cur = cur->nxt;
            if (cur->id == -1) {
                cur = cur->nxt;
            }
        }
        if (cur->id == -1) {
                cur = cur->nxt;
        }
        cur->pre->nxt = cur->nxt;
        cur->nxt->pre = cur->pre;
        n--;
        //cout << cur->id << "出局" << "总数变为" << n << endl;
        m = cur->pwd;
        return cur->id;
    } else {
        m = n - m + 1;
        //cout << "逆时针";
        while (m--) {
            cur = cur->pre;
            if (cur->id == -1) {
                cur = cur->pre;
            }
        }
        if (cur->id == -1) {
                cur = cur->pre;
        }
        cur->pre->nxt = cur->nxt;
        cur->nxt->pre = cur->pre;
        n--;
        //cout << cur->id << "出局" << "总数变为" << n << endl;
        m = cur->pwd;
        return cur->id;
    }
}
