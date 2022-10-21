

--- Replace ground tiles in an area: `fillgtilesreplace`
-- API function to replace all ground tiles in an area that have a specific id.
-- @tparam string id The string id of the new ground tile
-- @tparam string rid The string id of the ground tile(s) to be replaced
-- @tparam number sx The starting x coordinate for the fill. Must be smaller than ex
-- @tparam number sy The starting y coordinate for the fill. Must be smaller than ey
-- @tparam number ex The ending x coordinate for the fill. Must be greater than sx
-- @tparam number ey The ending y coordinate for the fill. Must be greater than sy
-- @note 
--

function fillgtiles(id,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
			if not setgtile(id,x,y) then return false end
		end
	end
	return true
end
function filltiles(id,sx,sy,ex,ey)
	for y=sy,ey do
		for x=sx,ex do
			if not settile(id,x,y) then return false end
		end
	end
	return true
end

--- Replace ground tiles in an area: `fillgtilesreplace`
-- API function to replace all ground tiles in an area that have a specific id.
-- @tparam string id The string id of the new ground tile
-- @tparam string rid The string id of the ground tile(s) to be replaced
-- @tparam number sx The starting x coordinate for the fill. Must be smaller than ex
-- @tparam number sy The starting y coordinate for the fill. Must be smaller than ey
-- @tparam number ex The ending x coordinate for the fill. Must be greater than sx
-- @tparam number ey The ending y coordinate for the fill. Must be greater than sy
-- @note 
--
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

--- Replace tiles in an area: `filltilesreplace`
-- API function to replace all tiles in an area that have a specific id.
-- @tparam string id The string id of the new tile
-- @tparam string rid The string id of the tile(s) to be replaced
-- @tparam number sx The starting x coordinate for the fill. Must be smaller than ex
-- @tparam number sy The starting y coordinate for the fill. Must be smaller than ey
-- @tparam number ex The ending x coordinate for the fill. Must be greater than sx
-- @tparam number ey The ending y coordinate for the fill. Must be greater than sy
--
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
print = function(v)consoleprint(tostring(v))end
consoleprint = nil
