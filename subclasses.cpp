#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm> 


class dynamicClass{
    static int _id;
    std::map<std::string, int> variables;
    std::map<std::string, std::string> variables2;
    //check the name exist in the variable or not
    bool checkVariableName(const std::string& name) {
        return variables.find(name) != variables.end()||variables2.find(name) != variables2.end();
    }
    public:
    void setVariable(const std::string& name, int value) {
        if (checkVariableName(name)) {
            std::cerr << "Variable '" << name << "' already exists." << std::endl;
            return;
        }
        variables[name] = value;
    }
    void setVariable2(const std::string& name, std::string value) {
        if (checkVariableName(name)) {
            std::cerr << "Variable '" << name << "' already exists." << std::endl;
            return;
        }
        variables2[name] = value;
    }
    int getVariable(const std::string& name) const {
    if (variables.find(name) != variables.end()) {
        return variables.at(name);
    } else {
        // std::cerr << "Variable '" << name << "' not found." << std::endl;
        return 0;
    }
}
  std::string getVariable2(const std::string& name) const {
    if (variables2.find(name) != variables2.end()) {
        return variables2.at(name);
    } else {
        // std::cerr << "Variable '" << name << "' not found." << std::endl;
        return "";
    }
}
    bool hasVariable1(const std::string& name)const {
        return variables.find(name) != variables.end();
    }
    bool hasVariable2(const std::string& name) const {
        return variables2.find(name) != variables2.end();
    }
    void print(std::vector<std::string> variableNames){
        for(int i=0;i<variableNames.size();i++){
            if(variables.find(variableNames[i])!=variables.end()){
                std::cout<<variables[variableNames[i]]<<"\t";
            }
            else if(variables2.find(variableNames[i])!=variables2.end()){
                std::cout<<variables2[variableNames[i]]<<"\t";
            }
            else{
                std::cerr<<"Variable "<<variableNames[i]<<" not found"<<std::endl;
                return;
            }
        }
        std::cout << std::endl;
    }
    void printDetails(){
        for (auto const& x : variables2){std::cout << x.first<<"\t";}
        for (auto const& x : variables){std::cout << x.first<< "\t";}
        std::cout << std::endl;
    }
    void printTotal(){
        std::cout <<"\u001b[33m{\u001b[0m"<<std::endl;
        for (auto const& x : variables2){std::cout <<"\u001b[33m\t"<< x.first<<"\u001b[0m : \u001b[34m"<<x.second<<"\u001b[0m\n";}
        for (auto const& x : variables){std::cout <<"\u001b[33m\t"<< x.first<<"\u001b[0m : \u001b[34m"<<x.second<<"\u001b[0m\n";}
        std::cout <<"\u001b[33m},\u001b[0m"<<std::endl;
        std::cout << std::endl;
    }
    void update(std::map<std::string,std::string> values){
        for (auto const& x : values){
            if(variables2.find(x.first)!=variables2.end()){
                variables2[x.first]=x.second;
            }
            else if(variables.find(x.first)!=variables.end()){
                variables[x.first]=stoi(x.second);
            }
            else{
                std::cerr<<"Variable "<<x.first<<" not found"<<std::endl;
                return;
            }
        }
    }

    dynamicClass(){
        setVariable("id",_id++);
    }
    //gives the vector of string name of vbariables of string and valuse and same for int also
    dynamicClass(std::vector<std::string> names,std::vector<std::string> values,std::vector<int> values2){
        setVariable("id",_id++);
        if(names.size()!=values.size()+values2.size()){
            std::cerr<<"Given insuffiecnt values"<<std::endl;
            return;
        }
        for(int i=0;i<values.size();i++){
            setVariable2(names[i],values[i]);
        }
        for(int i=0;i<values2.size();i++){
            setVariable(names[i+values.size()],values2[i]);
        }
    }
    //gives the map of string name of vbariables of string and valuse and same for int also
    dynamicClass(std::vector<std::string> names,std::vector<std::string> values){
        setVariable("id",_id++);
        if(names.size()!=values.size()){
            std::cerr<<"Given insuffiecnt values"<<std::endl;
            return;
        }
        for(int i=0;i<values.size();i++){
            if(all_of(values[i].begin(), values[i].end(), ::isdigit)){
                setVariable(names[i],stoi(values[i]));
            }else{
                setVariable2(names[i],values[i]);
            }
        }
     }
};
int dynamicClass::_id = 0;