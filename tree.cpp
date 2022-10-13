#include <iostream>
#include <limits>

using namespace std;
int check(int x) //checking for a fool
{
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect input. Try again: ";
        cin >> x;
    }
    return x;
}

int check_n(int x) //checking for a fool
{
    while (cin.fail() || x < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect input. Try again: ";
        cin >> x;
    }
    return x;
}

int check_m(int x) //checking for a fool
{
    while (cin.fail() || x < 1 || x>7)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect input. Try again: ";
        cin >> x;
    }
    return x;
}

int check_t(int x) //checking for a fool
{
    while (cin.fail() || x < 1 || x>2)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect input. Try again: ";
        cin >> x;
    }
    return x;
}

struct tree
{
    int elem; //node content
    int height; //node height
    tree* left; //pointer to the left child
    tree* right; //pointer to the right child
};

tree* putel(tree* p, int el)
{
    p->elem = el;
    p->left = 0;
    p->right = 0;
    p->height = 1;

    return p;
}

int height(tree* p)
{
    return p ? p->height : 0;
}

int balfactor(tree* p)
{
    return height(p->right) - height(p->left);
}

void newheight(tree* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

tree* turnright(tree* p)
{
    tree* q = p->left;
    p->left = q->right;
    q->right = p;
    newheight(p);
    newheight(q);
    return q;
}

tree* turnleft(tree* p)
{
    tree* q = p->right;
    p->right = q->left;
    q->left = p;
    newheight(p);
    newheight(q);
    return q;
}

void print_tree(tree* p, int level)
{
    if (p)
    {
        print_tree(p->right, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->elem << endl;
        print_tree(p->left, level + 1);
    }
}

tree* balance(tree* p) // balancing node p
{
    newheight(p);
    if (balfactor(p) == 2)
    {
        if (balfactor(p->right) < 0)
            p->right = turnright(p->right);
        return turnleft(p);
    }
    if (balfactor(p) == -2)
    {
        if (balfactor(p->left) > 0)
            p->left = turnleft(p->left);
        return turnright(p);
    }
    return p;
}

tree* adding(tree* p, int el) // inserting the key k into a tree with the root p
{
    if (p) {
        if (el < p->elem)
            p->left = adding(p->left, el);
        else
            p->right = adding(p->right, el);
    }
    else {
        p = (struct tree*)malloc(sizeof(struct tree)); //allocating memory for a pointer

        p = putel(p, el);
        return p; //output of the pointer to the beginning of the list
    }
    //   print_tree(p, p->height);
    return balance(p);
}

void travel(tree* p) {
    if (p) {
        travel(p->left);
        cout << p->elem << "\t";
        travel(p->right);
    }
}

bool findel(tree* p, int el, int* k)
{
    (*k)++;
    if (p) {
        if (findel(p->left, el, k)) return true;
        if (p->elem == el) return true;
        if (findel(p->right, el, k)) return true;
    }
    return false;
}

tree* newtree(tree* q, tree* p, int el)
{
    if (p) {
        q = newtree(q, p->left, el);
        if (p->elem != el)
        {
            q = adding(q, p->elem);
        }
        q = newtree(q, p->right, el);
    }
    return q;
}

tree* findmin(tree* p)
{
    return p->left ? findmin(p->left) : p;
}

tree* delmin(tree* p)
{
    if (p->left == 0)
        return p->right;
    p->left = delmin(p->left);
    return balance(p);
}

tree* del(tree* p, int el)
{
    if (!p) return 0;
    p->left = del(p->left, el);
    if (el == p->elem)
    {
        tree* l = p->left;
        tree* r = p->right;
        delete p;
        if (!r) return l;
        tree* minim = findmin(r);
        minim->right = delmin(r);
        minim->left = l;
        return balance(minim);
    }
    p->right = del(p->right, el);
    return balance(p);
}

void medium(tree* p, int* m, int* k)
{
    if (p)
    {
        medium(p->left, m, k);
        (*k)++;
        *m = *m + p->elem;
        medium(p->right, m, k);
    }
}

tree* minusik(tree* p, int m)
{
    if (p)
    {
        p->left = minusik(p->left, m);
        p->elem -= m;
        p->right = minusik(p->right, m);
    }
    return p;
}

tree* ext(tree* p)
{
    if (p)
    {
        p->left = ext(p->left);
        if ((p->elem) % 3 == 0)
        {
            p = del(p, p->elem);
        }
        if (p != 0) {
            p->right = ext(p->right);
            balance(p);
        }
        else
            return p;
    }
  
    return p;
}

tree* delminus(tree* p)
{
    if (p)
    {
        p->left = delminus(p->left);
        if (p->elem < 0)
        {
            p = del(p, p->elem);
        }
        if (p != 0) {
            p->right = delminus(p->right);
            balance(p);
        }
        else
        {
            return p;
        }
    }
    return p;
}

bool negativ(tree* p)
{
    if (p)
    {
        if (negativ(p->left)) return true;
        if ((p->elem) < 0)
        {
            return true;
        }
        if(negativ(p->right)) return true;
    }
    return false;
}

tree* chchchange(tree* p)
{
    int m = 0;
    int k = 0;
    medium(p, &m, &k);
    m = m / k;
    cout << "Arithmetic mean : " << m << endl;
    p = minusik(p, m);
    cout << "The result of subtraction:" << endl;
    print_tree(p, p->height);

    p = ext(p);
    cout << "The result of removing numbers that are multiples of 3:" << endl;
    if (p == 0)
    {
        cout << "The tree is empty" << endl;
        return p;
    }
    print_tree(p, p->height);
    while (negativ(p))
    {
        p = delminus(p);
    }
    cout << "The end result:" << endl;
    if (p == 0)
    {
        cout << "The tree is empty" << endl;
        return p;
    }
    print_tree(p, p->height);
    return p;
}

int menu()
{
    cout << "\nSelect an action:\n\n";
    cout << "1.Element Search\n";
    cout << "2.Add an element\n";
    cout << "3.Delete an item\n";
    cout << "4.Tree output\n";
    cout << "5.Wood processing\n";
    cout << "6.Exit\n";
    cout << "\nEnter a menu item: ";

    int ch;
    cin >> ch;
    ch = check_m(ch);
    return ch;
}

int main()
{
    setlocale(LC_ALL, "rus");
    tree* p = 0;
    bool stop = false;
    cout << "Enter the number of items in the tree: ";
    int n;
    cin >> n;
    n = check_n(n);
    cout << "Fill in the tree:\n\n1.Random values.\n2.Manually.\n\n";
    cout << "Your choice: ";
    int ch;
    cin >> ch;
    ch = check_t(ch);
    if (ch == 1)
    {
        for (int i = 0; i < n; i++)
        {
            int x = rand() % 100;
            int k = 0;
            if (findel(p, x, &k))
            {
                cout << "Mistake! Element " << x << "already present in the tree!" << endl;
                continue;
            }
            p = adding(p, x);
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << "Enter a number: ";
            int x;
            cin >> x;
            x = check(x);
            p = adding(p, x);
            cout << "Successfully added!\n";
        }
    }
    while (!stop)
        switch (menu())
        {
        case 1:
        {
            cout << "Enter a number: ";
            int x;
            cin >> x;
            x = check(x);
            int k = 0;
            if (findel(p, x, &k))
            {
                cout << "Element " << x << " found.\n";
                cout << "\nNumber of steps: " << k << endl;
            }
            else cout << "Element not found!" << endl;
            break;
        }
        case 2:
        {
            cout << "Enter a number: ";
            int x;
            cin >> x;
            x = check_n(x);
            int k = 0;
            if (findel(p, x, &k))
            {
                cout << "Mistake! Element " << x << " already present in the tree!" << endl;
                continue;
            }
            p = adding(p, x);
            cout << "New item successfully added!\n";
            break;
        }
        case 3:
        {
            if (p == 0)
            {
                cout << "Mistake! The tree is empty!" << endl;
                break;
            }
            cout << "Enter a number: ";
            int x;
            cin >> x;
            x = check_n(x);
            int k = 0;
            if (findel(p, x, &k))
            {
                p = del(p, x);
                cout << "The item was successfully deleted!\n";
                break;
            }
            cout << "Element not found!\n";
            break;
        }
        case 4:
            print_tree(p, 1);
            break;
        case 5:
            if (p == 0)
            {
                cout << "Mistake! The tree is empty!" << endl;
                break;
            }
            p = chchchange(p);
            break;
        case 6:
            stop = true;
            break;
       
        default:
            break;
        }

    return 0;
}
