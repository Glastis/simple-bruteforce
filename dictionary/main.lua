--
-- User: glastis
-- Date: 07/02/18
-- Time: 23:16
--
local md5 = require('md5')
local file = require('file')

local arg = {...}

function compare_dico(dico, hash, verbose)
    local f
    local line

    f = io.open(dico, 'rb')
    for line in f:lines() do
        if verbose then
            print(line .. ': ' .. md5.sumhexa(line))
        end
        if md5.sumhexa(line) == hash then
            f:close()
            print('Match found with passphrase: ' .. line)
            return true
        end
    end
    f:close()
    print('No match found')
    return false
end

function core(dico, hash, verbose)
    if not file.is_existing(dico) then
        print(dico .. 'not found.')
        return false
    end
    if verbose ~= '-v' and verbose ~= '--verbose' then
        verbose = nil
    end
    return compare_dico(dico, string.lower(hash), verbose)
end

if not arg[1] or not arg[2] then
    print('lua main.lua dictionary.txt hash_to_reverse [-v]')
    return false
end


return core(arg[1], arg[2], arg[3])