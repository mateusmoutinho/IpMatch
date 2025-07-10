


local function Preparation(cc, main, flags, path, name_out)

  if not path then
    path = '.'
  end

  local path_out = path .. '/'

  if path and path ~= '.' then
    darwin.dtw.write_file(path_out .. "cache", "")
    darwin.dtw.remove_any(path_out .. "cache")
  end

  local path_exe = path_out .. name_out

  --darwin.dtw.write_file(path_exe, "")
  darwin.dtw.remove_any(path_exe)

  local command = cc .. ' ' .. flags .. " -o " .. path_exe .. " src/" .. main
  print("\n\tCommand: " .. command .. "\n")
  local result = os.execute(cc .. ' ' .. flags .. " -o " .. path_exe .. " src/" .. main)

  if not result then
    os.exit(1)
  end

  Text.green("\n\tCompiled the" .. name_out .. " in " .. path .. "\n")
end

function Comp_testing()
  Preparation("gcc", "testing.c ", "", "test/c", "test.out")
  os.execute("test/c/test.out > test/c/teste.txt")
end

function Comp()
  Preparation("gcc", "main.c", "", nil, Name_lib)
end



