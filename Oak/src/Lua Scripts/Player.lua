function Update(delta)
		speed = 5
		if Get_Y("Player") - (delta * speed) - Get_H("Player") > Get_Y("Ground") then Move("Player", 0, - (delta * speed)) else Set_Y("Player", Get_Y("Ground") + Get_H("Player")) end
		if Key_Pressed(LEFT) then Move("Player", -speed * delta, 0) end
		if Key_Pressed(RIGHT) then Move("Player", speed * delta, 0) end
	end