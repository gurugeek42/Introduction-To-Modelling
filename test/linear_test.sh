#!/usr/bin/env bash

set -e

save_folder="test/benchmark"

mkdir -p $save_folder
rm -f $save_folder/*

cat << EOF > $save_folder/constants.js
{
  "Pr":0.5,
  "Ra":1,
  "aspectRatio":3,
  "icFile":"$save_folder/ICn1nZ101nN51",
  "initialDt":1e-5,
  "nN":51,
  "nZ":101,
  "saveFolder":"$save_folder/",
  "timeBetweenSaves":0.01,
  "isNonlinear":false,
  "totalTime":10
}
EOF

constants_file=$save_folder/constants.js
python tools/make_initial_conditions.py --output $save_folder/ICn1nZ101nN51 --n_modes 51 --n_gridpoints 101 --linear_stability

echo "==================== Building program"
make clean
make release

echo "==================== Starting program"
time build/exe --constants $constants_file | tee $save_folder/log
