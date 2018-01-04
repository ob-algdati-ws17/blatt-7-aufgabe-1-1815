file(REMOVE_RECURSE
  "testList.pdb"
  "testList.exe"
  "testList.exe.manifest"
  "libtestList.dll.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/testList.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
