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
int main(){
    printf(" ADVANCED NAVAL BATTLE SIMULATOR \n");
int d;
int n;
        BattleShip B;
        EscortShip E[n];
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

    printf("battlefield size is %d x %d\n",d,d);
    printf("Number of escort ships: %d\n",n);
    printf("\n--- Battleship Details ---\n");
    printf("Type: %c\n", B.type);
    printf("Position: (%d,%d)\n", B.x, B.y);
    printf("Maximum Shell Velocity: %.2f m/s\n", B.maxVelocity);


    return 0;
    
}
