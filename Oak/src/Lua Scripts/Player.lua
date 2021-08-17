function HitsDown(entity)

end

function Move(up, down, left, right)
	
end

function Update(delta)
		speed = 20
		if Key_Pressed(LEFT) then Move("Player", -speed * delta, 0) end
		if Key_Pressed(RIGHT) then Move("Player", speed * delta, 0) end
		if Get_Y("Player") - ((delta * speed)*2) - Get_H("Player") > Get_Y("Ground") or  (Get_X("Player") > Get_X("Ground") + Get_W("Ground") or Get_X("Player") + Get_W("Player") < Get_X("Ground")) then
			Fall(- delta * speed)
		end
		Set_Camera_Pos(Get_X("Player"), Get_Y("Player"))
		Set_Camera_Zoom(10)
	end