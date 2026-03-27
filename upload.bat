@echo off
echo Enter commit-message
set /p msg=

git add .
git commit -m "%msg%"
git push

echo Finished
pause
