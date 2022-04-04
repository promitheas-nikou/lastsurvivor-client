
function filltiles(id,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
			settile(id,x,y)
		end
	end
end

function fillgtiles(id,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
			setgtile(id,x,y)
		end
	end
end

