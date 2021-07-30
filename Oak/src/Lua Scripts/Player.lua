function Update()
	Move("Player", Get_VX("Player"), Get_VY("Player"));
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
end