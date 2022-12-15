#!/bin/sh
set -e
image="scuba/qemu"
cd $(dirname $0)
docker build -t $image .
echo "Built $image"