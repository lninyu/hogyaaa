cd $(dirname $0)/../
git add ./
git commit -m "$(date)"|tee|head -n 2|tail -n 1 >> README.md
git push origin ugaaaaaa
