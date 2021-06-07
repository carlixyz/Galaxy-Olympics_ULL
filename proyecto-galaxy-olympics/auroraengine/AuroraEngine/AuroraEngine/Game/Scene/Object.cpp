#include "Object.h"
#include "ObjectManager.h"
#include "Player.h"

void cObject::Init()
{	
	mWorldMatrix.LoadIdentity();
}
void cObject::Init( const std::string &lacNameID,const std::string &lacFile )
{
	macName = lacNameID;
	mWorldMatrix.LoadIdentity();
	mModel.Init( lacNameID, lacFile, true );
}

void cObject::Init( const std::string &lacNameID,const std::string &lacFile, bool lbBoundingBox )
{
	macName = lacNameID;
	mWorldMatrix.LoadIdentity();
	mModel.Init( lacNameID, lacFile, lbBoundingBox );
}

void cObject::Update( float lfTimestep )
{
	//Aqui se controlara el comportamiento de los objetos

	mModel.Update(lfTimestep);
//	mModel.mCollisionObject.Update(mWorldMatrix);

	cPlayer *lpPlayer = cObjectManager::Get().GetPlayer();
	
	cVec3 & lpPosition = lpPlayer->GetMatrix().GetPosition();

	if ( GetCollisionBox().CheckCollision(lpPlayer->GetCollisionBox()))
	{
		
		if (meType == eRing)
		{
			cVec3 & PlayerCenter = lpPlayer->GetCollisionBox().Center;
			cVec3 & ObjectCenter = GetCollisionBox().Center;
			float Distance = sqrt(pow(PlayerCenter.x-ObjectCenter.x,2)+pow(PlayerCenter.y-ObjectCenter.y,2));
			if ((Distance <=4) && (abs(ObjectCenter.z-PlayerCenter.z)<=2))
			{
				lpPlayer->SetCollisionObject(NULL);
				lpPlayer->AddTurbo();
			}
			else if ((Distance >4) && (Distance<=5.5) &&(abs(ObjectCenter.z-PlayerCenter.z)<=1))
			{
				lpPlayer->SetCollisionObject(this);
				lpPlayer->AddTurbo();
			}
			else 
			{
				lpPlayer->SetCollisionObject(NULL);
				lpPlayer->AddTurbo();
			}
		}
		else
			lpPlayer->SetCollisionObject(this);				
	}
}

void cObject::Render()
{
	mModel.Render(mWorldMatrix);
//	mModel.mCollisionObject.Render(); // too expensive
}

void cObject::Deinit()
{
	mModel.Deinit();	
}

