#!/usr/bin/env bash

# OPT="-O2"

./make.sh RunPoof
[ $? -ne 0 ] && exit 1
# exit 1

# exit 0

# ./make.sh -O2 BuildSingleExample examples/blank_project
# ./make.sh -O2 BuildSingleExample examples/the_wanderer
# ./make.sh     BuildSingleExample examples/the_wanderer

# ./make.sh BuildTests



# ./make.sh MakeDebugLibRelease

# ./make.sh BuildTests
# ./make.sh BuildExecutables
# ./make.sh BuildDebugSystem
# ./make.sh BuildBundledExamples

# ./make.sh BuildAll -O0
# ./make.sh BuildAll -O2

# OPT="-O2"
# ./make.sh $OPT \
#     BuildDebugSystem


# ./make.sh BuildTests

# OPT="-O2"
./make.sh $OPT \
  BuildSingleExample examples/turn_based \
  # BuildExecutables \
  # BuildDebugSystem \
  # BuildSingleExample examples/tools/voxel_synthesis_rule_baker \
  # BuildSingleExample examples/the_wanderer \
  # BuildSingleExample examples/graveyard \
  # BuildSingleExample examples/terrain_gen \
  # BuildSingleExample examples/transparency \
  # BuildSingleExample examples/blank_project \
  # BuildSingleExample examples/transparency \
  # BuildTests \

# ./make.sh $OPT BuildAll
