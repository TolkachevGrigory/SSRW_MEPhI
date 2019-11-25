#!/bin/bash
# $1 - pass to data root file
# $2 - pass to mc root file
# Example: . draw.sh ../test1/SM_WLepton_copy.root ../test1/SM_WLepton.root
root -l -b -q StartDraw.C\(\"$1\"\,\"$2\"\)