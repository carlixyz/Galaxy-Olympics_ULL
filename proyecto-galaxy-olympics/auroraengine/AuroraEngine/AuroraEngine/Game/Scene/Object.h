#ifndef OBJECT_H
#define OBJECT_H

#include "../../Libraries/MathLib/MathLib.h"
#include "Model.h"
#include "BoundingBox.h"

#define kfSPEED_SLOW 5.0f
#define kfSPEED_NORMAL 20.0f
#define kfSPEED_TURBO 55.0f

static const float kfMoveSpeed = 25.0f;
static const float kfAngSpeed = 0.5f;

enum eObjectType
{
eObject = 0,
eRing,
eObstacle,
eItem,
eEnemy,
ePlayer,
eSkybox,
eBackground
};


class cObject
{
	public:
		cObject() { meType = eObject ;}

		eObjectType meType;	
	
		void Init();

		void Init( const std::string &lacNameID,const std::string &lacFile );
		
		void Init( const std::string &lacNameID,const std::string &lacFile, bool lbBoundingBox );

		void Deinit();

		virtual void Update( float lfTimestep );
		
		virtual void Render();

		inline void SetPosition( cVec3 &lvPosition ){ mWorldMatrix.SetPosition( lvPosition) ;}

		inline void Translate( cVec3 &lvPosition ){ mWorldMatrix.LoadTranslation( lvPosition) ;}

		inline void Rotate( cVec3 &lvRotation, float &lfRad ){ mWorldMatrix.LoadRotation( lvRotation, lfRad) ;}

		inline cMatrix &GetMatrix(){ return this->mWorldMatrix ;}
				
		inline cBoundingBox &GetCollisionBox(){return *((cBoundingBox *)this->mModel.mCollisionObject);}
		inline std::string GetName(){ return macName;}
	protected:
		std::string macName;
		cMatrix mWorldMatrix;
		cModel mModel;
};
#endif