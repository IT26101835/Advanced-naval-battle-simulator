#include <stdio.h>
#include "battle.h"

void RunPart1A(BattleShip B, EscortShip E[], int n)
{
    printf("\n=== PART 1-A ===\n");

    FILE *file;

    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int hitEscortCount = 0;
    float totalBattleTime = 0;

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
        return ;
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
}
    FILE *file;
    void RunPart1BSimulation1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int d){
        printf("\n=== PART 1-B SIMULATION 1 ===\n");


    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int pointHitCount = 0;
    float pointBattleTime = 0;
    file = fopen("part1b_simulation1.txt", "w"); //open part 1b file

    if (file == NULL){ //check wether errors comming or not
        printf("Error opening Part1b file!\n");
        return ;
    }
    fprintf(file, "=== PART 1-B SIMULATION 1 ===\n\n");
    fprintf(file, "Number of Path Points = %d\n\n", k);
        for (int i = 0; i < k; i++){ 
            pathX[i] = GenerateRandomCoordinate(d);
            pathY[i] = GenerateRandomCoordinate(d);
            printf("Path Point %d = (%d, %d)\n",i + 1, pathX[i], pathY[i]);
        }
        for (int i = 0; i < k; i++){     // Move the battleship to each path point
            pointHitCount = 0;
            pointBattleTime = 0;
            B.x = pathX[i];
            B.y = pathY[i];
            printf("\nBattleship moved to Point %d\n", i + 1);
            printf("Battleship Position = (%d, %d)\n", B.x, B.y);

            fprintf(file, "=== Path Point %d ===\n", i + 1);
            fprintf(file, "Battleship Position = (%d, %d)\n",B.x, B.y);
        
            for (int j = 0; j < n; j++){ // Check only escort ships that are still active
                if (E[j].isAlive == 1){
                   // E[j].maxAttackRange = 0;  
                    E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y); // Recalculate the distance from the new battleship position
                // Check if the battleship and esscort ship can hit each other
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
                                fprintf(file, "Result = BATTLESHIP SUNK\n");
                                fprintf(file, "Battleship was sunk by Escort Ship E%d\n\n",E[j].index);
                                break;
                        }
                         if (E[j].canBeHitByB == 1){         // Destroy the escort ship if B can hit it
                                E[j].firingAngleFromB = CalculateFiringAngle(E[j].distanceFromB,B.maxVelocity);
                                E[j].timeToHitFromB = CalculateTimeToHit(E[j].distanceFromB,B.maxVelocity,E[j].firingAngleFromB);
                                if (E[j].timeToHitFromB > pointBattleTime){
                                    pointBattleTime = E[j].timeToHitFromB;
                                }
                                E[j].isAlive = 0;
                                pointHitCount++;
                                printf("Escort Ship E%d was destroyed by B\n",E[j].index);
                                printf("Time to Hit = %.2f seconds\n",E[j].timeToHitFromB);
                                fprintf(file, "Result = DESTROYED BY B\n");
                                fprintf(file, "Time to Hit = %.2f seconds\n\n",E[j].timeToHitFromB);
                        }
                }
            }
            if (battleshipSunk == 0){     // Save results if B survived this path point
                fprintf(file, "Battleship SURVIVED this point\n");
                fprintf(file, "Number of Escort Ships hit by B = %d\n\n",pointHitCount);
                fprintf(file, "Battle Time at this Point = %.2f seconds\n\n",pointBattleTime);
            }
            if (battleshipSunk == 1){     // Stop the simulation if the battleship is sunk
                break;
            }
        }
        fprintf(file, "\n=== FINAL SIMULATION 1 STATUS ===\n");
        if (battleshipSunk == 1){
            fprintf(file, "Battleship Status = SUNK\n");
            fprintf(file, "Sunk by Escort Ship E%d\n",sinkingEscortIndex);
        }
        else{
            fprintf(file, "Battleship Status = SURVIVED\n");
        }
        fprintf(file, "\nEscort Ships Final Status:\n");

        for (int i = 0; i < n; i++){
            if (E[i].isAlive == 1){
                fprintf(file, "Escort Ship E%d = ALIVE\n",E[i].index);
            }
            else{
                fprintf(file, "Escort Ship E%d = DESTROYED\n",E[i].index);
            }
        }   
    fclose(file);
    }

    void RunPart1BSimulation2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin){
    FILE *file;

    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int pointHitCount = 0;
    float pointBattleTime = 0;
    float currentFiringAngle;

    file = fopen("part1b_simulation2.txt", "w"); //open simulation 2 file

    if (file == NULL){
        printf("Error opening Part 1-B Simulation 2 file!\n");
        return ;
    }

    fprintf(file, "=== PART 1-B SIMULATION 2 ===\n\n");
    fprintf(file, "Number of Path Points = %d\n", k);
    fprintf(file, "Gun Jams After Iteration = %d\n", t);
    fprintf(file, "Minimum Angle After Jam = %.2f degrees\n\n", thetaMin);


    for (int i = 0; i < k; i++){  // Simulate the battle at each path point
        pointHitCount = 0;
        pointBattleTime = 0;

        B.x = pathX[i];
        B.y = pathY[i];

        printf("\nBattleship moved to Point %d\n", i + 1);
        printf("Battleship Position = (%d, %d)\n", B.x, B.y);

        fprintf(file, "=== Path Point %d ===\n", i + 1);
        fprintf(file, "Battleship Position = (%d, %d)\n",B.x, B.y);
        if (i < t){  // Check whether the battleship gun is jammed
            printf("Battleship Gun Status = NORMAL\n\n");
            fprintf(file, "Battleship Gun Status = NORMAL\n\n");
        }
        else{
            printf("Battleship Gun Status = JAMMED\n\n");
            fprintf(file, "Battleship Gun Status = JAMMED\n\n");
        }
        for (int j = 0; j < n; j++){  // Check each escort ship at the current path point
            if (E[j].isAlive == 1){
                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB,E[j].maxAttackRange);
                E[j].canBeHitByB = CanBattleshipHit(E[j].distanceFromB,B.maxAttackRange);
                if (E[j].canBeHitByB == 1){
                    currentFiringAngle = CalculateFiringAngle(E[j].distanceFromB,B.maxVelocity);

                    if (i >= t){  // Use the higher firing angle if the lower angle is not allowed
                        if (currentFiringAngle < thetaMin){
                            currentFiringAngle = 90.0 - currentFiringAngle;
                        }
                    }
                    E[j].firingAngleFromB = currentFiringAngle;
                    E[j].timeToHitFromB = CalculateTimeToHit(E[j].distanceFromB,B.maxVelocity,currentFiringAngle);
                    if (E[j].canHitB == 1){
                        battleshipSunk = 1;
                        sinkingEscortIndex = E[j].index;

                        printf("Battleship was sunk by Escort Ship E%d\n",E[j].index);
                        fprintf(file, "Escort Ship Position = (%d, %d)\n", E[j].x, E[j].y);
                        fprintf(file, "Distance from B = %.2f\n", E[j].distanceFromB);
                        if (E[j].canBeHitByB == 1){
                            fprintf(file, "B Can Hit = YES\n");
                        }
                        fprintf(file, "Result = BATTLESHIP SUNK\n");
                        fprintf(file, "Battleship was sunk by Escort Ship E%d\n\n",E[j].index);
                        break;
                    }  
                    if (E[j].canBeHitByB == 1){
                        E[j].isAlive = 0;
                        pointHitCount++;

                        if (E[j].timeToHitFromB > pointBattleTime){
                            pointBattleTime = E[j].timeToHitFromB;
                        }

                        printf("Escort Ship E%d was destroyed by B\n",E[j].index);
                        printf("Firing Angle = %.2f degrees\n",E[j].firingAngleFromB);
                        printf("Time to Hit = %.2f seconds\n",E[j].timeToHitFromB);
                        fprintf(file, "Escort Ship Position = (%d, %d)\n", E[j].x, E[j].y);
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
                        fprintf(file, "Battleship Firing Angle = %.2f degrees\n",E[j].firingAngleFromB);
                        fprintf(file, "Time to Hit = %.2f seconds\n",E[j].timeToHitFromB);
                        fprintf(file, "Result = Escort Ship E%d DESTROYED BY B\n\n", E[j].index);
                        
                    }            
                }
                printf("Distance to E%d = %.2f\n",E[j].index, E[j].distanceFromB);
            }
        }
        if (battleshipSunk == 0){
            fprintf(file, "Battleship SURVIVED this point\n");
            fprintf(file, "Number of Escort Ships hit by B = %d\n",pointHitCount);
            fprintf(file, "Battle Time at this Point = %.2f seconds\n\n",pointBattleTime);
        }
        if (battleshipSunk == 1){
            break;
        }
    }
    fprintf(file, "\n=== FINAL SIMULATION 2 STATUS ===\n"); // Save the final status of Simulation 2

    if (battleshipSunk == 1){
        fprintf(file, "Battleship Status = SUNK\n");
        fprintf(file, "Sunk by Escort Ship E%d\n",sinkingEscortIndex);
    }
    else{
        fprintf(file, "Battleship Status = SURVIVED\n");
    }

    fprintf(file, "\nEscort Ships Final Status:\n");

    for (int i = 0; i < n; i++){ // Reset escort ships for Simulation 2
        if (E[i].isAlive == 1){
            fprintf(file, "Escort Ship E%d = ALIVE\n",E[i].index);
        }
        else{
            fprintf(file, "Escort Ship E%d = DESTROYED\n",E[i].index);
        }
    }

    fclose(file);
}

void RunPart1CSimulationA(BattleShip B, EscortShip E[], int n,int initialBX, int initialBY){
    FILE *file;
// Reset battle values for Part 1-C
    float currentImpact = 0;
    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int hitEscortCount = 0;
    float totalBattleTime = 0;

        // Part 1-C
    printf("\n=== PART 1-C ===\n");
  

B.x = initialBX;
B.y = initialBY;
    for (int i = 0; i < n; i++){ //reset all escort ships
        E[i].isAlive = 1;
    }

file = fopen("part1c_simulationA.txt", "w");

    if (file == NULL){
        printf("Error opening Part 1-C file.\n");
        return;
    }

    fprintf(file, "=== PART 1-C - PART 1-A SIMULATION ===\n\n");

    for (int i = 0; i < n; i++){ // Recalculate distances and attack ranges
        E[i].distanceFromB = CalculateDistance(B.x, B.y, E[i].x, E[i].y);
        E[i].canBeHitByB = CanBattleshipHit(E[i].distanceFromB, B.maxAttackRange);
        E[i].canHitB = CanEscortHitBattleship(E[i].distanceFromB, E[i].maxAttackRange);
    }
    for (int i = 0; i < n; i++){
        if (E[i].canHitB == 1){ 
            currentImpact = currentImpact + E[i].impactPower;
            if (currentImpact >= 1.0){ // Calculate the total impact on the battleship
                battleshipSunk = 1;
                sinkingEscortIndex = E[i].index;
                break;
            }
        }
    }
    fprintf(file, "\n------- Battle Ship Position: (%d,%d) ------- \n", B.x,B.y);
    for (int i = 0; i < n; i++){
        if (battleshipSunk == 0 && E[i].canBeHitByB == 1){
            E[i].firingAngleFromB = CalculateFiringAngle(E[i].distanceFromB, B.maxVelocity);
            E[i].timeToHitFromB = CalculateTimeToHit(E[i].distanceFromB,B.maxVelocity,E[i].firingAngleFromB);
            E[i].isAlive = 0;
            hitEscortCount++;
            fprintf(file, "\nEscort ship %d was hit by B\n", E[i].index);
            fprintf(file, "Escort Ship Type: E%c\n", E[i].type);
            fprintf(file, "Escort Ship %d Position: (%d, %d)\n",E[i].index, E[i].x, E[i].y);
            fprintf(file, "Distance from B: %.2f\n", E[i].distanceFromB);
            fprintf(file, "Firing angle from B: %.2f\n", E[i].firingAngleFromB);
            fprintf(file, "Time to hit: %.2f seconds\n", E[i].timeToHitFromB);
            if (E[i].timeToHitFromB > totalBattleTime){
                totalBattleTime = E[i].timeToHitFromB;
            }
        }
    }
    if (battleshipSunk == 1){ // Check if the battleship is destroyed
        printf("Battleship was sunk by Escort %d\n", sinkingEscortIndex);

        fprintf(file, "Battleship was sunk by Escort %d\n",sinkingEscortIndex);
    }
    else{ 
        printf("\nBattleship survived.\n");
        printf("Current Impact on B = %.2f%%\n", currentImpact * 100);
        printf("Escort ships hit by B: %d\n", hitEscortCount);
        printf("Total battle time: %.2f seconds\n", totalBattleTime);
// Display and save the final battle result
        fprintf(file, "\nBattleship survived.\n");
        fprintf(file, "Current Impact on B = %.2f%%\n",currentImpact*100);
        fprintf(file, "Escort ships hit by B: %d\n",hitEscortCount);
        fprintf(file, "Total battle time: %.2f seconds\n",totalBattleTime);
    }
   
fclose(file);
}

void RunPart1CSimulationB1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[]){
    FILE *file;

    float currentImpact = 0;
    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int pointHitCount = 0;
    int hitEscortCount =0;

    // Part 1-C - Part 1-B Simulation 1
    printf("\n=== PART 1-C - PART 1-B SIMULATION 1 ===\n");


    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }

    file = fopen("part1c_simulationB1.txt", "w");

    if (file == NULL){
        printf("Error opening Part 1-C Simulation 1 file.\n");
        return ;
    }

    fprintf(file, "=== PART 1-C - PART 1-B SIMULATION 1 ===\n\n");

    for (int i = 0; i < k; i++){ //Battleship position change with k points
        // Move battleship to the current path point
        B.x = pathX[i];
        B.y = pathY[i];

        printf("\nBattleship moved to Point %d\n", i + 1);
        printf("Battleship Position = (%d, %d)\n", B.x, B.y);

        fprintf(file, "\n=== Path Point %d ===\n", i + 1);
        fprintf(file, "Battleship Position = (%d, %d)\n", B.x, B.y);

        for (int j = 0; j < n; j++){ //Escort ships 
            if (E[j].isAlive == 1){
                int firedThisPoint = 0; // seperately E ships
                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);
                E[j].canBeHitByB = CanBattleshipHit(E[j].distanceFromB,B.maxAttackRange);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB,E[j].maxAttackRange);
            // check if Escort ship has fired or not
                if (E[j].canHitB == 1 && E[j].hasFired == 0){
                    currentImpact = currentImpact + E[j].impactPower;
                    E[j].hasFired = 1;
                    firedThisPoint = 1; // E attacked B at this point
                    if (currentImpact >= 1.0){
                        battleshipSunk = 1;
                        sinkingEscortIndex = E[j].index;
                        break;
                    }
                }
                if (battleshipSunk == 0 && E[j].canBeHitByB == 1){ //attacking B to E
                    E[j].firingAngleFromB = CalculateFiringAngle(E[j].distanceFromB, B.maxVelocity);
                    E[j].timeToHitFromB = CalculateTimeToHit(E[j].distanceFromB,B.maxVelocity,E[j].firingAngleFromB);
                    E[j].isAlive = 0;
                    hitEscortCount++;

                }
                fprintf(file, "\nEscort ship %d \n", E[j].index);
                fprintf(file, "Escort Ship Type: E%c\n", E[j].type);
                fprintf(file, "Escort Ship %d Position: (%d, %d)\n",E[j].index, E[j].x, E[i].y);
                fprintf(file, "Distance from B: %.2f\n", E[j].distanceFromB);
                fprintf(file, "B Can Hit: %d\n", E[j].canBeHitByB);
                fprintf(file, "E Can Hit B: %d\n", E[j].canHitB);
                fprintf(file, "Current Impact on B: %.2f%%\n", currentImpact * 100);
                
                if (firedThisPoint == 1){
                    fprintf(file, "Escort attacked B\n");
                }
                else{
                    fprintf(file, "Escort did not attack B\n");
                }
                if (E[j].isAlive == 0){ //after the B attack check weather is it escort ship is alive
                    fprintf(file, "Result: Escort Ship destroyed by B\n");
                }
                else{
                    fprintf(file, "Result: Escort Ship still alive\n");
                }
                
            }
        }
        if (battleshipSunk == 1){ //if already sunk other paths cannot go
            break;
        }
    }
    if (battleshipSunk == 1){
        printf("\nBattleship was sunk by Escort %d\n",sinkingEscortIndex);
        fprintf(file, "\nBattleship was sunk by Escort %d\n",sinkingEscortIndex);
    }
    else{
        printf("\nBattleship survived.\n");
        printf("Current Impact on B = %.2f%%\n",currentImpact * 100);

        fprintf(file, "\nBattleship survived.\n");
        fprintf(file, "Current Impact on B = %.2f%%\n",currentImpact * 100);
        fprintf(file, "Escort ships hit by B: %d\n",hitEscortCount);

    }
    fclose(file);
    
}

void RunPart1CSimulationB2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin){
    FILE *file;

    float currentImpact = 0;
    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int pointHitCount = 0;
    float pointBattleTime = 0;
    float currentFiringAngle;
    int hitEscortCount = 0;

      // Part 1-C - Part 1-B Simulation 2
    printf("\n=== PART 1-C - PART 1-B SIMULATION 2 ===\n");

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }
    file = fopen("part1c_simulationB2.txt", "w");

    if (file == NULL){
        printf("Error opening Part 1-C Simulation 2 file.\n");
        return ;
    }

    fprintf(file, "=== PART 1-C - PART 1-B SIMULATION 2 ===\n\n");

    for (int i = 0; i < k; i++){
    // Move battleship to the current path point
        B.x = pathX[i];
        B.y = pathY[i];

        printf("\nBattleship moved to Point %d\n", i + 1);
        printf("Battleship Position = (%d, %d)\n", B.x, B.y);

        fprintf(file, "\n=== Path Point %d ===\n", i + 1);
        if (i >= t){ //check and print the gun status
            fprintf(file, "Gun Status: JAMMED\n");
        }
        else{
            fprintf(file, "Gun Status: NORMAL\n");
        }
        fprintf(file, "Battleship Position = (%d, %d)\n", B.x, B.y);

        for (int j = 0; j < n; j++){
            if (E[j].isAlive == 1){
                int firedThisPoint = 0;

                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);
                E[j].canBeHitByB = CanBattleshipHit(E[j].distanceFromB,B.maxAttackRange);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB,E[j].maxAttackRange);

                if (E[j].canHitB == 1 && E[j].hasFired == 0){ //(check E can attck B or not) and (already fired or not)
                    currentImpact = currentImpact + E[j].impactPower;

                    E[j].hasFired = 1;
                    firedThisPoint = 1;

                    if (currentImpact >= 1.0){ //check the dammage amount
                        battleshipSunk = 1;
                        sinkingEscortIndex = E[j].index;
                        break;
                    }
                }
                if (battleshipSunk == 0 && E[j].canBeHitByB == 1){
                    currentFiringAngle = CalculateFiringAngle(E[j].distanceFromB, B.maxVelocity);
                    hitEscortCount++; //increment E count
                    if (i >= t){
                        if (currentFiringAngle < thetaMin){
                            currentFiringAngle = 90.0 - currentFiringAngle;
                        }
                    }
                    E[j].firingAngleFromB = currentFiringAngle;
                    E[j].timeToHitFromB = CalculateTimeToHit(E[j].distanceFromB,B.maxVelocity,currentFiringAngle);
                    E[j].isAlive = 0;
                }
                fprintf(file, "\nEscort ship %d \n", E[j].index);
                fprintf(file, "Escort Ship Type: E%c\n", E[j].type);
                fprintf(file, "Escort Ship %d Position: (%d, %d)\n",E[j].index, E[j].x, E[i].y);
                fprintf(file, "Distance from B: %.2f\n", E[j].distanceFromB);
                fprintf(file, "B Can Hit: %d\n", E[j].canBeHitByB);
                fprintf(file, "E Can Hit B: %d\n", E[j].canHitB);
                fprintf(file, "Current Impact on B: %.2f%%\n", currentImpact * 100);
                
                if (firedThisPoint == 1){ //check weather at this point E attcked B or not
                    fprintf(file, "Escort attacked B\n");
                }
                else{
                    fprintf(file, "Escort did not attack B\n");
                }
                if (E[j].isAlive == 0){ //after the B attack check weather is it escort ship is alive
                    fprintf(file, "Result: Escort Ship destroyed by B\n");
                    fprintf(file, "Firing angle from B: %.2f\n",E[j].firingAngleFromB);
                    fprintf(file, "Time to hit: %.2f seconds\n",E[j].timeToHitFromB);
                }
                else{
                    fprintf(file, "Result: Escort Ship still alive\n");
                }

            }
        }
        if (battleshipSunk == 1){
            break;
        }
    }
    //final printing details
    if (battleshipSunk == 1){
        printf("\nBattleship was sunk by Escort %d\n",sinkingEscortIndex);

        fprintf(file, "\nBattleship was sunk by Escort %d\n",sinkingEscortIndex);
    }
    else{
        printf("\nBattleship survived.\n");
        printf("Current Impact on B = %.2f%%\n",currentImpact * 100);

        fprintf(file, "\nBattleship survived.\n");
        fprintf(file, "Current Impact on B = %.2f%%\n",currentImpact * 100);
        fprintf(file, "Escort ships hit by B: %d\n",hitEscortCount);
    }
    fclose(file);
}

// PART 2-A
// Attack nearest E ship inside B attack range first

// Find nearest escort ship inside B attack range
int FindNearestEscort(BattleShip B, EscortShip E[], int n){
    int nearestIndex = -1;
    float nearestDistance = 999999;

    for (int i = 0; i < n; i++){
        if (E[i].isAlive == 1){
            E[i].distanceFromB = CalculateDistance(B.x, B.y, E[i].x, E[i].y);
            E[i].canBeHitByB = CanBattleshipHit(E[i].distanceFromB, B.maxAttackRange);

            if (E[i].canBeHitByB == 1){
                if (E[i].distanceFromB < nearestDistance){
                    nearestDistance = E[i].distanceFromB;
                    nearestIndex = i;
                }
            }
        }
    }
    return nearestIndex;
}
// PART 2-A -> PART 1-A
void RunPart2APart1A(BattleShip B, EscortShip E[], int n, float TBq){
    FILE *file;

    int attackOrder[n];
    int attackCount = 0;
    float currentTime = 0;
    int nearestIndex;

    file = fopen("part2a_part1a.txt", "w");

    if (file == NULL)
    {
        printf("Error opening Part 2-A Part 1-A file.\n");
        return;
    }

    printf("\n=== PART 2-A : PART 1-A ===\n");
    fprintf(file,"=== PART 2-A : PART 1-A ===\n\n");
    fprintf(file, "B firing delay TBq = %.2f seconds\n\n", TBq);

// Reset escort ships
    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }
    while (1){
        nearestIndex = FindNearestEscort(B, E, n);
        if (nearestIndex == -1){
            break;
        }
        attackOrder[attackCount] = E[nearestIndex].index;
        attackCount++;
        E[nearestIndex].firingAngleFromB =CalculateFiringAngle(E[nearestIndex].distanceFromB, B.maxVelocity);
        E[nearestIndex].timeToHitFromB = CalculateTimeToHit(E[nearestIndex].distanceFromB, B.maxVelocity, E[nearestIndex].firingAngleFromB);
        
        printf("Time %.2f : B attacks Escort Ship %d\n", currentTime, E[nearestIndex].index);
        fprintf(file,"Time %.2f : B attacks Escort Ship %d\n", currentTime, E[nearestIndex].index);
        fprintf(file, "Distance = %.2f\n", E[nearestIndex].distanceFromB);
        fprintf(file, "Firing Angle = %.2f\n", E[nearestIndex].firingAngleFromB);
        fprintf(file,"Time To Hit = %.2f seconds\n\n", E[nearestIndex].timeToHitFromB);
// B destroys E with one shot
        E[nearestIndex].isAlive = 0;
// B must wait TBq before next firing
        currentTime = currentTime + TBq;
    }


    fprintf(file,"\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1,attackOrder[i]);
    }


    fprintf(file, "\n=== ESCORT FINAL STATUS ===\n");

    for (int i = 0; i < n; i++){
        if (E[i].isAlive == 1){
            fprintf(file, "Escort Ship %d = ALIVE\n", E[i].index);
        }
        else{
            fprintf(file, "Escort Ship %d = DESTROYED\n", E[i].index);
        }
    }


    fclose(file);
}

// PART 2-A -> PART 1-B SIMULATION 1
void RunPart2APart1BSim1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int d, float TBq){
    FILE *file;

    float currentTime = 0;
    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;

    file = fopen("part2a_part1b_sim1.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-A Simulation 1 file.\n");
        return;
    }
    printf("\n=== PART 2-A : PART 1-B SIMULATION 1 ===\n");

    fprintf(file,"=== PART 2-A : PART 1-B SIMULATION 1 ===\n\n");

    fprintf(file, "TBq = %.2f seconds\n\n", TBq);
// Reset escorts
    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }
// Generate B path
    for (int i = 0; i < k; i++){
        pathX[i] = GenerateRandomCoordinate(d);
        pathY[i] = GenerateRandomCoordinate(d);

        printf("Path Point %d = (%d, %d)\n", i + 1, pathX[i], pathY[i]);
        fprintf(file,"Path Point %d = (%d, %d)\n", i + 1, pathX[i], pathY[i]);
    }
    for (int i = 0; i < k; i++){
        B.x = pathX[i];
        B.y = pathY[i];


        printf("\nB moved to Path Point %d\n", i + 1);
        printf("B Position = (%d, %d)\n", B.x, B.y);
        fprintf(file, "\n=== PATH POINT %d ===\n", i + 1);
        fprintf(file, "B Position = (%d, %d)\n", B.x, B.y);
// At this path point B attacks nearest ships
        while (1){
            nearestIndex = FindNearestEscort(B, E, n);
            if (nearestIndex == -1){
                break;
            }
            attackOrder[attackCount] = E[nearestIndex].index;
            attackCount++;
            E[nearestIndex].firingAngleFromB = CalculateFiringAngle(E[nearestIndex].distanceFromB,B.maxVelocity);
            E[nearestIndex].timeToHitFromB = CalculateTimeToHit(E[nearestIndex].distanceFromB, B.maxVelocity, E[nearestIndex].firingAngleFromB);

            printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
            fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
            fprintf(file, "Distance = %.2f\n", E[nearestIndex].distanceFromB);
            fprintf(file, "Angle = %.2f\n", E[nearestIndex].firingAngleFromB);
            fprintf(file, "Time To Hit = %.2f seconds\n\n", E[nearestIndex].timeToHitFromB);
            E[nearestIndex].isAlive = 0;
            currentTime = currentTime + TBq;
        }
    }
    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1, attackOrder[i]);
    }
    fprintf(file, "\n=== FINAL ESCORT STATUS ===\n");

    for (int i = 0; i < n; i++){
        if (E[i].isAlive == 1){
            fprintf(file, "Escort Ship %d = ALIVE\n", E[i].index);
        }
        else{
            fprintf(file, "Escort Ship %d = DESTROYED\n",E[i].index);
        }
    }
    fclose(file);
}
// PART 2-A -> PART 1-B SIMULATION 2
// gun jam seen
void RunPart2APart1BSim2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin, float TBq){
    FILE *file;

    float currentTime = 0;
    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;
    float currentFiringAngle;
    
    file = fopen("part2a_part1b_sim2.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-A Simulation 2 file.\n");
        return;
    }
    printf("\n=== PART 2-A : PART 1-B SIMULATION 2 ===\n");
    fprintf(file,"=== PART 2-A : PART 1-B SIMULATION 2 ===\n\n");

    fprintf(file, "TBq = %.2f seconds\n", TBq);
    fprintf(file, "Gun Jam Iteration = %d\n", t);
    fprintf(file, "Theta Minimum = %.2f\n\n", thetaMin);

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }
    for (int i = 0; i < k; i++){
        B.x = pathX[i];
        B.y = pathY[i];

        fprintf(file, "\n=== PATH POINT %d ===\n", i + 1);
        fprintf(file, "B Position = (%d, %d)\n", B.x, B.y);

        if (i < t){
            fprintf(file, "Battleship Gun Status = NORMAL\n");
        }
        else{
            fprintf(file, "Battleship Gun Status = JAMMED\n");
        }
        while (1){
            nearestIndex = FindNearestEscort(B, E, n);
        
            if (nearestIndex == -1){
                break;
            }
            currentFiringAngle = CalculateFiringAngle(E[nearestIndex].distanceFromB, B.maxVelocity);
    // Gun jam after t iterations
            if (i >= t){
                if (currentFiringAngle < thetaMin){
                    currentFiringAngle = thetaMin;
                }
            }
            E[nearestIndex].firingAngleFromB = currentFiringAngle;
            E[nearestIndex].timeToHitFromB = CalculateTimeToHit(E[nearestIndex].distanceFromB, B.maxVelocity, currentFiringAngle);
            attackOrder[attackCount] = E[nearestIndex].index;
            attackCount++;

            printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
            fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
            fprintf(file,"Firing Angle = %.2f\n", currentFiringAngle);
            fprintf(file, "Time To Hit = %.2f seconds\n\n",E[nearestIndex].timeToHitFromB);

            E[nearestIndex].isAlive = 0;
            currentTime = currentTime + TBq;
        }
    }
    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n",i + 1, attackOrder[i]);
    }
    fclose(file);
}

// PART 2-A -> PART 1-C PART 1-A
// Escort impact power included
void RunPart2APart1CA(BattleShip B, EscortShip E[],int n, float TBq){
    FILE *file;

    float currentTime = 0;
    float currentImpact = 0;
    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;
    
    file = fopen("part2a_part1c_a.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-A Part 1-C A file.\n");
        return;
    }
    printf("\n=== PART 2-A : PART 1-C A ===\n");
    fprintf(file,"=== PART 2-A : PART 1-C A ===\n\n");
    
    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }
    while (1){
        nearestIndex =FindNearestEscort(B, E, n);
        if (nearestIndex == -1){
            break;
        }
        attackOrder[attackCount] =E[nearestIndex].index;
        attackCount++;
        
        printf("Time %.2f : B attacks E%d\n",currentTime,E[nearestIndex].index);
        fprintf(file, "Time %.2f : B attacks E%d\n", currentTime,E[nearestIndex].index);
        
        E[nearestIndex].isAlive = 0;
        currentTime = currentTime + TBq;
    }
// Remaining alive escorts can attack B once
    for (int i = 0; i < n; i++){
        if (E[i].isAlive == 1 && E[i].hasFired == 0){
            E[i].distanceFromB =CalculateDistance(B.x, B.y, E[i].x, E[i].y);
            E[i].canHitB = CanEscortHitBattleship(E[i].distanceFromB,E[i].maxAttackRange);

            if (E[i].canHitB == 1){ 
                currentImpact = currentImpact + E[i].impactPower;
                E[i].hasFired = 1;


                fprintf(file, "Escort E%d attacked B\n",E[i].index);
                fprintf(file, "Current Impact on B = %.2f%%\n",currentImpact * 100);
            }
        }
    }


    fprintf(file,"\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file,"%d. Escort Ship %d\n",i + 1,attackOrder[i]);
    }

    if (currentImpact >= 1.0)
    {
        fprintf(file,"\nBattleship Status = SUNK\n");
    }
    else
    {
        fprintf(file,"\nBattleship Status = SURVIVED\n");

        fprintf(file,"Current Impact = %.2f%%\n",currentImpact * 100);
    }
    fclose(file);
}
// PART 2-A -> PART 1-C B SIMULATION 1
void RunPart2APart1CB1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], float TBq){
    FILE *file;

    float currentTime = 0;
    float currentImpact = 0;
    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;

    file = fopen("part2a_part1c_b1.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-A Part 1-C B1 file.\n");
        return;
    }
    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }
    for (int i = 0; i < k; i++){
        B.x = pathX[i];
        B.y = pathY[i];

        fprintf(file, "\n=== PATH POINT %d ===\n",i + 1);
        while (1){
            nearestIndex = FindNearestEscort(B, E, n);
            if (nearestIndex == -1){
                break;
            }

            attackOrder[attackCount] = E[nearestIndex].index;
            attackCount++;

            fprintf(file,"Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);

            E[nearestIndex].isAlive = 0;
            currentTime = currentTime + TBq;
        }
// Alive E ships attack only once
        for (int j = 0; j < n; j++){
            if (E[j].isAlive == 1 && E[j].hasFired == 0){
                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);


                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB, E[j].maxAttackRange);


                if (E[j].canHitB == 1){
                    currentImpact = currentImpact +E[j].impactPower;
                    E[j].hasFired = 1;
                    fprintf(file,"E%d attacked B\n",E[j].index);
                    fprintf(file,"Current Impact = %.2f%%\n",currentImpact * 100);
                }
            }
        }
        if (currentImpact >= 1.0){
            fprintf(file,"\nBattleship SUNK\n");

            break;
        }
    }


    fprintf(file,"\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file,"%d. Escort Ship %d\n",i + 1,attackOrder[i]);
    }


    if (currentImpact < 1.0){
        fprintf(file,"\nB SURVIVED\n");

        fprintf(file,"Current Impact = %.2f%%\n",currentImpact * 100);
    }
    fclose(file);
}


// PART 2-A -> PART 1-C B SIMULATION 2
void RunPart2APart1CB2(BattleShip B, EscortShip E[],int n, int k,int pathX[], int pathY[],int t, float thetaMin,float TBq){
    FILE *file;

    float currentTime = 0;
    float currentImpact = 0;
    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;
    float currentFiringAngle;
    
    file = fopen("part2a_part1c_b2.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-A Part 1-C B2 file.\n");
        return;
    }

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].hasFired = 0;
    }

    for (int i = 0; i < k; i++){
        B.x = pathX[i];
        B.y = pathY[i];

        fprintf(file,"\n=== PATH POINT %d ===\n",i + 1);
        if (i < t){
            fprintf(file,"Gun Status = NORMAL\n");
        }
        else{
            fprintf(file,"Gun Status = JAMMED\n");
        }

        while (1){
            nearestIndex = FindNearestEscort(B, E, n);
            if (nearestIndex == -1){
                break;
            }
            currentFiringAngle = CalculateFiringAngle(E[nearestIndex].distanceFromB,B.maxVelocity);
            
            if (i >= t){
                if (currentFiringAngle < thetaMin){
                    currentFiringAngle = thetaMin;
                }
            }
            E[nearestIndex].firingAngleFromB = currentFiringAngle;
            attackOrder[attackCount] = E[nearestIndex].index;

            attackCount++;
            fprintf(file,"Time %.2f : B attacks E%d\n",currentTime,E[nearestIndex].index);
            fprintf(file,"Firing Angle = %.2f\n",currentFiringAngle);
            E[nearestIndex].isAlive = 0;
            currentTime = currentTime + TBq;
        }
// Alive escorts attack B only once
        for (int j = 0; j < n; j++){
            if (E[j].isAlive == 1 && E[j].hasFired == 0){
                E[j].distanceFromB = CalculateDistance(B.x, B.y,E[j].x, E[j].y);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB,E[j].maxAttackRange);

                if (E[j].canHitB == 1){
                    currentImpact =currentImpact +E[j].impactPower;
                    E[j].hasFired = 1;
                    fprintf(file,"E%d attacked B\n",E[j].index);
                    fprintf(file,"Current Impact = %.2f%%\n",currentImpact * 100);
                }
            }
        }
        if (currentImpact >= 1.0){
            fprintf(file,"\nBattleship SUNK\n");
            break;
        }
    }

    fprintf(file,"\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1,attackOrder[i]);
    }

    if (currentImpact < 1.0){
        fprintf(file,"\nBattleship SURVIVED\n");
        fprintf(file, "Current Impact = %.2f%%\n", currentImpact * 100);
    }
    fclose(file);
}

float GetEscortFiringDelay(char type, float TEA, float TEB, float TEC, float TED, float TEE){
    if (type == 'A'){
        return TEA;
    }
    else if (type == 'B'){
        return TEB;
    }
    else if (type == 'C'){
        return TEC;
    }
    else if (type == 'D'){
        return TED;
    }
    else{
        return TEE;
    }
}

// PART 2-B -> PART 1-A
// Single E hit can destroy B

void RunPart2BPart1A(BattleShip B, EscortShip E[], int n, float TBq, float TEA, float TEB, float TEC, float TED, float TEE)
{
    FILE *file;

    float currentTime = 0;
    float nextBFireTime = 0;
    float delay;

    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;
    int battleshipSunk = 0;

    file = fopen("part2b_part1a.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-B Part 1-A file.\n");
        return;
    }

    fprintf(file, "=== PART 2-B : PART 1-A ===\n\n");

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].nextFireTime = 0;
    }

    while (battleshipSunk == 0){

        // B fires
        if (currentTime >= nextBFireTime){
            nearestIndex = FindNearestEscort(B, E, n);

            if (nearestIndex != -1){
                attackOrder[attackCount] = E[nearestIndex].index;
                attackCount++;

                printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);

                E[nearestIndex].isAlive = 0;
                nextBFireTime = currentTime + TBq;
            }
        }

        // E ships fire
        for (int i = 0; i < n; i++){

            if (E[i].isAlive == 1){
                E[i].distanceFromB = CalculateDistance(B.x, B.y, E[i].x, E[i].y);
                E[i].canHitB = CanEscortHitBattleship(E[i].distanceFromB, E[i].maxAttackRange);

                if (E[i].canHitB == 1 && currentTime >= E[i].nextFireTime){
                    delay = GetEscortFiringDelay(E[i].type, TEA, TEB, TEC, TED, TEE);

                    printf("Time %.2f : E%d fires at B\n", currentTime, E[i].index);
                    fprintf(file, "Time %.2f : E%d fires at B\n", currentTime, E[i].index);

                    E[i].nextFireTime = currentTime + delay;
                    battleshipSunk = 1;

                    printf("Battleship SUNK by E%d\n", E[i].index);
                    fprintf(file, "Battleship SUNK by E%d\n", E[i].index);
                    break;
                }
            }
        }

        if (battleshipSunk == 1){
            break;
        }

        nearestIndex = FindNearestEscort(B, E, n);
        int escortCanAttack = 0;

        for (int i = 0; i < n; i++){
            if (E[i].isAlive == 1){
                E[i].distanceFromB = CalculateDistance(B.x, B.y, E[i].x, E[i].y);
                E[i].canHitB = CanEscortHitBattleship(E[i].distanceFromB, E[i].maxAttackRange);

                if (E[i].canHitB == 1){
                    escortCanAttack = 1;
                }
            }
        }

        if (nearestIndex == -1 && escortCanAttack == 0){
            break;
        }
        currentTime = currentTime + 1;
    }

    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1, attackOrder[i]);
    }

    if (battleshipSunk == 0){
        fprintf(file, "\nBattleship SURVIVED\n");
    }

    fclose(file);
}

// PART 2-B -> PART 1-B SIMULATION 1
void RunPart2BPart1BSim1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], float TBq,float TEA, float TEB, float TEC, float TED, float TEE)
{
    FILE *file;

    float currentTime = 0;
    float nextBFireTime = 0;
    float delay;

    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;
    int battleshipSunk = 0;

    file = fopen("part2b_part1b_sim1.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-B Part 1-B Simulation 1 file.\n");
        return;
    }

    fprintf(file, "=== PART 2-B : PART 1-B SIMULATION 1 ===\n\n");

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].nextFireTime = 0;
    }

    for (int i = 0; i < k; i++){

        B.x = pathX[i];
        B.y = pathY[i];

        printf("\nPath Point %d - B Position = (%d, %d)\n", i + 1, B.x, B.y);
        fprintf(file, "\n=== PATH POINT %d ===\n", i + 1);
        fprintf(file, "B Position = (%d, %d)\n", B.x, B.y);

        // B fires
        if (currentTime >= nextBFireTime){
            nearestIndex = FindNearestEscort(B, E, n);

            if (nearestIndex != -1){
                attackOrder[attackCount] = E[nearestIndex].index;
                attackCount++;

                printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);

                E[nearestIndex].isAlive = 0;
                nextBFireTime = currentTime + TBq;
            }
        }

        // E ships fire continuously
        for (int j = 0; j < n; j++){
            if (E[j].isAlive == 1){
                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB, E[j].maxAttackRange);

                if (E[j].canHitB == 1 && currentTime >= E[j].nextFireTime){
                    delay = GetEscortFiringDelay(E[j].type, TEA, TEB, TEC, TED, TEE);

                    printf("Time %.2f : E%d fires at B\n", currentTime, E[j].index);
                    fprintf(file, "Time %.2f : E%d fires at B\n", currentTime, E[j].index);

                    E[j].nextFireTime = currentTime + delay;
                    battleshipSunk = 1;

                    printf("Battleship SUNK by E%d\n", E[j].index);
                    fprintf(file, "Battleship SUNK by E%d\n", E[j].index);

                    break;
                }
            }
        }

        if (battleshipSunk == 1){
            break;
        }

        currentTime = currentTime + 1;
    }

    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1, attackOrder[i]);
    }

    if (battleshipSunk == 0){
        fprintf(file, "\nBattleship SURVIVED\n");
    }
    fclose(file);
}

// PART 2-B -> PART 1-B SIMULATION 2
// Gun jam
void RunPart2BPart1BSim2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin,float TBq, float TEA, float TEB, float TEC,float TED, float TEE)
{
    FILE *file;

    float currentTime = 0;
    float nextBFireTime = 0;
    float delay;
    float currentFiringAngle;

    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;
    int battleshipSunk = 0;

    file = fopen("part2b_part1b_sim2.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-B Part 1-B Simulation 2 file.\n");
        return;
    }

    fprintf(file, "=== PART 2-B : PART 1-B SIMULATION 2 ===\n\n");

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].nextFireTime = 0;
    }

    for (int i = 0; i < k; i++){

        B.x = pathX[i];
        B.y = pathY[i];

        printf("\nPath Point %d - B Position = (%d, %d)\n", i + 1, B.x, B.y);
        fprintf(file, "\n=== PATH POINT %d ===\n", i + 1);
        fprintf(file, "B Position = (%d, %d)\n", B.x, B.y);

        if (i < t){
            fprintf(file, "Gun Status = NORMAL\n");
        }
        else{
            fprintf(file, "Gun Status = JAMMED\n");
        }

        // B fires
        if (currentTime >= nextBFireTime){

            nearestIndex = FindNearestEscort(B, E, n);

            if (nearestIndex != -1){
                currentFiringAngle = CalculateFiringAngle(E[nearestIndex].distanceFromB, B.maxVelocity);

                if (i >= t){
                    if (currentFiringAngle < thetaMin){
                        currentFiringAngle = thetaMin;
                    }
                }

                attackOrder[attackCount] = E[nearestIndex].index;
                attackCount++;

                printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Firing Angle = %.2f\n", currentFiringAngle);

                E[nearestIndex].isAlive = 0;
                nextBFireTime = currentTime + TBq;
            }
        }
// E ships fire continuously
        for (int j = 0; j < n; j++){
            if (E[j].isAlive == 1){
                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB, E[j].maxAttackRange);

                if (E[j].canHitB == 1 && currentTime >= E[j].nextFireTime){
                    delay = GetEscortFiringDelay(E[j].type, TEA, TEB, TEC, TED, TEE);

                    printf("Time %.2f : E%d fires at B\n", currentTime, E[j].index);
                    fprintf(file, "Time %.2f : E%d fires at B\n", currentTime, E[j].index);

                    E[j].nextFireTime = currentTime + delay;
                    battleshipSunk = 1;

                    printf("Battleship SUNK by E%d\n", E[j].index);
                    fprintf(file, "Battleship SUNK by E%d\n", E[j].index);
                    break;
                }
            }
        }

        if (battleshipSunk == 1){
            break;
        }

        currentTime = currentTime + 1;
    }

    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1, attackOrder[i]);
    }

    if (battleshipSunk == 0){
        fprintf(file, "\nBattleship SURVIVED\n");
    }
    fclose(file);
}
// PART 2-B -> PART 1-C A
// Continuous E firing + cumulative impact
void RunPart2BPart1CA(BattleShip B, EscortShip E[], int n, float TBq,float TEA, float TEB, float TEC, float TED, float TEE){
    FILE *file;

    float currentTime = 0;
    float nextBFireTime = 0;
    float currentImpact = 0;
    float delay;

    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;

    file = fopen("part2b_part1c_a.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-B Part 1-C A file.\n");
        return;
    }

    fprintf(file, "=== PART 2-B : PART 1-C A ===\n\n");

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].nextFireTime = 0;
    }

    while (currentImpact < 1.0){
// B fires
        if (currentTime >= nextBFireTime){
            nearestIndex = FindNearestEscort(B, E, n);

            if (nearestIndex != -1){

                attackOrder[attackCount] = E[nearestIndex].index;
                attackCount++;

                printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);

                E[nearestIndex].isAlive = 0;
                nextBFireTime = currentTime + TBq;
            }
        }

        int escortCanAttack = 0;
// E ships fire continuously
        for (int i = 0; i < n; i++){
            if (E[i].isAlive == 1){
                E[i].distanceFromB = CalculateDistance(B.x, B.y, E[i].x, E[i].y);
                E[i].canHitB = CanEscortHitBattleship(E[i].distanceFromB, E[i].maxAttackRange);

                if (E[i].canHitB == 1){
                    escortCanAttack = 1;

                    if (currentTime >= E[i].nextFireTime){
                        delay = GetEscortFiringDelay(E[i].type, TEA, TEB, TEC, TED, TEE);
                        currentImpact = currentImpact + E[i].impactPower;

                        printf("Time %.2f : E%d attacks B\n", currentTime, E[i].index);
                        printf("Current Impact = %.2f%%\n", currentImpact * 100);

                        fprintf(file, "Time %.2f : E%d attacks B\n", currentTime, E[i].index);
                        fprintf(file, "Current Impact = %.2f%%\n", currentImpact * 100);

                        E[i].nextFireTime = currentTime + delay;

                        if (currentImpact >= 1.0){
                            break;
                        }
                    }
                }
            }
        }

        if (currentImpact >= 1.0){
            break;
        }

        nearestIndex = FindNearestEscort(B, E, n);

        if (nearestIndex == -1 && escortCanAttack == 0){
            break;
        }

        currentTime = currentTime + 1;
    }

    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1, attackOrder[i]);
    }

    if (currentImpact >= 1.0){
        fprintf(file, "\nBattleship SUNK\n");
    }
    else{
        fprintf(file, "\nBattleship SURVIVED\n");
        fprintf(file, "Final Impact = %.2f%%\n", currentImpact * 100);
    }
    fclose(file);
}
// PART 2-B -> PART 1-C B SIMULATION 1
void RunPart2BPart1CB1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], float TBq, float TEA, float TEB, float TEC, float TED, float TEE){
    FILE *file;

    float currentTime = 0;
    float nextBFireTime = 0;
    float currentImpact = 0;
    float delay;

    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;

    file = fopen("part2b_part1c_b1.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-B Part 1-C B1 file.\n");
        return;
    }

    fprintf(file, "=== PART 2-B : PART 1-C B SIMULATION 1 ===\n\n");

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].nextFireTime = 0;
    }

    for (int i = 0; i < k; i++){

        B.x = pathX[i];
        B.y = pathY[i];

        printf("\nPath Point %d - B Position = (%d, %d)\n", i + 1, B.x, B.y);
        fprintf(file, "\n=== PATH POINT %d ===\n", i + 1);
        fprintf(file, "B Position = (%d, %d)\n", B.x, B.y);

        // B fires
        if (currentTime >= nextBFireTime){
            nearestIndex = FindNearestEscort(B, E, n);

            if (nearestIndex != -1){
                attackOrder[attackCount] = E[nearestIndex].index;
                attackCount++;

                printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);

                E[nearestIndex].isAlive = 0;
                nextBFireTime = currentTime + TBq;
            }
        }
    // E ships fire continuously
        for (int j = 0; j < n; j++){
            if (E[j].isAlive == 1){
                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB, E[j].maxAttackRange);

                if (E[j].canHitB == 1 && currentTime >= E[j].nextFireTime){
                    delay = GetEscortFiringDelay(E[j].type, TEA, TEB, TEC, TED, TEE);
                    currentImpact = currentImpact + E[j].impactPower;

                    printf("Time %.2f : E%d attacks B\n", currentTime, E[j].index);
                    printf("Current Impact = %.2f%%\n", currentImpact * 100);

                    fprintf(file, "Time %.2f : E%d attacks B\n", currentTime, E[j].index);
                    fprintf(file, "Current Impact = %.2f%%\n", currentImpact * 100);

                    E[j].nextFireTime = currentTime + delay;
                }
            }
        }

        if (currentImpact >= 1.0){
            printf("Battleship SUNK\n");
            fprintf(file, "\nBattleship SUNK\n");
            break;
        }

        currentTime = currentTime + 1;
    }

    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1, attackOrder[i]);
    }

    if (currentImpact < 1.0){
        fprintf(file, "\nBattleship SURVIVED\n");
        fprintf(file, "Final Impact = %.2f%%\n", currentImpact * 100);
    }
    fclose(file);
}
// PART 2-B -> PART 1-C B SIMULATION 2
// Continuous E firing + B gun jam
void RunPart2BPart1CB2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin, float TBq, float TEA, float TEB, float TEC,float TED, float TEE){
    FILE *file;

    float currentTime = 0;
    float nextBFireTime = 0;
    float currentImpact = 0;
    float delay;
    float currentFiringAngle;

    int attackOrder[n];
    int attackCount = 0;
    int nearestIndex;

    file = fopen("part2b_part1c_b2.txt", "w");

    if (file == NULL){
        printf("Error opening Part 2-B Part 1-C B2 file.\n");
        return;
    }

    fprintf(file, "=== PART 2-B : PART 1-C B SIMULATION 2 ===\n\n");

    for (int i = 0; i < n; i++){
        E[i].isAlive = 1;
        E[i].nextFireTime = 0;
    }

    for (int i = 0; i < k; i++){

        B.x = pathX[i];
        B.y = pathY[i];

        printf("\nPath Point %d - B Position = (%d, %d)\n", i + 1, B.x, B.y);
        fprintf(file, "\n=== PATH POINT %d ===\n", i + 1);
        fprintf(file, "B Position = (%d, %d)\n", B.x, B.y);

        if (i < t){
            fprintf(file, "Gun Status = NORMAL\n");
        }
        else{
            fprintf(file, "Gun Status = JAMMED\n");
        }

        // B fires
        if (currentTime >= nextBFireTime){
            nearestIndex = FindNearestEscort(B, E, n);

            if (nearestIndex != -1){
                currentFiringAngle = CalculateFiringAngle(E[nearestIndex].distanceFromB, B.maxVelocity);

                if (i >= t){
                    if (currentFiringAngle < thetaMin){
                        currentFiringAngle = thetaMin;
                    }
                }

                attackOrder[attackCount] = E[nearestIndex].index;
                attackCount++;

                printf("Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Time %.2f : B attacks E%d\n", currentTime, E[nearestIndex].index);
                fprintf(file, "Firing Angle = %.2f\n", currentFiringAngle);

                E[nearestIndex].isAlive = 0;
                nextBFireTime = currentTime + TBq;
            }
        }

        // E ships fire continuously
        for (int j = 0; j < n; j++){

            if (E[j].isAlive == 1){
                E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y);
                E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB, E[j].maxAttackRange);

                if (E[j].canHitB == 1 && currentTime >= E[j].nextFireTime){
                    delay = GetEscortFiringDelay(E[j].type, TEA, TEB, TEC, TED, TEE);
                    currentImpact = currentImpact + E[j].impactPower;

                    printf("Time %.2f : E%d attacks B\n", currentTime, E[j].index);
                    printf("Current Impact = %.2f%%\n", currentImpact * 100);

                    fprintf(file, "Time %.2f : E%d attacks B\n", currentTime, E[j].index);
                    fprintf(file, "Current Impact = %.2f%%\n", currentImpact * 100);

                    E[j].nextFireTime = currentTime + delay;
                }
            }
        }

        if (currentImpact >= 1.0){
            printf("Battleship SUNK\n");
            fprintf(file, "\nBattleship SUNK\n");
            break;
        }

        currentTime = currentTime + 1;
    }

    fprintf(file, "\n=== ATTACK ORDER ===\n");

    for (int i = 0; i < attackCount; i++){
        fprintf(file, "%d. Escort Ship %d\n", i + 1, attackOrder[i]);
    }

    if (currentImpact < 1.0){
        fprintf(file, "\nBattleship SURVIVED\n");
        fprintf(file, "Final Impact = %.2f%%\n", currentImpact * 100);
    }

    fclose(file);
}