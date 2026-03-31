#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{
    struct NODE {
        int data;
        NODE *next;
    };

    NODE *head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }

    NODE* move(int i) {
        // Move to the node at position i-1 (so we can access position i via ->next)
        // For circular list, we need to handle the wrap-around
        if (head == nullptr || i < 0) {
            return nullptr;
        }

        NODE *current = head;
        for (int j = 0; j < i; j++) {
            current = current->next;
        }
        return current;
    }

    void insert(int i, int x) {
        NODE *newNode = new NODE;
        newNode->data = x;

        if (len == 0) {
            // First node - circular points to itself
            newNode->next = newNode;
            head = newNode;
        } else if (i == 0) {
            // Insert at the beginning
            // Find the last node
            NODE *last = move(len - 1);
            newNode->next = head;
            last->next = newNode;
            head = newNode;
        } else {
            // Insert at position i (after position i-1)
            NODE *prev = move(i - 1);
            newNode->next = prev->next;
            prev->next = newNode;
        }
        len++;
    }

    void remove(int i) {
        if (len == 0 || i < 0 || i >= len) {
            return;
        }

        NODE *toDelete;

        if (len == 1) {
            // Only one node
            toDelete = head;
            head = nullptr;
        } else if (i == 0) {
            // Remove head
            NODE *last = move(len - 1);
            toDelete = head;
            head = head->next;
            last->next = head;
        } else {
            // Remove node at position i
            NODE *prev = move(i - 1);
            toDelete = prev->next;
            prev->next = toDelete->next;
        }

        delete toDelete;
        len--;
    }

    void remove_insert(int i) {
        // Delete position i and insert it at the tail
        if (len == 0 || i < 0 || i >= len) {
            return;
        }

        // Special case: if i is already at the last position, do nothing
        if (i == len - 1) {
            return;
        }

        // Get the value at position i
        NODE *nodeToMove;

        if (i == 0) {
            // Moving head to tail
            nodeToMove = head;
            NODE *last = move(len - 1);
            head = head->next;
            last->next = head;
            // nodeToMove is now detached, but we need to insert it at tail
            nodeToMove->next = head;
            // Find new last position (which is len-2 now since we moved head)
            NODE *newLast = move(len - 2);
            newLast->next = nodeToMove;
        } else {
            // Moving non-head node
            NODE *prev = move(i - 1);
            nodeToMove = prev->next;
            prev->next = nodeToMove->next;

            // Now insert at tail
            NODE *last = move(len - 2); // len-2 because we already removed one
            nodeToMove->next = head;
            last->next = nodeToMove;
        }
        // Length doesn't change
    }

    void get_length() {
        cout << len << endl;
    }

    void query(int i) {
        if (i < 0 || i >= len) {
            cout << -1 << endl;
            return;
        }

        NODE *node = move(i);
        cout << node->data << endl;
    }

    void get_max() {
        if (len == 0) {
            cout << -1 << endl;
            return;
        }

        int maxVal = head->data;
        NODE *current = head->next;

        for (int i = 1; i < len; i++) {
            if (current->data > maxVal) {
                maxVal = current->data;
            }
            current = current->next;
        }

        cout << maxVal << endl;
    }

    void clear() {
        if (head == nullptr) {
            return;
        }

        NODE *current = head;
        NODE *next;

        for (int i = 0; i < len; i++) {
            next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        len = 0;
    }
}

int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}
