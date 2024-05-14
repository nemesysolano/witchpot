#!/bin/bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd witchpot
mvn surefire:test -Dtest=TrendTest -Dsymbols.folder=${SCRIPT_DIR}/data/symbols/train -Dmerged.folder=${SCRIPT_DIR}/data/symbols/train/merged
cd ..
