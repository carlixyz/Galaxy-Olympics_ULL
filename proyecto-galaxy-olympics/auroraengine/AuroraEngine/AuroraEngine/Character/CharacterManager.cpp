#include "CharacterManager.h"

bool cCharacterManager::Init()
{
	return true;
}

void cCharacterManager::Update(float lfTimestep)
{
	for (cCharacterListIt lIterator = mCharacters.begin(); lIterator != mCharacters.end(); lIterator++)
	{
		cCharacter *lCharacter = (*lIterator);
		lCharacter->Update(lfTimestep);
	}
}

void cCharacterManager::Render()
{
	for (cCharacterListIt lIterator = mCharacters.begin(); lIterator != mCharacters.end(); lIterator++)
	{
		cCharacter *lCharacter = (*lIterator);
		lCharacter->Render();
	}
}

bool cCharacterManager::Deinit()
{
	for (cCharacterListIt lIterator = mCharacters.begin(); lIterator != mCharacters.end(); lIterator++)
	{
		cCharacter *lCharacter = (*lIterator);
		lCharacter->Deinit();
	}
	return true;
}

cCharacter* cCharacterManager::CreateCharacter()
{
	cCharacter *lCharacter = new cCharacter();
	mCharacters.push_back(lCharacter);
	return lCharacter;
}

void cCharacterManager::DestroyCharacter(cCharacter *lpCharacter)
{
	lpCharacter->Deinit();
	mCharacters.remove(lpCharacter);
	
}
cCharacter* cCharacterManager::getCharacter(int characterId)
{
	for (cCharacterListIt lIterator = mCharacters.begin(); lIterator != mCharacters.end(); lIterator++)
	{
		cCharacter *lCharacter = (*lIterator);
		if (lCharacter->GetId()==characterId) 
			return lCharacter;
	}
	return NULL;
	
}



