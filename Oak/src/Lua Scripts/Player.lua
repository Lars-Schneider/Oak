function Update()
	--If its off screen, then move it to (0,0)
	if Get_X("Player") + Get_W("Player") > Screen_Width() + 1 or Get_Y("Player") + Get_H("Player") > Screen_Height() + 1 then
		Set_X("Player", 0)
		Set_Y("Player", 0)
	end
	--Bounce
	if Get_X("Player") + Get_W("Player") > Screen_Width() then
		Set_VX("Player", -Get_VX("Player"))
	end
	if Get_Y("Player") + Get_H("Player") > Screen_Height() then
		Set_VY("Player", -Get_VY("Player"))
	end
	if Get_X("Player") < 0 then
	Set_VX("Player", -Get_VX("Player"))
	end
	if Get_Y("Player") < 0 then
	Set_VY("Player", -Get_VY("Player"))
	end
	--Move
	Move("Player", Get_VX("Player"), Get_VY("Player"));
	Print("a");
end