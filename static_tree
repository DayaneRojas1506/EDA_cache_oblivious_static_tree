#include <bits/stdc++.h>
using namespace std;

/*
    ================================
    CACHE-OBLIVIOUS STATIC TREE (vEB)
    ================================
*/

class VEBTree {
private:
    vector<int> veb;

    // Construcción recursiva vEB
    void build(const vector<int>& A, int l, int r, int idx) {
        if (l > r) return;

        int n = r - l + 1;

        // altura del árbol
        int h = floor(log2(n));

        // altura del top tree
        int top_h = h / 2;

        // tamaño del top tree
        int top_size = (1 << top_h) - 1;

        int mid = l + top_size;

        if (mid > r) mid = (l + r) / 2;

        veb[idx] = A[mid];

        // subárbol izquierdo
        if (l <= mid - 1)
            build(A, l, mid - 1, 2 * idx + 1);

        // subárbol derecho
        if (mid + 1 <= r)
            build(A, mid + 1, r, 2 * idx + 2);
    }

public:
    VEBTree(const vector<int>& sorted) {
        int n = sorted.size();
        veb.resize(n);
        build(sorted, 0, n - 1, 0);
    }

    bool search(int key) {
        int i = 0;
        int n = veb.size();

        while (i < n) {
            if (veb[i] == key) return true;

            if (key < veb[i]) i = 2 * i + 1;
            else i = 2 * i + 2;
        }
        return false;
    }
};

/*
    ================================
    BST CLÁSICO
    ================================
*/

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

bool searchBST(Node* root, int key) {
    while (root) {
        if (root->key == key) return true;
        if (key < root->key) root = root->left;
        else root = root->right;
    }
    return false;
}

/*
    ================================
    EXPERIMENTO
    ================================
*/

int main() {
    const int N = 1'000'000;
    const int Q = 1'000'000;

    srand(42);

    // Generar datos
    vector<int> data(N);
    for (int i = 0; i < N; i++) data[i] = rand();

    sort(data.begin(), data.end());

    // Construir BST
    Node* bst = nullptr;
    for (int x : data) bst = insert(bst, x);

    // Construir vEB
    VEBTree veb(data);

    // Queries
    vector<int> queries(Q);
    for (int i = 0; i < Q; i++)
        queries[i] = data[rand() % N];

    // BST timing
    auto start = chrono::high_resolution_clock::now();

    for (int q : queries)
        searchBST(bst, q);

    auto end = chrono::high_resolution_clock::now();

    double bst_time = chrono::duration<double>(end - start).count();

    // vEB timing
    start = chrono::high_resolution_clock::now();

    for (int q : queries)
        veb.search(q);

    end = chrono::high_resolution_clock::now();

    double veb_time = chrono::duration<double>(end - start).count();

    cout << "BST time: " << bst_time << " s\n";
    cout << "vEB time: " << veb_time << " s\n";

    return 0;
}
