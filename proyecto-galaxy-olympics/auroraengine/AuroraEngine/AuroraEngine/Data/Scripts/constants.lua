
lPositionTargets = {}
lPositionTargets[1] = {}
lPositionTargets[2] = {}
lPositionTargets[3] = {}

--Posiciones del patrullero 1
lPositionTargets[1][1] = {x=3.0, y=0.0, z=3.0}
lPositionTargets[1][2] = {x=4.0, y=0.0, z=-5.0}
lPositionTargets[1][3] = {x=-3.0, y=0.0, z=-2.0}
lPositionTargets[1][4] = {x=-1.0, y=0.0, z=5.0}

--Posiciones del patrullero 2
lPositionTargets[2][1] = {x=2.0, y=0.0, z=2.0}
lPositionTargets[2][2] = {x=3.0, y=0.0, z=-4.0}
lPositionTargets[2][3] = {x=-2.0, y=0.0, z=-1.0}
lPositionTargets[2][4] = {x=-0.0, y=0.0, z=4.0}

--Posiciones del patrullero 3
lPositionTargets[3][1] = {x=1.0, y=0.0, z=0.0}
lPositionTargets[3][2] = {x=3.0, y=0.0, z=-2.0}
lPositionTargets[3][3] = {x=-4.0, y=0.0, z=-0.0}
lPositionTargets[3][4] = {x=-1.0, y=0.0, z=5.0}


--Estado actual es cero (cambiará a 1 cuando se llame a NextPoint)
lCharacterCurrentState = {} 
--Estado del personaje 1
lCharacterCurrentState[1] = 0 
--Estado del personaje 2
lCharacterCurrentState[2] = 0
--Estado del personaje 3
lCharacterCurrentState[3] = 0


--Numero de estados
lPointCount = 4

