// Coded By AssortRock Unreal Engine Class Project


#include "Data/YggConst.h"


const float CameraConst::MaxCameraBoomLength = 1000.0f;
const float CameraConst::MinCameraBoomLength = 100.0f;
const float CameraConst::ZoomSpeed = 50.0f;

const float CameraConst::NormalCameraBoomLength = 450.0f;
const float CameraConst::AimCameraBoomLength = 200.0f;

const FVector CameraConst::NormalSocketOffset = FVector(0.0f, 0.0f, 200.0f);
const FVector CameraConst::AimSocketOffset = FVector(0.0f, 45.0f, 150.0f);



// EnemyConst

const FName UEnemyConst::AI::EnemyAIDataName = TEXT("EnemyAIData");
const FName UEnemyConst::Collision::ProfileName_MonsterAttack = TEXT("MonsterAttack");