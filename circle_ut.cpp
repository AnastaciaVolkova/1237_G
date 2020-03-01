#include "circle_list.hpp"

using namespace std;

void TestCircleInt() {
    cout << "Test circle integer" << endl;
    {
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
    }
    {
        CircleList<int> cir = {0, 1, 2};
        CircleList<int>:: iterator it = cir.begin();
        while(it != cir.end()){
            cout << *it << endl;
            ++it;
        }
        cout << *it << endl;
    }
};

void TestCircleAdv(){
    cout << "Test circle advanced." << endl;
    CircleListAdvance<int> cir = {3, 2, 6, 1, 10, 3, 2};
    CircleListAdvance<int>::PQueue mm;
    cir.ComputeSums(mm);
    while(!mm.empty()){
        auto a = mm.top();
        mm.pop();
        cout << a.sum << endl;
    }
    cout << "Before Balance" << endl;
    cout << cir << endl;

    auto it = cir.begin();
    ++it;
    cir.Balance(it);
    cout << "After Balance" << endl;
    cout << cir << endl;
    cout << endl << endl;
};

template<> long long Node<int>::global_id = 0;

int main(int argc, char* argv[]){
    if (argc == 1){
        TestCircleInt();
    } else {
        for (int i = 1; i < argc; i++){
            switch(stoi(argv[i])){
                case 0: TestCircleInt(); break;
                case 1: TestCircleAdv(); break;
            }
        }
    }
    return 0;
}
