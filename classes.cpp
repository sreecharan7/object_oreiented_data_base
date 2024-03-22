#include"subclasses.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm> 

using namespace std;
//print vector
template<class T>
void printVector(vector<T> v,vector<string> variableNames){
    //add id in variableNames front
    variableNames.insert(variableNames.begin(),"id");
    if(v.empty()){
        cout<<"\u001b[31mNo data found\u001b[0m\n";
        return;
    }
    for(int i=0;i<v.size();i++){
        v[i].print(variableNames);
    }
    cout<<"\u001b[0m";
}


class dynamicClassVector{
    std::map<std::string, std::string> variables;
    std::vector<std::string> variableNames;
    std::vector<dynamicClass> vec;
    public:
    dynamicClassVector(std::vector<string> name,std::vector<string> type){
        if(name.size()!=type.size()){
            std::cerr<<"Name and type size not equal"<<std::endl;
            return;
        }
        for(int i=0;i<name.size();i++){
            variables[name[i]] = type[i];
        }
        //take key and store in variableNames
        for (auto const& x : variables){variableNames.push_back(x.first);}
    }
    void addClass( std::map<std::string, std::string> v){
        vector<string> temp1;
        vector<int> temp2;
        vector<string> temp3;
        vector<string> temp4;
        for(int i=0;i<variableNames.size();i++){
            if(v.find(variableNames[i])==v.end()){
                std::cerr<<"Variable "<<variableNames[i]<<" not found"<<std::endl;
                return;
            }
            if(variables[variableNames[i]]=="int"){
                if(!all_of(v[variableNames[i]].begin(), v[variableNames[i]].end(), ::isdigit)){
                    std::cerr<<"\u001b[31mInvalid input for "<<variableNames[i]<<" it shoulb be integer\u001b[0m"<<std::endl;
                    return;
                }
                temp2.push_back(stoi(v[variableNames[i]]));
                temp4.push_back(variableNames[i]);
            }
            else if(variables[variableNames[i]]=="string"){
                temp1.push_back(v[variableNames[i]]);
                temp3.push_back(variableNames[i]);
            }
        }
        //add temp4 and temp3 and store in temp3
        for(int i=0;i<temp4.size();i++){
            temp3.push_back(temp4[i]);
        }
        vec.push_back(dynamicClass(temp3,temp1,temp2));
    }
    vector<dynamicClass> getdata(){
        return vec;
    }
    vector<dynamicClass> getdata(string name,string value,char op='='){
        vector<dynamicClass> temp;
        //check the name exist as variable name or not
        if(variables.find(name)==variables.end()&&name!="id"){
            std::cerr<<"Variable "<<name<<" not found"<<std::endl;
            return temp;
        }
        //check the name is int or string

        if(variables[name]=="int"&&all_of(value.begin(), value.end(), ::isdigit)){
            int num=stoi(value);
            for(int i=0;i<vec.size();i++){
                switch(op){
                    case '=':
                        if(vec[i].getVariable(name)==num){
                            temp.push_back(vec[i]);
                        }
                        break;
                    case '>':
                        if(vec[i].getVariable(name)>num){
                            temp.push_back(vec[i]);
                        }
                        break;
                    case '<':
                        if(vec[i].getVariable(name)<num){
                            temp.push_back(vec[i]);
                        }
                        break;
                    case '!':
                        if(vec[i].getVariable(name)!=num){
                            temp.push_back(vec[i]);
                        }
                        break;
                    default:
                        std::cerr<<"Invalid operator"<<std::endl;
                        return temp;
                }
            }
        }else{
            for(int i=0;i<vec.size();i++){
                switch(op){
                    case '=':
                        if(vec[i].getVariable2(name)==value){
                            temp.push_back(vec[i]);
                        }
                        break;
                    case '!':
                        if(vec[i].getVariable2(name)!=value){
                            temp.push_back(vec[i]);
                        }
                        break;
                    default:
                        std::cerr<<"Invalid operator"<<std::endl;
                        return temp;
                }
            }
        }
        return temp;
    }
    //delete the vector of dynamic class
    // int deleteObjects(vector<dynamicClass> temp){
    //     int count=0;
    //     for(int i=0;i<temp.size();i++){
    //         for(int j=0;j<vec.size();j++){
    //             if(temp[i].id==vec[j].id){
    //                 vec.erase(vec.begin()+j);
    //                 count++;
    //                 break;
    //             }
    //         }
    //     }
    //     return count;
    // }
    void printDetails(){
        cout<<"\u001b[33mid\t";
        for(int i=0;i<variableNames.size();i++){
            cout<<variableNames[i]<<"\t";
        }
        cout<<"\u001b[36m"<<endl;
    }
    friend class database;
};






class database{
    map<string, dynamicClassVector*> classes;
    void addClass(string name, dynamicClassVector *d){
        classes[name] =d;
    }
    bool checkClass(string name){
        return classes.find(name) != classes.end();
    }
    public:
    void createClass(string name){
        if(checkClass(name)){
            cout<<"\u001b[31mClass already exist\u001b[0m\n";
            return;
        }
        vector<string> temp;
        vector<string> temp2;
        cout<<"\u001b[31m/stop in variable name to stop ,  variable type is int or string\n\u001b[0m";
        while(1){
            cout<<"\u001b[36mEnter the varable name :\u001b[0m";
            string vname;
            getline(cin,vname);
            if(vname=="/stop"){
                if(temp.empty()){
                    cout<<"\u001b[31mNo variable found, try again\u001b[0m\n";
                    break;
                }
                dynamicClassVector *d=new dynamicClassVector(temp,temp2);
                addClass(name,d);
                break;
            }
            cout<<"\u001b[36mEnter the type of variable :\u001b[0m";
            string vtype;
            getline(cin,vtype);
            //check string is 3emprty vname or not
            if((vtype=="int"||vtype=="string")&&!vname.empty()){temp.push_back(vname);temp2.push_back(vtype);}
            else{cout<<"\u001b[31mInvalid type try again or string is empty\u001b[0m\n";}
        }     
    }
    void createClass(string name,vector<string> temp,vector<string> temp2){
        if(checkClass(name)){
            cout<<"\u001b[31mClass not found\u001b[0m\n";
            return;
        }
        dynamicClassVector *d=new dynamicClassVector(temp,temp2);
        addClass(name,d);
    }
    void addObject(string name){
        if(!checkClass(name)){
            cout<<"\u001b[31mClass not found\u001b[0m\n";
            return;
        }
        dynamicClassVector *d=classes[name];
        map<string, string> v;
        for(int i=0;i<d->variableNames.size();i++){
            cout<<"\u001b[36mEnter the value of "<<d->variableNames[i]<<" ("<<d->variables[d->variableNames[i]]<<") :\u001b[0m";
            string temp;
            getline(cin,temp);
            v[d->variableNames[i]] = temp;
        }
        d->addClass(v);
    }
    void addObject(string name,map<string, string> v){
        if(!checkClass(name)){
            cout<<"\u001b[31mClass not found\u001b[0m\n";
            return;
        }
        dynamicClassVector *d=classes[name];
        d->addClass(v);
    }

    void getData(vector<string> v){
        if(v.size()==2){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata();
            d->printDetails();
            printVector(temp,d->variableNames);
        }
        else if(v.size()==6&&v[2]=="by"){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata(v[3],v[5],v[4][0]);
            d->printDetails();
            printVector(temp,d->variableNames);
        }
        else{
            cout<<"\u001b[31mInvalid input\u001b[0m\n";
        }
    }

};