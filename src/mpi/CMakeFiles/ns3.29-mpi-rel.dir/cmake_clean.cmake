file(REMOVE_RECURSE
  "../../build/lib/libns3.29-mpi-rel.pdb"
  "../../build/lib/libns3.29-mpi-rel.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/ns3.29-mpi-rel.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
