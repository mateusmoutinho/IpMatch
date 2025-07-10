
RESET = "\27[0m"

function Private_print_green(text)
  local green = "\27[32m"

  print(green .. text .. RESET)

end

function Private_print_red(text)
  local red = "\27[31m"

  print(red .. text .. RESET)
end

function Private_print_blue(text)
  local blue = "\27[34m"

  print(blue .. text .. RESET)
end

