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
    int no_of_transactions;
    cout<<endl;
    cout<<"---------------------------------------"<<endl;
    
    cout<<"No of transactions:"<<" ";
    cin >> no_of_transactions;
   
    string payer, receiver; // x - debit person | y - credit person
    int amount;
    map<string, int> net;

    cout<<"---------------------------------------"<<endl;
    cout<<"Enter transactions in the given format:"<<endl;
    cout<<"Payer needs to pay AMOUNT to Receiver."<<endl;
    cout<<"---------------------------------------"<<endl;
    cout<<"|    Payer     Receiver     amount    |"<<endl;
    cout<<"---------------------------------------"<<endl;

    //LOOP FOR USER_INPUT & MAINTAIN AMOUNT BY ADDING AMT TO RECEIVER AND SUBTRACTING AMT FROM PAYER
    while (no_of_transactions--){
        cin >> payer >> receiver >> amount;
        if (net.count(payer) == 0){
            net[payer] = 0;
        }
        if (net.count(receiver) == 0){
            net[receiver] = 0;
        }
        net[payer] -= amount; //subtract amount from Person1
        net[receiver] += amount; //add amount to Person2
    }
    cout<<"---------------------------------------"<<endl;

    //Iterate over the persons, add those person in the multiset who have non zero net
    multiset<pair<string, int>, person_compare> m;
    for (auto p : net){
        string person = p.first;
        int amount = p.second;
        if (net[person] != 0){
            m.insert(make_pair(person, amount));
        }
    }

    //settlements 
    int count = 0; // to count min transactions
    while (!m.empty()) {
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->second;
        string debit_person = low->first;
        int credit = high->second;
        string credit_person = high->first;

        //after settlement of low & high, Pop low and high
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
    
    cout<<"---------------------------------------"<<endl;
    if(count==0)
        cout <<"No transactions"<< endl;
    else cout <<"Total transactions to be made:"<<" "<<count << endl;
    cout<<"---------------------------------------"<<endl;
    return 0;
}

/*
Output will be:
Rahul pays 50 to Ajay
Rahul pays 10 to Neha
Total transactions to be made: 2
*/
