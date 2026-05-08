#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* insertBST(Node* root, int key) {
    if (!root) return new Node(key);

    Node* cur = root;

    while (true) {
        if (key < cur->key) {
            if (!cur->left) {
                cur->left = new Node(key);
                break;
            }
            cur = cur->left;
        } else {
            if (!cur->right) {
                cur->right = new Node(key);
                break;
            }
            cur = cur->right;
        }
    }

    return root;
}

bool searchBST(Node* root, int key) {
    while (root) {
        if (root->key == key)
            return true;

        root = (key < root->key)
            ? root->left
            : root->right;
    }

    return false;
}

void freeBST(Node* root) {
    if (!root) return;

    freeBST(root->left);
    freeBST(root->right);

    delete root;
}

struct VEBNode {
    int key;
    int left;
    int right;
};

class VEBTree {
private:

    vector<VEBNode> data;
    int n;

    // Altura de un BST casi completo
    static int heightOf(int sz) {
        if (sz <= 0) return 0;

        int h = 0;

        while ((1 << h) <= sz)
            h++;

        return h;
    }

    // Raíz del BST casi completo

    static int bstRoot(int l, int r) {

        int sz = r - l + 1;

        if (sz == 1)
            return l;

        int h = heightOf(sz) - 1;

        int left_full = (1 << (h - 1)) - 1;

        int last_max = (1 << (h - 1));

        int extra = sz - ((1 << h) - 1);

        int left_count = left_full + min(extra, last_max);

        return l + left_count;
    }

    int buildRec(
        const vector<int>& sorted,
        int l,
        int r,
        int top_levels
    ) {

        if (l > r)
            return -1;

        int root_pos = bstRoot(l, r);

        int idx = (int)data.size();

        data.push_back({
            sorted[root_pos],
            -1,
            -1
        });

        int next_top;

        if (top_levels <= 1) {

            int h = heightOf(r - l + 1);

            int bot_h = h - (h / 2);

            next_top = max(1, bot_h);

        } else {

            next_top = top_levels - 1;
        }

        data[idx].left = buildRec(sorted, l, root_pos - 1, next_top);

        data[idx].right = buildRec(sorted, root_pos + 1, r, next_top);

        return idx;
    }

public:

    VEBTree(const vector<int>& sorted) {

        n = (int)sorted.size();

        if (n == 0)
            return;

        data.reserve(n);

        int h = heightOf(n);

        int top_levels = max(1, h / 2);

        buildRec(sorted, 0, n - 1, top_levels);
    }

    bool search(int key) const {

        int cur = 0;

        while (cur != -1) {

            if (data[cur].key == key)
                return true;

            cur = (key < data[cur].key)
                ? data[cur].left
                : data[cur].right;
        }

        return false;
    }

    int size() const {
        return n;
    }
};

// ======================================================
// MAIN
// ======================================================

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Parámetros
    const int N = 1'000'000;
    const int Q = 1'000'000;
    const int T = 5;

    // Block size teórico
    const int B = 16;

    cout << "====================================\n";
    cout << "PARÁMETROS DEL EXPERIMENTO\n";
    cout << "====================================\n";

    cout << "N (elementos)    : " << N << "\n";
    cout << "Q (consultas)    : " << Q << "\n";
    cout << "T (experimentos) : " << T << "\n";

    cout << "B (block size)   : "
         << B
         << " elementos ("
         << B * (int)sizeof(int)
         << " bytes)\n\n";

    // Generación de datos

    vector<int> values(N);

    for (int i = 0; i < N; i++)
        values[i] = i;

    mt19937 rng(42);

    shuffle(values.begin(), values.end(), rng);

    // Construcción BST

    cout << "Construyendo BST...\n";

    Node* bst = nullptr;

    for (int x : values) {

        if (!bst)
            bst = new Node(x);
        else
            insertBST(bst, x);
    }

    cout << "BST construido.\n";

    cout << "Construyendo vEB tree...\n";

    vector<int> sorted = values;

    sort(sorted.begin(), sorted.end());

    VEBTree veb(sorted);

    cout << "vEB tree construido ("
         << veb.size()
         << " nodos).\n\n";

    // Generación de queries
    vector<int> queries(Q);

    uniform_int_distribution<int> dist(0, N - 1);

    for (int i = 0; i < Q; i++)
        queries[i] = sorted[dist(rng)];

    vector<double> bst_times;
    vector<double> veb_times;

    using Clock = chrono::steady_clock;

    for (int t = 0; t < T; t++) {

        // BST

        volatile long long bst_dummy = 0;

        auto start_bst = Clock::now();

        for (int q : queries)
            bst_dummy += searchBST(bst, q);

        auto end_bst = Clock::now();

        double bst_time = chrono::duration<double>(end_bst - start_bst).count();

        bst_times.push_back(bst_time);

        // vEB

        volatile long long veb_dummy = 0;

        auto start_veb = Clock::now();

        for (int q : queries)
            veb_dummy += veb.search(q);

        auto end_veb = Clock::now();

        double veb_time = chrono::duration<double>(end_veb - start_veb).count();

        veb_times.push_back(veb_time);

        cout << "Experimento " << (t + 1) << "\n";

        cout << "  BST : "
             << bst_time
             << " s  (hits: "
             << bst_dummy
             << ")\n";

        cout << "  vEB : "
             << veb_time
             << " s  (hits: "
             << veb_dummy
             << ")\n";

        cout << "  Speedup : "
             << (bst_time / veb_time)
             << "x\n\n";
    }

    // Promedios

    double avg_bst = 0.0;
    double avg_veb = 0.0;

    for (double x : bst_times)
        avg_bst += x;

    for (double x : veb_times)
        avg_veb += x;

    avg_bst /= T;
    avg_veb /= T;

    double speedup = avg_bst / avg_veb;

    cout << "====================================\n";
    cout << "RESULTADOS PROMEDIO\n";
    cout << "====================================\n";

    cout << "BST promedio : "
         << avg_bst
         << " s\n";

    cout << "vEB promedio : "
         << avg_veb
         << " s\n";

    cout << "Speedup      : "
         << speedup
         << "x\n\n";

    // Exportar CSV

    ofstream out("results.csv");

    out << "Experimento,BST_s,vEB_s,Speedup\n";

    for (int i = 0; i < T; i++) {

        out << (i + 1)
            << ","
            << bst_times[i]
            << ","
            << veb_times[i]
            << ","
            << (bst_times[i] / veb_times[i])
            << "\n";
    }

    out << "Promedio,"
        << avg_bst
        << ","
        << avg_veb
        << ","
        << speedup
        << "\n";

    out.close();

    cout << "Resultados exportados a results.csv\n";

    // Liberando memoria
    freeBST(bst);

    return 0;
}
