#ifndef CAMERA_H
#define CAMERA_H

#include "../Libraries/MathLib/MathLib.h"

class cCamera // Base
{
public:

	virtual void Init(); 
	inline virtual void Update(float lfTimestep){;}

	inline void RefreshViewProj() { mViewProj = mView * mProj; }
	
    // LvUpWorld by default is +Y Vector
	void SetLookAt( const cVec3 &lvPosition,
					const cVec3 &lvTarget,
					const cVec3 &lvUpWorld = cVec3(0.0f, 1.0f, 0.0f) );

	void SetYaw(float rad);
	void SetPitch(float rad);

	// Set 2D Proyection
	void SetOrtho( float lfLeft, float lfRight,float lfBottom, float lfTop, float lfZNear, float lfZNFar );

	// Set 3D Proyection
	void SetPerspective( float lfFOVY_Rad, float lfAspect, float lfZNear, float lfZFar);

	inline cVec3 GetFront()			const{return mView.GetFront();}
	inline cVec3 GetLeft()			const{return mView.GetLeft();}
	inline cVec3 GetRight()			const{ return mView.GetRight();}
	inline cVec3 GetUp()			const{return mView.GetUp();}
	inline cVec3 GetPosition()		const{return mView.GetPosition();}
	
	inline const cMatrix &GetView()		const {return mView;}
	inline const cMatrix &GetProj()		const {return mProj;}
	inline const cMatrix &GetViewProj()	const {return mViewProj;}

protected:
	cMatrix mView;
	cMatrix mProj;
	cMatrix mViewProj; // == View Matrix * Proj Matrix
};
#endif 
// GL_MODELVIEW = WorldMatrix * ViewMatrix
// GL_PROJECTION = ProyectionMatrix