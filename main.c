#include <stdio.h>

    typedef struct {
        char type;
        int x,y;
        float maxVelocity;
    }BattleShip;

    typedef struct {
        int index;
        char type;
        int x,y;
        float minAngle;
        float maxAngle;
        float minVelocity;
        float maxVelocity;
        float impactPower;

    }EscortShip;

    int GenerateRandomCoordinate(int d);
    char GenerateRandomEscortType();
int main(){
    printf(" ADVANCED NAVAL BATTLE SIMULATOR \n");

int d,n; //assigning variables
        BattleShip B; //create a battleship variable
 //getting user inputs
    printf("Enter battlefield size: "); 
    scanf("%d",&d);
    printf("Enter the no of escort ships: ");
    scanf("%d",&n);
    printf("Enter battleship types: ");
    scanf(" %c",&B.type);
    printf("Enter battleship X position: ");
    scanf("%d",&B.x);
 	printf("Enter battleship Y position: ");
    scanf("%d",&B.y);
    printf("Enter battleship maximum shell velocity: ");
    scanf("%f",&B.maxVelocity);
//print details
    printf("battlefield size is %d x %d\n",d,d);
    printf("Number of escort ships: %d\n",n);
    printf("\n--- Battleship Details ---\n");
    printf("Type: %c\n", B.type);
    printf("Position: (%d,%d)\n", B.x, B.y);
    printf("Maximum Shell Velocity: %.2f m/s\n", B.maxVelocity);

    printf("\n--- Escortship Details ---\n");

         EscortShip E[n]; // create an array to store escort ships

        for (int i=0; i<n; i++){
            E[i].index = i+1; //set the index of the escort ship
            E[i].x = GenerateRandomCoordinate(d); //set the escort ship cordinates
            E[i].y = GenerateRandomCoordinate(d); 
            E[i].type = GenerateRandomEscortType(); //set the escort ship type
            printf("Escort ship E%d | position = (%d,%d) | Type = E%c \n",E[i].index,E[i].x,E[i].y,E[i].type);
        }

   

    return 0;
    
}
