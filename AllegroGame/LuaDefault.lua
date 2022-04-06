
function filltiles(id,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
			if not settile(id,x,y) then return false end
		end
	end
	return true
end

function fillgtiles(id,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
			if not setgtile(id,x,y) then return false end
		end
	end
	return true
end

function fillgtilesreplace(id,rid,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
            if getgtile(x,y)==rid then
                if not setgtile(id,x,y) then return false end
            end
		end
	end
	return true
end

function filltilesreplace(id,rid,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
            if gettile(x,y)==rid then
                if not settile(id,x,y) then return false end
            end
		end
	end
	return true
end

local __print = print
print = consoleprint
consoleprint = nil
