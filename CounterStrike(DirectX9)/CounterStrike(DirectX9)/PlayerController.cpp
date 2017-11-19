#include "PlayerController.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "BoxCollider.h"
#include "SpriteRender.h"
#include "Bullet.h"
#include "LeftMove.h"
#include "RightMove.h"
#include "UpMove.h"
#include "DownMove.h"

RTTILINK(CPlayerController, CController)

void CPlayerController::Update()
{
	/* �÷��̾ ���콺 ��ǥ�� �ٶ� */
	VECTOR3 Mouse = GetMousePosition();
	MATRIX Matrix;
	DRX->GetTransform(D3DTS_VIEW, &Matrix);	// ���� �� ��ü ��ǥ �������� ����
	Mouse.TransformCoord(Matrix);
	gameObj.Angle = Angle(Mouse - gameObj.Position);

	/* ������ ���� */
	if (KEY.Push('S'))
		gameObj.AddComponent<CDownMove>();
	if (KEY.Push('W'))
		gameObj.AddComponent<CUpMove>();
	if (KEY.Push('D'))
		gameObj.AddComponent<CRightMove>();
	if (KEY.Push('A'))
		gameObj.AddComponent<CLeftMove>();
	/* ������ ���� */
	if (KEY.Pull('S'))
		Destroy(gameObj.GetComponent<CDownMove>());
	if (KEY.Pull('W'))
		Destroy(gameObj.GetComponent<CUpMove>());
	if (KEY.Pull('D'))
		Destroy(gameObj.GetComponent<CRightMove>());
	if (KEY.Pull('A'))
		Destroy(gameObj.GetComponent<CLeftMove>());

	/* �� �߻� */
	if (KEY.Push(VK_LBUTTON))
		Time = 0;
	if (KEY.Down(VK_LBUTTON))
	{
		Time += TIME.Delta;
		if (Time > ActionTime)
		{
			double Angle = Random(gameObj.Angle - 5, gameObj.Angle + 5);
			auto obj = GAMEOBJ.AddGameObj("Bullet", Tag_Enviroment, Layer_Enviroment);
			obj->Position = gameObj.Position;
			obj->Angle = Angle + 45;
			obj->AddComponent<CBoxCollider>();

			auto bullet = obj->AddComponent<CBullet>();
			bullet->Dir = VECTOR3(1, 0, 0);
			bullet->Dir.Rotation(Angle);
			bullet->Dir.Normalize();

			auto csr = obj->AddComponent<CSpriteRender>();
			csr->RenderKey = "Bullet";

			Time -= ActionTime;
		}
	}
}

CPlayerController::CPlayerController(CGameObj* Owner)
	: CController(Owner), Time(0), ActionTime(0.15)
{
}

CPlayerController::~CPlayerController()
{
}
