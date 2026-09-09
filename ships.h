 #ifndef SHIPS_H
#define SHIPS_H
 
 typedef struct {  // Structure to store Battleship details
        char type;
        int x,y;
        float maxVelocity;
        float maxAttackRange;
        
        float firingDelay;
        float nextFireTime;
//use for 2-c
        float gamma;
        int fireCount;
        float currentImpactPower;
    }BattleShip;

    typedef struct { // Structure to store Escort Ship details
        int index;
        char type;
        int x,y;
        float angleRange;
        float minAngle;
        float maxAngle; 
        float minVelocity;
        float maxVelocity;
        float impactPower;
        float distanceFromB;
        int canBeHitByB;
        float bestAngle;
        float maxAttackRange;
        int canHitB;
        float firingAngleFromB;
        float timeToHitFromB;

        int isAlive; // Stores whether the escort ship is still active
        int hasFired; //check weather already attack battleship or not

        float nextFireTime;
//use for 2-c
        float gamma;
        int fireCount;
        float currentImpactPower;
        float damageReceived;

    }EscortShip;

           // Functions for generating random Escort Ship properties
    int GenerateRandomCoordinate(int d);
    char GenerateRandomEscortType();
    float GetAngleRange(char type);
    float GetMinimumAngle();
    float GetMinimumVelocity(int maxVelocity);
    float GetMaximumVelocity(char type, int battleshipMaxVelocity);
    float GetImpactPower(char type);
    float GetBestAngle(float minAngle, float maxAngle);

        // Functions for calculating attack ranges and battle conditions
    float CalculateDistance(int x1, int y1, int x2, int y2);
    float CalculateBattleshipMaxRange(float maxVelocity);
    int CanBattleshipHit(float distance, float maxAttackRange);
    float CalculateEscortMaxRange(float maxVelocity, float bestAngle);
    int CanEscortHitBattleship(float distance, float maxAttackRange);
        // Functions for calculating shell firing angle and travel time
    float CalculateFiringAngle(float distance, float maxVelocity);
    float CalculateTimeToHit(float distance, float velocity, float angle);

    #endif