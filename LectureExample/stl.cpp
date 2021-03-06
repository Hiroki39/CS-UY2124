#include <algorithm>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
using namespace std;

// char* myFind(char* start, char* stop, char target) {
//     for (char* p = start; p != stop; ++p) {
//         if (target == *p) {
//             return p;
//         }
//     }
//     return stop;
// }

template <typename Fred, typename Mary>
Fred myFind(Fred start, Fred stop, Mary target) {
    for (Fred p = start; p != stop; ++p) {
        if (target == *p) {
            return p;
        }
    }
    return stop;
}

template <typename Fred, typename Predicate>
Fred myFind_if(Fred start, Fred stop, Predicate pred) {
    for (Fred p = start; p != stop; ++p) {
        if (pred(*p)) {  // if (pred(*p) == true)
            return p;
        }
    }
    return stop;
}

bool isEven(int n) {  // Predicate
    // return n % 2 == 0;

    // 5 == 101
    // 4 == 100
    // 5 & 1 = 101&001 == 001 == 1
    return (n & 1) == 0;  // bitwise operation! (faster)
}

// Functor
// struct IsEven
// functor is more efficient
class IsEven {
public:
    bool operator()(int n) { return (n & 1) == 0; }
};

class IsMultiple {
public:
    IsMultiple(int divisor) : divisor(divisor) {}
    bool operator()(int n) { return n % divisor == 0; }

private:
    int divisor;
};

// pair<int, string> foo() {
//     pair<int, string> result(42, "theanswer");
//     return result;
// }

auto foo() { return make_pair(42, "the answer"); }

int main() {
    char bjarne[] = "Bjarne Stroustrup";
    int len = 17;
    sort(bjarne, bjarne + len);  // Uses a half open range [start, stop

    vector<char> vc(bjarne, bjarne + len);
    // list<char> lc(&vc[0], &vc[vc.size()]);
    list<char> lc(vc.begin(),
                  vc.end());  // itialize a linked list based on the vector
    vector<char>::iterator loc1 =
        find(vc.begin(), vc.end(), 'S');  // return an Iterator!
    vector<char>::iterator loc2 = find(vc.begin(), vc.begin() + 4, 'Q');

    if (loc2 == vc.begin() + 4) {
        cout << "couldn't find 'Q' in bjarne's name" << endl;
    }

    list<char>::iterator loc3 =
        find(lc.begin(), lc.end(), 'S');  // return an Iterator!
    list<char>::iterator loc4 = find(lc.begin(), lc.end(), 'Q');

    for (char c : vc) {
        cout << c << ' ';
    }
    cout << endl;

    for (vector<char>::iterator iter = vc.begin(); iter != vc.end(); ++iter) {
        char c = *iter;
        cout << c << ' ';
    }
    cout << endl;

    char* loc5 = find(bjarne, bjarne + len, 'S');
    loc5 = myFind(bjarne, bjarne + len, 'S');
    vector<char>::iterator loc6 = myFind(vc.begin(), vc.begin() + 4, 'Q');

    IsEven anIsEvenFunct;
    anIsEvenFunct(14);  // return true

    vector<int> vi{3, 21, 14, 9};
    // returns an iterator pointing to the first found element
    // vector<int>::iterator loc7 = find_if(vi.begin(), vi.end(), isEven);
    // equivalent to
    vector<int>::iterator loc7 = find_if(vi.begin(), vi.end(), IsEven());

    IsMultiple multipleOf7(7);
    // loc7 = find_if(vi.begin(), vi.end(), multipleOf7);
    // equivalent to
    loc7 = find_if(vi.begin(), vi.end(), IsMultiple(7));

    // lambda expression
    // loc7 = find_if(vi.begin(), vi.end(), [](int n) -> bool { return n % 2 ==
    // 0; });
    loc7 = find_if(vi.begin(), vi.end(),
                   [](int n) { return n % 2 == 0; });  // a functor is created

    // automtically determine the type of loc8
    auto loc8 =
        find_if(vi.begin(), vi.end(), [](int n) { return (n & 1) == 0; });

    auto iamalambda = [] { cout << "I am a lambda\n"; };  // no parameter list!

    // pair<int, string> val = foo();
    auto val = foo();
    cout << val.first << " " << val.second << endl;

    int* arrInt = new int[10];
    for (int i = 0; i < 10; ++i) {
        arrInt[i] = i * i;
    }
    cout << myFind(arrInt, arrInt + 10, 49) << endl;
}
