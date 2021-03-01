#!/bin/bash

./clear.sh

read msg
pass="ToTheVoid01"

git add -A
git commit -m "$msg"
git push "$pass"