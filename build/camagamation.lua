


function Camalga()

  local max_content = darwin.camalgamator.ONE_MB * 10
  local max_recursion = 100
  local path_imports = "src/imports/imports."
  local result_header = darwin.camalgamator.generate_amalgamation(path_imports .. "dec.h", max_content, max_recursion)
  local result_cod = darwin.camalgamator.generate_amalgamation_with_callback(path_imports .. "def.h",
    function(import, path)
      if path:sub(-2) == ".h" then
        return "dont-include"
      end

      return "include-once"
    end,
    max_content,
    max_recursion
  )
  result_cod = "#include \"ipMatch.h\"\n\n" .. (result_cod or "")

  darwin.dtw.write_file("releases/ipMatch.h", result_header or "")
  darwin.dtw.write_file("releases/ipMatch.c", result_cod )

  print("\tFinalized Amalgamation.")

end





