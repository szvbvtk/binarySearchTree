#include <iostream>
#include <string>

template <typename T>
struct Node {
    Node<T>* parent = nullptr;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;

    T data;
};

template <typename T>
struct BST {
    Node<T>* root = nullptr;
    int size = 0;

    bool insert(T data, int (*func)(T*, T*)) {

        if (root == nullptr) {
            Node<T>* newNode = new Node<T>();
            newNode->data = data;
            root = newNode;
            size++;
            return 1;
        }

        Node<T>* tmp_root = root;
        Node<T>* last_leaf = nullptr;
        while (tmp_root != nullptr) {
            last_leaf = tmp_root;

            int cmp_result = func(&data, &tmp_root->data);
            if (cmp_result == 0) {
                return 0;
            }
            else if (cmp_result == -1) {
                tmp_root = tmp_root->left_child;
            }
            else {
                tmp_root = tmp_root->right_child;
            }
        }

        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        if (func(&data, &last_leaf->data) == -1) {
            last_leaf->left_child = newNode;
        }
        else {
            last_leaf->right_child = newNode;
        }
        newNode->parent = last_leaf;

        size++;
        return 1;
    }

    Node<T>* search(T data, int (*func)(T*, T*)) {
        Node<T>* tmp = root;
        int cmp_result;
        while (tmp != nullptr && (cmp_result = func(&data, &tmp->data)) != 0) {
            if (cmp_result == -1) {
                tmp = tmp->left_child;
            }
            else {
                tmp = tmp->right_child;
            }
        }

        return tmp;
    }


    void inorderTraversal_h(Node<T>* n, Node<T>** arr) {
        if (n != nullptr) {
            inorderTraversal_h(n->left_child, arr);
            arr[traversal_index++] = n;
            inorderTraversal_h(n->right_child, arr);
        }

    }

    std::string inorderTraversal(std::string(*func)(T*)) {
        traversal_index = 0;
        Node<T>** arr = new Node<T>*[size];
        std::string s = "";

        if (root == nullptr)
            return "BST is empty.";

        inorderTraversal_h(root, arr);

        for (int i = 0; i < size; i++) {
            s += '(' + func(&arr[i]->data) + ") ";
        }

        delete[] arr;
        return s;
    }

    void preorderTraversal_h(Node<T>* n, Node<T>** arr) {
        if (n != nullptr) {
            arr[traversal_index++] = n;
            preorderTraversal_h(n->left_child, arr);
            preorderTraversal_h(n->right_child, arr);
        }
    }

    std::string preorderTraversal(std::string(*func)(T*)) {
        traversal_index = 0;
        Node<T>** arr = new Node<T>*[size];
        std::string s = "";

        if (root == nullptr)
            return "BST is empty.";

        preorderTraversal_h(root, arr);

        for (int i = 0; i < size; i++) {
            s += '(' + func(&arr[i]->data) + ") ";
        }

        delete[] arr;
        return s;
    }

    void clear_h(Node<T>* n) {
        if (n != nullptr) {
            clear_h(n->left_child);
            clear_h(n->right_child);

            //std::cout << "\nUsuwam: " << std::to_string(n->data.f1) << '\n';
            if(n != nullptr)
                delete n;
        }
    }

    void clear() {
        clear_h(root);
        root = nullptr;
        size = 0;
    }

    static int traversal_index;
    std::string str(std::string(*func)(T*)) {
        traversal_index = 0;
        Node<T>** arr = new Node<T>*[size];
        std::string s = "Size: " + std::to_string(size) + "\nHeight: " + std::to_string(height_h(root)) + "\n{\n";
        preorderTraversal_h(root, arr);
        
        if (root == nullptr) {
            s += "\n\tBST is empty\n\n}";
            return s;
        }

        for (int i = 0; i < size; i++) {
            //std::cout << "(" << arr[i].f1 << ' ' << arr[i].f2 << ")\n";
            s += "\t[ Node: (" + func(&arr[i]->data) + ')';
            //std::cout << &arr[i]->parent << '\n';
            if (arr[i]->parent == nullptr)
                s += " Parent: ()";
            else
                s += " Parent: (" + func(&arr[i]->parent->data) + ')';

            if (arr[i]->left_child == nullptr)
                s += " L_child: ()";
            else
                s += " L_child: (" + func(&arr[i]->left_child->data) + ')';

            if (arr[i]->right_child == nullptr)
                s += " R_child: ()";
            else
                s += " R_child: (" + func(&arr[i]->right_child->data) + ')';

            s += " ]\n";
        }

        s += '}';

        delete[] arr;
        return s;
    }

    int height_h(Node<T>* n) {
        if (n == nullptr)
            return 0;

        int lb_height = height_h(n->left_child);
        int rb_height = height_h(n->right_child);

        if (lb_height < rb_height)
            return 1 + rb_height;
        else
            return 1 + lb_height;
        //return lb_height + 1; sprawdzić gdyby nie działało
    }

    int height() {
        return height_h(root);
    }

};

template <typename T>
int BST<T>::traversal_index = 0;

struct simple_object {
    int f1 = NULL;
    char f2 = NULL;
};

std::string str(simple_object* o) {
    std::string s = std::to_string(o->f1) + ", " + o->f2;
    return s;
}

int simpleObjectComparator(simple_object* o1, simple_object* o2) {
    if (o1->f1 == o2->f1)
        return 0;
    else if (o1->f1 < o2->f1)
        return -1;
    else
        return 1;
}

int main()
{
    BST<simple_object>* bst = new BST<simple_object>();
    std::cout << bst->insert({ 1, 'j' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 1, 'd' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 5, 'p' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 4, 'c' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 3, 't' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 3, 'f' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 0, 'f' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 2, 'f' }, simpleObjectComparator) << '\n';
    std::cout << bst->insert({ 7, 's' }, simpleObjectComparator) << '\n';
    //std::cout << bst->insert({ 8, 's' }, simpleObjectComparator) << '\n';
    //std::cout << bst->insert({ 9, 's' }, simpleObjectComparator) << '\n';
    //std::cout << bst->insert({ 10, 's' }, simpleObjectComparator) << '\n';
    Node<simple_object>* n1 = bst->search({ 4, 'n' }, simpleObjectComparator);
    //std::cout << n1->parent->data.f1;
    //bool y = (bst->root->parent == nullptr);
    //std::cout << "Czy nullptr " << y;
    std::cout << "\n---------\n";
    //bst->clear();
    std::cout << "In-order walk" << bst->inorderTraversal(str) << '\n';
    std::cout << "Pre-order walk" << bst->preorderTraversal(str) << '\n';

    //std::cout << '\n' << bst->root << '\n';
    std::cout << bst->str(str);

    std::cout << "\n" << bst->height();
    delete bst;
}

