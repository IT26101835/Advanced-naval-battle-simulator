#include <stdlib.h>
#include <math.h>

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
float GetAngleRange(char type){ //getting angle range from the type of escort ship
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
float GetMinimumAngle(){ //getting minimum angle randomly
    return rand() % 46;
}
float GetMinimumVelocity(int maxVelocity){ //get minimum velocity 
    return rand() % maxVelocity;
}
float GetMaximumVelocity(char type, int battleshipMaxVelocity){ //getting maximum velocity from the type of the escort ship and max velocity of battleship
    if (type == 'A')
    {
        return 1.2 * battleshipMaxVelocity;
    }
    else
    {
        return rand() % battleshipMaxVelocity;
    }
}
float GetImpactPower(char type){  //impact power get from type of escort ship
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
float CalculateDistance(int x1, int y1, int x2, int y2){  //calculate the distance between 2 ships
    return sqrt((x2 - x1)*(x2 - x1)+(y2 - y1)*(y2 - y1));
}
float CalculateBattleshipMaxRange(float maxVelocity){  // Calculate the maximum attack range of the battleship
    float g = 9.81;
    return (maxVelocity * maxVelocity) / g;
}
int CanBattleshipHit(float distance, float maxAttackRange){ // Check if the battleship can hit an escort ship
    if (distance <= maxAttackRange)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
float GetBestAngle(float minAngle, float maxAngle){ // Select the best firing angle for the escort ship
    if (minAngle <= 45.0 && maxAngle >= 45.0)
    {
        return 45.0;
    }
    else if (maxAngle < 45.0)
    {
        return maxAngle;
    }
    else
    {
        return minAngle;
    }
}
float CalculateEscortMaxRange(float maxVelocity, float bestAngle){ // Calculate the maximum attack range of the escort ship
    float g = 9.81;
    float angleInRadians = bestAngle * 3.14159 / 180.0;

    return (maxVelocity * maxVelocity * sin(2 * angleInRadians)) / g;
}
int CanEscortHitBattleship(float distance, float maxAttackRange){ // Check if any escort ship can hit the battleship
    if (distance <= maxAttackRange)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
float CalculateFiringAngle(float distance, float maxVelocity){ // Calculate the firing angle needed to hit the target

    float g = 9.81;
    float value;
    float angleRadians;
    float angleDegrees;

    value = (distance * g) / (maxVelocity * maxVelocity);

    angleRadians = 0.5 * asin(value);

    angleDegrees = angleRadians * 180.0 / 3.14159;

    return angleDegrees;
}
float CalculateTimeToHit(float distance, float velocity, float angle){ // Calculate the time taken for hit to the target
    float angleRadians;

    angleRadians = angle * 3.14159 / 180.0;

    return distance / (velocity * cos(angleRadians));
}