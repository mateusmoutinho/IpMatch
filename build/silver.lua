

function Initialize_silver()
  --darwin.dtw.remove_any("src/imports")

  darwin.silverchain.generate({
      src = "src",
      tags = { "dep", "includes", "macros", "namespace", "types", "globals", "dec", "def" },
      project_short_cut = Name_lib
  })

  print("\tFinalized SilverChain.")

end



