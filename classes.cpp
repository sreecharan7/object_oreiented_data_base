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
    //chck the vector of variableNames is valid or not
    bool checkVariableNames(vector<string> v){
        for(int i=0;i<v.size();i++){
            if(variables.find(v[i])==variables.end()){
                std::cerr<<"Variable "<<v[i]<<" not found"<<std::endl;
                return false;
            }
        }
        return true;
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
        if(variables[name]=="int"&&all_of(value.begin(), value.end(), ::isdigit)||name=="id"){
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
    int deleteObjects(vector<dynamicClass> temp){
        int count=0;
        for(int i=0;i<temp.size();i++){
            for(int j=0;j<vec.size();j++){
                if(temp[i].getVariable("id")==vec[j].getVariable("id")){
                    // delete &vec[j];
                    vec.erase(vec.begin()+j);
                    count++;
                    break;
                }
            }
        }
        return count;
    }
    //update the vector of dynamic class
    int updateObjects(vector<dynamicClass> temp,map<string, string> v){
        int count=0;
        //check map variable is valid or not
        for (auto const& x : v){
            if(variables.find(x.first)==variables.end()){
                std::cerr<<"Variable "<<x.first<<" not found"<<std::endl;
                return count;
            }
            if(variables[x.first]=="int"&&all_of(x.second.begin(), x.second.end(), ::isdigit)){
                continue;
            }
            else if(variables[x.first]=="string"){
                continue;
            }
            else{
                std::cerr<<"Invalid input for "<<x.first<<std::endl;
                return count;
            }
        }
        for(int i=0;i<temp.size();i++){
            for(int j=0;j<vec.size();j++){
                if(temp[i].getVariable("id")==vec[j].getVariable("id")){
                    vec[j].update(v);
                    count++;
                    break;
                }
            }
        }
        return count;
    }
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
    map<string,string> extractData(vector<string> v, int s){
            map<string, string> temp2;
            //untill it found , it will go to next element a = sree , b = sree
            string str1="",str2="";
            for(int i=s;i<v.size();i++){
                if(v[i]=="="){
                    str2=str1;
                    str1="";
                }
                else if(v[i]==","){
                    temp2[str2]=str1;
                    str1="";
                    str2="";
                }
                else{
                    str1+=v[i];
                }
            }
            if(str1!=""){
                temp2[str2]=str1;
            }
            return temp2;
    }
    vector<string> extractData2(vector<string> v, int s){
        vector<string> temp2;
        //untill it found , it will go to next element a  , b
        string str1="";
        for(int i=s;i<v.size();i++){
            if(v[i]==","){
                temp2.push_back(str1);
                str1="";
            }
            else{
                if(str1!=""){str1+=" ";}
                str1+=v[i];
            }
        }
        if(str1!=""){
            temp2.push_back(str1);
        }
        return temp2;
    }
    void printWithVaraiblesNames(vector<dynamicClass> temp,vector<string> temp2,dynamicClassVector *d){
        if(!d->checkVariableNames(temp2)){
            cout<<"\u001b[31mInvalid variable name\u001b[0m\n";
        }
        else{
            //print temp2
            cout<<"\u001b[33mid\t";
            for(int i=0;i<temp2.size();i++){
                cout<<temp2[i]<<"\t";
            }
            cout<<"\u001b[36m"<<endl;
            printVector(temp,temp2);
        }
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
            if(vname=="id"&&!vname.empty()){cout<<"\u001b[31mInvalid variable name or vname is empty\u001b[0m\n";}
            else if(vtype=="int"||vtype=="string"){temp.push_back(vname);temp2.push_back(vtype);}
            else{cout<<"\u001b[31mInvalid type try again\u001b[0m\n";}
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
        if(v.size()==2||(v.size()>=3&&v[2]=="all")){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata();
            if(v.size()>3&&v[3]=="with"){
                vector<string> temp2=extractData2(v,4);
                printWithVaraiblesNames(temp,temp2,d);
            }else{
                d->printDetails();
                printVector(temp,d->variableNames);
            }
        }
        else if(v.size()>=6&&v[2]=="by"){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata(v[3],v[5],v[4][0]);
            if(v.size()>6&&v[6]=="with"){
                vector<string> temp2=extractData2(v,7);
                printWithVaraiblesNames(temp,temp2,d);
            }else{
                d->printDetails();
                printVector(temp,d->variableNames);
            }
        }
        else{
            cout<<"\u001b[31mInvalid input\u001b[0m\n";
        }
    }

    void deleteData(vector<string> v){
        if(v.size()==2){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata();
            int count=d->deleteObjects(temp);
            cout<<"\u001b[32m"<<count<<" objects deleted\u001b[0m\n";
        }
        else if(v.size()==6&&v[2]=="by"){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata(v[3],v[5],v[4][0]);
            int count=d->deleteObjects(temp);
            cout<<"\u001b[32m"<<count<<" objects deleted\u001b[0m\n";
        }
        else{
            cout<<"\u001b[31mInvalid input\u001b[0m\n";
        }
    }
    void updateData(vector<string> v){
        if(v.size()>3&&v[2]=="all"){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata();
            map<string, string> temp2=extractData(v,4);
            int count=d->updateObjects(temp,temp2);
            cout<<"\u001b[32m"<<count<<" objects updated\u001b[0m\n";
        }
        else if(v.size()>4&&v[2]=="by"){
            if(!checkClass(v[1])){
                cout<<"\u001b[31mClass not found\u001b[0m\n";
                return;
            }
            dynamicClassVector *d=classes[v[1]];
            vector<dynamicClass> temp=d->getdata(v[3],v[5],v[4][0]);
            map<string, string> temp2=extractData(v,7);
            int count=d->updateObjects(temp,temp2);
            cout<<"\u001b[32m"<<count<<" objects updated\u001b[0m\n";
        }
        else{
            cout<<"\u001b[31mInvalid input\u001b[0m\n";
        }
    }
};