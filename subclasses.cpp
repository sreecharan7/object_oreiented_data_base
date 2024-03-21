#include <vector>
#include <string>
#include <iostream>

class missile{
    static int _id;
    int id;
    std::string name;
    int damage;
    int range;
    int type;
    double speed;
    int Payload;
    double accuracy;
    std::string coo;//country of origin

    public:
    missile(){
        id=_id++;
        name="default";
        damage=0;
        range=0;
        type=0;
        speed=0;
        Payload=0;
        accuracy=0;
        coo="default";
    }
    missile(std::string name,int damage,int range,int type
        ,double speed,int Payload,double accuracy,std::string coo){
        id=_id++;
        this->name=name;
        this->damage=damage;
        this->range=range;
        this->type=type;
        this->speed=speed;
        this->Payload=Payload;
        this->accuracy=accuracy;
        this->coo=coo;
    }
    void print(){
        //just print the missile contions manner with tab
        std::cout<<name<<"\t"<<damage<<"\t"<<range<<"\t"<<type<<"\t"<<speed<<"\t"<<Payload<<"\t"<<accuracy<<"\t"<<coo<<std::endl;
    }
    friend class missileList;
};
int missile::_id = 0;


// class for tanks
class tank{
    static int _id;
    int id;
    std::string name;
    int damage;
    int health;
    int range;
    double speed;
    int Payload;
    std::string coo;//country of origin

    public:
    tank(){
        id=_id++;
        name="default";
        damage=0;
        range=0;
        speed=0;
        health=0;
        Payload=0;
        coo="default";
    }
    tank(std::string name,int damage,int health,int range
        ,double speed,int Payload,std::string coo){
        id=_id++;
        this->name=name;
        this->damage=damage;
        this->range=range;
        this->health=health;
        this->speed=speed;
        this->Payload=Payload;
        this->coo=coo;
    }
    void print(){
        //just print the tank contions manner with tab
        std::cout<<name<<"\t"<<damage<<"\t"<<health<<"\t"<<range<<"\t"<<speed<<"\t"<<Payload<<"\t"<<coo<<std::endl;
    }
    friend class tankList;
};
int tank::_id = 0;