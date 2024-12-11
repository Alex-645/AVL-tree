#include <iostream>
#include <vector>
using namespace std;

// Структура узла дерева
struct Node {
    int key;
    unsigned char height;
    Node* left;
    Node* right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Функция для получения высоты узла
unsigned char height(Node* p) {
    return p ? p->height : 0;
}

// Вычисление баланс-фактора узла
int bfactor(Node* p) {
    return height(p->right) - height(p->left);
}

// Обновление высоты узла
void fixheight(Node* p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = max(hl, hr) + 1;
}

// Правый поворот вокруг узла p
Node* rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

// Левый поворот вокруг узла q
Node* rotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

// Балансировка узла
Node* balance(Node* p) {
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p; // Балансировка не требуется
}

// Вставка ключа k в дерево с корнем p
Node* insert(Node* p, int k) {
    if (!p) return new Node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else if (k > p->key)
        p->right = insert(p->right, k);
    return balance(p);
}

// Поиск узла с минимальным ключом
Node* findMin(Node* p) {
    return p->left ? findMin(p->left) : p;
}

// Удаление узла с минимальным ключом
Node* removeMin(Node* p) {
    if (!p->left)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

// Удаление ключа k из дерева с корнем p
Node* remove(Node* p, int k) {
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if (!r) return q;
        Node* min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

// Обход дерева (in-order) для вывода
void printTree(Node* p) {
    if (p) {
        printTree(p->left);
        cout << p->key << " ";
        printTree(p->right);
    }
}

// Тестирование АВЛ-дерева
void runTests() {
    Node* root = nullptr;

    cout << "### Тест 1: Пустое дерево ###" << endl;
    printTree(root);
    cout << "\nДерево пусто.\n" << endl;

    cout << "### Тест 2: Вставка элементов ###" << endl;
    vector<int> elements = { 50, 30, 70, 20, 40, 60, 80 };
    for (int e : elements) {
        root = insert(root, e);
        cout << "После вставки " << e << ": ";
        printTree(root);
        cout << endl;
    }

    cout << "\n### Тест 3: Удаление листа (20) ###" << endl;
    root = remove(root, 20);
    cout << "После удаления 20: ";
    printTree(root);
    cout << endl;

    cout << "\n### Тест 4: Удаление узла с одним потомком (30) ###" << endl;
    root = remove(root, 30);
    cout << "После удаления 30: ";
    printTree(root);
    cout << endl;

    cout << "\n### Тест 5: Удаление узла с двумя потомками (50 - корень) ###" << endl;
    root = remove(root, 50);
    cout << "После удаления 50: ";
    printTree(root);
    cout << endl;

    cout << "\n### Тест 6: Вставка дубликатов ###" << endl;
    root = insert(root, 60); // Дубликат
    root = insert(root, 80); // Дубликат
    cout << "После вставки дубликатов: ";
    printTree(root);
    cout << "\n(Дубликаты игнорируются в данной реализации).\n" << endl;

    cout << "### Тест 7: Удаление всех элементов ###" << endl;
    vector<int> toRemove = { 40, 60, 70, 80 };
    for (int r : toRemove) {
        root = remove(root, r);
        cout << "После удаления " << r << ": ";
        printTree(root); cout << endl;
    }

    cout << "Дерево пусто.\n" << endl;
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 65001 > nul");
    runTests();
    return 0;
}