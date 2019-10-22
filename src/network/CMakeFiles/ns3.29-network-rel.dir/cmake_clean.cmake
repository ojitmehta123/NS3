file(REMOVE_RECURSE
  "../../build/lib/libns3.29-network-rel.pdb"
  "../../build/lib/libns3.29-network-rel.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/ns3.29-network-rel.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
