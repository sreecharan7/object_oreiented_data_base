#include<iostream>
#include"classes.cpp"
using namespace std;

//print vector
template<class T>
void printVector(vector<T> v){
    for(int i=0;i<v.size();i++){
        v[i].print();
    }
    cout<<"\u001b[0m";
}

template<class T,class X>
void getData(T &t,vector<string> v){
    if(v.size()==2){
        vector<X> temp=t.getData();
        t.printDetails();
        printVector(temp);
    }
    else if(v[2]=="by"){
        if(v[3]=="country"){
            vector<X> temp=t.getData(v[4]);
            t.printDetails();
            printVector(temp);
        }
        else if(v[3]=="name"){
            vector<X> temp=t.getData(v[4],0.0);
            t.printDetails();
            printVector(temp);
        }
        else if(v[3]=="range"||v[3]=="damage"){
            vector<X> temp;
            t.printDetails();
            char c=v[4][0];
            if(v.size()>5)temp=t.getData(v[6],stoi(v[4].substr(1,v[4].size())));
            else temp=t.getData(stoi(v[4]));
            printVector(temp);
        }

    }
}

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
    missileList ml;
    tankList tl;


    //infinte loop print > take string input > if input is "exit" break
    while(1){
        string input;
        cout<<"moodm>";
        //take lin as input
        getline(cin,input);
        if(input=="exit"){
            break;
        }
        else if(input=="add missile"){
            string name;
            int damage,range,type,Payload;
            double speed,accuracy;
            string coo;
            cout<<"Enter name: ";
            getline(cin,name);
            cout<<"Enter damage: ";
            cin>>damage;
            cout<<"Enter range: ";
            cin>>range;
            cout<<"Enter type: ";
            cin>>type;
            cout<<"Enter speed: ";
            cin>>speed;
            cout<<"Enter Payload: ";
            cin>>Payload;
            cout<<"Enter accuracy: ";
            cin>>accuracy;
            cout<<"Enter country of origin: ";
            cin>>coo;
            ml.addMissile(name,damage,range,type,speed,Payload,accuracy,coo);
        }
        else if(input=="add tank"){
            string name;
            int damage,health,range,Payload;
            double speed;
            string coo;
            cout<<"Enter name: ";
            cin>>name;
            cout<<"Enter damage: ";
            cin>>damage;
            cout<<"Enter health: ";
            cin>>health;
            cout<<"Enter range: ";
            cin>>range;
            cout<<"Enter speed: ";
            cin>>speed;
            cout<<"Enter Payload: ";
            cin>>Payload;
            cout<<"Enter country of origin: ";
            cin>>coo;
            tl.addTank(name,damage,health,range,speed,Payload,coo);
        }
        //split the input by space and store
        vector<string> v=split(input);


        if(v[0]=="get"){
            if(v[1]=="tank"){
                getData<tankList,tank>(tl,v);
            }
            else if(v[1]=="missile"){
                getData<missileList,missile>(ml,v);
            }
        }

    }

    return 0;
}