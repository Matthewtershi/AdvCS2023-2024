# AdvCS2023-2024
LASA Adv CS Repo

git init
gh auth login
git remote add origin https://github.com/Matthewtershi/AdvCS2023-2024.git
git config --global user.name "Matthewtershi"
git config --global user.email "matthewtershi@gmail.com"
mkdir BTreeSplit
mv * BTreeSplit/
git add BTreeSplit/
git commit -m "BTreeSplit"
git config pull.rebase false
git pull origin --allow-unrelated-histories
git branch --set-upstream-to=origin/main
git pull origin --allow-unrelated-histories
git add BTreeSplit/
git commit -m "merge"
git push