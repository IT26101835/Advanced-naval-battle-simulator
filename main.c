#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    typedef struct {  // Structure to store Battleship details
        char type;
        int x,y;
        float maxVelocity;
        float maxAttackRange;
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

   
int main(){
        srand(time(NULL)); //change the starting seed
    printf(" ADVANCED NAVAL BATTLE SIMULATOR \n");
    //assigning variables
int d,n; 
int battleshipSunk = 0;
int sinkingEscortIndex = -1;
int hitEscortCount = 0;
float totalBattleTime = 0;

int k;
int pathX[100];
int pathY[100];
float pointBattleTime = 0;
    FILE *file; // File pointer for saving battle conditions

    BattleShip B; //create a battleship variable

 //getting user inputs
    printf("Enter battlefield size: "); 
    scanf("%d",&d);
    printf("Enter the no of escort ships: ");
    scanf("%d",&n);
    printf("Enter Battleship type (U/M/R/S): ");
    scanf(" %c", &B.type);
    printf("Enter battleship X position: ");
    scanf("%d",&B.x);
 	printf("Enter battleship Y position: ");
    scanf("%d",&B.y);
    printf("Enter battleship maximum shell velocity: ");
    scanf("%f",&B.maxVelocity);
    B.maxAttackRange = CalculateBattleshipMaxRange(B.maxVelocity);
//print details
    printf("battlefield size is %d x %d\n",d,d);
    printf("Number of escort ships: %d\n",n);
    printf("\n--- Battleship Details ---\n");
    printf("Type: %c\n", B.type);
    printf("Position: (%d,%d)\n", B.x, B.y);
    printf("Maximum Shell Velocity: %.2f m/s\n", B.maxVelocity);
    printf("Battleship Maximum Attack Range: %.2f\n", B.maxAttackRange);

    printf("\n--- Escortship Details ---\n");

         EscortShip E[n]; // create an array to store escort ships

        for (int i=0; i<n; i++){
            E[i].index = i+1; //set the index of the escort ship
            E[i].isAlive = 1;
            E[i].x = GenerateRandomCoordinate(d); //set the escort ship cordinates
            E[i].y = GenerateRandomCoordinate(d); 
            E[i].distanceFromB = CalculateDistance(B.x, B.y, E[i].x, E[i].y); // Calculate the distance between the battleship and escort ship
            E[i].canBeHitByB = CanBattleshipHit(E[i].distanceFromB, B.maxAttackRange);
        if (E[i].canBeHitByB == 1){
            E[i].firingAngleFromB = CalculateFiringAngle(E[i].distanceFromB, B.maxVelocity);
            E[i].timeToHitFromB = CalculateTimeToHit(E[i].distanceFromB, B.maxVelocity, E[i].firingAngleFromB);
        }
        else{
            E[i].firingAngleFromB = 0;
            E[i].timeToHitFromB = 0;
    }
            E[i].type = GenerateRandomEscortType(); //set the escort ship type
            E[i].angleRange = GetAngleRange(E[i].type);
            E[i].minAngle = GetMinimumAngle ();
            E[i].maxAngle = E[i].minAngle + E[i].angleRange;
            E[i].bestAngle = GetBestAngle(E[i].minAngle, E[i].maxAngle);
            E[i].maxVelocity = GetMaximumVelocity(E[i].type, B.maxVelocity);
            E[i].minVelocity = GetMinimumVelocity(E[i].maxVelocity);
            E[i].maxAttackRange = CalculateEscortMaxRange(E[i].maxVelocity, E[i].bestAngle);
            E[i].canHitB = CanEscortHitBattleship(E[i].distanceFromB,E[i].maxAttackRange);
            E[i].impactPower = GetImpactPower(E[i].type); //ser the impact power
    //print the escort ship details
        printf("Escort ship E%d\n", E[i].index);
        printf("Position = (%d, %d)\n", E[i].x, E[i].y);
        printf("Type = E%c\n", E[i].type);
        printf("Angle Range = %.1f\n", E[i].angleRange);
        printf("Min Angle = %.1f\n", E[i].minAngle);
        printf("Max Angle = %.1f\n", E[i].maxAngle);
        printf("Max Velocity = %.1f\n", E[i].maxVelocity);
        printf("Min Velocity = %.1f\n", E[i].minVelocity);
        printf("Impact Power = %.2f\n", E[i].impactPower);
        printf("Distance from B = %.2f\n", E[i].distanceFromB);
        printf("Best Angle = %.1f\n", E[i].bestAngle);
        printf("E Max Attack Range = %.2f\n", E[i].maxAttackRange);
        printf("B Firing Angle = %.2f\n", E[i].firingAngleFromB);
        printf("Time to Hit from B = %.2f seconds\n", E[i].timeToHitFromB);

    if (E[i].canBeHitByB == 1){  //check weather b can hit or not 
       printf("B Can Hit = YES\n");
    }
     else{
    printf("B Can Hit = NO\n");
    }
        if (E[i].canHitB == 1){
            printf("E Can Hit B = YES\n");
            printf("\n");
        }
    else{
        printf("E Can Hit B = NO\n");
        printf("\n");
    }
}
    file = fopen("initial_conditions.txt", "w");             // Save initial battlefield conditions to a text file
        if (file == NULL){
            printf("Error opening file!\n");
            return 1;
        }
    fprintf(file, "=== INITIAL BATTLE CONDITIONS ===\n\n");
                //Battleship ships properties save for the file
    fprintf(file, "Battleship\n");
    fprintf(file, "Type = %c\n", B.type);
    fprintf(file, "Position = (%d, %d)\n", B.x, B.y);
    fprintf(file, "Max Velocity = %.2f\n", B.maxVelocity);
    fprintf(file, "Max Attack Range = %.2f\n\n", B.maxAttackRange);
            //Escort ships properties save for the file
    fprintf(file, "Escort Ships\n\n");
for (int i = 0; i < n; i++){
    fprintf(file, "Escort Ship E%d\n", E[i].index);
    fprintf(file, "Position = (%d, %d)\n", E[i].x, E[i].y);
    fprintf(file, "Type = E%c\n", E[i].type);
    fprintf(file, "Angle Range = %.1f\n", E[i].angleRange);
    fprintf(file, "Min Angle = %.1f\n", E[i].minAngle);
    fprintf(file, "Max Angle = %.1f\n", E[i].maxAngle);
    fprintf(file, "Min Velocity = %.1f\n", E[i].minVelocity);
    fprintf(file, "Max Velocity = %.1f\n", E[i].maxVelocity);
    fprintf(file, "Impact Power = %.2f\n", E[i].impactPower);
    fprintf(file, "\n");
}
    fclose(file); //closing the text file
//check weather escort ship can hit battleship sunk
     for (int i = 0; i < n; i++){  
          if (E[i].canHitB == 1){
                battleshipSunk = 1;
                sinkingEscortIndex = E[i].index;
                break;
            }
        }
    if (battleshipSunk == 1){
         printf("\nBattleship SANK!\n");
         printf("Battleship was sunk by Escort Ship E%d\n", sinkingEscortIndex);
   }
  else{
    printf("\nBattleship SURVIVED!\n");

    for (int i = 0; i < n; i++) //count the no of escort ships ditroyed
    {
        if (E[i].canBeHitByB == 1)
        {
            hitEscortCount++;
        if (E[i].timeToHitFromB > totalBattleTime){
                totalBattleTime = E[i].timeToHitFromB;
        }
        }
    }
    printf("Number of Escort Ships hit by B = %d\n", hitEscortCount);
    printf("Total Battle Time = %.2f seconds\n", totalBattleTime);
   }
file = fopen("final_conditions.txt", "w"); // Display the final+_+ battle result to text file
    if (file == NULL){
        printf("Error opening final conditions file!\n");
        return 1;
    }

    fprintf(file, "=== FINAL BATTLE CONDITIONS ===\n\n");  

        if (battleshipSunk == 1){
            fprintf(file, "Battleship SANK!\n");
            fprintf(file, "Battleship was sunk by Escort Ship E%d\n",sinkingEscortIndex);
        }
    else{
            fprintf(file, "Battleship SURVIVED!\n");
            fprintf(file, "Number of Escort Ships hit by B = %d\n",hitEscortCount);
            fprintf(file, "Total Battle Time = %.2f seconds\n",totalBattleTime);
            fprintf(file, "\nHit Escort Ship Details: \n");
        for (int i = 0; i < n; i++){
                if (E[i].canBeHitByB == 1){
                        fprintf(file, "Escort Ship E%d\n", E[i].index);
                        fprintf(file, "Time to Hit = %.2f seconds\n",E[i].timeToHitFromB);
                    }
                else{
                    fprintf(file, "  None !\n");
                }
            }
        }   
    fprintf(file, "\n=== FINAL ESCORT SHIP STATUS ===\n");
            for (int i = 0; i < n; i++){               
                fprintf(file, "Escort Ship E%d: ", E[i].index);
                    if (E[i].canBeHitByB == 1){
                        fprintf(file, "DESTROYED\n");
                    }
                else{
                        fprintf(file, "NOT DESTROYED\n");
                }
            }
fclose(file);
    printf("\nEnter number of path points: ");
    scanf("%d", &k);
battleshipSunk = 0;
sinkingEscortIndex = -1;
    file = fopen("part1b_simulation1.txt", "w"); //open part 1b file

    if (file == NULL){ //check wether errors comming or not
        printf("Error opening Part1b file!\n");
        return 1;
    }
    fprintf(file, "=== PART 1-B SIMULATION 1 ===\n\n");
    fprintf(file, "Number of Path Points = %d\n\n", k);
        for (int i = 0; i < k; i++){ 
            pathX[i] = GenerateRandomCoordinate(d);
            pathY[i] = GenerateRandomCoordinate(d);
            printf("Path Point %d = (%d, %d)\n",i + 1, pathX[i], pathY[i]);
        }
        for (int i = 0; i < k; i++){     // Move the battleship to each path point
            B.x = pathX[i];
            B.y = pathY[i];
            printf("\nBattleship moved to Point %d\n", i + 1);
            printf("Battleship Position = (%d, %d)\n", B.x, B.y);

            fprintf(file, "=== Path Point %d ===\n", i + 1);
            fprintf(file, "Battleship Position = (%d, %d)\n",B.x, B.y);
        
            for (int j = 0; j < n; j++){ // Check only escort ships that are still active
                if (E[j].isAlive == 1){
                    E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y); // Recalculate the distance from the new battleship position
                // Check if the battleship and escort ship can hit each other
                    E[j].canBeHitByB = CanBattleshipHit(E[j].distanceFromB, B.maxAttackRange);
                    E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB, E[j].maxAttackRange);
                    printf("Distance to E%d = %.2f\n",E[j].index, E[j].distanceFromB);
                        
                    fprintf(file, "Escort Ship E%d\n", E[j].index);
                    fprintf(file, "Position = (%d, %d)\n", E[j].x, E[j].y);
                    fprintf(file, "Distance from B = %.2f\n", E[j].distanceFromB);

                if (E[j].canBeHitByB == 1){
                    fprintf(file, "B Can Hit = YES\n");
                }
                else{
                    fprintf(file, "B Can Hit = NO\n");
                }
                if (E[j].canHitB == 1){
                    fprintf(file, "E Can Hit B = YES\n");
                }
                else{
                    fprintf(file, "E Can Hit B = NO\n");
                }
                fprintf(file, "\n");
                         if (E[j].canHitB == 1){         // Check if the escort ship can sink the battleship
                                battleshipSunk = 1;
                                sinkingEscortIndex = E[j].index;
                                printf("Battleship was sunk by Escort Ship E%d\n",E[j].index);
                                break;
                        }
                         if (E[j].canBeHitByB == 1){         // Destroy the escort ship if B can hit it
                                E[j].firingAngleFromB = CalculateFiringAngle(E[j].distanceFromB,B.maxVelocity);
                                E[j].timeToHitFromB = CalculateTimeToHit(E[j].distanceFromB,B.maxVelocity,E[j].firingAngleFromB);
                                E[j].isAlive = 0;
                                printf("Escort Ship E%d was destroyed by B\n",E[j].index);
                                printf("Time to Hit = %.2f seconds\n",E[j].timeToHitFromB);
                                fprintf(file, "Result = DESTROYED BY B\n");
                                fprintf(file, "Time to Hit = %.2f seconds\n\n",E[j].timeToHitFromB);
                        }
                }
            }
            if (battleshipSunk == 1){     // Stop the simulation if the battleship is sunk
                break;
            }
        }

    return 0;
    
}
