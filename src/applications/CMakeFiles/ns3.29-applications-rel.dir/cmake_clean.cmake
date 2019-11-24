file(REMOVE_RECURSE
  "../../build/lib/libns3.29-applications-rel.pdb"
  "../../build/lib/libns3.29-applications-rel.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/ns3.29-applications-rel.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
