#ifndef BATTLE_H
#define BATTLE_H
#include "ships.h"
//prototypees
void RunPart1A(BattleShip B, EscortShip E[], int n);
void RunPart1BSimulation1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int d);
void RunPart1BSimulation2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin);
void RunPart1CSimulationA(BattleShip B, EscortShip E[], int n, int initialBX, int initialBY);
void RunPart1CSimulationB1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[]);
void RunPart1CSimulationB2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin);
int FindNearestEscort(BattleShip B, EscortShip E[], int n);
void RunPart2APart1A(BattleShip B, EscortShip E[], int n, float TBq);
void RunPart2APart1BSim1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int d, float TBq);
void RunPart2APart1BSim2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin,float TBq);
void RunPart2APart1CA(BattleShip B, EscortShip E[],int n, float TBq);
void RunPart2APart1CB1(BattleShip B, EscortShip E[],int n, int k,int pathX[], int pathY[],float TBq);
void RunPart2APart1CB2(BattleShip B, EscortShip E[],int n, int k, int pathX[], int pathY[],int t, float thetaMin,float TBq);
void RunPart2APart1BSim2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin, float TBq);
float GetEscortFiringDelay(char type, float TEA, float TEB, float TEC, float TED, float TEE);

float GetEscortFiringDelay(char type, float TEA, float TEB, float TEC, float TED, float TEE);

void RunPart2BPart1A(BattleShip B, EscortShip E[], int n, float TBq, float TEA, float TEB, float TEC, float TED, float TEE);

void RunPart2BPart1BSim1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], float TBq, float TEA, float TEB, float TEC, float TED, float TEE);

void RunPart2BPart1BSim2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin, float TBq, float TEA, float TEB, float TEC, float TED, float TEE);

void RunPart2BPart1CA(BattleShip B, EscortShip E[], int n, float TBq, float TEA, float TEB, float TEC, float TED, float TEE);

void RunPart2BPart1CB1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], float TBq, float TEA, float TEB, float TEC, float TED, float TEE);

void RunPart2BPart1CB2(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int t, float thetaMin, float TBq, float TEA, float TEB, float TEC, float TED, float TEE);

#endif