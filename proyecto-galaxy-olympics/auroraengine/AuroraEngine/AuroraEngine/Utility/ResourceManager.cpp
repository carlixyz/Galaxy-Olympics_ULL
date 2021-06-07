#include "ResourceManager.h"
#include <assert.h>
void cResourceManager::Init( unsigned luiMaxSize )
{
	muiMaxSize = luiMaxSize;
	// Initialize the structures
	maResources.resize( muiMaxSize );
	mFreeResourceSlot.clear();
	for ( unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex )
	{
		// Initialize the resource slot
		maResources[luiIndex].muiKey = kuiInvalidKey;
		maResources[luiIndex].mpResource = NULL;
		// Add the free index to the list
		mFreeResourceSlot.push_back( luiIndex );
	}
	// Prepare the first key
	muiNextKey = kuiInvalidKey + 1;
}


void cResourceManager::Deinit()
{
	for ( unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex )
	{
		// Is a valid resource?
		if ( maResources[luiIndex].muiKey != kuiInvalidKey )
		{
			// Check that all is right
			assert( maResources[luiIndex].mpResource );
			assert( maResources[luiIndex].mpResource->IsLoaded() );
			// Deinit the resource
			maResources[luiIndex].mpResource->Deinit();
			delete maResources[luiIndex].mpResource;
			// Clear the resource slot
			maResources[luiIndex].muiKey = kuiInvalidKey;
			maResources[luiIndex].mpResource = NULL;
		}
	}
}


cResource * cResourceManager::GetResource(cResourceHandle *lpHandle)
{
	assert(lpHandle);
	assert(lpHandle->IsValidHandle());

	unsigned luiIndex = lpHandle->GetID();
	assert(luiIndex < muiMaxSize);
	if (maResources[luiIndex].muiKey == lpHandle->GetKey() && maResources[luiIndex].mpResource->IsLoaded())
		return maResources[luiIndex].mpResource;
	return NULL;
}

void cResourceManager::UnloadResource( cResourceHandle * lpHandle )
{
	assert( lpHandle );
	assert( lpHandle->IsValidHandle() );
	unsigned luiIndex = lpHandle->GetID();
	assert( luiIndex < muiMaxSize );
	if ( maResources[luiIndex].muiKey == lpHandle->GetKey()
		&& maResources[luiIndex].mpResource->IsLoaded() )
	{
		// Deinit the resource
		maResources[luiIndex].mpResource->Deinit();
		delete maResources[luiIndex].mpResource;
		// Clear the resource slot
		maResources[luiIndex].muiKey = kuiInvalidKey;
		maResources[luiIndex].mpResource = NULL;
		// Add the slot to the free list
		mFreeResourceSlot.push_front(luiIndex);
	}
}

cResourceHandle cResourceManager::SearchResource( std::string lacNameID )
{
	cResourceHandle lHandle;
	for ( unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex )
	{
		// Is a valid resource?
		if ( maResources[luiIndex].muiKey != kuiInvalidKey )
		{
			// Check that all is right
			assert( maResources[luiIndex].mpResource );
			assert( maResources[luiIndex].mpResource->IsLoaded() );
			// Is the right resource?
			if ( maResources[luiIndex].mpResource->IsThisResource( lacNameID ) )
			{
				lHandle.Init(this, luiIndex,
					maResources[luiIndex].muiKey);
				break;
			}
		}
	}
	return lHandle;
}



cResourceHandle cResourceManager::LoadResource( std::string lacNameID, const std::string &lacFile )
{
	cResourceHandle lHandle = SearchResource( lacNameID );
	if ( !lHandle.IsValidHandle() )
	{
		// Load the Resource
		cResource * lpResource = LoadResourceInternal( lacNameID,	lacFile );
		if (lpResource)
		{
			// Set the ID
			lpResource->SetNameID( lacNameID );
			// Save it into the pool
			lHandle = AddResourceToPool( lpResource );
		}
		else
		{
			lHandle.Invalidate();
		}
	}
	return lHandle;
}
cResourceHandle cResourceManager::LoadResource( std::string lacNameID, void * lpMemoryData, int luiTypeID )
{
	cResourceHandle lHandle = SearchResource( lacNameID );
	if ( !lHandle.IsValidHandle() )
	{
		// Load the Resource
		cResource * lpResource = LoadResourceInternal( lacNameID, lpMemoryData, luiTypeID );
		if (lpResource)
		{
			// Set the ID
			lpResource->SetNameID( lacNameID );
			// Save it into the pool
			lHandle = AddResourceToPool( lpResource );
		}
		else
		{
			lHandle.Invalidate();
		}
	}
	return lHandle;
}

cResourceHandle cResourceManager::AddResourceToPool( cResource * lpResource )
{
	assert( mFreeResourceSlot.size() > 0 );
	unsigned luiNext = *mFreeResourceSlot.begin();
	mFreeResourceSlot.pop_front();
	assert( maResources[luiNext].muiKey == kuiInvalidKey );
	assert(muiNextKey != kuiInvalidKey );
	maResources[luiNext].muiKey = muiNextKey++;
	maResources[luiNext].mpResource = lpResource;
	cResourceHandle lHandle;
	lHandle.Init(this, luiNext, maResources[luiNext].muiKey);
	return lHandle;
}

