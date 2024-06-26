#include<iostream>
#include"classes.cpp"
using namespace std;


void sampleData(database &d);
void nosql(database2 &d,char delimeter);

//extract the space separated string and store in vector
vector<string> split(string s,char d=' '){
    vector<string> v;
    string temp="";
    for(int i=0;i<s.size();i++){
        if(s[i]==d||s[i]=='\n'||s[i]=='\t'){
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
    database2 nd;
    sampleData(d);

    char delimeter=' ';
    //infinte loop print > take string input > if input is "exit" break
    while(1){
        string input;
        cout<<"moodm>";
        //take lin as input
        getline(cin,input);
        if(input=="exit"){
            break;
        }
        vector<string> v=split(input,delimeter);
        try{
        if(v[0]=="create"){
            d.createClass(v[1]); 
        }
        else if(v[0]=="add"){
            d.addObject(v[1]);
        }
        else if(v[0]=="list"){
            d.getData(v);
        }
        else if(v[0]=="delete"){
            d.deleteData(v);
        }
        else if(v[0]=="update"){
            d.updateData(v);
        }
        else if(v[0]=="delimeter"){
            if(v.size()==3&&v[1]=="="){
                delimeter=v[2][0];
            }
            else{
                delimeter=' ';
            }
        }
        else if(v[0]=="nosql"){
            nosql(nd,delimeter);
        }

         else if (v[0] == "save") {
                if (v.size() > 0) {
                    d.saveData(v[1]);
                } else {
                    cout << "\u001b[31mInvalid input. Usage: save <filename>\u001b[0m\n";
                }
            }
             else if (v[0] == "load") {
                if (v.size() > 0) {
                    d.loadData(v[1]);
                } else {
                    cout << "\u001b[31mInvalid input. Usage: load <filename>\u001b[0m\n";
                }
            }
        else{
            cout<<"\u001b[31mInvalid command\u001b[0m\n";
        }
        }
        catch(const char* msg){
            cout<<"error happened"<<endl;
        }
    }

    return 0;
}

void nosql(database2 &d,char delimeter){
    string current="nosql";
    string input;
    while(1){
        cout<<current<<">";
        getline(cin,input);
        if(input=="exit"){
            break;
        }
        vector<string> v=split(input,delimeter);
        try{
            if(v[0]=="create"){
                d.addCollection(v);
            }
            else if(v[0]=="add"){
                d.addObject(v);
            }
            else if(v[0]=="list"){
                d.listData(v);
            }
            else{
                cout<<"\u001b[31mInvalid command\u001b[0m\n";
            }
        }catch(const char* msg){
            cout<<"error happened"<<endl;
        }
    }
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