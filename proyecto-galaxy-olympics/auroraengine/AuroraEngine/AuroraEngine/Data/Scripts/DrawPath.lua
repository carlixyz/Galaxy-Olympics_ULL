require "./Data/Scripts/constants"

function DrawPath ()
		--Recorrido de patrullero 1
		Drawline(lPositionTargets[1][1].x,lPositionTargets[1][1].y,lPositionTargets[1][1].z,
				 lPositionTargets[1][2].x,lPositionTargets[1][2].y,lPositionTargets[1][2].z,
				 1,0,0)	 
		Drawline(lPositionTargets[1][2].x,lPositionTargets[1][2].y,lPositionTargets[1][2].z,
				 lPositionTargets[1][3].x,lPositionTargets[1][3].y,lPositionTargets[1][3].z,
				 1,0,0)
		Drawline(lPositionTargets[1][3].x,lPositionTargets[1][3].y,lPositionTargets[1][3].z,
				 lPositionTargets[1][4].x,lPositionTargets[1][4].y,lPositionTargets[1][4].z,
				 1,0,0)
		Drawline(lPositionTargets[1][4].x,lPositionTargets[1][4].y,lPositionTargets[1][4].z,
				 lPositionTargets[1][1].x,lPositionTargets[1][1].y,lPositionTargets[1][1].z,
				 1,0,0)
		
		--Recorrido de patrullero 2
		
		--Drawline(lPositionTargets[2][1].x,lPositionTargets[2][1].y,lPositionTargets[2][1].z,
			--	 lPositionTargets[2][2].x,lPositionTargets[2][2].y,lPositionTargets[2][2].z,
				-- 0,1,0)	 
		--Drawline(lPositionTargets[2][2].x,lPositionTargets[2][2].y,lPositionTargets[2][2].z,
			--	 lPositionTargets[2][3].x,lPositionTargets[2][3].y,lPositionTargets[2][3].z,
				-- 0,1,0)
		--Drawline(lPositionTargets[2][3].x,lPositionTargets[2][3].y,lPositionTargets[2][3].z,
			--	 lPositionTargets[2][4].x,lPositionTargets[2][4].y,lPositionTargets[2][4].z,
				-- 0,1,0)
		--Drawline(lPositionTargets[2][4].x,lPositionTargets[2][4].y,lPositionTargets[2][4].z,
			--	 lPositionTargets[2][1].x,lPositionTargets[2][1].y,lPositionTargets[2][1].z,
				-- 0,1,0)
				 
		--Recorrido de patrullero 3
		
		--Drawline(lPositionTargets[3][1].x,lPositionTargets[3][1].y,lPositionTargets[3][1].z,
			--	 lPositionTargets[3][2].x,lPositionTargets[3][2].y,lPositionTargets[3][2].z,
				-- 0,0,1)	 
		--Drawline(lPositionTargets[3][2].x,lPositionTargets[3][2].y,lPositionTargets[3][2].z,
			--	 lPositionTargets[3][3].x,lPositionTargets[3][3].y,lPositionTargets[3][3].z,
				-- 0,0,1)
		--Drawline(lPositionTargets[3][3].x,lPositionTargets[3][3].y,lPositionTargets[3][3].z,
			--	 lPositionTargets[3][4].x,lPositionTargets[3][4].y,lPositionTargets[3][4].z,
				-- 0,0,1)
		--Drawline(lPositionTargets[3][4].x,lPositionTargets[3][4].y,lPositionTargets[3][4].z,
			--	 lPositionTargets[3][1].x,lPositionTargets[3][1].y,lPositionTargets[3][1].z,
				-- 0,0,1)
				 

				 
		
			
	end
	
	--CODIGO LUA--
	print ("estoy aqui")
	value = DrawPath()