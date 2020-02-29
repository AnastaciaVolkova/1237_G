#include "CircleList.hpp"
#include <string>

void TestCircle() {
    CircleList<int> cir(1);
    cir.Insert(2);
    cir.Insert(3);
    cir.Insert(4);

    {
        CircleList<int>::iterator it = cir.begin();
        it = cir.Insert(it, 10);
        it += 2;
        it = cir.Insert(it, 30);
        it += 1;
        it = cir.Insert(it, 40);
        it = cir.begin();
        it += (cir.size() - 1);
        cir.Insert(it, 50);
    }

    CircleList<int>::iterator it = cir.begin();
    for (int i = 0; i < 19; i++) {
        cout << *it << endl;
        ++it;
    }
    cout << endl << endl;
    for (int i = 0; i < 18; i++) {
        cout << *it << endl;
        --it;
    }
};


template<> long long Node<conditional<is_specialization<int, vector>::value, int, vector<int>>::type>::global_id = 0;

int main(int argc, char* argv[]){
    if ((argc == 1) || (argv[1] == "0")){
        TestCircle();
    }
    return 0;
}
