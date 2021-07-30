
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>
#include <sstream>
using namespace std;

void ClearScreen()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

class Plane {
    public:
        const int X_range = 80;
        const int Y_range = 80;
        char WallTile = 178;
        bool YOUAREDEAD(int X, int Y,Plane SPACE) {
            int PX = SPACE.X_range / 2;
            int PY = SPACE.Y_range / 2;
            //  87654321 123456789012345
            //  #   # ##### #   #
            //  #   # #   # #   #
            //  ##### # @ # #   #
            //    #   #   # #   #
            //    #   ##### #####
            //
            //  #     ##### ##### #####
            //  #     #   # #     #
            //  #     #   # ##### #####
            //  #     #   #     # #
            //  ##### ##### ##### #####

            if (Y == PY + 2) {
                if (X == PX - 8 || X == PX - 4 || X == PX + 4 || X == PX + 8 || (X >= PX - 2 && X <= PX + 2)) {
                    return true;
                }
            }else if(Y == PY + 1) {
                if (X == PX - 8 || X == PX - 4 || X == PX + 4 || X == PX + 8 || X == PX - 2 || X == PX + 2) {
                    return true;
                }
            }
            else if (Y == PY) {
                if ((X >= PX - 8 && X <= PX - 4) || X == PX + 4 || X == PX + 8 || X == PX - 2 || X == PX + 2) {
                    return true;
                }
            }
            else if (Y == PY - 1) {
                if (X == PX - 6 || X == PX + 4 || X == PX + 8 || X == PX - 2 || X == PX + 2) {
                    return true;
                }
            }
            else if (Y == PY - 2) {
                if (X == PX - 6 || (X >= PX + 4 && X <= PX + 8) || (X >= PX - 2 && X <= PX + 2)) {
                    return true;
                }
            }
            else if (Y == PY - 4) {
                if (X == PX - 8 || (X >= PX - 2 && X <= PX + 2) || (X >= PX + 4 && X <= PX + 8) || (X >= PX + 10 && X <= PX + 14)) {
                    return true;
                }
            }
            else if (Y == PY - 5) {
                if (X == PX - 8 || X == PX - 2 || X == PX + 2 || X == PX + 4 || X == PX + 10) {
                    return true;
                }
            }
            else if (Y == PY - 6) {
                if (X == PX - 8 || X == PX - 2 || X == PX + 2 || (X >= PX + 4 && X <= PX + 8) || (X >= PX + 10 && X <= PX + 14)) {
                    return true;
                }
            }
            else if (Y == PY - 7) {
                if (X == PX - 8 || X == PX - 2 || X == PX + 2 || X == PX + 8 || X == PX + 10) {
                    return true;
                }
            }
            else if (Y == PY - 8) {
                if ((X >= PX - 8 && X <= PX - 4) || (X >= PX - 2 && X <= PX + 2) || (X >= PX + 4 && X <= PX + 8) || (X >= PX + 10 && X <= PX + 14)) {
                    return true;
                }
            }

            return false;

        }
        
};

class Player {
        
    public:
        double X;
        double Y;
        
        double XSpeed;
        double MaxHp = 400;
        double HP = MaxHp;

        double YSpeed;
        double LaserX[21] = {};
        double LaserY[21] = {};
        double LaserDMG = 2;
        int LaserCount = 20;
        double LaserSpeed;
        int LaserIndex = 0;
        bool StopShooting = false;
        
        Player(double X1, double Y1, double Speed1, double Speed2, double Speed3) {
            X = X1;
            Y = Y1;
            XSpeed = Speed1;
            YSpeed = Speed2;
            LaserSpeed = Speed3;
        }

        void LaserDEFAULT(Player &PLAYER) {
            for (int i = 0; i <= LaserCount; i++) {
                PLAYER.LaserX[i] = 100;
                PLAYER.LaserY[i] = 100;
            }
        }
        void SetLaser(Player &PLAYER) {
            PLAYER.LaserX[PLAYER.LaserIndex] = floor(PLAYER.X);
            PLAYER.LaserY[PLAYER.LaserIndex] = floor(PLAYER.Y) + 2;
        }
        void UpdateLaser(Player &PLAYER) {
            for (int i = 1; i <= PLAYER.LaserCount; i++) {
                PLAYER.LaserY[i] += PLAYER.LaserSpeed;
            }
        }
        void LaserMaxRange(Player &PLAYER,int Range) {
            for (int i = 1; i <= PLAYER.LaserCount; i++) {
                if (PLAYER.LaserY[i] > Range) {
                    PLAYER.LaserY[i] = 100;
                }
            }
        }
};

class Enemy {
    public:
        string EnemyType;
        //
        // Common (ShootNothing slow) 5 hit
        //
        // UnCommon (FireMissile)  7 hit
        //
        // Rare (zigzag move ) 10 hit
        //
        // Boss                    30 hit
        //
        //
        //
        //
        //
        //
        double HP;
        double X;
        double Y;
        double CommonSpeedX = 0;
        double CommonSpeedY = 0.9;
        double CommonBodyDamage = 10;
        int CommonScoreReward = 10;
        double UnCommonSpeedX = 0;
        double UnCommonSpeedY = 0.95;
        double UnCommonBodyDamage = 10;
        int UncommonScoreReward = 15;
        double MissileX = 100;
        double MissileY = 100;
        double MissileSpeedY = 2;
        double MissileSpeedX = 0.3;
        double MissileDMG = 15;
        int MissileLeft = 2;
        int MissileExplosionRange = 1;
        bool MissileDestroy = true;
        double RareSpeedX = 1;
        double RareSpeedY = 0.45;
        double RareBodyDamage = 25;
        int RareScoreReward = 30;
        string MoveDirection = "LEFT";
        int CommonHp = 4;
        int UnCommonHp = 7;
        double RareHp = 9;
        double RareLaserResistant = 0.5;
        int ExplosionRange = 1;
        bool Destroy = false;
        void SetEnemyType(Enemy &ENEMY) {
            int Random_num1 = (rand() % 99) + 1;
            if (Random_num1 <= 60) {
                ENEMY.EnemyType = "COMMON";
                ENEMY.HP = CommonHp;
            }
            else if (Random_num1 <= 90) {
                ENEMY.EnemyType = "UNCOMMON";
                ENEMY.HP = UnCommonHp;
            }
            else {
                ENEMY.EnemyType = "RARE";
                ENEMY.HP = RareHp;
            }
        }
        void SetMissile(Enemy &ENEMY) {
            int EX = ceil(ENEMY.X);
            int EY = ceil(ENEMY.Y);
            //
            //     _     _
            //    | \_^_/ |
            //    | _   _ |
            //    @/ | | \@
            //       | |
            //       \%/ 
            switch (rand() % 2)
            {
            case 0:
                ENEMY.MissileX = EX - 4;
                ENEMY.MissileY = EY + 2;
                break;
            case 1:
                ENEMY.MissileX = EX + 4;
                ENEMY.MissileY = EY + 2;
                break;
            }
        }
};

class Boss {
    public:
        int SpawnTime = 120;
        int WarningTime = 40;
        bool MainDestroy = true;

        double SpeedX;
        double SpeedY;
        double MainX = 20;
        double MainY = 30;
        
        double BossSpawnX = 40;
        double BossSpawnY = 100;

        double BossDefaultX = 40;
        double BossDefaultY = 65;
        bool ReturnToDefault = false;
        int BossScoreReward = 500;
        bool BossRetreat = false;

        ////////////////////////////////////////// cannon - laser

        int VectorYtoCannonBarrel = -2;
        int VectorXtoLeftCannonBarrel = -7;
        int VectorXtoRightCannonBarrel = 7;
        double LaserX[21];
        double LaserY[21];
        double LaserAngle[21];
        int LaserQuadrant[21];
        int LaserIndex = 1;
        int LaserCount = 20;
        int LaserRange = -10;
        double LaserDMG = 20;
        double LaserSpeedMultiplyer = 1.25;
        string MoveDirection = "RIGHT";

        void SetLaser(Boss &BOSS,double X,double Y) {

            BOSS.LaserX[BOSS.LaserIndex] = floor(X);
            BOSS.LaserY[BOSS.LaserIndex] = floor(Y);

        }

        void UpdateLaser(Boss &BOSS) {

            for (int i = 1; i <= BOSS.LaserCount; i++) {

                if (BOSS.LaserQuadrant[i] == 1) {
                    BOSS.LaserX[i] += BOSS.LaserSpeedMultiplyer * cos(BOSS.LaserAngle[i]);
                    BOSS.LaserY[i] += BOSS.LaserSpeedMultiplyer * sin(BOSS.LaserAngle[i]);
                }
                else if (BOSS.LaserQuadrant[i] == 2) {
                    BOSS.LaserX[i] -= BOSS.LaserSpeedMultiplyer * cos(BOSS.LaserAngle[i]);
                    BOSS.LaserY[i] += BOSS.LaserSpeedMultiplyer * sin(BOSS.LaserAngle[i]);
                }
                else if (BOSS.LaserQuadrant[i] == 3) {
                    BOSS.LaserX[i] -= BOSS.LaserSpeedMultiplyer * cos(BOSS.LaserAngle[i]);
                    BOSS.LaserY[i] -= BOSS.LaserSpeedMultiplyer * sin(BOSS.LaserAngle[i]);
                }
                else if (BOSS.LaserQuadrant[i] == 4) {
                    BOSS.LaserX[i] += BOSS.LaserSpeedMultiplyer * cos(BOSS.LaserAngle[i]);
                    BOSS.LaserY[i] -= BOSS.LaserSpeedMultiplyer * sin(BOSS.LaserAngle[i]);
                }

            }

        }

        void LaserMaxRange(Boss &BOSS, int Range) {

            for (int i = 1; i <= BOSS.LaserCount; i++) {
                if (BOSS.LaserY[i] < Range) {
                    BOSS.LaserY[i] = 3000;
                }
            }

        }

        void LaserDefault(Boss &BOSS) {
            for (int i = 1; i <= LaserCount; i++) {
                BOSS.LaserX[i] = 3000;
                BOSS.LaserY[i] = 3000;
                BOSS.LaserAngle[i] = 1;
                BOSS.LaserQuadrant[i] = 1;
            }
        }

        double GetAngle(Boss &BOSS,Player PLAYER,double Xorigin,double Yorigin) {
            double Pi = 3.14159265359;
            if ((Xorigin - PLAYER.X) == 0) {
                return Pi / 2;
            }
            else {
                return atan(abs((Yorigin - PLAYER.Y) / (Xorigin - PLAYER.X)));
            }
        }

        int GetQuadrant(Boss &BOSS, Player PLAYER, double Xorigin, double Yorigin) {
            if ((Yorigin - PLAYER.Y) >= 0 && (Xorigin - PLAYER.X) >= 0) {
                return 3;
            }
            if ((Yorigin - PLAYER.Y) >= 0 && (Xorigin - PLAYER.X) < 0) {
                return 4;
            }
            if ((Yorigin - PLAYER.Y) < 0 && (Xorigin - PLAYER.X) < 0) {
                return 1;
            }
            if ((Yorigin - PLAYER.Y) < 0 && (Xorigin - PLAYER.X) >= 0) {
                return 2;
            }
        }

        double LeftCannonX;
        double LeftCannonY;
        double LeftCannonHP = 50;
        double LeftCannonFullHP = 50;
        bool LeftCannonDestroy = true;
        bool LeftCannonHit = false;


        double RightCannonX;
        double RightCannonY;
        double RightCannonHP = 50;
        double RightCannonFullHP = 50;
        bool RightCannonDestroy = true;
        bool RightCannonHit = false;

        ////////////////////////////////////////// cannon - laser

        ///////////////////////////////////////// wing - missile

        double MissileX[31];
        double MissileY[31];
        int MissileIndex = 1;
        int MissileCount = 30;
        double MissileSpeedX = 0.4;
        double MissileSpeedY = 0.75;
        double MissileDMG = 20;

        void SetMissile(Boss& BOSS, double X, double Y) {
            BOSS.MissileX[MissileIndex] = X;
            BOSS.MissileY[MissileIndex] = Y;
        }

        void UpdateMissile(Boss& BOSS,Player PLAYER) {
            for (int i = 1; i <= MissileCount; i++) {
                if (floor(BOSS.MissileX[i]) < floor(PLAYER.X)) {
                    BOSS.MissileX[i] += BOSS.MissileSpeedX;
                }
                else if (floor(BOSS.MissileX[i]) > floor(PLAYER.X)) {
                    BOSS.MissileX[i] -= BOSS.MissileSpeedX;
                }
                BOSS.MissileY[i] -= BOSS.MissileSpeedY;
            }
        }

        void MissileDefault(Boss& BOSS) {
            for (int i = 1; i <= MissileCount; i++) {
                BOSS.MissileX[i] = -3000;
                BOSS.MissileY[i] = -3000;
            }
        }


        double LeftUpperWingX;
        double LeftUpperWingY;
        double LeftUpperWingHP = 50;
        double LeftUpperWingFullHP = 50;
        bool LeftUpperWingDestroy = true;
        bool LeftUpperWingHit = false;


        double RightUpperWingX;
        double RightUpperWingY;
        double RightUpperWingHP = 50;
        double RightUpperFullWingHP = 50;
        bool RightUpperWingDestroy = true;
        bool RightUpperWingHit = true;


        ///////////////////////////////////////// wing - missile

        ///////////////////////////////////////// Engine - superlaser
        double EngineX;
        double EngineY;
        double EngineHP = 55;
        double EngineFullHP = 55;
        bool EngineDestroy = true;
        bool FireSuperLaser = false;
        double SpeedWhileFiringSuperLaser = 1.2;
        double SuperLaserDMG = 1.5;
        bool EngineHit = true;
        ///////////////////////////////////////// Engine - superlaser

        int VectorYtoEngine = 4;
        int VectorYtoWing = 4;
        int VectorYtoCannon = 2;
        int VectorXtoLeftCannon = -10;
        int VectorXtoRightCannon = 10;
        int VectorXtoLeftWing = -13;
        int VectorXtoRightWing = 13;

        string BossAttackType;
        bool IsBossAttacking = false;

        int LaserAttackTime = 0;
        int EndLaserAttackTime = 100;

        int MissileAttackTime = 0;
        int EndMissileAttackTime = 100;

        void SetBodyPosition(Boss &BOSS) {

            BOSS.EngineX = BOSS.MainX;
            BOSS.EngineY = BOSS.MainY + VectorYtoEngine;

            BOSS.LeftCannonX = BOSS.MainX + VectorXtoLeftCannon;
            BOSS.LeftCannonY = BOSS.MainY + VectorYtoCannon;

            BOSS.RightCannonX = BOSS.MainX + VectorXtoRightCannon;
            BOSS.RightCannonY = BOSS.MainY + VectorYtoCannon;

            BOSS.LeftUpperWingX = BOSS.MainX + VectorXtoLeftWing;
            BOSS.LeftUpperWingY = BOSS.MainY + VectorYtoWing;

            BOSS.RightUpperWingX = BOSS.MainX + VectorXtoRightWing;
            BOSS.RightUpperWingY = BOSS.MainY + VectorYtoWing;
        }
};

////////////////////////////////////////////////////////////////// X Y function



bool PlayerHitbox(int X,int Y,Player PLAYER) {
    //
    //        /$\
    //       /| |\
    //      /  x  \
    //      \_____/   
    
    if (Y == floor(PLAYER.Y)) {
        if (X >= floor(PLAYER.X) - 1 && X <= floor(PLAYER.X) + 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == floor(PLAYER.Y) - 1) {
        if (X >= floor(PLAYER.X) - 2 && X <= floor(PLAYER.X) + 2) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == floor(PLAYER.Y) - 2) {
        if (X >= floor(PLAYER.X) - 3 && X <= floor(PLAYER.X) + 3) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == floor(PLAYER.Y) - 3) {
        if (X >= floor(PLAYER.X) - 3 && X <= floor(PLAYER.X) + 3) {
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}

int PlayerTexture(int X, int Y, Player PLAYER) {

    if (Y == floor(PLAYER.Y)) {
        if (X == floor(PLAYER.X)) {
            return 186;
        }
        else if (X == floor(PLAYER.X) + 1) {
            return 92;
        }
        else if (X == floor(PLAYER.X) - 1) {
            return 47;
        }
    }
    else if (Y == floor(PLAYER.Y) - 1) {
        if (X == floor(PLAYER.X)) {
            return 186;
        }
        else if (X == floor(PLAYER.X) + 1 || X == floor(PLAYER.X) - 1) {
            return 124;
        }
        else if (X == floor(PLAYER.X) - 2) {
            return 47;
        }
        else if (X == floor(PLAYER.X) + 2) {
            return 92;
        }
    }
    else if (Y == floor(PLAYER.Y) - 2) {
        if (X == floor(PLAYER.X)) {
            return 30;
        }
        else if (X == floor(PLAYER.X) - 3) {
            return 47;
        }
        else if (X == floor(PLAYER.X) + 3) {
            return 92;
        }
        else {
            return 32;
        }
    }
    else if (Y == floor(PLAYER.Y) - 3) {
        if (X == floor(PLAYER.X) - 3) {
            return 92;
        }
        else if (X == floor(PLAYER.X) + 3) {
            return 47;
        }
        else {
            return 95;
        }
    }
    
}

bool PlayerTrail1(int X, int Y, Player PLAYER) {
    // -4
    if (Y == floor(PLAYER.Y) - 4) {
        if (X >= floor(PLAYER.X) - 2 && X <= floor(PLAYER.X) + 2) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool PlayerTrail2(int X, int Y, Player PLAYER) {
    if (Y == floor(PLAYER.Y) - 5) {
        if (X >= floor(PLAYER.X) - 2 && X <= floor(PLAYER.X) + 2) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool PlayerTrail3(int X, int Y, Player PLAYER) {
    if (Y == floor(PLAYER.Y) - 6) {
        if (X >= floor(PLAYER.X) - 2 && X <= floor(PLAYER.X) + 2) {
            return true;
        }
        else {
            return !true;
        }
    }
    return !true;
}

bool PlayerLaserPosition(int X, int Y, Player PLAYER) {
    for (int i = 1; i <= PLAYER.LaserCount; i++) {
        if (X == floor(PLAYER.LaserX[i]) && Y == floor(PLAYER.LaserY[i])) {
            return true;
        }
    }
    return false;
}

int ReturnLaserIndex(int X, int Y, Player PLAYER) {
    for (int i = 1; i <= PLAYER.LaserCount; i++) {
        if (X == floor(PLAYER.LaserX[i]) && Y == floor(PLAYER.LaserY[i])) {
            return i;
        }
    }
}



/////////////////////////////////////////////////////////////////// BOSS
          // 
          //  1234567890123456789012345678901234567890
          //  0       01        12        23        34
          // ▓                                        ▓
          // ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
          // ▓      /\                       /\       ▓ //10
          // ▓     / |  /\_   #  #  #   _/\  | \      ▓ //9    
          // ▓    /   \/  \\_/ \/ \/ \_//  \/   \     ▓ //8   1 
          // ▓  _/##@##\__/ 0\_/\*/\_/0 \__/##@##\_   ▓ //7     
          // ▓ //\     #\ \__ 0\\_//0 __/ /#     /\\  ▓ //6   -1 
          // ▓//  \_###@/\   \ 0\_/0 /   /\@###_/  \\ ▓ //5   -2 
          // ▓\\  / \__/ /    \_/^\_/    \ \__/ \  // ▓ //4   
          // ▓ \\/    \_ \      \^/      / _/    \//  ▓ //3
          // ▓  \|      \/\             /\/      |/   ▓ //2
          // ▓           \/             \/            ▓ //1
          //  9876543210987654321 1234567890123456789
          //  1111111111                   1111111111
          //  1234567890123456789012345678901234567890
          //  0       01        12        23        34
          // ▓                                        ▓
          // ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
          // ▓      /\                       /\       ▓ //10
          // ▓     / |  /\_   #  #  #   _/\  | \      ▓ //9    
          // ▓    /   \/  \\_/ \/ \/ \_//  \/   \     ▓ //8   1 
          // ▓  _/\_@_/\__/ 0\_/\*/\_/0 \__/\_@_/\_   ▓ //7     
          // ▓ //\   __/\ \__ 0\\_//0 __/ /\__   /\\  ▓ //6   -1 
          // ▓//  \_/  \/\   \ 0\_/0 /   /\/  \_/  \\ ▓ //5   -2 
          // ▓\\  / \__/ /    \_/^\_/    \ \__/ \  // ▓ //4   
          // ▓ \\/    \_ \      \^/      / _/    \//  ▓ //3
          // ▓  \|      \/\             /\/      |/   ▓ //2
          // ▓           \/             \/            ▓ //1
          //  9876543210987654321 1234567890123456789
          //  1111111111                   1111111111
int BossMainTexture(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.MainX);
    int BY = ceil(BOSS.MainY);
    if (Y == BY - 1) {
        if (X == BX - 16 || X == BX + 16) {
            return 124;
        }
        else if (X == BX - 17) {
            return 92;
        }
        else if (X == BX + 17) {
            return 47;
        }
    }
    else if (Y == BY) {
        if (X == BX) {
            return 31;
        }
        else if (X == BX - 1 || X == BX + 16 || X == BX - 18 || X == BX - 17) {
            return 92;
        }
        else {
            return 47;
        }
    }
    else if (Y == BY + 1) {
        if (X == BX) {
            return 31;
        }
        else if (X == BX - 2 || X == BX + 2) {
            return 95;
        }
        else if (X == BX + 1 || X == BX - 3 || X == BX + 15 || X == BX - 19 || X == BX - 18) {
            return 92;
        }
        else if (X == BX - 1 || X == BX + 3 || X == BX + 18 || X == BX + 19 || X == BX - 15) {
            return 47;
        }
        else {
            return 32;
        }
    }
    else if (Y == BY + 2) {
        if (X == BX - 2 || X == BX + 2) {
            return 4;
        }
        else if (X == BX - 14 || X == BX + 14) {
            return 95;
        }
        else if (X == BX + 4 || X == BX + 15 || X == BX - 18 || X == BX - 19) {
            return 47;
        }
        else if (X == BX - 15 || X == BX - 4 || X == BX + 18 || X == BX + 19) {
            return 92;
        }
        else {
            return 32;
        }
    }
    else if (Y == BY + 3) {
        if (X == BX + 3 || X == BX - 3) {
            return 4;
        }
        else if (X == BX - 6 || X == BX - 5 || X == BX + 5 || X == BX + 6 || X == BX - 11 || X == BX - 12 || X == BX + 11 || X == BX + 12) {
            return 95;
        }
        else if (X == BX + 7 || X == BX + 16 || X == BX - 18 || X == BX - 17) {
            return 47;
        }
        else if (X == BX - 7 || X == BX - 16 || X == BX + 18 || X == BX + 17) {
            return 92;
        }
        else {
            return 32;
        }
    }
    else if (Y == BY + 4) {
        if (X == BX + 5 || X == BX - 5) {
            return 4;
        }
        else if (X == BX + 6 || X == BX - 6) {
            return 32;
        }
        else if (X == BX - 10 || X == BX + 7 || X == BX + 16) {
            return 92;
        }
        else if (X == BX + 10 || X == BX - 7 || X == BX - 16) {
            return 47;
        }
        else {
            return 95;
        }
    }
    else if (Y == BY + 5) {
        if (X == BX + 5 || X == BX - 5) {
            return 95;
        }
        else if (X == BX - 10 || X == BX + 6 || X == BX + 7) {
            return 47;
        }
        else if (X == BX + 10 || X == BX - 6 || X == BX - 7) {
            return 92;
        }
        else {
            return 32;
        }
    }
    else if (Y == BY + 6) {
        if (X == BX + 7 || X == BX - 7) {
            return 95;
        }
        else if (X == BX - 8 || X == BX + 9) {
            return 92;
        }
        else if (X == BX + 8 || X == BX - 9) {
            return 47;
        }
    }
}

int BossLeftUpperWingTexture(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.LeftUpperWingX);
    int BY = ceil(BOSS.LeftUpperWingY);

    if (Y == BY) {
        if (X == BX - 2) {
            return 92;
        }
        else if (X == BX + 2) {
            return 47;
        }
        else {
            return 95;
        }
    }
    else if (Y == BY + 1) {
        if (X == BX - 2) {
            return 47;
        }
        else if (X == BX + 2) {
            return 92;
        }
        else {
            return 32;
        }
    }
    else if (Y == BY + 2) {
        if (X == BX) {
            return 32;
        }
        else if (X == BX - 1) {
            return 47;
        }
        else {
            return 124;
        }
    }
    else if (Y == BY + 3) {
        if (X == BX) {
            return 47;
        }
        else {
            return 92;
        }
    }
}
bool BossLeftUpperWingHPbar(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.LeftUpperWingX);
    int BY = ceil(BOSS.LeftUpperWingY);

    if (Y == BY + 5) {
        if (X >= BX - 3 && X <= BX + 3) {
            return true;
        }
    }
    return false;

}
bool BossLeftUpperWingHPbarColor(int X, Boss BOSS) {
    int BX = ceil(BOSS.LeftUpperWingX);
    int HpDisplay = ceil((BOSS.LeftUpperWingHP / BOSS.LeftUpperWingFullHP) * 7);
    if (X - BX + 4 <= HpDisplay) {
        return true;
    }
    return false;
}

int BossRightUpperWingTexture(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.RightUpperWingX);
    int BY = ceil(BOSS.RightUpperWingY);
    if (Y == BY) {
        if (X == BX - 2) {
            return 92;
        }
        else if (X == BX + 2) {
            return 47;
        }
        else {
            return 95;
        }
    }
    else if (Y == BY + 1) {
        if (X == BX - 2) {
            return 47;
        }
        else if (X == BX + 2) {
            return 92;
        }
        else {
            return 32;
        }
    }
    else if (Y == BY + 2) {
        if (X == BX - 1) {
            return 124;
        }
        else if(X == BX){
            return 32;
        }
        else {
            return 92;
        }
    }
    else if (Y == BY + 3) {
        if (X == BX) {
            return 92;
        }
        else {
            return 47;
        }
    }
}
bool BossRightUpperWingHPbar(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.RightUpperWingX);
    int BY = ceil(BOSS.RightUpperWingY);

    if (Y == BY + 5) {
        if (X >= BX - 3 && X <= BX + 3) {
            return true;
        }
    }
    return false;
}
bool BossRightUpperWingHPbarColor(int X, Boss BOSS) {
    int BX = ceil(BOSS.RightUpperWingX);
    int HpDisplay = ceil((BOSS.RightUpperWingHP / BOSS.RightUpperFullWingHP) * 7);
    if (X - BX + 4 <= HpDisplay) {
        return true;
    }
    return false;
}

int BossEngineTexture(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.EngineX);
    int BY = ceil(BOSS.EngineY);
    if (Y == BY + 1) {
        if (X == BX - 1 || X == BX - 4 || X == BX + 2) {
            return 47;
        }
        else if (X == BX + 1 || X == BX + 4 || X == BX - 2) {
            return 92;
        }
        else {
            return 240;
        }
    }
    else if (Y == BY) {
        if (X == BX - 1 || X == BX - 4 || X == BX + 2) {
            return 92;
        }
        else if (X == BX + 1 || X == BX + 4 || X == BX - 2) {
            return 47;
        }
        else {
            return 95;
        }
    }
    else if (Y == BY - 1) {
        if (X == BX) {
            return 89;
        }
        else if (X == BX - 1 || X == BX - 2) {
            return 92;
        }
        else if (X == BX + 1 || X == BX + 2) {
            return 47;
        }
    }
    else if (Y == BY - 2) {
        if (X == BX - 1) {
            return 92;
        }
        else if (X == BX + 1) {
            return 47;
        }
        else {
            return 95;
        }
    }
}
bool BossEngineHPbar(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.EngineX);
    int BY = ceil(BOSS.EngineY);

    if (Y == BY + 3) {
        if (X >= BX - 3 && X <= BX + 3) {
            return true;
        }
    }
    return false;

}
bool BossEngineHPbarColor(int X, Boss BOSS) {
    int BX = ceil(BOSS.EngineX);
    int HpDisplay = ceil((BOSS.EngineHP / BOSS.EngineFullHP) * 7);
    if (X - BX + 4 <= HpDisplay) {
        return true;
    }
    return false;
}

int BossLeftCannonTexture(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.LeftCannonX);
    int BY = ceil(BOSS.LeftCannonY);
    if (Y == BY + 1) {
        if (X == BX) {
            return 47;
        }
        else {
            return 92;
        }
    }
    else if (Y == BY) {
        if (X == BX - 1 || X == BX - 2) {
            return 32;
        }
        else if (X == BX || X == BX + 2) {
            return 92;
        }
        else {
            return 47;
        }
    }
    else if (Y == BY - 1) {
        if (X == BX - 1 || X == BX - 2) {
            return 95;
        }
        else if (X == BX + 1) {
            return 32;
        }
        else if (X == BX - 3) {
            return 92;
        }
        else {
            return 47;
        }
    }
    else if (Y == BY - 2) {
        if (X == BX) {
            return 95;
        }
        else if (X == BX + 1) {
            return 32;
        }
        else {
            return 92;
        }
    }
    else if (Y == BY - 3) {
        if (X == BX + 2) {
            return 47;
        }
        else {
            return 92;
        }
    }
    else if (Y == BY - 4) {
        if (X == BX + 2) {
            return 92;
        }
        else {
            return 47;
        }
    }
}
bool BossLeftCannonHPbar(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.LeftCannonX) - 5;
    int BY = ceil(BOSS.LeftCannonY) - 3;

    if (Y == BY - 2) {
        if (X >= BX - 3 && X <= BX + 3) {
            return true;
        }
    }
    return false;


}
bool BossLeftCannonHPbarColor(int X, Boss BOSS) {
    int BX = ceil(BOSS.LeftCannonX) - 5;
    int HpDisplay = ceil((BOSS.LeftCannonHP / BOSS.LeftCannonFullHP) * 7);
    if (X - BX + 4 <= HpDisplay) {
        return true;
    }
    return false;
}

int BossRightCannonTexture(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.RightCannonX);
    int BY = ceil(BOSS.RightCannonY);
    if (Y == BY + 1) {
        if (X == BX) {
            return 92;
        }
        else if (X == BX - 1) {
            return 47;
        }
    }
    else if (Y == BY) {
        if (X == BX - 1 || X == BX + 3) {
            return 92;
        }
        else if (X >= BX + 1 && X <= BX + 2) {
            return 32;
        }
        else {
            return 47;
        }
    }
    else if (Y == BY - 1) {
        if (X == BX - 1) {
            return 32;
        }
        else if (X == BX + 3) {
            return 47;
        }
        else if (X == BX + 1 || X == BX + 2) {
            return 95;
        }
        else {
            return 92;
        }
    }
    else if (Y == BY - 2) {
        if (X == BX) {
            return 95;
        }
        else if (X == BX - 1) {
            return 32;
        }
        else {
            return 47;
        }
    }
    else if (Y == BY - 3) {
        if (X == BX - 2) {
            return 92;
        }
        else {
            return 47;
        }
    }
    else if (Y == BY - 4) {
        if (X == BX - 2) {
            return 47;
        }
        else {
            return 92;
        }
    }
}
bool BossRightCannonHPbar(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.RightCannonX) + 5;
    int BY = ceil(BOSS.RightCannonY) - 3;

    if (Y == BY - 2) {
        if (X >= BX - 3 && X <= BX + 3) {
            return true;
        }
    }
    return false;

}
bool BossRightCannonHPbarColor(int X, Boss BOSS) {
    int BX = ceil(BOSS.RightCannonX) + 5;
    int HpDisplay = ceil((BOSS.RightCannonHP / BOSS.RightCannonFullHP) * 7);
    if (X - BX + 4 <= HpDisplay) {
        return true;
    }
    return false;
}

bool BossRightUpperWingHitbox(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.RightUpperWingX);
    int BY = ceil(BOSS.RightUpperWingY);
    if (Y == BY) {
        if (X >= BX - 2 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY + 1) {
        if (X >= BX - 2 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY + 2) {
        if (X >= BX - 1 && X <= BX + 1) {
            return true;
        }
    }
    else if (Y == BY + 3) {
        if (X >= BX - 1 && X <= BX) {
            return true;
        }
    }
    return false;
}
bool BossLeftUpperWingHitbox(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.LeftUpperWingX);
    int BY = ceil(BOSS.LeftUpperWingY);
    if (Y == BY) {
        if (X >= BX - 2 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY + 1) {
        if (X >= BX - 2 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY + 2) {
        if (X >= BX - 1 && X <= BX + 1) {
            return true;
        }
    }
    else if (Y == BY + 3) {
        if (X >= BX && X <= BX + 1) {
            return true;
        }
    }
    return false;
}
bool BossRightCannonHitbox(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.RightCannonX);
    int BY = ceil(BOSS.RightCannonY);
    if (Y == BY + 1) {
        if (X == BX - 1 || X == BX) {
            return true;
        }
    }
    else if (Y == BY) {
        if (X >= BX - 2 && X <= BX + 3) {
            return true;
        }
    }
    else if (Y == BY - 1) {
        if (X >= BX - 2 && X <= BX + 3) {
            return true;
        }
    }
    else if (Y == BY - 2) {
        if (X >= BX - 2 && X <= BX + 1) {
            return true;
        }
    }
    else if (Y == BY - 3) {
        if (X >= BX - 3 && X <= BX - 1) {
            return true;
        }
    }
    else if (Y == BY - 4) {
        if (X >= BX - 3 && X <= BX - 2) {
            return true;
        }
    }
    return false;
}
bool BossLeftCannonHitbox(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.LeftCannonX);
    int BY = ceil(BOSS.LeftCannonY);
    if (Y == BY + 1) {
        if (X == BX + 1 || X == BX) {
            return true;
        }
    }
    else if (Y == BY) {
        if (X >= BX - 3 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY - 1) {
        if (X >= BX - 3 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY - 2) {
        if (X >= BX - 1 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY - 3) {
        if (X >= BX + 1 && X <= BX + 3) {
            return true;
        }
    }
    else if (Y == BY - 4) {
        if (X >= BX + 2 && X <= BX + 3) {
            return true;
        }
    }
    return false;
}
bool BossEngineHitbox(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.EngineX);
    int BY = ceil(BOSS.EngineY);
    if (Y == BY + 1) {
        if (X >= BX - 4 && X <= BX + 4) {
            return true;
        }
    }
    else if (Y == BY) {
        if (X >= BX - 4 && X <= BX + 4) {
            return true;
        }
    }
    else if (Y == BY - 1) {
        if (X >= BX - 2 && X <= BX + 2) {
            return true;
        }
    }
    else if (Y == BY - 2) {
        if (X >= BX - 1 && X <= BX + 1) {
            return true;
        }
    }
    return false;
}
bool BossMainHitbox(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.MainX);
    int BY = ceil(BOSS.MainY);
    if (Y == BY - 1) {
        if (X == BX + 16 || X == BX + 17 || X == BX - 16 || X == BX - 17) {
            return true;
        }
    }
    else if (Y == BY) {
        if ((X >= BX + 16 && X <= BX + 18) || (X <= BX - 16 && X >= BX - 18) || (X >= BX - 1 && X <= BX + 1)) {
            return true;
        }
    }
    else if (Y == BY + 1) {
        if ((X >= BX + 15 && X <= BX + 19) || (X <= BX - 15 && X >= BX - 19) || (X >= BX - 3 && X <= BX + 3) ){
            return true;
        }
    }
    else if (Y == BY + 2) {
        if ((X >= BX - 19 && X <= BX -  14) || (X <= BX + 19 && X >= BX + 14) || (X >= BX - 4 && X <= BX + 4 && !(X >= BX - 1 && X <= BX + 1))) {
            return true;
        }
    }
    else if (Y == BY + 3) {
        if ((X >= BX - 18 && X <= BX - 11) || (X <= BX + 18 && X >= BX + 11) || (X >= BX - 7 && X <= BX + 7 && !(X >= BX - 2 && X <= BX + 2))) {
            return true;
        }
    }
    else if (Y == BY + 4) {
        if (X == BX - 17 || X == BX - 16 || X == BX + 16 || X == BX + 17 || (X >= BX - 10 && X <= BX + 10 && !(X >= BX - 4 && X <= BX + 4))) {
            return true;
        }
    }
    else if (Y == BY + 5) {
        if ((X >= BX - 10 && X <= BX + 10) && !(X >= BX - 4 && X <= BX + 4)) {
            return true;
        }
    }
    else if (Y == BY + 6) {
        if ((X >= BX - 9 && X <= BX - 7) || (X >= BX + 7 && X <= BX + 9)) {
            return true;
        }
    }
    return false;
}

bool BossSuperLaserHitbox(int X, int Y, Boss BOSS) {
    int BX = ceil(BOSS.MainX);
    int BY = ceil(BOSS.MainY);
    if (Y < BY) {
        if (X >= BX - 1 && X <= BX + 1) {
            return true;
        }
    }
    return false;
}

bool SuperLaserColor(int X, Boss BOSS) {
    int BX = ceil(BOSS.MainX);
    if (X == BX) {
        return true;
    }
    else {
        return false;
    }
}

bool BossMissilePosition(int X, int Y, Boss BOSS) {
    //
    //
    //  \^^/
    //   ||
    //   ||
    //   @/
    //
    for (int i = 1; i <= BOSS.MissileCount; i++) {
        int MX = floor(BOSS.MissileX[i]);
        int MY = floor(BOSS.MissileY[i]);
        if (Y == MY || Y == MY + 1 || Y == MY + 2) {
            if (X == MX || X == MX + 1) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (Y == MY + 3) {
            if (X >= MX - 1 && X <= MX + 2) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

int BossMissileTexture(int X, int Y, Boss BOSS) {
    for (int i = 1; i <= BOSS.MissileCount; i++) {
        int MX = floor(BOSS.MissileX[i]);
        int MY = floor(BOSS.MissileY[i]);
        if (Y == MY) {
            if (X == MX) {
                return 92;
            }
            else {
                return 47;
            }
        }
        else if (Y == MY + 1 || Y == MY + 2) {
            if (X == MX || X == MX + 1) {
                return 124;
            }
        }
        else if (Y == MY + 3) {
            if (X  == MX - 1 || X == MX) {
                return 92;
            }
            else {
                return 47;
            }
        }
    }
}

bool BossLaserPosition(int X, int Y, Boss BOSS) {
    for (int i = 1; i <= BOSS.LaserCount; i++) {
        if (X == floor(BOSS.LaserX[i]) && Y == floor(BOSS.LaserY[i])) {
            return true;
        }
    }
    return false;
}

int ReturnBossLaserIndex(int X, int Y, Boss BOSS) {
    for (int i = 1; i <= BOSS.LaserCount; i++) {
        if (X == floor(BOSS.LaserX[i]) && Y == floor(BOSS.LaserY[i])) {
            return i;
        }
    }
}

int ReturnBossMissileIndex(int X, int Y, Boss BOSS) {
    for (int i = 1; i <= BOSS.MissileCount; i++) {
        int MX = floor(BOSS.MissileX[i]);
        int MY = floor(BOSS.MissileY[i]);
        if (Y == MY || Y == MY + 1 || Y == MY + 2) {
            if (X == MX || X == MX + 1) {
                return i;
            }
        }
        else if (Y == MY + 3) {
            if (X >= MX - 1 && X <= MX + 2) {
                return i;
            }
        }
    }
}


/////////////////////////////////////////////////////////////////// BOSS



/////////////////////////////////////////////////////////////// COMMON
bool CommonEnemyHitbox(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //
    //
    //   
    //   8888
    //   \ @/
    //    \/
    //
    //
    //
    if (Y == EY + 1) {
        if (X >= EX - 2 && X <= EX + 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY) {
        if (X >= EX - 2 && X <= EX + 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY - 1) {
        if (X >= EX - 1 && X <= EX) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;

}

int CommonEnemyTexture(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //
    //
    //   
    //   8888
    //   \ @/
    //    \/
    //
    //
    //
    if (Y == EY + 1) {
        return 31;
    }
    else if (Y == EY) {
        if (X == EX - 2) {
            return 92;
        }
        else if(X == EX + 1) {
            return 47;
        }
        else {
            return 32;
        }
    }
    else if (Y == EY - 1) {
        if (X == EX - 1) {
            return 92;
        }
        else if (X = EX) {
            return 47;
        }
        else {
            return 32;
        }
    }
}

bool CommonEnemyHpBar(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //
    //
    //   
    //   8888
    //   \ @/
    //    \/
    //   ____ HP BAR char is 22
    //
    //
    if (Y == EY - 2) {
        if (X >= EX - 2 && X <= EX + 1) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool CommonEnemyHpColor(int X, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    //   8888
    //   \ @/
    //    \/
    //   ____ HP BAR char is 22
    //   $ = EX - 2
    //
    if (X - EX + 3 <= ENEMY.HP) {
        return true;
    }
    return false;
}
/////////////////////////////////////////////////////////////// COMMON

/////////////////////////////////////////////////////////////// UNCOMMON
bool UnCommonEnemyHitbox(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //     _     _
    //    | \_^_/ |
    //    | _   _ |
    //    \/ | | \/
    //       | |
    //       \_/ 
    
    if (Y == EY || Y == EY + 1) {
        if (X >= EX - 1 && X <= EX + 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY + 2) {
        if ((X >= EX - 1 && X <= EX + 1) || (X >= EX -4 && X <= EX - 3) || (X <= EX + 4 && X >= EX + 3) ) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY + 3) {
        if (X >= EX - 4 && X <= EX + 4) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY + 4) {
        if (X >= EX - 4 && X <= EX + 4) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY + 5) {
        if (X == EX - 3 || X == EX + 3) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

int UnCommonEnemyTexture(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //     _     _
    //    | \_^_/ |
    //    | _   _ |
    //    \/ | | \/
    //       | |
    //       \_/ 
    if (Y == EY) {
        if (X == EX - 1) {
            return 92;
        }
        else if (X == EX + 1) {
            return 47;
        }
        else {
            return 95;
        }
    }
    else if (Y == EY + 1) {
        if (X == EX + 1 || X == EX - 1) {
            return 124;
        }
        else {
            return 32;
        }
    }
    else if (Y == EY + 2) {
        if (X == EX + 1 || X == EX - 1) {
            return 124;
        }
        else if(X == EX - 3 || X == EX + 4) {
            return 47;
        }
        else if (X == EX + 3 || X == EX - 4) {
            return 92;
        }
        else {
            return 31;
        }
    }
    else if (Y == EY + 3) {
        if (X == EX - 2 || X == EX + 2) {
            return 95;
        }
        else if (X == EX - 4 || X == EX + 4) {
            return 124;
        }
        else {
            return 32;
        }
    }
    else if (Y == EY + 4) {
        if (X >= EX - 1 && X <= EX + 1) {
            return 95;
        }
        else if(X == EX - 4 || X == EX + 4) {
            return 124;
        }
        else if (X == EX - 2) {
            return 92;
        }
        else if (X == EX + 2) {
            return 47;
        }
        else {
            return 32;
        }
    }
    else if (Y == EY + 5) {
        return 95;
    }
}

bool UnCommonEnemyHpBar(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //     _     _
    //    | \_^_/ |
    //    | _   _ |
    //    \/ | | \/
    //       | |
    //       \_/ 
    //     _______
    if (Y == EY - 1) {
        if (X >= EX - 3 && X <= EX + 3) {
            return true;
        }
    }
    return false;
}

bool UnCommonEnemyHpColor(int X, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    //
    //     _     _
    //    | \_^_/ |
    //    | _   _ |
    //    \/ | | \/
    //       | |
    //       \$/ 
    //     _______
    if (X - EX + 4 <= ENEMY.HP) {
        return true;
    }
    return false;
}

bool MissileHitbox(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.MissileX);
    int EY = ceil(ENEMY.MissileY);
    //
    // ###
    //  #
    //  $
    if (Y == EY) {
        if (X == EX) {
            return true;
        }
    }
    else if (Y == EY + 1) {
        if (X == EX) {
            return true;
        }
    }
    else if (Y == EY + 2) {
        if (X >= EX - 1 && X <= EX + 1) {
            return true;
        }
    }
    return false;
}

int MissileTexture(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.MissileX);
    int EY = ceil(ENEMY.MissileY);
    //
    // ###
    //  #
    //  Y
    //
    if (Y == EY) {
        if (X == EX) {
            return 31;
        }
    }
    else if (Y == EY + 1) {
        if (X == EX) {
            return 186;
        }
    }
    else if (Y == EY + 2) {
        if (X == EX) {
            return 186;
        }
        else if (X == EX - 1) {
            return 92;
        }
        else if (X == EX + 1) {
            return 47;
        }
    }
}
/////////////////////////////////////////////////////////////// UNCOMMON

/////////////////////////////////////////////////////////////// RARE

bool RareEnemyHitbox(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //    
    //   ##  _  ##
    //  ##  UUU  ##
    //  ##kkk$KKK##
    //  ##  UUU  ##
    //   ##     ##
    // 
    //
    if (Y == EY + 2) {
        if (X == EX - 4 || X == EX - 3 || X == EX || X == EX + 3 || X == EX + 4) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY + 1 || Y == EY - 1) {
        if (X >= EX - 5 && X <= EX + 5 && !(X == EX - 3 || X == EX - 2 || X == EX + 2 || X == EX + 3)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY) {
        if (X >= EX - 5 && X <= EX + 5) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (Y == EY - 2) {
        if (X == EX - 4 || X == EX - 3 || X == EX + 3 || X == EX + 4) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

int RareEnemyTexture(int X, int Y, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //    
    //   ##  _  ##
    //  ##  U U  ##
    //  |#kkk$KKK#|
    //  ##  UUU  ##
    //   ##     ##
    // 
    //
    if (Y == EY + 2) {
        if (X == EX) {
            return 95;
        }
        else if (X == EX - 4 || X == EX - 3) {
            return 47;
        }
        else if (X == EX + 4 || X == EX + 3) {
            return 92;
        }
    }
    else if (Y == EY + 1) {
        if (X == EX - 5 || X == EX - 4 || X == EX - 1) {
            return 47;
        }
        else if (X == EX + 5 || X == EX + 4 || X == EX + 1) {
            return 92;
        }
        else {
            return 32;
        }
    }
    else if (Y == EY) {
        if (X == EX - 5 || X == EX + 5) {
            return 124;
        }
        else if (X == EX) {
            return 31;
        }
        else if (X == EX - 1 || X == EX + 4) {
            return 185;
        }
        else if (X == EX + 1 || X == EX - 4) {
            return 204;
        }
        else {
            return 205;
        }
    }
    else if (Y == EY - 1) {
        if (X == EX - 5 || X == EX - 4 || X == EX - 1) {
            return 92;
        }
        else if (X == EX + 5 || X == EX + 4 || X == EX + 1) {
            return 47;
        }
        else {
            return 95;
        }
    }
    else if (Y == EY - 2) {
        if (X == EX - 4 || X == EX - 3) {
            return 92;
        }
        else if (X == EX + 4 || X == EX + 3) {
            return 47;
        }
    }
}

bool RareEnemyHpBar(int X,int Y,Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    //
    //    
    //   ##  _  ##
    //  ##  UUU  ##
    //  ##kkk$KKK##
    //  ##  UUU  ##
    //   ##     ##
    // 
    //
    if (Y == EY - 3) {
        if (X >= EX - 4 && X <= EX + 4) {
            return true;
        }
        return false;
    }
    return false;
}

bool RareEnemyHpColor(int X, Enemy ENEMY) {
    int EX = ceil(ENEMY.X);
    //
    //    
    //   ##  _  ##
    //  ##  UUU  ##
    //  ##kkk$KKK##
    //  ##  UUU  ##
    //   ##     ##
    //   ____i____
    if (X - EX + 5 <= ENEMY.HP) {
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////// RARE

/////////////////////////////////////////////////////////////// Explode Animation

bool EnemyExplosion(int X, int Y,Enemy ENEMY,int Range) {
    int EX = ceil(ENEMY.X);
    int EY = ceil(ENEMY.Y);
    if (pow(abs(EX - X), 2) + pow(abs(EY - Y), 2) >= pow(Range - 1, 2) && pow(abs(EX - X), 2) + pow(abs(EY - Y), 2) <= pow(Range + 1, 2)) {
        return true;
    }
    return false;
}

bool MissileExplosion(int X, int Y, Enemy ENEMY, int Range) {
    int EX = ceil(ENEMY.MissileX);
    int EY = ceil(ENEMY.MissileY);
    if (pow(abs(EX - X), 2) + pow(abs(EY - Y), 2) >= pow(Range - 1, 2) && pow(abs(EX - X), 2) + pow(abs(EY - Y), 2) <= pow(Range + 1, 2)) {
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////// Explode Animation

////////////////////////////////////////////////////////////////// LASER hit detection

bool LaserHitEnemy(int X,int Y, Player PLAYER,Enemy ENEMY) {
    if (ENEMY.EnemyType == "COMMON" && CommonEnemyHitbox(X, Y, ENEMY) && PlayerLaserPosition(X,Y,PLAYER)) {
        return true;
    }
    else if (ENEMY.EnemyType == "UNCOMMON" && UnCommonEnemyHitbox(X, Y, ENEMY) && PlayerLaserPosition(X, Y, PLAYER)) {
        return true;
    }
    else if (ENEMY.EnemyType == "RARE" && RareEnemyHitbox(X, Y, ENEMY) && PlayerLaserPosition(X, Y, PLAYER)) {
        return true;
    }
    return false;
}

int ReturnLaserHitIndex(int X, int Y, Player PLAYER, Enemy ENEMY) {
    if (ENEMY.EnemyType == "COMMON" && CommonEnemyHitbox(X, Y, ENEMY)) {
        return ReturnLaserIndex(X, Y, PLAYER);
    }
    else if (ENEMY.EnemyType == "UNCOMMON" && UnCommonEnemyHitbox(X, Y, ENEMY)) {
        return ReturnLaserIndex(X, Y, PLAYER);
    }
    else if (ENEMY.EnemyType == "RARE" && RareEnemyHitbox(X, Y, ENEMY)) {
        return ReturnLaserIndex(X, Y, PLAYER);
    }
}
/// for enemy

// for boss

bool LaserHitBoss(int X, int Y, Player PLAYER, bool BossPartToHit) {
    if (BossPartToHit) {
        if (PlayerLaserPosition(X, Y, PLAYER)) {
            return true;
        }
    }
    return false;
}

int ReturnLaserHitBoss(int X, int Y, Player PLAYER) {
    return ReturnLaserIndex(X,Y,PLAYER);
}

////////////////////////////////////////////////////////////////// LASER hit detection

////////////////////////////////////////////////////////////////// PLAYER hit ENEMY

bool PlayerCollideEnemy(int X, int Y, Player PLAYER, Enemy ENEMY) {
    if (ENEMY.EnemyType == "COMMON" && PlayerHitbox(X, Y, PLAYER) && CommonEnemyHitbox(X,Y,ENEMY)) {
        return true;
    }
    else if (ENEMY.EnemyType == "UNCOMMON" && PlayerHitbox(X, Y, PLAYER) && UnCommonEnemyHitbox(X, Y, ENEMY)) {
        return true;
    }
    else if (ENEMY.EnemyType == "RARE" && PlayerHitbox(X, Y, PLAYER) && RareEnemyHitbox(X, Y, ENEMY)) {
        return true;
    }
    return false;
    
}

////////////////////////////////////////////////////////////////// PLAYER hit ENEMY

////////////////////////////////////////////////////////////////// PLAYER hit MISSILE

bool PlayerHitMissile(int X, int Y, Player PLAYER, Enemy ENEMY) {
    if (MissileHitbox(X, Y, ENEMY) && PlayerHitbox(X, Y, PLAYER)) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////// PLAYER hit MISSILE

///////////////////////////////////////////////////////////////// PLAYER hit BOSS laser

bool PlayerHitBossLaser(int X, int Y, Player PLAYER, Boss BOSS) {
    if (BossLaserPosition(X, Y, BOSS) && PlayerHitbox(X, Y, PLAYER)) {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////// PLAYER hit BOSS laser

///////////////////////////////////////////////////////////////// PLAYER hit BOSS Missile

bool PlayerHitBossMissile(int X, int Y, Player PLAYER, Boss BOSS) {
    if (BossMissilePosition(X, Y, BOSS) && PlayerHitbox(X, Y, PLAYER)) {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////// PLAYER hit BOSS Missile

///////////////////////////////////////////////////////////////// PLAYER hit BOSS SUPER LASER

bool PlayerHitBossSuperLaser(int X, int Y, Player PLAYER, Boss BOSS) {

    if (BossSuperLaserHitbox(X, Y, BOSS) && PlayerHitbox(X, Y, PLAYER) && BOSS.FireSuperLaser) {
        return true;
    }
    return false;

}

///////////////////////////////////////////////////////////////// PLAYER hit BOSS SUPER LASER

////////////////////////////////////////////////////////////////// X Y function

void Endline(int term) {
    for (int i = 0; i <= term; i++) {
        cout << endl;
    }
}

char DrawTile(char tile) {
    return tile;
}

int main()//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    stringstream LINE;
    srand(time(NULL));
    Plane SPACE;
    Enemy ENEMY1;
    Enemy ENEMY2;
    Boss BOSS;
    Player PLAYER(SPACE.X_range / 2, 10, 3,2,3);
    int GameTime = 0;
    int GameScore = 0;

    //////////// SET OBJECT

    PLAYER.LaserDEFAULT(PLAYER);
    PLAYER.LaserIndex = 0;

    ENEMY1.X = (rand() % (SPACE.X_range - 10)) + 5;
    ENEMY1.Y = SPACE.Y_range + 14;
    ENEMY2.X = (rand() % (SPACE.X_range - 10)) + 5;
    ENEMY2.Y = SPACE.Y_range + 6;

    ENEMY1.ExplosionRange = ENEMY2.ExplosionRange = ENEMY1.MissileExplosionRange = ENEMY2.MissileExplosionRange = 3;
    
    ENEMY1.SetEnemyType(ENEMY1);
    ENEMY2.SetEnemyType(ENEMY2);

    if (ENEMY1.EnemyType == "RARE") {
        if (ENEMY1.X >= SPACE.X_range / 2) {
            ENEMY1.MoveDirection = "LEFT";
        }
        else {
            ENEMY1.MoveDirection = "RIGHT";
        }
    }
    if (ENEMY2.EnemyType == "RARE") {
        if (ENEMY2.X >= SPACE.X_range / 2) {
            ENEMY2.MoveDirection = "LEFT";
        }
        else {
            ENEMY2.MoveDirection = "RIGHT";
        }
    }

    BOSS.MainX = 120;
    BOSS.MainY = 120;
    BOSS.SetBodyPosition(BOSS);
    BOSS.LaserDefault(BOSS);
    BOSS.MissileDefault(BOSS);

    //////////// SET OBJECT ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (true) {//////////////////////////////////////////////////////////////////////////////////////// GAME LOOP

        ClearScreen();

        /// input

        if (_kbhit()) {

            char ch = _getch();
            switch (ch)
            {

            case 'w':
            case 'W':
                PLAYER.Y += PLAYER.YSpeed;
                break;
            case 's':
            case 'S':
                PLAYER.Y -= PLAYER.YSpeed;
                break;
            case 'a':
            case 'A':
                PLAYER.X -= PLAYER.XSpeed;
                break;
            case 'D':
            case 'd':
                PLAYER.X += PLAYER.XSpeed;
                break;
            case 'F':
            case 'f':
                PLAYER.StopShooting = !PLAYER.StopShooting;
                break;
            }
            

        }
        

        /// input

        // Physic

        ///////////////////////////////////////////////////////////////////// BOSS MOVEMENT

        if (GameTime == BOSS.SpawnTime && BOSS.MainDestroy) { //////////// spawn boss
            BOSS.EngineHP = BOSS.EngineFullHP;
            BOSS.RightUpperWingHP = BOSS.RightUpperFullWingHP;
            BOSS.LeftUpperWingHP = BOSS.LeftUpperWingFullHP;
            BOSS.RightCannonHP = BOSS.RightCannonFullHP;
            BOSS.LeftCannonHP = BOSS.LeftCannonFullHP;
            BOSS.ReturnToDefault = false;
            BOSS.MainDestroy = false;
            BOSS.EngineDestroy = false;
            BOSS.RightCannonDestroy = false;
            BOSS.LeftCannonDestroy = false;
            BOSS.RightUpperWingDestroy = false;
            BOSS.LeftUpperWingDestroy = false;
            BOSS.IsBossAttacking = false;
            BOSS.MainX = BOSS.BossSpawnX;
            BOSS.MainY = BOSS.BossSpawnY;
            if (rand() % 2 == 0) {
                BOSS.MoveDirection = "RIGHT";
            }
            else {
                BOSS.MoveDirection = "LEFT";
            }
            BOSS.SetBodyPosition(BOSS);
        } //////////// spawn boss

        if (!BOSS.ReturnToDefault) {
            if (floor(BOSS.MainX) < BOSS.BossDefaultX) {
                BOSS.MainX += 1;
            }
            else if (floor(BOSS.MainX) > BOSS.BossDefaultX) {
                BOSS.MainX -= 1;
            }
            else if (floor(BOSS.MainX) == BOSS.BossDefaultX) {
                BOSS.MainX = BOSS.BossDefaultX;
            }
            if (floor(BOSS.MainY) < BOSS.BossDefaultY) {
                BOSS.MainY += 1;
            }
            else if (floor(BOSS.MainY) > BOSS.BossDefaultY) {
                BOSS.MainY -= 1;
            }
            else if (floor(BOSS.MainY) == BOSS.BossDefaultY) {
                BOSS.MainY = BOSS.BossDefaultY;
            }
            BOSS.SetBodyPosition(BOSS);
            if (BOSS.MainX == BOSS.BossDefaultX && BOSS.MainY == BOSS.BossDefaultY) {
                BOSS.ReturnToDefault = true;
            }
        }

        if (!BOSS.MainDestroy && !BOSS.IsBossAttacking && BOSS.ReturnToDefault) {
            BOSS.LaserAttackTime = 0;
            BOSS.MissileAttackTime = 0;
            //rand() % 3
            switch (rand() % 3) {////////////////////////////////////////////
                case 0:
                    if (BOSS.LeftCannonDestroy && BOSS.RightCannonDestroy) {
                        BOSS.BossAttackType = "MISSILE";
                        break;
                    }
                    BOSS.BossAttackType = "LASER";
                    BOSS.IsBossAttacking = true;
                    break;
                case 1:
                    if (BOSS.LeftUpperWingDestroy && BOSS.RightUpperWingDestroy) {
                        BOSS.BossAttackType = "SUPERLASER";
                        break;
                    }
                    BOSS.BossAttackType = "MISSILE";
                    BOSS.IsBossAttacking = true;
                    break;
                case 2:
                    BOSS.BossAttackType = "SUPERLASER";
                    BOSS.IsBossAttacking = true;
                    break;

            }
        }

        if (BOSS.BossAttackType == "LASER" && BOSS.IsBossAttacking) {

            if (GameTime % 20 == 0) {
                
                if (BOSS.LeftCannonDestroy || BOSS.RightCannonDestroy ) {
                    if (!BOSS.LeftCannonDestroy) {
                        BOSS.LaserAngle[BOSS.LaserIndex] = BOSS.GetAngle(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoLeftCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.LaserQuadrant[BOSS.LaserIndex] = BOSS.GetQuadrant(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoLeftCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.SetLaser(BOSS, BOSS.MainX + BOSS.VectorXtoLeftCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                    }
                    if (!BOSS.RightCannonDestroy) {
                        BOSS.LaserAngle[BOSS.LaserIndex] = BOSS.GetAngle(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoRightCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.LaserQuadrant[BOSS.LaserIndex] = BOSS.GetQuadrant(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoRightCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.SetLaser(BOSS, BOSS.MainX + BOSS.VectorXtoRightCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                    }
                }
                else {
                    if (rand() % 2) {
                        BOSS.LaserAngle[BOSS.LaserIndex] = BOSS.GetAngle(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoLeftCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.LaserQuadrant[BOSS.LaserIndex] = BOSS.GetQuadrant(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoLeftCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.SetLaser(BOSS, BOSS.MainX + BOSS.VectorXtoLeftCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                    }
                    else {
                        BOSS.LaserAngle[BOSS.LaserIndex] = BOSS.GetAngle(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoRightCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.LaserQuadrant[BOSS.LaserIndex] = BOSS.GetQuadrant(BOSS, PLAYER, BOSS.MainX + BOSS.VectorXtoRightCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                        BOSS.SetLaser(BOSS, BOSS.MainX + BOSS.VectorXtoRightCannonBarrel, BOSS.MainY + BOSS.VectorYtoCannonBarrel);
                    }
                }
                BOSS.LaserIndex += 1;
                if (BOSS.LaserIndex > BOSS.LaserCount) {
                    BOSS.LaserIndex = 1;
                }
            }
        
            if (BOSS.MoveDirection == "RIGHT") {
                BOSS.MainX += 1;
            }
            else if (BOSS.MoveDirection == "LEFT") {
                BOSS.MainX -= 1;
            }

            if (BOSS.MainX >= SPACE.X_range - BOSS.VectorXtoRightWing) {
                BOSS.MainX = SPACE.X_range - BOSS.VectorXtoRightWing - 1;
                BOSS.MoveDirection = "LEFT";
            }
            if (BOSS.MainX <= 1 - BOSS.VectorXtoLeftWing) {
                BOSS.MainX = 1 - BOSS.VectorXtoLeftWing + 1;
                BOSS.MoveDirection = "RIGHT";
            }

            BOSS.SetBodyPosition(BOSS);
            BOSS.LaserAttackTime += 1;
            if (BOSS.LaserAttackTime == BOSS.EndLaserAttackTime) {
                BOSS.IsBossAttacking = false;
                BOSS.ReturnToDefault = false;
            }
        }
        else if (BOSS.BossAttackType == "MISSILE" && BOSS.IsBossAttacking) {

            if (GameTime % 15 == 0) {

                if (BOSS.LeftUpperWingDestroy || BOSS.RightUpperWingDestroy) {
                    if (!BOSS.LeftUpperWingDestroy) {
                        BOSS.SetMissile(BOSS, BOSS.MainX + BOSS.VectorXtoLeftWing, BOSS.MainY + BOSS.VectorYtoWing);
                    }
                    else if(!BOSS.RightUpperWingDestroy){
                        BOSS.SetMissile(BOSS, BOSS.MainX + BOSS.VectorXtoRightWing, BOSS.MainY + BOSS.VectorYtoWing);
                    }
                }
                else {
                    if (rand() % 2 == 0) {
                        BOSS.SetMissile(BOSS, BOSS.MainX + BOSS.VectorXtoLeftWing, BOSS.MainY + BOSS.VectorYtoWing);
                    }
                    else {
                        BOSS.SetMissile(BOSS, BOSS.MainX + BOSS.VectorXtoRightWing, BOSS.MainY + BOSS.VectorYtoWing);
                    }
                }
                BOSS.MissileIndex += 1;
                if (BOSS.MissileIndex > BOSS.MissileCount) {
                    BOSS.MissileIndex = 1;
                }

            }

            if (BOSS.MoveDirection == "RIGHT") {
                BOSS.MainX += 1;
            }
            else if (BOSS.MoveDirection == "LEFT") {
                BOSS.MainX -= 1;
            }

            if (BOSS.MainX >= SPACE.X_range - BOSS.VectorXtoRightWing) {
                BOSS.MainX = SPACE.X_range - BOSS.VectorXtoRightWing - 1;
                BOSS.MoveDirection = "LEFT";
            }
            if (BOSS.MainX <= 1 - BOSS.VectorXtoLeftWing) {
                BOSS.MainX = 1 - BOSS.VectorXtoLeftWing + 1;
                BOSS.MoveDirection = "RIGHT";
            }

            BOSS.SetBodyPosition(BOSS);
            BOSS.MissileAttackTime += 1;
            if (BOSS.MissileAttackTime == BOSS.EndMissileAttackTime) {
                BOSS.IsBossAttacking = false;
                BOSS.ReturnToDefault = false;
            }
        }
        else if (BOSS.BossAttackType == "SUPERLASER" && BOSS.IsBossAttacking) {



            if(!BOSS.FireSuperLaser){


                if (BOSS.MoveDirection == "RIGHT") {

                    if (floor(BOSS.MainX) < SPACE.X_range - BOSS.VectorXtoRightWing + 12) {
                        BOSS.MainX += 1;
                    }
                    if (floor(BOSS.MainY) < SPACE.Y_range - 5) {
                        BOSS.MainY += 0.3;
                    }
                    if (floor(BOSS.MainX) >= SPACE.X_range - BOSS.VectorXtoRightWing + 11 && floor(BOSS.MainY) >= SPACE.Y_range - 5) {
                        BOSS.FireSuperLaser = true;
                        BOSS.MoveDirection = "LEFT";
                    }

                }

                if (BOSS.MoveDirection == "LEFT") {

                    if (floor(BOSS.MainX) > 1 - BOSS.VectorXtoLeftWing - 12) {
                        BOSS.MainX -= 1;
                    }
                    if (floor(BOSS.MainY) < SPACE.Y_range - 5) {
                        BOSS.MainY += 0.3;
                    }
                    if (floor(BOSS.MainX) <= 1 - BOSS.VectorXtoLeftWing - 11 && floor(BOSS.MainY) >= SPACE.Y_range - 5) {
                        BOSS.FireSuperLaser = true;
                        BOSS.MoveDirection = "RIGHT";
                    }

                }
            }
            if (BOSS.FireSuperLaser) {
                if (BOSS.MoveDirection == "RIGHT") {
                    BOSS.MainX += BOSS.SpeedWhileFiringSuperLaser;
                    if (floor(BOSS.MainX) >= SPACE.X_range - BOSS.VectorXtoRightWing) {
                        BOSS.IsBossAttacking = false;
                        BOSS.ReturnToDefault = false;
                        BOSS.FireSuperLaser = false;
                    }
                    
                }
                if (BOSS.MoveDirection == "LEFT") {
                    BOSS.MainX -= BOSS.SpeedWhileFiringSuperLaser;
                    if (floor(BOSS.MainX) <= 1 - BOSS.VectorXtoLeftWing) {
                        BOSS.IsBossAttacking = false;
                        BOSS.ReturnToDefault = false;
                        BOSS.FireSuperLaser = false;
                    }
                }
            }
            BOSS.SetBodyPosition(BOSS);

        }

        ///////////// laser

        BOSS.UpdateLaser(BOSS);
        BOSS.LaserMaxRange(BOSS, BOSS.LaserRange);
        
        ///////////// laser

        //////////// missile

        BOSS.UpdateMissile(BOSS,PLAYER);

        /////////// missile

        ///////////////////////////////////////////////////////////////////// BOSS MOVEMENT

        /////////////////////////////////////////////////////////////// dont go off the wall
        if (floor(PLAYER.X) < 4) {
            PLAYER.X = 4;
        }
        if (floor(PLAYER.X) > SPACE.X_range - 3) {
            PLAYER.X = SPACE.X_range - 3;
        }
        if (floor(PLAYER.Y) < 5) {
            PLAYER.Y = 5;
        }
        if (floor(PLAYER.Y) > SPACE.Y_range - 1) {
            PLAYER.Y = SPACE.Y_range - 1;
        }
        /////////////////////////////////////////////////////////////// dont go off the wall
        
        ///////////////////////////// Shoot LASER
        if (GameTime % 2 == 1 && !PLAYER.StopShooting) {
            PLAYER.LaserIndex += 1;
            if (PLAYER.LaserIndex > 20) {
                PLAYER.LaserIndex = 1;
            }
            PLAYER.SetLaser(PLAYER);
        }
        ///////////////////////////// Shoot LASER

        //////////////////////// update laser
        PLAYER.UpdateLaser(PLAYER);
        PLAYER.LaserMaxRange(PLAYER, SPACE.Y_range);
        //////////////////////// update laser

        //////////////////////// update enemy1
        if (ENEMY1.EnemyType == "COMMON" && !ENEMY1.Destroy) {
            ENEMY1.Y -= ENEMY1.CommonSpeedY;
        }
        if (ENEMY1.EnemyType == "UNCOMMON" && !ENEMY1.Destroy) {
            ENEMY1.Y -= ENEMY1.UnCommonSpeedY;
        }
        if (ENEMY1.EnemyType == "RARE" && !ENEMY1.Destroy) {
            ENEMY1.Y -= ENEMY1.RareSpeedY;
            if (ENEMY1.MoveDirection == "LEFT") {
                ENEMY1.X -= ENEMY1.RareSpeedX;
            }
            else if (ENEMY1.MoveDirection == "RIGHT") {
                ENEMY1.X += ENEMY1.RareSpeedX;
            }
            if (ENEMY1.X >= SPACE.X_range) {
                ENEMY1.MoveDirection = "LEFT";
            }
            if (ENEMY1.X <= 1) {
                ENEMY1.MoveDirection = "RIGHT";
            }
        }
        //////////////////////// update enemy1
        
        //////////////////////// update enemy2
        if (ENEMY2.EnemyType == "COMMON" && !ENEMY2.Destroy) {
            ENEMY2.Y -= ENEMY2.CommonSpeedY;
        }
        if (ENEMY2.EnemyType == "UNCOMMON" && !ENEMY2.Destroy) {
            ENEMY2.Y -= ENEMY2.UnCommonSpeedY;
        }
        if (ENEMY2.EnemyType == "RARE" && !ENEMY2.Destroy) {
            ENEMY2.Y -= ENEMY2.RareSpeedY;
            if (ENEMY2.MoveDirection == "LEFT") {
                ENEMY2.X -= ENEMY1.RareSpeedX;
            }
            else if (ENEMY2.MoveDirection == "RIGHT") {
                ENEMY2.X += ENEMY1.RareSpeedX;
            }
            if (ENEMY2.X >= SPACE.X_range) {
                ENEMY2.MoveDirection = "LEFT";
            }
            if (ENEMY2.X <= 1) {
                ENEMY2.MoveDirection = "RIGHT";
            }
        }
        //////////////////////// update enemy2

        //////////////////////// ENEMY reset
        if (ENEMY1.Y < -7 && BOSS.MainDestroy) {
            ENEMY1.SetEnemyType(ENEMY1);
            ENEMY1.X = (rand() % (SPACE.X_range - 10)) + 5;
            ENEMY1.Y = SPACE.Y_range + 6;
            ENEMY1.Destroy = false;
            ENEMY1.ExplosionRange = 1;
            ENEMY1.MissileLeft = 2;
            if (ENEMY1.EnemyType == "RARE") {
                if (ENEMY1.X >= SPACE.X_range / 2) {
                    ENEMY1.MoveDirection = "LEFT";
                }
                else {
                    ENEMY1.MoveDirection = "RIGHT";
                }
            }
            if (ENEMY2.EnemyType == "RARE") {
                if (ENEMY2.X >= SPACE.X_range / 2) {
                    ENEMY2.MoveDirection = "LEFT";
                }
                else {
                    ENEMY2.MoveDirection = "RIGHT";
                }
            }
            ENEMY1.CommonSpeedY += 0.01;
            ENEMY1.UnCommonSpeedY += 0.01;
            ENEMY1.RareSpeedY += 0.01;
            if (ENEMY1.EnemyType == "COMMON") {
                GameScore += ENEMY1.CommonScoreReward;
            }
            else if (ENEMY1.EnemyType == "UNCOMMON") {
                GameScore += ENEMY1.UncommonScoreReward;
            }
            else if (ENEMY1.EnemyType == "RARE") {
                GameScore += ENEMY1.RareScoreReward;
            }
        }
        if (ENEMY2.Y < -7 && BOSS.MainDestroy) {
            ENEMY2.SetEnemyType(ENEMY2);
            ENEMY2.X = (rand() % (SPACE.X_range - 10)) + 5;
            ENEMY2.Y = SPACE.Y_range + 6;
            ENEMY2.Destroy = false;
            ENEMY2.ExplosionRange = 1;
            ENEMY2.MissileLeft = 2;
            if (ENEMY1.EnemyType == "RARE") {
                if (ENEMY1.X >= SPACE.X_range / 2) {
                    ENEMY1.MoveDirection = "LEFT";
                }
                else {
                    ENEMY1.MoveDirection = "RIGHT";
                }
            }
            if (ENEMY2.EnemyType == "RARE") {
                if (ENEMY2.X >= SPACE.X_range / 2) {
                    ENEMY2.MoveDirection = "LEFT";
                }
                else {
                    ENEMY2.MoveDirection = "RIGHT";
                }
            }
            ENEMY2.CommonSpeedY += 0.01;
            ENEMY2.UnCommonSpeedY += 0.01;
            ENEMY2.RareSpeedY += 0.01;
            if (ENEMY2.EnemyType == "COMMON") {
                GameScore += ENEMY2.CommonScoreReward;
            }
            else if (ENEMY2.EnemyType == "UNCOMMON") {
                GameScore += ENEMY2.UncommonScoreReward;
            }
            else if (ENEMY1.EnemyType == "RARE") {
                GameScore += ENEMY2.RareScoreReward;
            }
        }
        //////////////////////// ENEMY reset

        //////////////////////// ENEMY destroy
        if (ENEMY1.HP <= 0) {
            ENEMY1.Destroy = true;
        }
        if (ENEMY2.HP <= 0) {
            ENEMY2.Destroy = true;
        }
        //////////////////////// ENEMY destroy

        //////////////////////////////// ENEMY explosion range control
        if (ENEMY1.Destroy) {
            if (ENEMY1.ExplosionRange == 5) {
                ENEMY1.Destroy = false;
                ENEMY1.Y = -8;
                ENEMY1.ExplosionRange = 3;
            }
            ENEMY1.ExplosionRange += 1;
            
        }
        if (ENEMY2.Destroy) {
            if (ENEMY2.ExplosionRange == 5) {
                ENEMY2.Destroy = false;
                ENEMY2.Y = -8;
                ENEMY2.ExplosionRange = 3;
            }
            ENEMY2.ExplosionRange += 1;
        }

        //////////////////////////////// ENEMY explosion range control

        //////////////////////////////// ENEMY missile explosion range control
        if (ENEMY1.MissileDestroy) {
            if (ENEMY1.MissileExplosionRange == 5) {
                ENEMY1.MissileDestroy = false;
                ENEMY1.MissileY = -8;
                ENEMY1.MissileExplosionRange = 3;
            }
            ENEMY1.MissileExplosionRange += 1;
        }
        if (ENEMY2.MissileDestroy) {
            if (ENEMY2.MissileExplosionRange == 5) {
                ENEMY2.MissileDestroy = false;
                ENEMY2.MissileY = -8;
                ENEMY2.MissileExplosionRange = 3;
            }
            ENEMY2.MissileExplosionRange += 1;
        }
        //////////////////////////////// ENEMY missile explosion range control

        ///////////////////////////////// Missile move
        if (!ENEMY1.MissileDestroy) {
            ENEMY1.MissileY -= ENEMY1.MissileSpeedY;
            if (floor(ENEMY1.MissileX) >= floor(PLAYER.X)) {
                ENEMY1.MissileX -= ENEMY1.MissileSpeedX;
            }
            if (floor(ENEMY1.MissileX) <= floor(PLAYER.X)) {
                ENEMY1.MissileX += ENEMY1.MissileSpeedX;
            }
        }
        if (!ENEMY2.MissileDestroy) {
            ENEMY2.MissileY -= ENEMY2.MissileSpeedY;
            if (floor(ENEMY2.MissileX) >= floor(PLAYER.X)) {
                ENEMY2.MissileX -= ENEMY2.MissileSpeedX;
            }
            if (floor(ENEMY2.MissileX) <= floor(PLAYER.X)) {
                ENEMY2.MissileX += ENEMY2.MissileSpeedX;
            }
        }
        ///////////////////////////////// Missile move

        ///////////////////////////////// Missile Destroy
        if (ENEMY1.MissileY <= -7) {
            ENEMY1.MissileDestroy = true;
            ENEMY1.MissileX = 100;
            ENEMY1.MissileY = 100;
            ENEMY1.MissileExplosionRange = 3;
        }
        if (ENEMY2.MissileY <= -7) {
            ENEMY2.MissileDestroy = true;
            ENEMY2.MissileX = 100;
            ENEMY2.MissileY = 100;
            ENEMY2.MissileExplosionRange = 3;
        }
        ///////////////////////////////// Missile Destroy
        
        // Physic

        Endline(0);
        LINE << " ";
        for (int X = 0; X <= SPACE.X_range + 1; X++) {

            LINE << SPACE.WallTile;

        }
        LINE << "\n";
        for (int Y = SPACE.Y_range; Y >= 1; Y--) {
            LINE << " ";
            for (int X = 0; X <= SPACE.X_range + 1; X++) {
                // X Y PHYSIC
                /////////////////////////////// Laser Hit
                if (LaserHitEnemy(X, Y, PLAYER, ENEMY1)) {
                    if (ENEMY1.EnemyType == "RARE") {
                        ENEMY1.HP -= PLAYER.LaserDMG - ENEMY1.RareLaserResistant;
                    }
                    else {
                        ENEMY1.HP -= PLAYER.LaserDMG;
                    }
                    PLAYER.LaserY[ReturnLaserHitIndex(X,Y,PLAYER,ENEMY1)] = 100;
                }
                if (LaserHitEnemy(X, Y, PLAYER, ENEMY2)) {
                    if (ENEMY2.EnemyType == "RARE") {
                        ENEMY2.HP -= PLAYER.LaserDMG - ENEMY2.RareLaserResistant;
                    }
                    else {
                        ENEMY2.HP -= PLAYER.LaserDMG;
                    }
                    PLAYER.LaserY[ReturnLaserHitIndex(X, Y, PLAYER, ENEMY2)] = 100;
                }
                /////////////////////////////// Laser Hit
                /////////////////////////////// Boss LASER hit player
                if (PlayerHitBossLaser(X, Y, PLAYER, BOSS)) {
                    PLAYER.HP -= BOSS.LaserDMG;
                    BOSS.LaserX[ReturnBossLaserIndex(X, Y, BOSS)] = 3000;
                }
                /////////////////////////////// Boss LASER hit player
                /////////////////////////////// Boss Missile hit Player
                if (PlayerHitBossMissile(X, Y, PLAYER, BOSS)) {
                    PLAYER.HP -= BOSS.MissileDMG;
                    BOSS.MissileX[ReturnBossMissileIndex(X, Y, BOSS)] = -3000;
                }
                /////////////////////////////// Boss Missile hit Player
                /////////////////////////////// Boss Hit Super Laser
                if (PlayerHitBossSuperLaser(X, Y, PLAYER, BOSS) && !BOSS.EngineDestroy) {
                    PLAYER.HP -= BOSS.SuperLaserDMG;
                 }
                /////////////////////////////// Boss Hit Super Laser 
                /////////////////////////////// fire Missile
                if (ENEMY1.Y <= SPACE.Y_range - SPACE.Y_range / 4 && ENEMY1.EnemyType == "UNCOMMON" && ENEMY1.MissileDestroy && ENEMY1.MissileLeft >= 1) {
                    ENEMY1.SetMissile(ENEMY1);
                    ENEMY1.MissileDestroy = false;
                    ENEMY1.MissileLeft -= 1;
                }
                if (ENEMY2.Y <= SPACE.Y_range - SPACE.Y_range / 4 && ENEMY2.EnemyType == "UNCOMMON" && ENEMY2.MissileDestroy && ENEMY2.MissileLeft >= 1) {
                    ENEMY2.SetMissile(ENEMY2);
                    ENEMY2.MissileDestroy = false;
                    ENEMY2.MissileLeft -= 1;
                }
                /////////////////////////////// fire Missile
                
                ///////////////////////////////////////////// laser - boss collision
                //// reset
                BOSS.EngineHit = BOSS.RightCannonHit = BOSS.LeftCannonHit = BOSS.RightUpperWingHit = BOSS.LeftUpperWingHit = false;

                if (LaserHitBoss(X, Y, PLAYER, BossEngineHitbox(X, Y, BOSS)) && BOSS.LeftUpperWingDestroy && BOSS.RightUpperWingDestroy) {
                    PLAYER.LaserX[ReturnLaserHitBoss(X, Y, PLAYER)] = 100;
                    BOSS.EngineHP -= PLAYER.LaserDMG;
                    BOSS.EngineHit = true;
                }
                if (LaserHitBoss(X, Y, PLAYER, BossLeftCannonHitbox(X, Y, BOSS)) && !BOSS.LeftCannonDestroy) {
                    PLAYER.LaserX[ReturnLaserHitBoss(X, Y, PLAYER)] = 100;
                    BOSS.LeftCannonHP -= PLAYER.LaserDMG;
                    BOSS.LeftCannonHit = true;
                }
                if (LaserHitBoss(X, Y, PLAYER, BossRightCannonHitbox(X, Y, BOSS)) && !BOSS.RightCannonDestroy) {
                    PLAYER.LaserX[ReturnLaserHitBoss(X, Y, PLAYER)] = 100;
                    BOSS.RightCannonHP -= PLAYER.LaserDMG;
                    BOSS.RightCannonHit = true;
                }
                if (LaserHitBoss(X, Y, PLAYER, BossLeftUpperWingHitbox(X, Y, BOSS)) && BOSS.RightCannonDestroy && BOSS.LeftCannonDestroy && !BOSS.LeftUpperWingDestroy) {
                    PLAYER.LaserX[ReturnLaserHitBoss(X, Y, PLAYER)] = 100;
                    BOSS.LeftUpperWingHP -= PLAYER.LaserDMG;
                    BOSS.LeftUpperWingHit = true;
                }
                if (LaserHitBoss(X, Y, PLAYER, BossRightUpperWingHitbox(X, Y, BOSS)) && BOSS.RightCannonDestroy && BOSS.LeftCannonDestroy && !BOSS.RightUpperWingDestroy) {
                    PLAYER.LaserX[ReturnLaserHitBoss(X, Y, PLAYER)] = 100;
                    BOSS.RightUpperWingHP -= PLAYER.LaserDMG;
                    BOSS.RightUpperWingHit = true;
                }

                if (BOSS.EngineHP <= 0) {
                    BOSS.BossRetreat = true;
                    //BOSS.EngineHP = 2;

                }
                if (BOSS.BossRetreat) {
                    BOSS.MainY += 2;
                    BOSS.SetBodyPosition(BOSS);
                    if (BOSS.MainY > SPACE.Y_range + 50) {
                        BOSS.BossRetreat = false;
                        BOSS.EngineDestroy = true;
                        BOSS.MainDestroy = true;
                        GameTime = 0;
                        BOSS.EngineHP = 2;
                        GameScore += BOSS.BossScoreReward;
                    }
                }

                if (BOSS.LeftCannonHP <= 0) {
                    BOSS.LeftCannonDestroy = true;
                }
                if (BOSS.RightCannonHP <= 0) {
                    BOSS.RightCannonDestroy = true;
                }
                if (BOSS.LeftUpperWingHP <= 0) {
                    BOSS.LeftUpperWingDestroy = true;
                }
                if (BOSS.RightUpperWingHP <= 0) {
                    BOSS.RightUpperWingDestroy = true;
                }




                ///////////////////////////////////////////// laser - boss collision

                //////////////////////////////// enemy-player collision
                if (PlayerCollideEnemy(X, Y, PLAYER, ENEMY1) && !ENEMY1.Destroy) {
                    ENEMY1.Destroy = true;
                    if (ENEMY1.EnemyType == "COMMON") {
                        PLAYER.HP -= ENEMY1.CommonBodyDamage;
                    }
                    if (ENEMY1.EnemyType == "UNCOMMON") {
                        PLAYER.HP -= ENEMY1.UnCommonBodyDamage;
                    }
                    if (ENEMY1.EnemyType == "RARE") {
                        PLAYER.HP -= ENEMY1.RareBodyDamage;
                    }
                }
                if (PlayerCollideEnemy(X, Y, PLAYER, ENEMY2) && !ENEMY2.Destroy) {
                    ENEMY2.Destroy = true;
                    if (ENEMY2.EnemyType == "COMMON") {
                        PLAYER.HP -= ENEMY2.CommonBodyDamage;
                    }
                    if (ENEMY2.EnemyType == "UNCOMMON") {
                        PLAYER.HP -= ENEMY2.UnCommonBodyDamage;
                    }
                    if (ENEMY2.EnemyType == "RARE") {
                        PLAYER.HP -= ENEMY2.RareBodyDamage;
                    }
                }
                //////////////////////////////// enemy-player collision
                //////////////////////////////// missile-player collision
                if (PlayerHitMissile(X, Y, PLAYER, ENEMY1) && !ENEMY1.MissileDestroy) {
                    ENEMY1.MissileDestroy = true;
                    PLAYER.HP -= ENEMY1.MissileDMG;

                }
                if (PlayerHitMissile(X, Y, PLAYER, ENEMY2) && !ENEMY2.MissileDestroy) {
                    ENEMY2.MissileDestroy = true;
                    PLAYER.HP -= ENEMY2.MissileDMG;
                }
                //////////////////////////////// missile-player collision
                // X Y PHYSIC
                //////////////////////////////////////////////////////////////////// START of play zone
                if (X == 0 || X == SPACE.X_range + 1) {
                    LINE << SPACE.WallTile;
                }
                else {
                    if (PlayerHitbox(X, Y, PLAYER)) {
                        LINE << DrawTile(PlayerTexture(X, Y, PLAYER));
                    }
                    else if (PLAYER.HP <= 0 && SPACE.YOUAREDEAD(X,Y,SPACE)) {
                        LINE << "\033[31m" << DrawTile(219) << "\033[0m";
                    }
                    else if (EnemyExplosion(X, Y, ENEMY2, ENEMY2.ExplosionRange) && ENEMY2.Destroy) {
                        if (ENEMY2.ExplosionRange == 2) {
                            LINE << "\033[33m";
                        }
                        else if (ENEMY2.ExplosionRange == 3) {
                            LINE << "\033[1m\033[33m";
                        }
                        else if (ENEMY2.ExplosionRange == 4) {
                            LINE << "\033[31m";
                        }
                        LINE << DrawTile(219) << "\033[0m";;
                    }
                    else if (MissileExplosion(X, Y, ENEMY2, ENEMY2.MissileExplosionRange) && ENEMY2.MissileDestroy) {
                        if (ENEMY2.MissileExplosionRange == 2) {
                            LINE << "\033[33m";
                        }
                        else if (ENEMY2.MissileExplosionRange == 3) {
                            LINE << "\033[1m\033[33m";
                        }
                        else if (ENEMY2.MissileExplosionRange == 4) {
                            LINE << "\033[31m";
                        }
                        LINE << DrawTile(219) << "\033[0m";;
                    }
                    else if (EnemyExplosion(X, Y, ENEMY1, ENEMY1.ExplosionRange) && ENEMY1.Destroy) {
                        if (ENEMY1.ExplosionRange == 2) {
                            LINE << "\033[33m";
                        }
                        else if (ENEMY1.ExplosionRange == 3) {
                            LINE << "\033[1m\033[33m";
                        }
                        else if (ENEMY1.ExplosionRange == 4) {
                            LINE << "\033[31m";
                        }
                        LINE << DrawTile(219) << "\033[0m";
                    }
                    else if (MissileExplosion(X, Y, ENEMY1, ENEMY1.MissileExplosionRange) && ENEMY1.MissileDestroy) {
                        if (ENEMY1.MissileExplosionRange == 2) {
                            LINE << "\033[33m";
                        }
                        else if (ENEMY1.MissileExplosionRange == 3) {
                            LINE << "\033[1m\033[33m";
                        }
                        else if (ENEMY1.MissileExplosionRange == 4) {
                            LINE << "\033[31m";
                        }
                        LINE << DrawTile(219) << "\033[0m";
                    }//
                    else if (GameTime % 3 == 0 && PlayerTrail1(X, Y, PLAYER)) {
                        LINE << "\033[1m\033[33m" << DrawTile(219) << "\033[0m";
                    }
                    else if (GameTime % 3 == 1 && PlayerTrail2(X, Y, PLAYER)) {
                        LINE << "\033[33m" << DrawTile(219) << "\033[0m";
                    }
                    else if (GameTime % 3 == 2 && PlayerTrail3(X, Y, PLAYER)) {
                        LINE << "\033[31m" << DrawTile(219) << "\033[0m";
                    }
                    else if (PlayerLaserPosition(X, Y, PLAYER)) {
                        LINE << "\033[1m\033[32m" << DrawTile(124) << "\033[0m";
                    }
                    else if (BossEngineHPbar(X, Y, BOSS) && !BOSS.MainDestroy && !BOSS.EngineDestroy) {
                        if (BossEngineHPbarColor(X, BOSS)) {
                            LINE << "\033[1m\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[1m\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (BossLeftUpperWingHPbar(X, Y, BOSS) && !BOSS.MainDestroy && !BOSS.LeftUpperWingDestroy) {
                        if (BossLeftUpperWingHPbarColor(X, BOSS)) {
                            LINE << "\033[1m\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[1m\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (BossRightUpperWingHPbar(X, Y, BOSS) && !BOSS.MainDestroy && !BOSS.RightUpperWingDestroy) {
                        if (BossRightUpperWingHPbarColor(X, BOSS)) {
                            LINE << "\033[1m\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[1m\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (BossLeftCannonHPbar(X, Y, BOSS) && !BOSS.MainDestroy && !BOSS.LeftCannonDestroy) {
                        if (BossLeftCannonHPbarColor(X, BOSS)) {
                            LINE << "\033[1m\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[1m\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (BossRightCannonHPbar(X, Y, BOSS) && !BOSS.MainDestroy && !BOSS.RightCannonDestroy) {
                        if (BossRightCannonHPbarColor(X, BOSS)) {
                            LINE << "\033[1m\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[1m\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (BossSuperLaserHitbox(X, Y, BOSS) && BOSS.FireSuperLaser && !BOSS.EngineDestroy) {
                        if (SuperLaserColor(X, BOSS)) {
                            LINE << "\033[36m" << DrawTile(219) << "\033[0m";
                        }
                        else {
                            LINE << "\033[37m" << DrawTile(219) << "\033[0m";
                        }
                    }
                    else if (BossLaserPosition(X, Y, BOSS)) {
                        LINE << "\033[1m\033[35m" << DrawTile(254) << "\033[0m";
                    }
                    else if (BossMissilePosition(X, Y, BOSS)) {
                        LINE << "\033[1m\033[32m" << DrawTile(BossMissileTexture(X,Y,BOSS)) << "\033[0m";
                    }
                    else if (BossMainHitbox(X, Y, BOSS) && !BOSS.MainDestroy) {
                        LINE << "\033[1m\033[31m" << DrawTile(BossMainTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    else if (BossEngineHitbox(X,Y,BOSS) && !BOSS.MainDestroy) {
                        if (BOSS.EngineDestroy || BOSS.EngineHit) {
                            LINE << "\033[31m" << DrawTile(BossEngineTexture(X, Y, BOSS)) << "\033[0m";
                        }
                        else {
                            LINE << "\033[1m\033[33m" << DrawTile(BossEngineTexture(X, Y, BOSS)) << "\033[0m";
                        }
                    }
                    else if (BossLeftCannonHitbox(X, Y, BOSS) && !BOSS.MainDestroy) {
                    if (BOSS.LeftCannonDestroy || BOSS.LeftCannonHit) {
                        LINE << "\033[31m" << DrawTile(BossLeftCannonTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    else {
                        LINE << "\033[1m\033[33m" << DrawTile(BossLeftCannonTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    }
                    else if (BossRightCannonHitbox(X, Y, BOSS) && !BOSS.MainDestroy) {
                    if (BOSS.RightCannonDestroy || BOSS.RightCannonHit) {
                        LINE << "\033[31m" << DrawTile(BossRightCannonTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    else {
                        LINE << "\033[1m\033[33m" << DrawTile(BossRightCannonTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    }
                    else if (BossLeftUpperWingHitbox(X,Y,BOSS) && !BOSS.MainDestroy) {
                    if (BOSS.LeftUpperWingDestroy || BOSS.LeftUpperWingHit) {
                        LINE << "\033[31m" << DrawTile(BossLeftUpperWingTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    else {
                        LINE << "\033[1m\033[33m" << DrawTile(BossLeftUpperWingTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    }
                    else if (BossRightUpperWingHitbox(X, Y, BOSS) && !BOSS.MainDestroy) {
                    if (BOSS.RightUpperWingDestroy || BOSS.RightUpperWingHit) {
                        LINE << "\033[31m" << DrawTile(BossRightUpperWingTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    else {
                        LINE << "\033[1m\033[33m" << DrawTile(BossRightUpperWingTexture(X, Y, BOSS)) << "\033[0m";
                    }
                    }
                    else if (CommonEnemyHitbox(X, Y, ENEMY1) && ENEMY1.EnemyType == "COMMON" && !ENEMY1.Destroy) { ////// ENEMY 1 common
                        LINE << "\033[36m" << DrawTile(CommonEnemyTexture(X, Y, ENEMY1)) << "\033[0m";
                    }
                    else if (CommonEnemyHpBar(X, Y, ENEMY1) && ENEMY1.EnemyType == "COMMON" && !ENEMY1.Destroy) { ////// ENEMY 1 common HP
                        if (CommonEnemyHpColor(X, ENEMY1)) {
                            LINE << "\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (UnCommonEnemyHitbox(X, Y, ENEMY1) && ENEMY1.EnemyType == "UNCOMMON" && !ENEMY1.Destroy) { ////// ENEMY 1 uncommon
                        LINE << "\033[1m\033[32m" << DrawTile(UnCommonEnemyTexture(X, Y, ENEMY1)) << "\033[0m";
                    }
                    else if (UnCommonEnemyHpBar(X,Y,ENEMY1) && ENEMY1.EnemyType == "UNCOMMON" && !ENEMY1.Destroy) {
                        if (UnCommonEnemyHpColor(X, ENEMY1)) {
                            LINE << "\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (MissileHitbox(X, Y, ENEMY1) && !ENEMY1.MissileDestroy) {
                        LINE << "\033[1m\033[31m" << DrawTile(MissileTexture(X, Y, ENEMY1)) << "\033[0m";
                    }
                    else if (RareEnemyHitbox(X, Y, ENEMY1) && ENEMY1.EnemyType == "RARE" && !ENEMY1.Destroy) { ////// ENEMY 1 rare
                        LINE << "\033[33m" << DrawTile(RareEnemyTexture(X, Y, ENEMY1)) << "\033[0m";
                    }
                    else if (RareEnemyHpBar(X, Y, ENEMY1) && ENEMY1.EnemyType == "RARE" && !ENEMY1.Destroy) {
                        if (RareEnemyHpColor(X, ENEMY1)) {
                            LINE << "\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (CommonEnemyHitbox(X, Y, ENEMY2) && ENEMY2.EnemyType == "COMMON" && !ENEMY2.Destroy) { ////// ENEMY 2 common
                        LINE << "\033[36m" << DrawTile(CommonEnemyTexture(X, Y, ENEMY2)) << "\033[0m" ;
                    }
                    else if (CommonEnemyHpBar(X, Y, ENEMY2) && ENEMY2.EnemyType == "COMMON" && !ENEMY2.Destroy) { ////// ENEMY 2 common HP
                        if (CommonEnemyHpColor(X, ENEMY2)) {
                            LINE << "\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (UnCommonEnemyHitbox(X, Y, ENEMY2) && ENEMY2.EnemyType == "UNCOMMON" && !ENEMY2.Destroy) { ////// ENEMY 2 uncommon
                        LINE << "\033[1m\033[32m" << DrawTile(UnCommonEnemyTexture(X, Y, ENEMY2)) << "\033[0m";
                    }
                    else if (UnCommonEnemyHpBar(X, Y, ENEMY2) && ENEMY2.EnemyType == "UNCOMMON" && !ENEMY2.Destroy) {
                        if (UnCommonEnemyHpColor(X, ENEMY2)) {
                            LINE << "\033[32m" << DrawTile(22) << "\033[0m";
                        }
                        else {
                            LINE << "\033[31m" << DrawTile(22) << "\033[0m";
                        }
                    }
                    else if (MissileHitbox(X, Y, ENEMY2) && !ENEMY2.MissileDestroy) {
                        LINE << "\033[1m\033[31m" << DrawTile(MissileTexture(X, Y, ENEMY2)) << "\033[0m";
                    }
                    else if (RareEnemyHitbox(X, Y, ENEMY2) && ENEMY2.EnemyType == "RARE" && !ENEMY2.Destroy) { ////// ENEMY 2 rare
                        LINE << "\033[33m" << DrawTile(RareEnemyTexture(X, Y, ENEMY2)) << "\033[0m";
                    }
                    else if (RareEnemyHpBar(X, Y, ENEMY2) && ENEMY2.EnemyType == "RARE" && !ENEMY2.Destroy) {
                    if (RareEnemyHpColor(X, ENEMY2)) {
                        LINE << "\033[32m" << DrawTile(22) << "\033[0m";
                    }
                    else {
                        LINE << "\033[31m" << DrawTile(22) << "\033[0m";
                    }
                    }
                    else {
                        LINE << " ";
                    }
                }
            }
            //////////////////////////////////////////////////////////////////// END of play zone
            

            /////////////////////////////////////////////////////////////////// HEALTH BAR
            int BarLenght = 50;
            int HpDisplay = (PLAYER.HP / PLAYER.MaxHp) * 50;
            if (Y == SPACE.Y_range) {
                LINE << "     DAMAGE status : " << (50 - HpDisplay) * 2 << " %";
                if ((50 - HpDisplay) * 2 >= 70) {
                    if (GameTime % 3 == 1) {
                        LINE << "\033[31m" << "  Critical Damage" << "\033[0m";
                    }
                    else {
                        LINE << "\033[30m" << "  ███████████████" << "\033[0m";
                    }
                }
            }
            if (Y == SPACE.Y_range - 1) {
                LINE << "\033[1m\033[33m" << "    " << DrawTile(218);
                for (int i = 1; i <= BarLenght; i++) {
                    LINE << DrawTile(196);
                }
                LINE << DrawTile(191) << "\033[0m";
            }
            if (Y == SPACE.Y_range - 2) {
                LINE << "    " << "\033[1m\033[33m" << DrawTile(124);
                for (int i = 1; i <= BarLenght; i++) {
                    if (HpDisplay >= i) {
                        LINE << "\033[32m" << DrawTile(219);
                    }
                    else {
                        LINE << "\033[31m" << DrawTile(219);
                    }
                }
                LINE << "\033[1m\033[33m" << DrawTile(124) << "\033[0m";
            }
            if (Y == SPACE.Y_range - 3) {
                LINE << "\033[1m\033[33m" << "    " << DrawTile(192);
                for (int i = 1; i <= BarLenght; i++) {
                    LINE << DrawTile(196);
                }
                LINE << DrawTile(217) << "\033[0m";
            }
            if (Y == SPACE.Y_range - 7) {
                LINE << "\033[0m" << "      Press F to toggle off laser ";
            }
            /////////////////////////////////////////////////////////////////// HEALTH BAR



            /////////////////////////////////////////////////////////////////// BOSS SPAWN WARNING
            if (Y == SPACE.Y_range - 30) {
                if (GameTime >= BOSS.SpawnTime - BOSS.WarningTime && GameTime <= BOSS.SpawnTime) {
                    if (GameTime % 3 == 0 || GameTime % 3 == 1) {
                        LINE << "\033[1m\033[33m" << "     Boss Approching!" << "\033[0m";
                    }
                    else {
                        LINE << "\033[30m" << "      ███████████████" << "\033[0m";
                    }
                    
                }
                else {
                    LINE << "\033[30m" << "      ███████████████" << "\033[0m";
                }
            }
            /////////////////////////////////////////////////////////////////// BOSS SPAWN WARNING

            LINE << "\n"; // DO NOT DELETE

        }

        LINE << " ";
        for (int X = 0; X <= SPACE.X_range + 1; X++) {

            LINE << SPACE.WallTile;

        }
        LINE << "\n" << "\n";
        if (GameScore < 10) {
            LINE << "\033[0m" << "   The Score is : 0000" << "\033[1m\033[32m" << GameScore;
        }
        else if (GameScore < 100) {
            LINE << "\033[0m" << "   The Score is : 000" << "\033[1m\033[32m" << GameScore;
        }
        else if (GameScore < 1000) {
            LINE << "\033[0m" << "   The Score is : 00" << "\033[1m\033[32m" << GameScore;
        }
        else if (GameScore < 10000) {
            LINE << "\033[0m" << "   The Score is : 0" << "\033[1m\033[32m" << GameScore;
        }
        else if (GameScore < 10000) {
            LINE << "\033[0m" << "   The Score is :  " << "\033[1m\033[32m" << GameScore;
        }
        LINE << "\033[0m";


        cout << LINE.str();
        LINE.str("");
        GameTime += 1;
   
        if (PLAYER.HP <= 0) {
            cout << "          CLOSING GAME    ";
            Sleep(3000);
            break;
        }
        
    }


}


