#include<iostream>
#include"classes.cpp"
using namespace std;


void sampleData(database &d);

//extract the space separated string and store in vector
vector<string> split(string s){
    vector<string> v;
    string temp="";
    for(int i=0;i<s.size();i++){
        if(s[i]==' '||s[i]=='\n'||s[i]=='\t'){
            if(temp!=""){
                v.push_back(temp);
            }
            temp="";
        }
        else{
            temp+=s[i];
        }
    }
    v.push_back(temp);
    return v;
}


int main(){
    database d;
    sampleData(d);

    //infinte loop print > take string input > if input is "exit" break
    while(1){
        string input;
        cout<<"moodm>";
        //take lin as input
        getline(cin,input);
        if(input=="exit"){
            break;
        }
        vector<string> v=split(input);
        if(v[0]=="create"){
            d.createClass(v[1]); 
        }
        else if(v[0]=="add"){
            d.addObject(v[1]);
        }
        else if(v[0]=="list"){
            d.getData(v);
        }
        else{
            cout<<"\u001b[31mInvalid command\u001b[0m\n";
        }
    }

    return 0;
}


void sampleData(database &d){
    //create vector of string tank data
    vector<string> temp;
    temp.push_back("string");
    temp.push_back("int");
    temp.push_back("int");
    temp.push_back("int");
    temp.push_back("string");
    vector<string> temp2;
    temp2.push_back("name");
    temp2.push_back("damage");
    temp2.push_back("health");
    temp2.push_back("speed");
    temp2.push_back("country");
    d.createClass("tank",temp2,temp);
    //create vector of string tank data object
    map<string, string> v;
    v["name"]="tiger";
    v["damage"]="100";
    v["health"]="1000";
    v["speed"]="50";
    v["country"]="germany";
    d.addObject("tank",v);
    v["name"]="panther";
    v["damage"]="80";
    v["health"]="800";
    v["speed"]="60";
    v["country"]="germany";
    d.addObject("tank",v);
    v["name"]="sherman";
    v["damage"]="50";
    v["health"]="500";
    v["speed"]="70";
    v["country"]="usa";
    d.addObject("tank",v);

    //add data of missile with country of origin
    temp.clear();
    temp.push_back("string");
    temp.push_back("int");
    temp.push_back("int");
    temp.push_back("string");
    temp2.clear();
    temp2.push_back("name");
    temp2.push_back("damage");
    temp2.push_back("speed");
    temp2.push_back("country");
    d.createClass("missile",temp2,temp);
    v.clear();
    v["name"]="scud";
    v["damage"]="100";
    v["speed"]="1000";
    v["country"]="russia";
    d.addObject("missile",v);
    v["name"]="patriot";
    v["damage"]="80";
    v["speed"]="800";
    v["country"]="usa";
    d.addObject("missile",v);
    v["name"]="brahmos";
    v["damage"]="50";
    v["speed"]="500";
    v["country"]="india";
    d.addObject("missile",v);
}