



---@param Link table
---@param path string
---@return nil
local function Install_dependencie(Link, path)

  darwin.dtw.remove_any(path .. Link.out)

  local sucesses = os.execute("curl -L " .. Link.link .. " -o " .. path .. Link.out .. " > /dev/null 2>&1") -- Curl -L {link} -o {path_for_dependencie/}{out_renamed}

  if sucesses then
    Text.green("\n\tSuccess in downloading:\n\t" .. Link.out .. "\n")
    return
  end

  Text.red("\n\tError making request on:\n\t" .. Link.out .. "\n")

end

local links = {
  {
    link = "https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.c",
    out = "dep.cJSON.c",
    name = "cJSON"
  },
  {
    link = "https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.h",
    out = "cJSON.h",
    name = "cJSON"
  }
}

---@return nil
function Install_dependencies()


  local Creat_past = function(path)
    local cache = path .. "cache"
    darwin.dtw.write_file(cache, "")
    darwin.dtw.remove_any(cache)
  end

  local path = "src/dependencies/"
  darwin.dtw.remove_any(path)
  Creat_past(path)

  for I=1, #links do
    local new_path = path .. links[I].name .. "/"
    Creat_past(new_path)
    Install_dependencie(links[I], new_path)
  end

  print("\n")

end




