#include <stdlib.h>

int GenerateRandomCoordinate(int d){ // generate random coordinate function 
    return rand() % (d+1);
};

char GenerateRandomEscortType(){ // generate random type function
    int randomtype = rand() % 5; 

    if (randomtype == 0){
        return 'A'; // return value
    }
    else if (randomtype == 1){
        return 'B';
    }
    else if (randomtype == 2){
        return 'C';
    }
    else if (randomtype == 3){
        return 'D';
    }
    else{
        return 'E';
    }
}
float GetAngleRange(char type){
    if (type == 'A')
    {
        return 20.0;
    }
    else if (type == 'B')
    {
        return 30.0;
    }
    else if (type == 'C')
    {
        return 25.0;
    }
    else if (type == 'D')
    {
        return 50.0;
    }
    else
    {
        return 70.0;
    }
}
float GetMinimumAngle(){
    return rand() % 46;
}
float GetMinimumVelocity(int maxVelocity){
    return rand() % maxVelocity;
}
float GetMaximumVelocity(char type, int battleshipMaxVelocity){
    if (type == 'A')
    {
        return 1.2 * battleshipMaxVelocity;
    }
    else
    {
        return rand() % battleshipMaxVelocity;
    }
}
float GetImpactPower(char type){
    if (type == 'A')
    {
        return 0.08;
    }
    else if (type == 'B')
    {
        return 0.06;
    }
    else if (type == 'C')
    {
        return 0.07;
    }
    else if (type == 'D')
    {
        return 0.05;
    }
    else
    {
        return 0.04;
    }
}
