#include "../MainInclude.h"


int ObjectiveMapID = 0;

void ResetFlag(int ThisFlag)
{
     GameFlag[ThisFlag].Position[0] = SpawnPoint[ThisFlag][0];
     GameFlag[ThisFlag].Position[1] = SpawnPoint[ThisFlag][1];
     GameFlag[ThisFlag].Position[2] = SpawnPoint[ThisFlag][2];

     GameFlag[ThisFlag].Velocity[0] = 0;
     GameFlag[ThisFlag].Velocity[1] = 0;
     GameFlag[ThisFlag].Velocity[2] = 0;

     GameFlag[ThisFlag].PlayerHolding = -1;
     GameFlag[ThisFlag].IFrames = 0;
     GameFlag[ThisFlag].RespawnTimer = 0;
     GameFlag[ThisFlag].Angle[0] = 0;
     GameFlag[ThisFlag].Angle[1] = 0;
     GameFlag[ThisFlag].Angle[2] = 0;
}


void PlacePlayerSpawn(SVector Position, int PlayerID)
{
     GlobalPlayer[PlayerID].position[0] = (float)Position[0];
     GlobalPlayer[PlayerID].position[1] = (float)Position[1] + 5;
     GlobalPlayer[PlayerID].position[2] = (float)Position[2];
     GlobalPlayer[PlayerID].direction[1] = (short)(CalcDirection(GlobalPlayer[PlayerID].position, Origin) * -1);
}

void PlaceFlagSpawn(SVector Position, int PlayerID)
{
     SpawnPoint[PlayerID][0] = (float)Position[0];
     SpawnPoint[PlayerID][1] = (float)Position[1] + 5;
     SpawnPoint[PlayerID][2] = (float)Position[2];

     ResetFlag(PlayerID);
}
void PlaceBaseSpawn(SVector Position, int PlayerID)
{
     GameBase[PlayerID].Position[0] = Position[0];
     GameBase[PlayerID].Position[1] = Position[1];
     GameBase[PlayerID].Position[2] = Position[2];     
}


void DrawGameBase(Camera* LocalCamera)
{    
     //Draw GameFlags
     objectAngle[0] = 0;    
     objectAngle[1] = 0; 
     objectAngle[2] = 0;
     for (int ThisFlag = 0; ThisFlag < FlagCount; ThisFlag++)
     {    
          DrawGeometryScale(GameBase[ThisFlag].Position, objectAngle, (int)GameBase[ThisFlag].F3D, 0.35);
     }
}

void DrawGameFlags(Camera* LocalCamera)
{
     
     //Draw GameFlags
     for (int ThisFlag = 0; ThisFlag < FlagCount; ThisFlag++)
     {
          GlobalIntA = (int)GameFlag[ThisFlag].PlayerHolding;
          GameFlag[ThisFlag].Angle[0] += (DEG1 * GameFlag[ThisFlag].AngularVel[0]);
          GameFlag[ThisFlag].Angle[1] += (DEG1 * GameFlag[ThisFlag].AngularVel[1]);
          GameFlag[ThisFlag].Angle[2] += (DEG1 * GameFlag[ThisFlag].AngularVel[2]);
          if (GlobalIntA != -1)
          {
               GameFlag[ThisFlag].Position[0] = GlobalPlayer[GlobalIntA].position[0];
               GameFlag[ThisFlag].Position[1] = GlobalPlayer[GlobalIntA].position[1] + 5;
               GameFlag[ThisFlag].Position[2] = GlobalPlayer[GlobalIntA].position[2];              
               GameFlag[ThisFlag].Velocity[0] = 0;
               GameFlag[ThisFlag].Velocity[1] = 0;
               GameFlag[ThisFlag].Velocity[2] = 0;
          }
          else
          {
               GameFlag[ThisFlag].Position[0] += GameFlag[ThisFlag].Velocity[0];
               GameFlag[ThisFlag].Position[1] += GameFlag[ThisFlag].Velocity[1];
               GameFlag[ThisFlag].Position[2] += GameFlag[ThisFlag].Velocity[2];

               

               CheckBump2((Bump*)&GameFlag[ThisFlag].BumpData, 4.0, GameFlag[ThisFlag].Position[0], GameFlag[ThisFlag].Position[1], GameFlag[ThisFlag].Position[2], GameFlag[ThisFlag].Position[0] - GameFlag[ThisFlag].Velocity[0], GameFlag[ThisFlag].Position[1] - GameFlag[ThisFlag].Velocity[1], GameFlag[ThisFlag].Position[2] - GameFlag[ThisFlag].Velocity[2] );
               ManualBump((Bump*)&GameFlag[ThisFlag].BumpData, GameFlag[ThisFlag].Position);     
               if (GameFlag[ThisFlag].BumpData.distance_xy < 0)               
               {
                    ManualBounce(GameFlag[ThisFlag].BumpData.bump_xy, GameFlag[ThisFlag].Velocity);                    
               }
               if (GameFlag[ThisFlag].BumpData.distance_yz < 0)
               {
                    ManualBounce(GameFlag[ThisFlag].BumpData.bump_yz, GameFlag[ThisFlag].Velocity);
               }
               if(GameFlag[ThisFlag].BumpData.distance_zx < 0)
               {
                    GameFlag[ThisFlag].Velocity[0] *= (1.0 -  (float)((float)GameFlag[ThisFlag].Friction / 30000.0));
                    if (GameFlag[ThisFlag].Velocity[1] < ((float)GameFlag[ThisFlag].Gravity / -250.0))
                    {
                         GameFlag[ThisFlag].Velocity[1] *= (-1.0 + (float)((float)GameFlag[ThisFlag].Bounce / 1000.0));
                    }
                    else
                    {
                         GameFlag[ThisFlag].Velocity[1] = 0;
                    }
                    
                    GameFlag[ThisFlag].Velocity[2] *= (1.0 -  (float)((float)GameFlag[ThisFlag].Friction / 30000.0));
               }
               else
               {
                    GameFlag[ThisFlag].Velocity[1] -= (float)((float)GameFlag[ThisFlag].Gravity / 1000.0);
               }
          }
                    
          DrawGeometryScale(GameFlag[ThisFlag].Position, GameFlag[ThisFlag].Angle, (int)GameFlag[ThisFlag].F3D, ((float)(GameFlag[ThisFlag].Scale / 1000.0)));
     }
}


void DropFlag(int PlayerIndex)
{
     if (Objectives[PlayerIndex].FlagHeld != -1)
     {
          GlobalIntA = (int)Objectives[PlayerIndex].FlagHeld;
          GameFlag[GlobalIntA].Position[0] = GlobalPlayer[PlayerIndex].position[0];
          GameFlag[GlobalIntA].Position[1] = GlobalPlayer[PlayerIndex].position[1] + 5;
          GameFlag[GlobalIntA].Position[2] = GlobalPlayer[PlayerIndex].position[2];

          
          GameFlag[GlobalIntA].Velocity[0] = -2 + (MakeRandomLimmit(4));
          GameFlag[GlobalIntA].Velocity[1] = (float)(GameFlag[GlobalIntA].Lift) / 1000.0;
          GameFlag[GlobalIntA].Velocity[2] = -3 + (MakeRandomLimmit(6));

          MakeAlignVector(objectVelocity,(GlobalPlayer[PlayerIndex].direction[1]));
          
          ChangeMaxSpeed((char)PlayerIndex, 60);

          GameFlag[(int)Objectives[PlayerIndex].FlagHeld].PlayerHolding = -1;
          GameFlag[(int)Objectives[PlayerIndex].FlagHeld].IFrames = 30;
          GameFlag[(int)Objectives[PlayerIndex].FlagHeld].RespawnTimer = 120;
          Objectives[PlayerIndex].FlagHeld= -1;
          Objectives[PlayerIndex].IFrames = 100;
     }       
	
}

bool CheckExecuteItem(int PlayerIndex)
{    
    if (Objectives[PlayerIndex].FlagHeld == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}