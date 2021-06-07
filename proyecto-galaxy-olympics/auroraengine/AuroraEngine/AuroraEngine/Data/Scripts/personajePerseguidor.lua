--REQUIRES--
--DECLARACION DE VARIABLES GLOBALES--
	posX = 5
	posY = 0
	posZ = 5
	speed = 1
	angSpeed = 10
--DEFINICION DE FUNCIONES--
--CODIGO LUA--
	
	value = CreatePatrol( posX, posY, posZ, speed, angSpeed, 1 )
	
	posX = 3
	posY = 0
	posZ = 3
	value2 = CreatePatrol( posX, posY, posZ, speed, angSpeed, 2 )
	
	posX = 0
	posY = 0
	posZ = -5
	value3 = CreatePatrol( posX, posY, posZ, speed, angSpeed, 3 )
	
	posX = 0
	posY = 0
	posZ = 0
	speed = 3
	value4 = CreatePlayer( posX, posY, posZ, speed, angSpeed, 4 )
	