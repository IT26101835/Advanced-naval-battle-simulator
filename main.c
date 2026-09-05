#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ships.h"
#include "battle.h"
 
   
int main(){
        srand(time(NULL)); //change the starting seed
    printf(" ADVANCED NAVAL BATTLE SIMULATOR \n");
    //assigning variables
int d,n; 
int battleshipSunk = 0;
int sinkingEscortIndex = -1;
int hitEscortCount = 0;
float totalBattleTime = 0;
    //use for part 1b simulation
int k;
int pathX[100];
int pathY[100];
int pointHitCount;
float pointBattleTime;
    //use for simulation 2
int t;
float thetaMin;
float currentFiringAngle;

float currentImpact; //for B
int initialBX;
int initialBY;
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
// save battleship position for upcoming simulation 
    initialBX = B.x;
    initialBY = B.y;
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

    RunPart1A(B, E, n);

    printf("\nEnter number of path points: ");
    scanf("%d", &k);
    if (k < 1 || k > 100){
        printf("Number of path points must be between 1 and 100.\n");
        return 1;
    }


    // Reset escort ships for Simulation 2
    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
    }
    printf("\n=== Part 1-B Simulation 2 ===\n");
         // Get the iteration when the gun jams
    printf("Enter the iteration after which the gun jams: ");
    scanf("%d", &t);
    if (t < 1 || t >= k){
        printf("Jam iteration must be between 1 and %d.\n", k - 1);
        return 1;
    }   // Get the minimum firing angle after the gun jams
    printf("Enter minimum firing angle after jam: "); 
    scanf("%f", &thetaMin);
    if (thetaMin <= 0 || thetaMin >= 30){
        printf("Minimum firing angle must be between 0 and 30 degrees.\n");
        return 1;
    }

RunPart1BSimulation2(B, E, n, k, pathX, pathY, t, thetaMin);

RunPart1CSimulationA(B, E, n, initialBX, initialBY);


RunPart1CSimulationB1(B, E, n, k, pathX, pathY);
  
RunPart1CSimulationB2(B, E, n, k, pathX, pathY, t, thetaMin);

float TBq;

    printf("\nEnter B firing delay TBq: ");
    scanf("%f", &TBq);

RunPart2APart1A(B, E, n, TBq);

RunPart2APart1BSim1(B, E, n, k, pathX, pathY, d, TBq);

RunPart2APart1BSim2(B, E, n, k, pathX, pathY,t, thetaMin, TBq);

RunPart2APart1CA(B, E, n, TBq);

//RunPart2APart1CB1(B, E, n, k, pathX, pathY, TBq);

//RunPart2APart1CB2(B, E, n, k, pathX, pathY, t, thetaMin, TBq);


    return 0;
    
}
