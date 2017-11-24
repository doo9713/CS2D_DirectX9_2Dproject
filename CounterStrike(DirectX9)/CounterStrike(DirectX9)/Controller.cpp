#include "Controller.h"
#include "GameObj.h"

RTTILINK(CController, CComponent)

CController::CController(CGameObj* Owner)
	: CComponent(Owner), Health(100)
{
}

CController::~CController()
{
}
