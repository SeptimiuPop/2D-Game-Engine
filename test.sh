#!/bin/bash

./clear.sh

read msg

git add -A
git commit -m "$msg"
