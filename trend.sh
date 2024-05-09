#!/bin/bash
cd witchpot
mvn test -Dtest=TrendTest -Dsymbols.folder=/media/rsolano/ubuntu-internal/workspaces/tensorflow/data/symbols/train -Dmerged.folder=/media/rsolano/ubuntu-internal/workspaces/tensorflow/data/symbols/train/merged
cd ..
