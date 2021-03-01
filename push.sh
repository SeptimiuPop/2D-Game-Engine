#!/bin/bash

./clear.sh

echo
echo "Add commit message: "

read msg
pass="ToTheVoid01"

git add -A
git commit -m "$msg"
git push -p "$pass"