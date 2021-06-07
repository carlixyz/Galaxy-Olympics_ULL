#include "Mesh.h"
#include <aiMesh.h>

#include "../GLHeaders.h"
#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>

bool cMesh::Init( const std::string &lacNameID, void * lpMemoryData )
{
	macFile = "";
	aiMesh * lpAiMesh = (aiMesh*) lpMemoryData;


	unsigned luiTextureCoordinateCount = lpAiMesh->GetNumUVChannels();
	assert(luiTextureCoordinateCount <= 4);
	maVboTexture.resize(luiTextureCoordinateCount);

	//Creamos el buffer de vertices
	glGenBuffers(1, &mVboVertices);
	assert( glGetError() == GL_NO_ERROR);


	//Creamos todos los buffers de coordenadas
	for(unsigned luiIndex = 0; luiIndex <luiTextureCoordinateCount; ++luiIndex) 
	{
		glGenBuffers(1, &maVboTexture[luiIndex]);
		assert(glGetError() == GL_NO_ERROR);
	}

	//Creamos el buffer de normales
	glGenBuffers (1, &mVboNormals);
	assert( glGetError() == GL_NO_ERROR);

	glGenBuffers (1, &mVboIndex);
	assert( glGetError() == GL_NO_ERROR);
	
	//Indicamos a openGL  que las siguientes llamadas se refieren al buffer de vertices
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	assert( glGetError() == GL_NO_ERROR);

	//Inicializamos el buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * lpAiMesh->mNumVertices,
		lpAiMesh->mVertices, GL_STATIC_DRAW);
	assert( glGetError() == GL_NO_ERROR);
	
	//Comprobamos que la malla tiene normales
	assert (lpAiMesh->HasNormals());

	//Indicamos a openGL  que las siguientes llamadas se refieren al buffer de normales
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	assert( glGetError() == GL_NO_ERROR);

	//Inicializamos el buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * lpAiMesh->mNumVertices,
		lpAiMesh->mNormals, GL_STATIC_DRAW);
	assert( glGetError() == GL_NO_ERROR);


	unsigned luiTexCoordNum = lpAiMesh->mNumVertices;
	unsigned luiTexCoordFloats = 2 * luiTexCoordNum;
	float* lpTexCoordinates = new float[ luiTexCoordFloats ];

	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel < luiTextureCoordinateCount; ++luiTexCoordChannel)
	{
		unsigned luiInc = 0;
		for (unsigned luiTexIndex = 0; luiTexIndex < luiTexCoordNum; ++luiTexIndex)
		{
			lpTexCoordinates[luiInc++] = lpAiMesh->mTextureCoords[luiTexCoordChannel][luiTexIndex].x;
			lpTexCoordinates[luiInc++] = (1.0f - lpAiMesh->mTextureCoords[luiTexCoordChannel][luiTexIndex].y);
		}

		glBindBuffer(GL_ARRAY_BUFFER, maVboTexture[luiTexCoordChannel]);
		assert(glGetError() == GL_NO_ERROR);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * luiTexCoordFloats, lpTexCoordinates, GL_STATIC_DRAW);
		assert(glGetError() == GL_NO_ERROR);
	}

	delete [] lpTexCoordinates;

	muiIndexCount = lpAiMesh->mNumFaces * 3;
	unsigned* lpIndex = new unsigned[ muiIndexCount ];
	
	unsigned luiIndex = 0;

	for (unsigned luiFaceIndex = 0; luiFaceIndex < lpAiMesh->mNumFaces; ++luiFaceIndex)
	{
		//Nos aseguramos que cada cara tenga 3 vertices
		assert(lpAiMesh->mFaces[luiFaceIndex].mNumIndices == 3);
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[0];
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[1];
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[2];

	
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIndex);
	assert( glGetError() == GL_NO_ERROR);
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, muiIndexCount *  sizeof(unsigned),
		lpIndex, GL_STATIC_DRAW);
	assert( glGetError() == GL_NO_ERROR);

	delete [] lpIndex;
	mbLoaded = true;
	return true;
}

void cMesh::Deinit()
{
	glDeleteBuffers(1, &mVboVertices);
	
	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel < maVboTexture.size(); ++luiTexCoordChannel)
	{
		glDeleteBuffers(1, &maVboTexture[luiTexCoordChannel]);
	}

	glDeleteBuffers(1, &mVboNormals);
	glDeleteBuffers(1, &mVboIndex);
}

void cMesh::RenderMesh()
{
	glColor3f (1.0f, 1.0f, 1.0f);
	
	// Position
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	assert(glGetError() == GL_NO_ERROR);
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 3, 0);
	assert(glGetError() == GL_NO_ERROR);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	glNormalPointer(GL_FLOAT, sizeof(float) * 3, 0);
	assert(glGetError() == GL_NO_ERROR);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	static GLenum meTextureChannelEnum[] = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3 };
	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel < maVboTexture.size(); ++luiTexCoordChannel)
	{
		// Texture coordinates
		glClientActiveTexture(meTextureChannelEnum[luiTexCoordChannel]);
		glBindBuffer(GL_ARRAY_BUFFER, maVboTexture[luiTexCoordChannel]);
		assert(glGetError() == GL_NO_ERROR);
		glTexCoordPointer(2, GL_FLOAT, sizeof(float)*2, 0);
		assert(glGetError() == GL_NO_ERROR);
	}

	// Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIndex);
	assert(glGetError() == GL_NO_ERROR);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawRangeElements(GL_TRIANGLES, 0, muiIndexCount, muiIndexCount, GL_UNSIGNED_INT, NULL);
	assert(glGetError() == GL_NO_ERROR);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	
}
