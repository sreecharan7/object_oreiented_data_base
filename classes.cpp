#include"subclasses.cpp"
#include<iostream>


//contain the class missile of vector<missile>
class missileList{
    std::vector<missile> missiles;
    public:
    missileList(){
        missiles.push_back(missile("R-73",8,30,1,2.5,22,0.9,"Russia"));
        missiles.push_back(missile("AIM-9X",9,35,1,2.5,22,0.9,"USA"));
        missiles.push_back(missile("Meteor",10,50,1,4,22,0.9,"UK"));
        missiles.push_back(missile("Astra",8,30,1,2.5,22,0.9,"India"));
        missiles.push_back(missile("PL-12",8,30,1,2.5,22,0.9,"China"));
    }
    void printDetails(){
        std::cout<<"\u001b[33mName\tDamage\tRange\tType\tSpeed\tPayload\t Accuracy Country\u001b[34m"<<std::endl;
    }
    //passes the arguments and creates a missile object and adds it to the vector
    void addMissile(std::string name,int damage,int range,int type
        ,double speed,int Payload,double accuracy,std::string coo){
        missiles.push_back(missile(name,damage,range,type,speed,Payload,accuracy,coo));
    }
    //return all
    std::vector<missile> getData(){
        return missiles;
    }
    //get missiles by country
    std::vector<missile> getData(std::string coo){
        std::vector<missile> temp;
        for(int i=0;i<missiles.size();i++){
            if(missiles[i].coo==coo){
                temp.push_back(missiles[i]);
            }
        }
        return temp;
    }
    //get missiles range >n and belongs to that country
    std::vector<missile> getData(std::string coo,int range){
        std::vector<missile> temp;
        for(int i=0;i<missiles.size();i++){
            if(missiles[i].coo==coo && missiles[i].range>range){
                temp.push_back(missiles[i]);
            }
        }
        return temp;
    }
    //get missile by range
        std::vector<missile> getData(int range){
        std::vector<missile> temp;
        for(int i=0;i<missiles.size();i++){
            if(missiles[i].range>range){
                temp.push_back(missiles[i]);
            }
        }
        return temp;
    }
    //get missile by name
    std::vector<missile> getData(std::string name,double temp2){
        std::vector<missile> temp;
        for(int i=0;i<missiles.size();i++){
            if(missiles[i].name==name){
                temp.push_back(missiles[i]);
            }
        }
        return temp;
    }

};
//contain the class tank of vector<tank>
class tankList{
    std::vector<tank> tanks;
    public:
    tankList(){
        tanks.push_back(tank("T-90",10,100,50,2.5,22,"Russia"));
        tanks.push_back(tank("M1A2",10,100,50,2.5,22,"USA"));
        tanks.push_back(tank("Challenger 2",4,100,50,2.5,22,"UK"));
        tanks.push_back(tank("Arjun",10,100,50,2.5,22,"India"));
        tanks.push_back(tank("Type 99",10,100,50,2.5,22,"China"));
    }
    void printDetails(){
        std::cout<<"\u001b[33mName\tDamage\tHealth\tRange\tSpeed\tPayload\tCountry\u001b[34m"<<std::endl;
    }
    //passes the arguments and creates a tank object and adds it to the vector
    void addTank(std::string name,int damage,int health,int range
        ,double speed,int Payload,std::string coo){
        tanks.push_back(tank(name,damage,health,range,speed,Payload,coo));
    }
    //return all
    std::vector<tank> getData(){
        return tanks;
    }
    //get tanks by country
    std::vector<tank> getData(std::string coo){
        std::vector<tank> temp;
        for(int i=0;i<tanks.size();i++){
            if(tanks[i].coo==coo){
                temp.push_back(tanks[i]);
            }
        }
        return temp;
    }
    //get tanks health >n and belongs to that country
    std::vector<tank> getData(std::string coo,int health){
        std::vector<tank> temp;
        for(int i=0;i<tanks.size();i++){
            if(tanks[i].coo==coo && tanks[i].health>health){
                temp.push_back(tanks[i]);
            }
        }
        return temp;
    }
    //get tank by damage
        std::vector<tank> getData(int damage){
        std::vector<tank> temp;
        for(int i=0;i<tanks.size();i++){
            if(tanks[i].damage>damage){
                temp.push_back(tanks[i]);
            }
        }
        return temp;
    }
    //get tank by name
    std::vector<tank> getData(std::string name,double temp2){
        std::vector<tank> temp;
        for(int i=0;i<tanks.size();i++){
            if(tanks[i].name==name){
                temp.push_back(tanks[i]);
            }
        }
        return temp;
    }
};