﻿#pragma GCC optimize("Ofast")
 
// #include <bits/stdc++.h>
#include <iostream>      // * Header that defines the standard input/output stream objects: [ cin, cout, cerr ]
#include <iomanip>       // * iomanip is a library that is used to manipulate the output of C++ program. [set_precision, set_time]
#include <cassert>       // * C Diagnostics Library -> assert.h defines one macro function that can be used as a standard debugging tool :
#include <cmath>         // * Header <cmath> declares a set of functions to compute common mathematical operations and transformations. Link: http://www.cplusplus.com/reference/cmath/
#include <cstdio>        // * Streams are handled in the cstdio library as pointers to FILE objects.
#include <cstring>       // * This header file defines several functions to manipulate C strings and arrays. Link: http://www.cplusplus.com/reference/cstring/
#include <cstdlib>       // * This header defines several general purpose functions, including dynamic memory management, random number generation, communication with the environment, integer arithmetics, searching, sorting and converting. Link : http://www.cplusplus.com/reference/cstdlib/
#include <map>           // * Header that defines the map and multimap container classes. Maps are typically implemented as BST. binary search trees.
#include <set>           // * Sets are typically implemented as binary search trees.
#include <stack>         // * template <class T, class Container = deque<T> > class stack;
#include <queue>         // * Link : https://en.cppreference.com/w/cpp/header/queue
#include <vector>        // * Constructs a vector, initializing its contents depending on the constructor version used.
#include <chrono>        // * The chrono library defines three main types as well as utility functions and common typedefs. clock, time points, durations.
#include <algorithm>     // * The header <algorithm> defines a collection of functions especially designed to be used on ranges of elements. Link : http://www.cplusplus.com/reference/algorithm/
#include <unordered_map> // *
#include <unordered_set> // *
 
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// Link : https://codeforces.com/blog/entry/11080
template <typename T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// ! order_of_key(x) : returns the number of values less than x
// ! find_by_order(k) : returns the iterator to kth largest element. (0-based)
 
#define int long long
#define pb push_back
#define endl "\n"
#define all(CON) (CON).begin(), (CON).end()
#define F first
#define S second
#define MP make_pair
#define sz(x) (int)x.size()
#define rp(i, n) for (int i = 0; i < n; i++)
#define fr(i, n) for (int i = 1; i <= n; i++)
#define ff(i, a, b) for (int i = a; i <= b; i++)
#define fff(i, a, b) for (int i = a; i < b; i++)
#define rrp(i, n) for (int i = n - 1; i >= 0; i--)
#define rfr(i, n) for (int i = n; i >= 1; i--)
#define onlyunique(v) v.erase(unique(v.begin(), v.end()), v.end()); // remove duplicates in a sorted vector
 
#define TRACE
#ifndef ONLINE_JUDGE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char *name, Arg1 &&arg1)
{
    cerr << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    cerr.write(names, comma - names) << " : " << arg1 << " || ";
    __f(comma + 1, args...);
}
#else
#define trace(...)
#endif
 
typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<pair<int, int>> vpi;
 
const int mod = 1e9 + 7;
// const int mod = 998244353;
const long long inff = 2e18;
const int inf = 2e9;
 
int min(int x, int y) // * returns minimum of two numbers
{
    return y ^ ((x ^ y) & -(x < y));
}
int max(int x, int y) // * returns maximum of two numbers
{
    return x ^ ((x ^ y) & -(x < y));
}
// int abs(int n)
// {
//     int const mask = n >> (sizeof(int) * CHAR_BIT - 1);
//     return ((n ^ mask) - mask);
// }
int add(int a, int b) // * Recursive addition of integers
{
    if (b == 0)
        return a;
    int sum = a ^ b;
    int carry = (a & b) << 1;
    return add(sum, carry);
}
int Add(int a, int b) // * Iterative addition of two integers
{
    while (b != 0)
    {
        int sum = a ^ b;
        int carry = (a & b) << 1;
        a = sum;
        b = carry;
    }
    return a;
}
int subtract(int a, int b) // * Recursive subtraction of two integers
{
    if (b == 0)
        return a;
    return subtract((a ^ b), ((~a) & b) << 1);
}
int Subtract(int x, int y) // * Iterative subtraction of two integers
{
    while (y != 0)
    {
        int borrow = (~x) & y;
        x = x ^ y;
        y = borrow << 1;
    }
    return x;
}
// Russian Peasant using bitwise operator
int multiply(int a, int b) // * Multiplication function without using "*"
{
    int res = 0;
    while (b)
    {
        if (b & 1)
        {
            res = res + a;
        }
        a = a << 1;
        b = b >> 1;
    }
    return res;
}
int divide(int a, int b)
{
    int sign = ((a < 0) ^ (b < 0)) ? -1 : 1;
    a = abs(a);
    b = abs(b);
    int q = 0, tmp = 0;
    for (int i = 31; i >= 0; --i)
    {
        if (tmp + (b << i) <= a)
        {
            tmp += (b << i);
            q |= (1LL << i);
        }
    }
    return sign * q;
}
int bitcount(int n) // * Recursive function to check number of set bits of an integer
{
    if (n < 2)
        return n;
    return (n & 1) + bitcount(n >> 1);
}
bool ispowerof2(int n) // * check if a number is a power of 2
{
    return (__builtin_popcountll(n) == 1);
}
int gcd(int a, int b) // * Computes gcd using Euclid's algorithm
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
int lcm(int a, int b) // * Computes lcm of two numbers.
{
    return (a / gcd(a, b)) * b;
}
int binpow(int a, int b) // * Recursive power function
{
    if (b == 0)
        return a;
    int res = binpow(a, b / 2);
    if (b % 2)
        return res * res * a;
    else
        return res * res;
}
int pow(int a, int b) // * Iterative power function
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
int modpow(int a, int b, int m) // *  Modular Exponentiation Iterative
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}
bool isprime(int x) // * Check if a number is prime or not.
{
    if (x < 2)
        return false;
    if (x < 4)
        return true;
    if (!(x & 1))
        return false;
    for (int i = 3; i * i <= x; i += 2)
        if (x % i == 0)
            return false;
    return true;
}
 
const int MOD = 1e9 + 7;
const int MXX = 1e5 + 69;
int fact[MXX], invfact[MXX];
int modinv(int k) // * Inverse Mod Function
{
    return modpow(k, MOD - 2, MOD);
}
void combinatorics()
{
    fact[0] = fact[1] = 1;
    for (int i = 2; i < MXX; i++)
    {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }
 
    invfact[MXX - 1] = modinv(fact[MXX - 1]);
    for (int i = MXX - 2; i >= 0; i--)
    {
        invfact[i] = invfact[i + 1] * (i + 1);
        invfact[i] %= MOD;
    }
}
int nCr(int x, int y) // ~ nCr = ( n! / ( (n-r)! * r! ) )
{
    if (y > x)
        return 0;
    int num = fact[x];
    num *= invfact[y];
    num %= MOD;
    num *= invfact[x - y];
    num %= MOD;
    return num;
}
// transforms a string into lower case
string lwr(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
// converts a string into uppercase
string upr(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}
// function to factorize a given number
vector<int> factorize(int n)
{
    vector<int> v;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            v.push_back(i);
            if (i * i != n)
            {
                v.push_back(n / i);
            }
        }
    }
    sort(v.begin(), v.end());
    return v;
}
// Implementation of Disjoint Set Union
// using path compression and union by size.
// ! Grows very slowly - inverse ackermann function
// Link to dsu : https://cp-algorithms.com/data_structures/disjoint_set_union.html
class DSU
{
public:
    vector<int> par, sz;
    // Constructor for initializing
    DSU(int n)
    {
        n = n + 2;
        par.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++)
            par[i] = i, sz[i] = 1;
    }
    // Returns the main parent/representative of the set
    int find(int x)
    {
        if (x == par[x])
            return par[x];
        else
            return (par[x] = find(par[x])); // Path Compression Optimization
        //  first find the representative of the set (root vertex), and the in the process of stack unwinding,
        // the visited nodes are attached directly to the representative.
    }
    // Unite two sets
    void Unite(int x, int y) // Union by Size
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (sz[x] < sz[y])
            swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
    }
    // Check if 2 elements are in the same component
    bool Same(int x, int y)
    {
        return find(x) == find(y);
    }
    // returns the size of component in which element x belongs
    int size(int x)
    {
        return sz[find(x)];
    }
};
// Stack is LIFO (Last in First Out)
// Linked List based implementation of stacks
// It is better tham the implementation using arrays.
// Because it is dynamic
// In the main function, call it as StackNode sn; StackNode *root = NULL; root = all operations.
class StackNode
{
public:
    int data;
    StackNode *next;
    // Creates a new node to push onto the stack
    StackNode *CreateNode(int val)
    {
        StackNode *snw = new StackNode();
        snw->data = val;
        snw->next = NULL;
    }
    // Checks if the stack is empty
    int isEmpty(StackNode *root)
    {
        return (!root);
    }
    // Pushes a new-node onto the stack
    StackNode *push(StackNode *root, int val)
    {
        StackNode *nn = CreateNode(val);
        nn->next = root;
        root = nn;
        return root;
    }
    // remove the topmost element from the stack.
    StackNode *pop(StackNode *root)
    {
        if (isEmpty(root))
            return NULL;
        StackNode *tmp = root;
        (root) = (root)->next;
        int popped = tmp->data;
        free(tmp);
        return root;
    }
    // Returns the topmost element of the stack.
    int peek(StackNode *root)
    {
        if (isEmpty(root))
            return -2e9;
        return root->data;
    }
    // Returns the size of the stack
    int size(StackNode *root)
    {
        StackNode *a = root;
        int ans = 0;
        while (a != NULL)
        {
            a = a->next;
            ans++;
        }
        return ans;
    }
};
// Node representing a node of a Queue
class QNode
{
public:
    int data;
    QNode *next;
    QNode(int val)
    {
        data = val;
        next = NULL;
    }
};
// Class for operations on a Queue
// Queue is LIFO Last in First Out
class Queue
{
public:
    QNode *front;
    QNode *rear;
    Queue()
    {
        front = rear = NULL;
    }
    // Adding an element
    void EnQueue(int x)
    {
        QNode *tmp = new QNode(x);
        if (rear == NULL)
        {
            front = rear = tmp;
            return;
        }
        rear->next = tmp;
        rear = tmp;
    }
    // Removing an element
    void DeQueue()
    {
        if (front == NULL)
            return;
        QNode *tmp = front;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        delete (tmp);
    }
    // To access the first element of the Queue
    int Front()
    {
        return front->data;
    }
    // To access the last element of the Queue
    int Back()
    {
        return rear->data;
    }
    // Check if the Queue is Empty
    bool isEmpty()
    {
        return front == rear and front == NULL;
    }
    // Prints the elements of the Queue
    void displayQueue()
    {
        QNode *a = front;
        while (a != NULL)
        {
            cout << (a->data) << " ";
            a = a->next;
        }
        cout << endl;
    }
};
// Function to print a vector
template <typename T>
void prev(vector<T> &v)
{
    for (auto t : v)
        cout << t << " ";
    cout << endl;
}
// Function to print a vector and its size too
template <typename T>
void prevs(vector<T> &v)
{
    cout << v.size() << endl;
    for (auto t : v)
        cout << t << " ";
    cout << endl;
}
// Function to print an array
void prar(int a[], int n, int x)
{
    for (int i = 0 + x; i < n + x; i++)
        cout << a[i] << " ";
    cout << endl;
}
template <typename T>
std::pair<bool, int> findInVector(const std::vector<T> &vecOfElements, const T &element)
{
    std::pair<bool, int> result;
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
    if (it != vecOfElements.end())
    {
        result.second = distance(vecOfElements.begin(), it);
        result.first = true;
    }
    else
    {
        result.first = false;
        result.second = -1;
    }
    return result;
}
// function to check if a character is a vowel.
bool isvowel(char ch)
{
    string s = "aeiouAEIOU";
    for (char c : s)
        if (c == ch)
            return true;
    return false;
}
const int infms = 2e9;
int inversions = 0;
void Merge(int a[], int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int left[n1 + 2];
    int right[n2 + 2];
    left[n1 + 1] = infms;
    right[n2 + 1] = infms;
 
    for (int i = 1; i <= n1; i++)
        left[i] = a[start + i - 1];
 
    for (int i = 1; i <= n2; i++)
        right[i] = a[mid + i];
 
    int x = 1, y = 1;
    for (int k = start; k <= end; k++)
        if (left[x] <= right[y])
        {
            a[k] = left[x];
            x++;
        }
        else
        {
            inversions += (1 + n1 - x);
            a[k] = right[y];
            y++;
        }
}
// Merge Sort algorithm
void MergeSort(int a[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(a, start, mid);
        MergeSort(a, mid + 1, end);
        Merge(a, start, mid, end);
    }
}
// Recursive function to check if string is a palindrome
bool ispalindrome(string s)
{
    int n = s.length();
    if (n <= 1)
        return true;
    else if (n == 2 && s[1] == s[0])
        return true;
    else if (n == 2 && s[0] != s[1])
        return false;
    else if (s[0] != s[n - 1])
        return false;
    else
        return ispalindrome(s.substr(1, n - 2));
}
// function to check if string is a palindrome using STL
bool palindrome(string s)
{
    string t = s;
    reverse(all(t));
    return (t == s);
}
// iterative function to check if a string is a palindrome
bool checkpalindrome(string s)
{
    for (int i = 0; i <= s.length(); i++)
        if (s[i] != s[s.length() - 1 - i])
            return false;
    return true;
}
bool sortbysec(const pair<int, int> &a, const pair<int, int> &b)
{
    return (a.second < b.second);
}
// Dijkstra algorithm for Sparse Graph.
// ! single source shortest path algorithm for a graph with non negative edges.
// Implementation using Priority_queue
// ! Priority Queue is based on heaps.
// Therefore, it has a smaller hidden constant factor
//  but also has a drawback: it doesn't support the operation of removing an element.
// ? Link : https://cp-algorithms.com/graph/dijkstra_sparse.html
const int NN = 1e5 + 5;
vector<pair<int, int>> adj[NN];
vi d, p;
void dijkstra(int s, vector<int> &d, vector<int> &p)
{
    int n = NN;
    d.assign(n, inf);
    p.assign(n, -1);
    d[s] = 0; // distance of node from itself is 0.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s}); // pushing the distance of node and node to the priority_queue
    while (!q.empty())
    {
        int v = q.top().second;  // the node
        int d_v = q.top().first; // the distance of the node from the source
        q.pop();
        if (d_v != d[v])
            continue; // we have found a shorter distance.
        // we can't delete the pii so we continue to next pii
        for (auto edge : adj[v])
        {
            int to = edge.first;
            int len = edge.second;
            if (d[v] + len < d[to])
            {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}
void path(vi &v, int d)
{
    if (p[d] != -1)
        path(v, p[d]);
    v.pb(d);
}
int addm(int a, int b)
{
    return ((a % mod) + (b % mod) + mod) % mod;
}
int subm(int a, int b)
{
    return ((a % mod) - (b % mod) + 2 * mod) % mod;
}
int mulm(int a, int b)
{
    return ((a % mod) * (b % mod) + mod) % mod;
}
int C(int n, int r)
{
    if (r > n - r)
        r = n - r; // because C(n, r) == C(n, n - r)
    int ans = 1;
    int i;
    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}
void dream();
auto clk = clock();
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    cout << setprecision(8);
    // ! while( (double)clock() / CLOCKS_PER_SEC < 0.95 ) // can be used in special cases
    // #ifndef ONLINE_JUDGE // Comment this if the question demands input-output through a file
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    // #endif
    // !  combinatorics(); // Take care of MOD
    int TESTCASES = 1;
    // cin >> TESTCASES;
    for (int i = 1; i <= TESTCASES; i++)
        dream();
 
#ifndef ONLINE_JUDGE
    cout << endl
         << "Time elapsed: " << (double)(clock() - clk) / CLOCKS_PER_SEC << endl
         << endl;
#endif
    return 0;
}
 
/* Comments  */
// * green
// ~ blue
// @ purple
// # orange
// $ lime
// ! red
 
void dream()
{
    int n, c;
    cin >> n >> c;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
 
    int ans = 0;
    for (int i = 0; i < n - 1; i++)
        ans = max(ans, a[i] - a[i + 1] - c);
 
    cout << ans << endl;
 
    // ? you should actually read the stuff at the bottom
}
/*
    ! stuff you should look for
        * int overflow, array bounds
        * special cases (n=1)?
        * boundary cases
        * do something instead of nothing and stay organized.
        # BELIEVE in yourself.
*/
/*
? Some basic stuff that you should learn:
 
        ? Sets : Unique element container.
            ! set<int,greater<int> > s; // to order the set in descending order
            * To check if an element is in a set : s.count(x)
            ! Another method to check if an element exists in a set :if(s.find(x)!=s.end()){ // condition  }
            * Value of First Element of Set : *(s.begin())
            * Value of Last Element of Set : *(--s.end())
            ! To erase an element by value: s.erase(x);
            * begin() - returns an iterator to first element of set. The value of the element can be accessed using *(s.begin())
            * end() - Returns an iterator to the theoretical element that follows last element in the set.
            * size() - Returns the number of elements in the set.
            * max_size() - Returns the maximum number of elements that the set can hold.
            * empty() - Returns whether the set is empty.
            ! find(x) - Returns an iterator to the element ‘x’ in the set if found, else returns the iterator to end.
            * erase(x)– Removes the value ‘x’ from the set. It erases an element by value
            * count(x) - Returns 1 or 0 based on the element ‘x’ is present in the set or not. It's the best way to check for the presence of an element.
            * lower_bound(x) – Returns an iterator to the first element that is equivalent to ‘x’ or definitely will not go before the element ‘x’ in the set.
              lower_bound can also be thought as the smallest element greater than or equal to x
            * Return reverse iterator to reverse beginning: (s.rbegin())
            * Set to be sorted in decreasing order: set<int, greater<int> >
            * emplace() : If the function successfully inserts the element (because no
                    equivalent element existed already in the set), the function returns a
                    pair of an iterator to the newly inserted element and a value of true.
            * const bool is_in = s.find(x) != s.end(); check if an element is in the set.
            ! myset.erase(x) #directly by value. logarithmic complexity
            ! myset.erase(iteratortoanelement,s.end())
            * for_each(all(s),do_something);
            ! set<int> :: iterator it = myset.find(60);
 
        ? Vectors
            @ Erase elemnents by value rather than position
            # vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());
            *
            @ Erase duplicates in a sorted array
            # v.erase(unique(v.begin(), v.end()), v.end());
            *
            @ Erase elements by position
            # vec.erase(vec.begin() + 1);
            vector<int> v; v.resize(n,0); // resizes the vector and initializes it too.
            front(), back(), push_back(), pop_back()
            * begin() - Returns an iterator pointing to the first element in the vector
            * end() - Returns an iterator pointing to the theoretical element that follows the last element in the vector
            * rbegin() - Returns a reverse iterator pointing to the last element in the vector (reverse beginning).
            * rend() - Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
            * cbegin(),cend(),crbegin(),crend()
            * size() - Returns the number of elements in the vector.
            * max_size() -  Returns the maximum number of elements that the vector can hold.
            * capacity() - Returns the size of the storage space currently allocated to the vector expressed as number of elements.
            * resize() - Resizes the container so that it contains ‘n’ elements.
            * empty() - Returns whether the container is empty.
            * shrink_to_fit() - Reduces the capacity of the container to fit its size and destroys all elements beyond the capacity.
            * reserve() - Requests that the vector capacity be at least enough to contain n elements.
            * [i] - Returns a reference to the element at position ‘i’ in the vector
            * at(i) - Returns a reference to the element at position ‘i’ in the vector
            # front() - Returns a reference to the first element in the vector
            # back() - Returns a reference to the last element in the vector
            * data() - Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
            * assign() - It assigns new value to the vector elements by replacing old ones
            * push_back() - It push the elements into a vector from the back
            # pop_back() - It is used to pop or remove elements from a vector from the back.
            ! insert() - It inserts new elements before the element at the specified position
            * erase() - It is used to remove elements from a container from the specified position or range
            * swap() - It is used to swap the contents of one vector with another vector of same type. Sizes may differ.
            * clear() - It is used to remove all the elements of the vector container
            * emplace() - It extends the container by inserting new element at position
            * emplace_back() - It is used to insert a new element into the vector container, the new element is added to the end of the vector
            # for (auto it = myvector.begin(); it != myvector.end(); ++it)  // normal iterator
            # for (auto t:v)
 
        ? Queue
            * empty() - Returns whether the queue is empty.
            * size() - Returns the size of the queue.
            * emplace() - Insert a new element into the queue container, the new element is added to the end of the queue.
            * front() - front() function returns a reference to the first element of the queue.
            * back() - returns a reference to the last element of the queue.
            * push(x) - adds the element ‘x’ at the end of the queue
            * pop() - deletes the first element of the queue
 
        ? Priority_Queue
            ! priority_queue <int, vector<int>, greater<int>> pq; // to make a priority queue in descending order
            * empty() - returns whether the queue is empty.
            * size() -  returns the size of the queue.
            # top() -  Returns a reference to the top most element of the queue
            * push(x) - adds the element ‘x’ at the end of the queue.
            * pop() -  deletes the first element of the queue.
            * swap() -  swap the contents of one priority queue with another priority queue of same type and size.
            * emplace() - insert a new element into the priority queue container, the new element is added to the top of the priority queue.
 
        ? Deque
            Double ended queues are sequence containers with the feature of expansion and contraction on both the ends.
            They are similar to vectors, but are more efficient in case of insertion and deletion of elements.
            Unlike vectors, contiguous storage allocation may not be guaranteed.
            * insert()
            * rbegin()
            * rend()
            * assign()
            * resize()
            * push_front()
            * push_back()
            * pop_front()
            * pop_back()
            * front()
            * back()
*/