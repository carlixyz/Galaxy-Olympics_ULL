#ifndef SUBMODEL_H
#define SUBMODEL_H

#include "../../Utility/ResourceHandle.h"
#include "../../Libraries/MathLib/MathLib.h"
#include "../../Graphics/GraphicManager.h"
#include "../../Graphics/Material/Material.h"
#include "../../Graphics/Meshes/Mesh.h"
#include <string>
#include <vector>
using namespace std;

class cSubmodel
{
	public:
		void Init();
		
		void Deinit();
		
		virtual void Update( float lfTimestep );
		
		virtual void Render(cMatrix &lWorld);
		
		inline string GetName() { return macName; }
		
		inline void SetName(const string &lacName){ macName = lacName; }
		
		inline cMatrix GetLocalMatrix(){ return mLocalMatrix; }

		inline void SetLocalMatrix(const cMatrix &lWorld){ mLocalMatrix = lWorld; } 
		
		void AddMesh( cResourceHandle lMeshHandle, cResourceHandle lMaterialHandle );

	protected:
		string macName;
		cMatrix mLocalMatrix;
		std::vector<cResourceHandle> mMeshHandles;
		std::vector<cResourceHandle> mMaterialHandles;
};

#endif