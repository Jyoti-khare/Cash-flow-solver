#include <iostream>
#include<set>
#include<map>
using namespace std;

class person_compare {
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    }
};

int main() {
    int no_of_transactions, friends;
    cout<<"No of transactions:"<<" ";
    cin >> no_of_transactions;
    cout<<"No. of friends:"<<" ";
    cin>> friends;
    string x, y;
    int amount;
    map<string, int> net;

    cout<<"Enter transactions in the given format:"<<endl;
    cout<<"Debit_person    Credit_person    amount"<<endl;
    while (no_of_transactions--){
        cin >> x >> y >> amount;
        if (net.count(x) == 0){
            net[x] = 0;
        }
        if (net.count(y) == 0){
            net[y] = 0;
        }
        net[x] -= amount; //subtract amount from debit_person
        net[y] += amount; //add amount to credit_person
    }

    //Iterate over the persons, add those person in the multiset who have non zero net
    multiset<pair<string, int>, person_compare> m;
    for (auto p : net){
        string person = p.first;
        int amount = p.second;
        if (net[person] != 0){
            m.insert(make_pair(person, amount));
        }
    }

    //settlements (start & end)
    int count = 0;
    while (!m.empty()) {
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->second;
        string debit_person = low->first;
        int credit = high->second;
        string credit_person = high->first;

        //Pop low and high
        m.erase(low);
        m.erase(high);

        int settled_amount = min(-debit, credit);
        debit += settled_amount;
        credit -= settled_amount;

        //Print the Transaction between people
        cout << debit_person << " will pay " << settled_amount << " to " << credit_person << endl;
        if (debit != 0){
            m.insert(make_pair(debit_person, debit));
        }
        if (credit != 0){
            m.insert(make_pair(credit_person, credit));
        }
        count++;
    }
    if(count==0)
        cout <<"No transactions"<< endl;
    else cout <<"Total transactions to be made:"<<" "<<count << endl;
    return 0;
}

/*
Output will be:
Rahul pays 50 to Ajay
Rahul pays 10 to Neha
Total transactions to be made: 2
*/