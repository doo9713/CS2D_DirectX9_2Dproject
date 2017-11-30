#include "Rigid.h"
#include "GameObj.h"
#include "BoxCollider.h"
#include "GameObjList.h"

RTTILINK(CRigid, CComponent)

bool CRigid::IsPrevIn(CGameObj* Other)
{
	for (auto obj : PrevCollision)
		if (obj == Other)
			return true;
	return false;
}

bool CRigid::IsIn(CGameObj* Other)
{
	for (auto obj : Collision)
		if (obj == Other)
			return false;
	return true;
}

void CRigid::Start()
{
	Collider = GetComponent<CBoxCollider>();
}

void CRigid::Update()
{
	if (Collider)
	{
		PrevCollision.clear();
		auto& active = GAMEOBJ.GetActive();
		CBoxCollider* otherbox;
		CRigid* otherrigid;
		for (auto obj : active)
		{
			if (!gameObj.SameParent(obj))
			{
				otherbox = obj->GetComponent<CBoxCollider>();
				if (otherbox)
				{
					/*  동일한 Tag의 물체는 서로 충돌처리를 하지 않음 */
					if (Collider->gameObj.Tag == otherbox->gameObj.Tag)
						continue;
					otherrigid = obj->GetComponent<CRigid>();
					if (otherrigid)
					{
						if (otherrigid->IsPrevIn(&gameObj))
							continue;
					}
					PrevCollision.emplace_back(obj);

					if (Collider->BoxToBox(otherbox))
					{
						if (IsIn(obj))
						{
							//충돌 시작
							Collision.emplace_back(obj);
							if (otherrigid)
								otherrigid->Collision.emplace_back(&gameObj);

							CGameObj* Temp = &gameObj;
							while (Temp)
							{
								for (auto com : Temp->component)
								{
									com->OnCollisionEnter(obj);
								}
								Temp = Temp->parent;
							}
							Temp = obj;
							while (Temp)
							{
								for (auto com : Temp->component)
								{
									com->OnCollisionEnter(&gameObj);
								}
								Temp = Temp->parent;
							}
						}
						else
						{
							// 충돌 도중
							CGameObj* Temp = &gameObj;
							while (Temp)
							{
								for (auto com : Temp->component)
								{
									com->OnCollisionStay(obj);
								}
								Temp = Temp->parent;
							}
							Temp = obj;
							while (Temp)
							{
								for (auto com : Temp->component)
								{
									com->OnCollisionStay(&gameObj);
								}
								Temp = Temp->parent;
							}
						}

						// 충돌후 처리
						Collider->BoxPushBox(otherbox);
					}
					else
					{
						// 충돌 끝
						for (auto coll = Collision.begin();
							coll != Collision.end(); ++coll)
						{
							if (*coll == obj)
							{
								Collision.erase(coll);
								break;
							}
						}
						if (otherrigid)
						{
							for (auto coll = otherrigid->Collision.begin();
								coll != otherrigid->Collision.end(); ++coll)
							{
								if (*coll == obj)
								{
									otherrigid->Collision.erase(coll);
									break;
								}
							}
						}
						CGameObj* Temp = &gameObj;
						while (Temp)
						{
							for (auto com : Temp->component)
							{
								com->OnCollisionExit(obj);
							}
							Temp = Temp->parent;
						}
						Temp = obj;
						while (Temp)
						{
							for (auto com : Temp->component)
							{
								com->OnCollisionExit(&gameObj);
							}
							Temp = Temp->parent;
						}
					}
				}
			}
		}
	}
	else
		Collider = GetComponent<CBoxCollider>();
}

CRigid::CRigid(CGameObj* Owner)
	: CComponent(Owner)
{
}

CRigid::~CRigid()
{
}
