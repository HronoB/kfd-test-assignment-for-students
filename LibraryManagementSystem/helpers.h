

#include <vector>
#include <string>

using namespace std;



template<typename T>
void printi(T &&data){
    cout << "{";
    for (auto i : data){
        cout << i << ", ";
    }
    cout << "}" << endl;
}

vector<string> parse(string &ip){
    ip.push_back(' ');
    vector<string> res;

    res.push_back("");
    for (int i = 0; i < ip.size(); i++){
        if (ip[i]==' '){
            if (res.back().empty()){
                res.pop_back();
            }
            res.push_back("");
        } else {
            res.back().push_back(ip[i]);
        }
    }

    if (res.back().empty()){
        res.pop_back();
    }

    return res;

}


struct command{
    string comm;
    int minParamsCount;
    int maxParamsCount;
    string desc;
    int id;

    pair<int, string> checkCommand(vector<string> &params){
        if (comm.find(params[0])!=0){
            return {-1, ""};
        }
        if (!isValidParam(params)) {
            throw runtime_error("Wrong params number for: " + desc);
        }
        return {id, ""};
    }
    bool isValidParam(vector<string> &params){
        if (params.size()-1 >= minParamsCount && params.size()-1 <= maxParamsCount){
            return true;
        }
        return false;
    }
};
























