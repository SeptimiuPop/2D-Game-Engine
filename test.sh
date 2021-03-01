#!/bin/bash

./clear.sh

read msg
pass="ToTheVoid01"

git add -A
git commit -m "$msg"
printf '$pass\n' | git pull