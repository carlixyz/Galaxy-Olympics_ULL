#include "DebugCamera.h"

#include "../Game/InputConfiguration.h"
#include "../Input/InputManager.h"

#define MOUSE_SPEED 0.0015f 

//#include "../Utility/Debug.h"

void cDebugCamera::Init() 
{

	this->mNew_pos  = cVec3(0.0f, 0.0f, 0.0f);
	this->mOld_pos = mNew_pos ;
	this->SetLookAt( cVec3(0.0f, 5.0f, -50.0f), cVec3(0.0f, 5.f, 0.f) );
	// cameraUp by default is = cVec3(0.0f, 1.f, 0.f);
}

void cDebugCamera::Update(float lfTimestep)
{
 // Process Some Input Here

	if (IsPressed(eIA_CameraLeft))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.x +=0.1f;
		mView.SetPosition( lPos);
	}	

	if (IsPressed(eIA_CameraRight))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.x -=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraUp))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.y +=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraDown))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.y -=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraUp))
	{
		cVec3 &lPos = this->GetPosition() ;
		lPos.y +=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraFoward))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.z +=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraBack))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.z -=0.1f;
		mView.SetPosition( lPos);
	}
	//this->SetLookAt( this->cameraPositon, this->cameraTarget); 

	if (  GetValue( eIA_MouseYaw ) || GetValue( eIA_MousePitch ) ) // Mouse Rotation
		{	
			if (mNew_pos.IsZero()) // Check First pass
			{
				mOld_pos.y = GetValue( eIA_MousePitch  ) ;
				mNew_pos.y = GetValue( eIA_MousePitch  ) ;

				mOld_pos.x = GetValue( eIA_MouseYaw  ) ;
				mNew_pos.x = GetValue( eIA_MouseYaw  ) ;
			}
			else
			{
				mOld_pos.x = mNew_pos.x ;
				mOld_pos.y = mNew_pos.y ;

				mNew_pos.x = GetValue( eIA_MouseYaw  ) ;
				mNew_pos.y = GetValue( eIA_MousePitch  ) ;

				if (mOld_pos.x - mNew_pos.x)
					this->SetYaw( GetValue( eIA_MouseYaw  )* MOUSE_SPEED );
				
				if (mOld_pos.y - mNew_pos.y)
					this->SetPitch( GetValue( eIA_MousePitch  )* MOUSE_SPEED );
			}
//		this->SetPitch(GetValue( eIA_MouseMoved  )* -0.001);
//		Debug().ToOutput(" \n old: %f - new: %f - total: %f - real: %f ", mOld_pos.x, mNew_pos.x,(mOld_pos.x - mNew_pos.x), GetValue(eIA_MouseYaw  ) );

		}

/* // get inside & Uncomment if you want to use keyboard keys for Pitch & Yaw
		if (IsPressed(eIA_CameraYawRight))
			this->SetYaw(0.01f);

		if (IsPressed(eIA_CameraYawLeft))
			this->SetYaw(-0.01f);

		if (IsPressed(eIA_CameraPitchUp))
			this->SetPitch(-0.01f);

		if (IsPressed(eIA_CameraPitchDown))
			this->SetPitch(0.01f);
*/		
}
