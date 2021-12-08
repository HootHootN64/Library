#ifndef OKCustomObjectH
#define OKCustomObjectH
#include "../MainInclude.h"
extern void Draw3DRacer();
extern void DisplayRedCoin(void *Camera, void *Object);
extern void DisplayCoinSprite();
extern void DisplayAfterEffects();
extern void loadCoin();
extern void DrawOKObjects(Camera* LocalCamera);
extern void DrawOKObjectLoop();
extern void CheckOKObjects();
extern void ClearOKObject(short ObjectID);
extern short FindOKObject();
extern bool TestCollideBox(float SourcePosition[], short SourceSize[], short SourceAngle[], float TargetPosition[], float TargetRadius);
extern bool TestCollideSphere(float SourcePosition[], float SourceRadius, float TargetPosition[], float TargetRadius);
#endif