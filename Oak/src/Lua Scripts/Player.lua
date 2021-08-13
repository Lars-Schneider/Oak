function Update()
	if Get_Y("Player") - 1 > Get_Y("Ground") and (Get_X("Player") < Get_X("Ground") + Get_W("Ground") or Get_X("Player") + Get_W("Player") > Get_X("Ground"))then Move("Player", 0, -0.1) end
	if Key_Pressed(LEFT) then Move("Player", -0.3, 0) end
	if Key_Pressed(RIGHT) then Move("Player", 0.3, 0) end
end