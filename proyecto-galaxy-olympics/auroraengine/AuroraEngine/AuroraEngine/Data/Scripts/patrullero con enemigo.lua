--REQUIRES--
--DECLARACION DE VARIABLES GLOBALES--
	posX = 5
	posY = 0
	posZ = 5
	speed = 1
	angSpeed = 10
--DEFINICION DE FUNCIONES--
--CODIGO LUA--
	
	posX = 0
	posY = 0
	posZ = -5
	value3 = CreatePatrol( posX, posY, posZ, speed, angSpeed, 1, 6, 3 )
	
	posX = 0
	posY = 0
	posZ = 0
	speed = 2
	angSpeed = 2
	value4 = CreatePlayer( posX, posY, posZ, speed, angSpeed, 6 )