


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
  local result = os.execute(command)

  if not result then
    os.exit(1)
  end

  Text.green("\n\tCompiled the " .. name_out .. " in " .. path_exe .. "\n")
end

function Comp_testing()
  local out_name = "test"
  local path_of_tests = "test/" .. os.date("H%H_M%M_S%S")
  Preparation("gcc", "main.c ", "", path_of_tests, out_name)
  os.execute(path_of_tests .. "/" .. out_name .. " | tee " .. path_of_tests .. "/" .. out_name .. ".txt")
end

function Comp()
  Preparation("gcc", "main.c", "", nil, Name_lib)
end



