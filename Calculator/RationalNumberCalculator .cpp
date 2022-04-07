#include <bits/stdc++.h>
using namespace std;
bool is_new = true,is_div = false, is_multi = false;
string user_input,s_tmp="";
int n_tmp;
vector<pair<int,int>>arr;
vector<bool>oper;

void make_variables(){
    // clear all variables
    is_new = true;
    is_div = is_multi = false;
    s_tmp = "";
    arr.clear();
    oper.clear();
}

void take_input(){
    // take user equation
    cout<<"Please enter a rational number operations (or exit):\n";
    user_input = "";
    while (user_input.empty()){
        getline(cin,user_input);
    }
    user_input.erase(remove(user_input.begin(),user_input.end(),' '),user_input.end());
}

bool is_valid(){
    // check equation validation
    bool is_operator = false,is_divisor = false;
    for(auto i : user_input){
        if((i<'0' || i>'9') && (i!= '-' && i != '+' && i != '*' && i != '/')){
            return false;
        }
        if(i == '-' || i == '+' || i == '*' || i =='/'){
            if(is_operator){
                return false;
            }
            if(i == '/'){
                is_divisor = true;
            }
            if(i == '+' || i == '-' || i == '*'){
                is_divisor = false;
            }
            is_operator = true;
        }else{
            if(i == '0' && is_divisor){
                return false;
            }
            is_operator = false;
        }
    }
    return true;
}


void solve(){
    // make blocks from the operation
    for (int i = 0; i <= user_input.size(); ++i) {
        if(i == 0 && user_input[i] == '-'){
            s_tmp += '-';
            continue;
        }
        if(i == user_input.size() || user_input[i] == '-' || user_input[i] == '+' || user_input[i] == '*' || user_input[i] == '/'){
            n_tmp = stoi(s_tmp);
            s_tmp = "";
            if(is_div){
                arr.back().second *= n_tmp;
                is_div = false;
            }
            if(is_multi){
                arr.back().first *= n_tmp;
                is_multi = false;
            }
            if(is_new){
                arr.push_back({n_tmp,1});
                is_new = false;
            }
            if(i == user_input.size()){
                break;
            }
            if(user_input[i] == '+' || user_input[i] == '-'){
                oper.push_back((user_input[i] == '+'));
                is_new = true;
            }
            if(user_input[i] == '*'){
                is_multi = true;
            }
            if(user_input[i] == '/'){
                is_div = true;
            }

        }else{
            s_tmp += user_input[i];
        }
    }
    // add or subtract blocks
    for(auto itr = oper.rbegin(); itr != oper.rend(); itr++){
        pair<int,int>p_tmp = arr.back();
        arr.pop_back();
        int arr_tmp = arr.back().second;
        arr.back().first *= p_tmp.second;
        arr.back().second *= p_tmp.second;
        p_tmp.first *= arr_tmp;
        p_tmp.second *= arr_tmp;
        if(*itr){
            arr.back().first += p_tmp.first;
        }else{
            arr.back().first -= p_tmp.first;
        }
    }
}

void print_solution(){
    // print final result
    int arr_gcd = __gcd(arr.back().first,arr.back().second);
    arr.back().first /= arr_gcd;
    arr.back().second /= arr_gcd;
    if(arr.back().second<0){
        arr.back().first *= -1;
        arr.back().second *= -1;
    }
    cout<<arr.back().first;
    if(arr.back().second!=1){
        cout<<'/'<<arr.back().second;
    }
    cout<<'\n';
}

void start(){
    make_variables();
    take_input();
    if(user_input == "exit"){
        cout<<"Thank you for using rational number calculator.\n";
        return;
    }
    if(!is_valid()){
        cout<<"Invalid operation. Try again!\n";
        start();
        return;
    }
    solve();
    print_solution();
    start();
}


int main() {
    start();
}