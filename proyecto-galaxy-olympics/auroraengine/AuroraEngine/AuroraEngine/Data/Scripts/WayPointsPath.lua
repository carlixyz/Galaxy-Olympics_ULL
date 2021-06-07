--REQUIRES--

require "./Data/Scripts/constants"
--DECLARACION DE VARIABLES GLOBALES--

--DEFINICION DE FUNCIONES--

	function NextEndPoint( liCharacterId )
		lNextState = lCharacterCurrentState[ liCharacterId ] + 1

		if ( lNextState > lPointCount ) then
			lNextState = 1
		end
		--Cambiar al siguiente estado
		lCharacterCurrentState[ liCharacterId ] = lNextState

		--Actualizar el nuevo punto a alcanzar
		SetPatrolTarget( liCharacterId, lPositionTargets[liCharacterId][lNextState].x, lPositionTargets[liCharacterId][lNextState].y, lPositionTargets[liCharacterId][lNextState].z)

	end