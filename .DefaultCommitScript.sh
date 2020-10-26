clear
echo "||||||||||||||||||||||||||||||||||||||||||	IN"
echo "||||||||||||||||||||||||||||||||||||||||||	git status"
git status
echo "||||||||||||||||||||||||||||||||||||||||||	git add ."
git add .
echo "||||||||||||||||||||||||||||||||||||||||||	git status"
git status
message="Commit Script : $1"
echo "||||||||||||||||||||||||||||||||||||||||||	$message"
git commit -a -m "$message"
echo "||||||||||||||||||||||||||||||||||||||||||	git status"
git status
echo "||||||||||||||||||||||||||||||||||||||||||	git push"
git push
echo "||||||||||||||||||||||||||||||||||||||||||	git status"
git status
echo "||||||||||||||||||||||||||||||||||||||||||	OUT"

