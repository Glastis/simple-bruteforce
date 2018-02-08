--
-- Created by IntelliJ IDEA.
-- User: Luciano
-- Date: 21/11/2017
-- Time: 06:47
-- To change this template use File | Settings | File Templates.
--

local file = {}

local function is_existing(filepath)
    local f

    f = io.open(filepath,"r")
    if f then
        io.close(f)
        return true
    end
    return false
end
file.is_existing = is_existing

return file


